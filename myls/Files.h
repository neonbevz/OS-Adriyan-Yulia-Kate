#ifndef MYLS_FILESYSTEM_H
#define MYLS_FILESYSTEM_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <iterator>
#include <iostream>
#include <dirent.h>
#include <ctime>

using namespace std;
using namespace boost::filesystem;

// Wrappers for Boost methods
bool pathExists(const string &path);
bool isFile(const string &path);
bool isDir(const string &path);
long int getSize(const string &path);
time_t getTime(const string &path);
string getExtension(const string &path);

string timeToString(time_t time);

vector<string> listDir(const string &path);
vector<string> recursiveListDir(const string &root, const string &path);




#endif //MYLS_FILESYSTEM_H
