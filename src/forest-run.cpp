#include <boost/program_options.hpp>
#include <boost/progress.hpp>
#include <boost/format.hpp>
#include <boost/timer.hpp>
#include <boost/filesystem.hpp>
#include <lshkit.h>
#include "GetInvar.h"

using namespace std;
using namespace boost::filesystem;
using namespace lshkit;
using namespace cv;
namespace po = boost::program_options;

const int PROPORT = 400;

float R = numeric_limits<float>::max(); //
float W = 10.0; // hash function window size
unsigned c = 30; //# points to scan from each tree
unsigned L = 5; //	number of trees
unsigned H = 10; //	maximal depth of tree
unsigned Q = 200; //	number of queries to use
unsigned K = 50; //	number of nearest neighbors to retrieve
bool do_benchmark = true;
boost::timer timer;

// Load matrix data, image paths
string data_file = "features.data";
FloatMatrix data(data_file);
FloatMatrix::Accessor accessor(data); // FloatMatrix: Matrix<float>
vector<unsigned> ids;
vector<string> paths;

// Extract feature from a image file
string query_file = "51_1.jpg";
float * feature;

// Index
typedef LSB<GaussianLsh> MyLsh;
typedef ForestIndex<MyLsh, unsigned> Index;

/// Metric
metric::l2<float> l2(data.getDim());

/// Search...

/// Evaluation
string benchmark = "features.train";

void loadData() {
	/**
	 * Loading Matrix Data
	 */
//	string data_file = "features.data";
//	cout << "LOADING DATA..." << endl;
//	timer.restart();
//	FloatMatrix data(data_file);
//	cout << boost::format("LOAD TIME: %1%s.") % timer.elapsed() << endl;
	/**
	 * Load image paths
	 */
	ifstream is("img_paths.txt");
	while (is) {
		unsigned id;
		string path;
		is >> id;
		is >> path;
		ids.push_back(id);
		paths.push_back(path);
	}
}

void extractFeature() {
	/**
	 * Extract feature from a image
	 */
	Mat img;
	img = imread(query_file, 0);
	GetInvar gi;
	if (!gi.IsVaild(img))
		return;
	if (img.cols > PROPORT)
		resize(img, img, Size(PROPORT, img.rows * PROPORT / img.cols),
				INTER_AREA);

	float dgin[64] = { 0.0 }; //double gray invariance
	float drin[36] = { 0.0 }; //double rotation invariance
	gi.GrayInvar(img);
	gi.RotationInvar(img, drin);
	gi.GrayHistog(img, dgin);

	feature = new float[data.getDim()];
//	ofstream os("query");
	for (int i = 0; i < 64; ++i) {
		feature[i] = dgin[i];
//		os.write((const char*)&dgin[i], sizeof(dgin[i]));
	}
	for (int j = 64; j < 100; ++j) {
		feature[j] = dgin[j];
//		os.write((const char*)&drin[j], sizeof(drin[j]));
	}
//	os.close();
}

Index & constructIndex() {
	/**
	 * LSH Index Constructing
	 */
	static Index index;
	static Index::Parameter param;

	// Setup the parameters.  Note that L is not provided here.
	param.W = W;
	param.dim = data.getDim();
	DefaultRng rng;

	// Initialize the index structure.  Note L is passed here.
	index.init(param, rng, L, H); // L(trees): 1; H(depth): 10

	// Load index file if exists
	path pt("features.index");
	if (exists(pt)) {
		ifstream is("features.index", ios_base::binary);
		BOOST_VERIFY(is);
		is.exceptions(ios_base::eofbit | ios_base::failbit | ios_base::badbit);
		cout << "LOADING INDEX..." << endl;
		timer.restart();
		index.load(is);
		BOOST_VERIFY(is);
		cout << boost::format("LOAD TIME: %1%s.") % timer.elapsed() << endl;
	} else {
		cout << "CONSTRUCTING INDEX..." << endl;
		timer.restart();
		{
			boost::progress_display progress(data.getSize()); // N feature vectors
			for (unsigned i = 0; i < data.getSize(); ++i) {
				// Insert an item to the hash table.
				// Note that only the key is passed in here.
				// MPLSH will get the feature from the accessor.
				index.insert(i, accessor); // i: key(N) == row of matrix
				++progress;
			}
		}
		cout << boost::format("CONSTRUCTION TIME: %1%s.") % timer.elapsed()
				<< endl;
	}
	return index;

}

void search(Index &index){
	/**
	 *	Search KNNs
	 */
	cout << "RUNNING QUERIES..." << endl;
	timer.restart();
	// R(range): numeric_limits<float>::max(); K(KNN): 50;
	TopkScanner<FloatMatrix::Accessor, metric::l2<float> > query(accessor, l2,
			K, R);

	query.reset(feature);
	//c: # points to scan from each tree (20); L: number of trees (1)
	index.query(feature, c * L, query);
	cout << boost::format("QUERY TIME: %1%s.") % timer.elapsed() << endl;

	//	Topk<unsigned> tk = query.topk();
	//	BOOST_FOREACH(TopkEntry<unsigned> n, tk){
	//		cout<<n.key<<": "<<n.dist<<endl;
	//
	//	}

	/**
	 * Generate Js file
	 */
	ofstream os("img.js");
	string b = "var photos = new Array(";
	Topk<unsigned> tk = query.topk();
	for (unsigned i = 0; i < K; ++i) {
		b += "\"" + paths[tk[i].key] + "\"";
		if (i < tk.size() - 1)
			b += ", ";
	}
	b += ")\n for (var i = 0, photo; photo = photos[i]; i++) {\n"
			" var img = document.createElement(\"image\");\n"
			"img.src = photo;\n"
			"document.body.appendChild(img); }";
	os << b;
	os.close();
}

void evaluation(Index &index){
	if (do_benchmark) {

		Benchmark<> bench;
		cout << "LOADING BENCHMARK..." << endl;
		bench.load(benchmark);
		bench.resize(Q, K);
		cout << "DONE." << endl;

		for (unsigned i = 0; i < Q; ++i) {
			for (unsigned j = 0; j < K; ++j) {
				assert(bench.getAnswer(i)[j].key < data.getSize());
			}
		}

		cout << "RUNNING QUERIES..." << endl;

		Stat recall;
		Stat cost;
		timer.restart();
		{
			// R(range): numeric_limits<float>::max(); K(KNN): 50;
			TopkScanner<FloatMatrix::Accessor, metric::l2<float> > query(
					accessor, l2, K, R);
			boost::progress_display progress(Q);
			for (unsigned i = 0; i < Q; ++i) {
				query.reset(data[bench.getQuery(i)]);
				//c: # points to scan from each tree (20); L: number of trees (1)
				index.query(data[bench.getQuery(i)], c * L, query);
				recall << bench.getAnswer(i).recall(query.topk());
				cost << double(query.cnt()) / double(data.getSize());
				++progress;
			}
		}
		cout << boost::format("QUERY TIME: %1%s.") % timer.elapsed() << endl;

		cout << "[RECALL] " << recall.getAvg() << " +/- " << recall.getStd()
				<< endl;
		cout << "[COST] " << cost.getAvg() << " +/- " << cost.getStd() << endl;

	}
}

int main(int argc, char *argv[]) {

	loadData();
	extractFeature();
	Index &index = constructIndex();
	search(index);
	evaluation(index);

	if (feature != NULL)
		delete[] feature;

	return 0;
}

