#include "Helpers.h"

bool checkOneDash(string str) {
    return str[0] == '-';
}

bool checkTwoDashes(string str) {
    return checkOneDash(str) && str[1] == '-';
}


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

void printError(int errnum) {
    switch (errnum) {
        case 1:
            fprintf(stderr, "Error: Too many arguments\n");
            break;
        case 2:
            fprintf(stderr, "Error: Path already exists\n");
            break;
        default:
            fprintf(stderr, "Unknown error");
            break;
    }
}

