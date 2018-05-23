#include "Helpers.h"

// Check for options

bool checkOneDash(string str) {
    return str[0] == '-';
}

bool checkTwoDashes(string str) {
    return checkOneDash(str) && str[1] == '-';    // ;=) :+)
}

// Parse args

vector<string> toVector(int argc, char *argv[]) {
    vector<string> argvec;
    for (int arg = 1; arg < argc; arg++) {
        argvec.emplace_back((string) argv[arg]);
    }
    return argvec;
}

vector<string> toOptions(vector<string> argvec) {
    vector<string> optsvec;
    for (const auto &arg : argvec) {
        if (arg != "--") {
            if (checkOneDash(arg)) {
                optsvec.emplace_back(arg);
            }
        } else {
            return optsvec;
        }
    }
}

vector<string> toDirs(vector<string> argvec) {
    vector<string> dirsvec;
    bool doubleDashed = false;
    for (const auto &arg : argvec) {
        if (arg == "--") {
            doubleDashed = true;
            continue;
        }
        if (doubleDashed || !checkOneDash(arg)) {
            dirsvec.emplace_back(arg);
        }
    }
    return dirsvec;
}

// Error to stderr

void printError(int errnum) {
    switch (errnum) {
        case 1:
            fprintf(stderr, "Error: Unknown parameter\n");
            break;
        default:
            fprintf(stderr, "Unknown error");
            break;
    }
}

// Look for specific options

string getSort(vector<string> optsvec) {
    string res = "";
    for (const auto &opt : optsvec) {
        if (opt == "--help") {
            continue;
        }
        if (checkTwoDashes(opt)) {
            int eq = opt.find("=");
            res = opt.substr(eq + 1, opt.size());
        }

    }
    return res;
}

bool inVector(const string &value, const vector<string> &vec) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

