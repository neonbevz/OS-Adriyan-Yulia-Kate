#include <iostream>
#include <iomanip>
#include "Helpers.h"
#include "Files.h"
#include "Path.h"

using namespace std;

int main1(int argc, char *argv[]) {
    vector<string> res = {"R", "a"};
    cout << inVector("r", res) << endl;
    cout << inVector("A", res) << endl;
}


int main(int argc, char *argv[]) {
    ,m

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
    vector<string> oneDashOpts = {"-h", "-l", "-r", "-F", "-R"};
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
    vector<string> temppaths;
    for (auto &p : pathsvector) {
        if (pathExists(p)) {
            temppaths.emplace_back(p);
        } else {
            cout << "myls: '" << p << "' not found" << endl;
        }
    }
    pathsvector = temppaths;
    temppaths.clear();

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

    // List directories
    vector<string> final;
    for (const auto &dir : dirs) {
        vector<string> indir;
        if (inVector("-R", options)) {
            string root;
            if (dir == ".") {
                root = "";
            } else {
                root = dir;
            }
            indir = recursiveListDir(root, dir);
        } else {
            indir = listDir(dir);
        }
        for (const auto &name : indir) {
            string path;
            if (dir != "."){
                path = dir + name;
            } else {
                path = name;
            }
            if (isDir(path)) {
                path += "/";
            }
            final.emplace_back(path);
        }
    }



    // Convert into objects
    vector<Path> objects;
    for (const auto &p : final) {
        objects.emplace_back(Path(p));
    }

    // Sort
    if (sortMode == "N") {
        // By name
        sort(objects.begin(), objects.end(), lessThanName());
    } else if (sortMode == "S") {
        // By size
        sort(objects.begin(), objects.end(), lessThanSize());
    } else if (sortMode == "t") {
        // By time modified
        sort(objects.begin(), objects.end(), lessThanTime());
    } else if (sortMode == "X") {
        // By extension
        sort(objects.begin(), objects.end(), lessThanExtension());
    }

    // Special sort
    if (specialSortMode.find('D') != -1) {
        // Directories first
        vector<Path> sortedDirs;
        vector<Path> sortedFiles;
        for (const auto &obj : objects) {
            if (isDir(obj.path)) {
                sortedDirs.emplace_back(obj);
            } else {
                sortedFiles.emplace_back(obj);
            }
        }
        objects = sortedDirs;
        objects.insert(objects.end(), sortedFiles.begin(), sortedFiles.end());
    }
    if (specialSortMode.find('s') != -1) {
        // Special files to end
        vector<Path> specials;
        vector<Path> normals;
        for (auto &obj : objects) {
            if (obj.isSpecial()) {
                specials.emplace_back(obj);
            } else {
                normals.emplace_back(obj);
            }
        }
        objects = normals;
        objects.insert(objects.end(), specials.begin(), specials.end());
    }

    // Reverse
    if (inVector("-r", options)) {
        reverse(objects.begin(), objects.end());
    }

    // Prefix specials
    if (inVector("-F", options)) {
        for (auto &obj : objects) {
            obj.path = obj.prefix() + obj.path;
        }
    }

    if (inVector("-l", options)) {
        for (auto &obj : objects) {
            cout << setw(30) << left << obj.path << " " << setw(20) << left << obj.stringSize() << " " << obj.stringDateTime() << endl;
        }
    } else {
        for (auto &obj : objects) {
            cout << setw(30) << left << obj.path << endl;
        }
    }


    //if no errors - exit
    return 0;
}
