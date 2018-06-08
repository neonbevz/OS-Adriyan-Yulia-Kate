#ifndef MYLS_FILESYSTEM_H
#define MYLS_FILESYSTEM_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <iterator>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

bool pathExists(const string &path);

bool isFile(const string &path);

bool isDir(const string &path);

int deleteFile(const string &path);

long int deleteDir(const string &path);

char confirmOverwrite(const string &path);

int copyFile(const string &src, const string &target, bool &SILENT);

vector<string> recursiveListDir(const string &root, const string &path);

#endif //MYLS_FILESYSTEM_H
