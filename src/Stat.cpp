#include<fstream>
#include "FileRecur.h"
#include "GetInvar.h"
using namespace std;
using namespace boost::filesystem;
using namespace cv;

const int PROPORT = 400;

void FileAttribute(char** Path) {
	path pt(Path[1]); // pt reads clearer than argv[1] in the following code
	try {
		if (exists(pt)) { // does p actually exist?
			if (is_regular_file(pt)) { // is p a regular file?
				cout << pt << " size is " << file_size(pt) << '\n';
				cout << "  extension()----------: " << pt.extension() << '\n';
			}

			else if (is_directory(pt)) { // is p a directory?
				cout << pt << " is a directory containing:\n";

				//directory_iterator::value_type is directory_entry,
				// which is converted to a path by the path stream inserter
				//copy(directory_iterator(pt), directory_iterator(),
				//		ostream_iterator<directory_entry>(cout, "\n"));

				typedef vector<path> vec; // store paths,
				vec v; // so we can sort them later

				copy(directory_iterator(pt), directory_iterator(),
						back_inserter(v));

				sort(v.begin(), v.end()); // sort, since directory iteration
										  // is not ordered on some file systems

				for (vec::const_iterator it(v.begin()); it != v.end(); ++it) {
					cout << "   " << it->filename() << '\n';
					if (it->has_extension())
						cout << it->extension() << '\n';
				}
			} else
				cout << pt
						<< " exists, but is neither a regular file nor a directory\n";
		} else
			cout << pt << " does not exist\n";
	} catch (const filesystem_error& ex) {
		cout << ex.what() << "\n";
	}
}

void WriteFile() {
	ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();
}



void FeatureCollection(int argc, char* argv[]) {
	Mat img;
	string a = "/home/luxe/Cpluspace/Retrieval/Img";
	FileRecur fr;
	vector<path> list;
	//cin>>a;
	fr.Run(a, list);
	if(list.size()==0)
		return;

	ofstream featureArr, img_paths;
	featureArr.open("features.txt");
	img_paths.open("img_paths.txt");
	int cnt = 0;
	for (vector<path>::const_iterator it(list.begin()); it != list.end();
			++it) {
		img_paths << cnt++ << " "<< it->string() << '\n';
		img = imread(it->string(), 0);
		GetInvar gi;
		if (!gi.IsVaild(img))
			return ;
		if (img.cols > PROPORT)
			resize(img, img, Size(PROPORT, img.rows * PROPORT / img.cols),
					INTER_AREA);

		float dgin[64] = { 0.0 }; //double gray invariance
		float drin[36] = { 0.0 }; //double rotation invariance
		gi.GrayInvar(img);
		gi.RotationInvar(img, drin);
		gi.GrayHistog(img, dgin);

		for (int i = 0; i < 64; ++i) {
			featureArr << dgin[i] << ' ';
		}
		for (int j = 0; j < 36; ++j) {
			featureArr << drin[j] << ' ';
		}
		featureArr << '\n';
	}

	featureArr.close();
	img_paths.close();

}



