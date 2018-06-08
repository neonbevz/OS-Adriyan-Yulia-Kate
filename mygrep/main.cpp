#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "Helpers.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> argsvector = toVector(argc, argv);

    if (inVector("-h", argsvector) || inVector("--help", argsvector)) {
        cout << "mygrep [-h|--help] [-v|--invert-match] [-i|--ignore-case]"
             << " [--file=<filename>] [--regexp=’<regexpression>’ | --string=<string>]" << endl;
        return 0;
    }

    bool INVERT = inVector("-v", argsvector) || inVector("--invert-match", argsvector);
    bool IGNORE_CASE = inVector("-i", argsvector) || inVector("--ignore-case", argsvector);

    string file = getParam("--file", argsvector);

    if (file.empty() || file == "NONE") {
        printError(2);
        return 2;
    }

    string searchRegex = getParam("--regexp", argsvector);
    if (searchRegex.empty()) {
        printError(3);
        return 3;
    }
    bool REGEXP_GIVEN = (searchRegex != "NONE");

    string searchString = getParam("--string", argsvector);
    if (searchRegex.empty()) {
        printError(3);
        return 3;
    }
    bool STRING_GIVEN = (searchString != "NONE");

    if (!STRING_GIVEN && !REGEXP_GIVEN) {
        printError(3);
        return 3;
    }

    if (STRING_GIVEN && IGNORE_CASE) {
        searchString = toLower(searchString);
    }

    ifstream infile("test.txt");

    string line;

    bool matches;
    while (getline(infile, line))
    {
        istringstream iss(line);
        if (IGNORE_CASE) {
            line = toLower(line);
        }

        if (REGEXP_GIVEN) {
            matches = regex_match(line, regex(searchRegex));
        } else {
            matches = line.find(searchString) != string::npos;
        }

        if (INVERT) {
            matches = !matches;
        }

        if (matches) {
            cout << line << endl;
        }
    }

    return 0;
}