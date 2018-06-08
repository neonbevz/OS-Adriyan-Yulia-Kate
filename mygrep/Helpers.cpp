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

bool inVector(const string &value, const vector<string> &vec) {
    return find(vec.begin(), vec.end(), value) != vec.end();
}

string getParam(const string &param, vector<string> argsvector) {
    string res = "NONE";
    for (const auto &arg : argsvector) {
        if (arg.compare(0, param.length(), param) == 0) {
            int eq = arg.find("=");
            res = arg.substr(eq + 1, arg.size());
        }
    }
    return res;
}

string toLower(const string &str) {
    string newStr = str;
    transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
    return newStr;
}

void printError(int errnum) {
    switch (errnum) {
        case 1:
            fprintf(stderr, "Error: Unknown parameter\n");
            break;
        case 2:
            fprintf(stderr, "Error: no file specified\n");
            break;
        case 3:
            fprintf(stderr, "Error: no search term specified\n");
            break;
        default:
            fprintf(stderr, "Unknown error");
            break;
    }
}

