#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <ftw.h>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

vector<string> toVector(int argc, char *argv[]) {
    vector<string> argvec;
    for (int arg = 1; arg < argc; arg++) {
        argvec.emplace_back((string) argv[arg]);
    }
    return argvec;
}

bool inVector(const string &value, const vector<string> &vec) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

void removeFromVector(const string &str, vector<string> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == str) {
            vec.erase(vec.begin() + i);
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    vector<string> argsvector = toVector(argc, argv);

    // Help
    if (inVector("-h", argsvector) || inVector("--help", argsvector)) {
        cout << "mymv [-h|--help] [-f] <oldfile> <newfile>" << endl;
        cout << "mymv [-h|--help] [-f] <oldfile_or_dir_1> <oldfile_or_dir_oldfile2> <oldfile_or_dir_oldfile3>.... <dir>"
             << endl;
        return 0;
    }

    bool silent = false;
    if (inVector("-f", argsvector)) {
        silent = true;
        removeFromVector("-f", argsvector);
    }

    string target = argsvector.back();
    argsvector.erase(argsvector.end());

    if (!exists(target)) {
        if (argsvector.size() == 1) {
            rename(argsvector[0], target);
        } else {
            create_directory(target);
            for (auto &p : argsvector) {
                path pp(p);
                rename(p, target + pp.filename().string());
            }
        }
    } else if (is_regular_file(target)) {
        if (argsvector.size() == 1) {
            if (!silent) {
                cout << "Overwrite?" << endl;
                char a;
                cin >> a;
                if (a == 'Y' || a == 'y' || a == 'A' || a == 'a') {
                    remove(target);
                    rename(argsvector[0], target);
                    return 0;
                }
            } else {
                remove(target);
                rename(argsvector[0], target);
                return 0;
            }
        } else {
            cerr << "Too many arguments" << endl;
        }
    } else if (is_directory(target)) {
        for (auto &p : argsvector) {
            path pp(p);
            if (exists(target + pp.filename().string())) {
                cout << "Overwrite?" << endl;
                char a;
                cin >> a;
                if (a == 'Y' || a == 'y') {
                    remove(target + pp.filename().string());
                    rename(p, target + pp.filename().string());
                    continue;
                } else if (a == 'A' || a == 'a') {
                    remove(target + pp.filename().string());
                    rename(p, target + pp.filename().string());
                    silent = true;
                    continue;
                } else if (a == 'C' || a == 'c') {
                    return 1;
                } else {
                    continue;
                }
            } else {
                rename(p, target + pp.filename().string());
                continue;
            }
        }
    }

    return 0;
}