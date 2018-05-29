#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int writebuffer (int fd, const char* buffer , ssize_t size , int* status ){
    ssize_t written_bytes = 0;
    while( written_bytes < size ) {
        ssize_t written_now = write(fd, buffer + written_bytes, size - written_bytes );
        if( written_now == -1){
            if (errno == EINTR)
                continue;
            else{
                *status = errno;
                return -1;
            }
        }else
            written_bytes += written_now;
    }
    return 0;
}

void output(string out){
    int status;
    int out_res = writebuffer(STDOUT_FILENO, out.c_str(), out.length(), &status);
    if (out_res){
        cerr << "FAIL: couldnt write to buffer" << endl;
    }
}

string readf(string file, int allsymb) {
    string fileinfo = "";

    int readfile = open(file.c_str(), O_RDONLY);
    if (readfile == -1) {
         cerr << "Sorry, something went wrong" << endl;
            //return "";
    }
    int info;
    int  count = lseek(readfile, 0, SEEK_END);
    if (count == -1) {
        cerr << "FAIL: no bytes found" << endl;
    }

    int err = lseek(readfile, 0, SEEK_SET);
    if (err == -1) {
        cerr << "FAIL: no bytes found" << endl;
    }
    char buff[count];

    info = read(readfile, buff, count);
    for (int i = 0; i < count; ++i) {
        if (allsymb) {
            if (isprint(buff[i])) {
                fileinfo += buff[i];
            } else {
                char buf[16];
                sprintf(buf, "\\x%02hhX", buff[i]);
                for (int k = 0; k < 6; ++k) {
                    fileinfo += buf[k];
                }
            }
        } else {
            fileinfo += buff[i];
        }
    }
    return fileinfo;
}

int main(int argc, char** argv) {

    vector<string> files;
    int allsymb = 0;
    int status;

    for(int i=1; i<argc; i++) {
        string arg(argv[i]);
        if(arg == "-h"|arg =="--help") {
            string desc = "Usage: mycat [-h|--help] [-A] <file1> <file2> ... <fileN>.\n[-A] displays all symbols\n";

            int outinfo = writebuffer(STDOUT_FILENO, desc.c_str(), desc.length(), &status);
            if (outinfo) {
                cerr << "FAIL: couldnt write to buffer" << endl;
                return 1;
            }
            return 0;
        }
        else if (arg == "-A") {
            allsymb = 1;
        }
        else {
            files.push_back(arg);
        }
    }

    for(string file : files) {
        string a = readf(file, allsymb);
        if (a==""){
            continue;
        }
        output(a);
    }
    if(allsymb){
        output("\n");
    }
    return 0;
}
