#include <iostream>
#include "Helpers.h"
#include <boost/filesystem.hpp>

void createDuplicate(const string &path) {
    if (boost::filesystem::exists(path)) {
        createDuplicate(path + "-another");
    } else {
        boost::filesystem::create_directory(path);
    }
}

int main (int argc, char *argv[]) {
    vector<string> argsvector = toVector(argc, argv);

    if (inVector("-h", argsvector) || inVector("--help", argsvector)) {
        cout << "mymkdir [-h|--help] [-p]  <dirname>" << endl;
        return 0;
    }

    bool PARENTS = false;

    if (inVector("-p", argsvector)) {
        // Erase "-p"
        for (int i=0; i<argsvector.size(); i++) {
            if (argsvector[i] == "-p") {
                argsvector.erase(argsvector.begin() + i);
            }
        }
        PARENTS = true;
    }

    if (argsvector.size() > 1) {
        printError(1);
        return 1;
    }

    string newDir = argsvector.front();

    if (newDir[0] != '/' && newDir[0] != '~') {
        newDir = "./" + newDir;
    }

    if (boost::filesystem::exists(newDir)) {
        if (PARENTS) {
            createDuplicate(newDir);
        } else {
            printError(2);
            return 2;
        }
    } else {
        boost::filesystem::create_directory(newDir);
    }
}