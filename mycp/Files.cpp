#include <dirent.h>
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

int deleteFile(const string &path) {
    return remove(path);
}

long int deleteDir(const string &path) {
    return remove_all(path);
}

char confirmOverwrite(const string &path) {
    cout << "Overwrite " << path << " ? [Y]es / [N]o / [A]ll / [C]ancel" << endl;
    char ans;
    cin >> ans;
    return (char) ::tolower(ans);
}

int copyFile(const string &src, const string &target, bool &SILENT) {
    int status = 0;
    if (isFile(target) && !SILENT) {
        char ans = confirmOverwrite(target);
        switch (ans) {
            case 'y':
                break;
            case 'a':
                SILENT = true;
                break;
            case 'c':
                status = 2;
                break;
            default:
                status = 1;
                cout << "Skipping overwriting " << target << endl;
                break;
        }
    }

    if (status != 0) { return status; }

    copy_file(src, target, copy_option::overwrite_if_exists);

    return status;
}

int copyDirectory(const string &src, const string &target, bool &SILENT) {
    int status = 0;

    if (!exists(target)) create_directory(target);

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(src.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string p = ent->d_name;

            if (p == "." || p == "..") continue;

            string newSrc = src + "/" + p;
            if (isFile(p)) {
                int s = copyFile(newSrc, target, SILENT);
                if (s == 2) return s;
                else if (s == 1) status = 1;
            } else if (isDir(p)) {
                copyDirectory(newSrc, target, SILENT);
            }
        }
    }
    return status;
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
