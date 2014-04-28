/*
 * FileRecur.h
 *
 *  Created on: Apr 29, 2012
 *      Author: luxe
 */

#ifndef FILERECUR_H_
#define FILERECUR_H_

#include <boost/filesystem.hpp>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>


class FileRecur {
public:
	FileRecur();
	void Run(std::string pt, std::vector<boost::filesystem::path> &list);
	virtual ~FileRecur();
};

#endif /* FILERECUR_H_ */
