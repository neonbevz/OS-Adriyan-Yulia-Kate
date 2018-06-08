#include "Helpers.h"

bool checkOneDash(string str) {
    return str[0] == '-';
}

bool checkTwoDashes(string str) {
    return checkOneDash(str) && str[1] == '-';    // ;=) :+)
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

void removeFromVector(const string &str, vector<string> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == str) {
            vec.erase(vec.begin() + i);
            break;
        }
    }
}

void printError(int errnum) {
    switch (errnum) {
        case 1:
            fprintf(stderr, "Error: Not enough paths\n");
            break;
        case 2:
            fprintf(stderr, "Error: Source path is not a file\n");
            break;
        case 3:
            fprintf(stderr, "Error: can't copy a directory non-recursively\n");
            break;
        case 4:
            fprintf(stderr, "Error: target is not a directory\n");
            break;
        case 5:
            fprintf(stderr, "Aborted by user\n");
            break;
        case 6:
            fprintf(stderr, "Error: can't copy multiple items to a file\n");
            break;
        default:
            fprintf(stderr, "Unknown error\n");
            break;
    }
}
