#include "Server.h"

std::string makeDateString() {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = localtime(&now);
    std::string y = std::to_string(1900 + ltm->tm_year);
    std::string m = std::to_string(1 + ltm->tm_mon);
    std::string d = std::to_string(ltm->tm_mday);
    return d + "-" + m + "-" + y;
}

std::string makeTimeString() {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = localtime(&now);
    std::string h = std::to_string(ltm->tm_hour);
    std::string m = std::to_string(ltm->tm_min);
    std::string s = std::to_string(ltm->tm_sec);
    return h + ":" + m + ":" + s;
}

int countWords(std::string s) {
    int nSpaces = 0;
    unsigned int i = 0;
    while(isspace(s.at(i)))
        i++;
    for(; i < s.length(); i++)
    {
        if(isspace(s.at(i)))
        {
            nSpaces++;
            while(isspace(s.at(i++)))
                if(s.at(i) == '\0')
                    nSpaces--;
        }
    }
    return nSpaces + 1;
}
