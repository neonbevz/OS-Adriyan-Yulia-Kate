#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <ftw.h>

#include "Helpers.h"
#include "Files.h"

using namespace std;


int main(int argc, char *argv[]) {
    vector<string> argsvector = toVector(argc, argv);

    // Help
    if (inVector("-h", argsvector) || inVector("--help", argsvector)) {
        cout << "mycp [-h|--help] [-f] <file1> <file2>" << endl;
        cout << "mycp [-h|--help] [-f]  <file1> <file2> <file3>... <dir>" << endl;
        cout << "mycp [-h|--help] [-f] -R  <dir_or_file_1> <dir_or_file_2> <dir_or_file_3> ... <dir>" << endl;
        removeFromVector("-h", argsvector);
        removeFromVector("--help", argsvector);
    }



    // Parameters
    bool SILENT = false;
    bool RECURSIVE = false;

    // Check for parameters and remove them from the vector
    if (inVector("-f", argsvector)) {
        SILENT = true;
        removeFromVector("-f", argsvector);
    }
    if (inVector("-R", argsvector)) {
        RECURSIVE = true;
        removeFromVector("-R", argsvector);
    }

    // Check if enough arguments
    if (argsvector.size() < 2) {
        printError(1);
        return 1;
    }

    // Get and remove target file/dir
    string target = argsvector.back();
    argsvector.erase(argsvector.end());

    if (RECURSIVE) {
        if (isFile(target)) {
            if (argsvector.size() > 1) {
                printError(6);
                return 6;
            }
            string src = argsvector[0];
            if (!isFile(src)) {
                printError(2);
                return 2;
            }

            int cres = copyFile(src, target, SILENT);
            if (cres == 2) {
                printError(5);
                return 5;
            }
            return 0;
        } else {
            for (auto &src : argsvector) {
                if (isDir(src)) {
                    string root;
                    if (src == ".") {
                        root = "";
                    } else {
                        root = src;
                    }
                    vector<string> srcs = recursiveListDir(root, src);
                    for (auto &s : srcs) {
                        if (isFile(s)) {
                            int cres = copyFile(s, target + s, SILENT);
                            if (cres == 2) {
                                printError(5);
                                return 5;
                            }
                        } else if (isDir(s)) {
                            create_directory(target);
                        }
                    }
                } else {
                    int cres = copyFile(src, target, SILENT);
                    if (cres == 2) {
                        printError(5);
                        return 5;
                    }
                }
            }
        }
    } else {
        if (isFile(target)) {
            if (argsvector.size() > 1) {
                printError(6);
                return 6;
            }
            string src = argsvector[0];
            if (!isFile(src)) {
                printError(2);
                return 2;
            }

            int cres = copyFile(src, target, SILENT);
            if (cres == 2) {
                printError(5);
                return 5;
            }
            return 0;
        } else {
            for (auto &src : argsvector) {
                if (!isFile(src)) {
                    printError(3);
                    return 3;
                }

                int cres = copyFile(src, target, SILENT);
                if (cres == 2) {
                    printError(5);
                    return 5;
                }
            }
            return 0;
        }
    }


    return 0;
}