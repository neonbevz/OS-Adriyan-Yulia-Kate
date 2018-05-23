#include "Files.h"

bool pathExists(const string &path) {
    return exists(path);
}

bool isFile(const string &path) {
    return is_regular_file(path);
}

bool isDir(const string &path) {
    return is_directory(path);
}

long int getSize(const string &path) {
    return file_size(path);
}

//vector<string> listDir(const string &path) {
//    vector<string> res;
//    copy(directory_iterator(path), directory_iterator(), back_inserter(res));
//
//    for (vector<string>::const_iterator it = res.begin(); it != res.end(); ++it) {
//        cout << (*it) <<endl;
//    }
//}