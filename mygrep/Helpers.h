#ifndef MYGREP_HELPERS_H
#define MYGREP_HELPERS_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool checkOneDash(string str);
bool checkTwoDashes(string str);

vector<string> toVector(int argc, char *argv[]);

bool inVector(const string &value, const vector<string> &vec);

string getParam(const string &param, vector<string> argsvector);

void printError(int errnum);

string toLower(const string &str);

#endif //MYGREP_HELPERS_H
