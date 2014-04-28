/*
 * FileRecur.cpp
 *
 *  Created on: Apr 29, 2012
 *      Author: luxe
 */

#include "FileRecur.h"
using namespace std;
using namespace boost::filesystem;

FileRecur::FileRecur() {
	// TODO Auto-generated constructor stub

}

FileRecur::~FileRecur() {
	// TODO Auto-generated destructor stub
}

void FileRecur::Run(string pa, vector<path> &list) {
	path pt(pa);
	try {
		if (exists(pt)) { // does p actually exist?
			if (is_regular_file(pt)) { // is p a regular file?
				if (pt.extension() == ".jpg" || pt.extension() == ".png") {
					//cout << pt << " size is " << file_size(pt) << '\n';
					//cout << "extension:" << pt.extension()<< '\n';
					list.push_back(pt);
				}
			} else if (is_directory(pt)) { // is p a directory?
				//cout << pt << " is a directory: \n";
				typedef vector<path> vec; // store paths,
				vec v; // so we can sort them later
				copy(directory_iterator(pt), directory_iterator(),
						back_inserter(v));
				sort(v.begin(), v.end()); // sort, since directory iteration
										  // is not ordered on some file systems

				for (vec::const_iterator it(v.begin()); it != v.end(); ++it) {
					Run(it->string(), list);
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
