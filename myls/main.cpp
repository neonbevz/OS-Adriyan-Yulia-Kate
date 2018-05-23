#include <iostream>
#include "Helpers.h"
#include "Files.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> argsvector = toVector(argc, argv);

    // Directories / files
    vector<string> pathsvector = toDirs(argsvector);
    // Options
    vector<string> optsvector = toOptions(argsvector);

    // Check for "help"
    if (inVector("-h", optsvector) || inVector("--help", optsvector)) {
        cout << "myls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X|D|s] [-r]" << endl;
        return 0;
    }

    // Default options
    string sortMode = "N";
    string specialSortMode = "U";
    vector<string> options;
    // Look for errors
    vector<string> oneDashOpts = {"-h", "-l", "-r", "F", "-R"};
    vector<string> sortOpts = {"U", "S", "t", "X", "N"};
    vector<string> specialSortOpts = {"D", "s"};
    for (const auto &opt : optsvector) {
        if (checkTwoDashes(opt)) {
            if (opt.substr(0, 7) == "--sort=") {
                string mode = opt.substr(7, opt.size() - 7);
                if (inVector(mode, sortOpts)) {
                    sortMode = mode;
                } else if (inVector(mode, specialSortOpts)) {
                    if (specialSortMode == "U") {
                        specialSortMode = mode;
                    } else if (specialSortMode != mode) {
                        specialSortMode += mode;
                    }
                } else {
                    cout << mode << endl;
                    printError(1);
                    return 1;
                }
            } else if (opt != "--help") {
                printError(1);
                return 1;
            }
        } else {
            if (inVector(opt, oneDashOpts)) {
                options.emplace_back(opt);
            } else {
                printError(1);
                return 1;
            }
        }
    }
    // Use current folder if no paths are given
    if (pathsvector.empty()) {
        pathsvector.emplace_back(".");
    }
    // Check for existance
    for (int p = 0; p < pathsvector.size(); p++) {
        if (!pathExists(pathsvector[p])) {
            cout << "myls: '" << pathsvector[p] << "' not found" << endl;
            pathsvector.erase(pathsvector.begin() + p);
        }
    }

    // Divide into files and dirs
    vector<string> dirs;
    vector<string> files;
    for (const auto &path : pathsvector) {
        if (isDir(path)) {
            dirs.emplace_back(path);
        } else {
            files.emplace_back(path);
        }
    }

    cout << "Options:" << endl;
    for (const auto &opt : options) {
        cout << opt << endl;
    }

    cout << "Files:" << endl;
    for (const auto &opt : files) {
        cout << opt << endl;
    }

    cout << "Dirs:" << endl;
    for (const auto &opt : dirs) {
        cout << opt << endl;
    }

//    for (const auto &path : pathsvector) {
//        listDir(path);
//    }

    //if no errors - exit
    cout << 0 << endl;
    return 0;
}