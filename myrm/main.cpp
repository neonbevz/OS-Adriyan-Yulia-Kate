#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;


int main(int argc, char** argv) {
    if (argc == 1){
        cerr << "myrm: missing operand\nTry './myrm [-h|--help]' for more information." << endl;
        return 1;
    }

    bool force = false;
    bool dir = false;
    vector<string> files;

    for (int i = 1; i < argc; i++) {
        string inp(argv[i]);
        if (inp == "-h" || inp == "--help") {
            cout << "myrm [-h|--help] [-f] [-R] <file1> <file2> <file3>\n"
                    "-f force remove\n-R remove directories" << endl;
            return 0;
        } else if (inp[0] == '-') {
            if (inp == "-f") {
                force = true;
            } else if (inp == "-R") {
                dir = true;
            } else {
                cerr << "myrm: invalid option -- '" <<
                     inp.substr(1) << "'\nTry './myrm [-h|--help]' for more information." << endl;
                return 1;
            }
        } else {
            files.emplace_back(inp);
        }
    }

    for (string s : files) {
        string answer;
        if (!force) {
            cout << "myrm: remove file '" << s << "'? (Y[es]/N[o]/A[ll]/C[ancel])" << endl;
            if (getline(cin, answer)) {
                if (answer == "a" || answer == "A") {
                    force = true;
                } else if (answer == "c" || answer == "C") {
                    break;
                }
            } else {
                continue;
            }
        }

        if (force || answer == "y" || answer == "Y") {
            string file = "./" + s;
            if (!exists(file)) {
                cerr << "myrm: cannot remove '" << s << "': No such file or directory" << endl;
                continue;
            }
            if (!is_directory(status(file))) {
                remove(file);
            } else if (dir) {
                remove_all("./" + file);
            } else {
                cerr << "myrm: cannot remove '" << s << "': Is a directory" << endl;
            }
        }
    } return 0;
}