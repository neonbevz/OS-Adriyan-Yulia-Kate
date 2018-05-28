#include "Path.h"

Path::Path(const string &path_) {
    path = path_;
    if (isFile(path)) {
        size = getSize(path);
        extension = getExtension(path);
    } else {
        size = 0;
        extension = "";
    }
    time = getTime(path);
    fs = status(path);
}

string Path::stringDateTime() {
    return timeToString(time);
}

string Path::stringSize() {
    return to_string(size);
}

string Path::prefix() {
    if (this->isExec()) {
        return "*";
    } else if (this->isSymlink()) {
        return "@";
    } else if (this->isPipe()) {
        return "|";
    } else if (this->isSocket()) {
        return "=";
    } else if (this->isOther()) {
        return "?";
    } else {
        return "";
    }
}

bool Path::isExec() {
    int n = fs.permissions();
    return ((n & ( 1 << 0 )) >> 0) || ((n & ( 1 << 3 )) >> 3) || ((n & ( 1 << 6 )) >> 6);
}

bool Path::isSymlink() {
    return fs.type() == 4;
}

bool Path::isPipe() {
    return fs.type() == 7;
}

bool Path::isSocket() {
    return fs.type() == 8;
}

bool Path::isOther() {
    return fs.type() == 9;
}


bool Path::isSpecial() {
    return this->isExec() || this->isSymlink() || this->isPipe() || this->isSocket() || this->isOther();
}
