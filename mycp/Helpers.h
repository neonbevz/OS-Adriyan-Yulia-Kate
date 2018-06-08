#ifndef MYCP_HELPERS_H
#define MYCP_HELPERS_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool checkOneDash(string str);

bool checkTwoDashes(string str);

vector<string> toVector(int argc, char *argv[]);

bool inVector(const string &value, const vector<string> &vec);

void removeFromVector(const string &str, vector<string> &vec);

void printError(int errnum);

string toLower(const string &str);

#endif //MYCP_HELPERS_H
