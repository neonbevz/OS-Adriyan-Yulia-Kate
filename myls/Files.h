#ifndef MYLS_FILESYSTEM_H
#define MYLS_FILESYSTEM_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <iterator>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

// Wrappers for Boost methods
bool pathExists(const string &path);
bool isFile(const string &path);
bool isDir(const string &path);
long int getSize(const string &path);

//vector<string> listDir(const string &path);




#endif //MYLS_FILESYSTEM_H
