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

time_t getTime(const string &path) {
    return last_write_time(path);
}

string getExtension(const string &path) {
    return extension(path);
}


string timeToString(time_t time) {
    tm *ptm = std::localtime(&time);
    char buf[32];
    // Format: 15.06.2009 20:20:00
    std::strftime(buf, 32, "%d.%m.%Y %H:%M:%S", ptm);
    string str(buf);
    return str;
}

vector<string> listDir(const string &path) {
    vector<string> res;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            res.emplace_back(ent->d_name);
        }
        closedir(dir);
    }
    return res;
}

vector<string> recursiveListDir(const string &root, const string &path) {
    vector<string> res;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string p = ent->d_name;
            if (p != "." && p != "..") {
                if (path != ".") {
                    res.emplace_back(root + p);
                } else {
                    res.emplace_back(p);
                }
                if (isDir(p)) {
                    string newRoot;
                    if (path == ".") {
                        newRoot = p + "/";
                    } else {
                        newRoot = root + "/" + p + "/";
                    }
                    vector<string> recursion = recursiveListDir(newRoot, path + "/" + p);
                    res.insert(res.end(), recursion.begin(), recursion.end());
                }
            }
        }
        closedir(dir);
    }
    return res;
}
