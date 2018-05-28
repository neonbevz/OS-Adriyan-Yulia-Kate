#ifndef MYLS_FILE_H
#define MYLS_FILE_H

#include <string>
#include "Files.h"

class Path {
public:
    string path;
    long int size;
    time_t time;
    string extension;
    file_status fs;

    explicit Path(const string &);

    string stringDateTime();
    string stringSize();

    string prefix();

    bool isExec();
    bool isSymlink();
    bool isPipe();
    bool isSocket();
    bool isOther();

    bool isSpecial();
};

struct lessThanName {
    inline bool operator() (const Path &path1, const Path &path2) {
        return path1.path < path2.path;
    }
};

struct lessThanSize {
    inline bool operator() (const Path &path1, const Path &path2) {
        return path1.size < path2.size;
    }
};

struct lessThanTime {
    inline bool operator() (const Path &path1, const Path &path2) {
        return path1.time < path2.time;
    }
};

struct lessThanExtension {
    inline bool operator() (const Path &path1, const Path &path2) {
        if (path1.extension == path2.extension) {
            return path1.path < path2.path;
        }
        return path1.extension < path2.extension;
    }
};

//struct lessThenDir {
//    inline bool operator() (const Path &path1, const Path &path2) {
//        if
//    }
//};

#endif //MYLS_FILE_H
