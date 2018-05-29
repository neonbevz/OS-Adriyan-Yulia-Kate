#include <iostream>
#include <cstdio>
#include <algorithm>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include <iterator>
#include <cstring>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <cctype>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <wordexp.h>

extern char **environ;

using namespace std;
using namespace boost::filesystem;

void help() {
    cout << "You can run following commands: " << endl;
    cout << "merrno [-h|--help] - to display the code of the last error" << endl;
    cout << "mpwd [-h|--help] - to display current working directory" << endl;
    cout << "mcd <path> [-h|--help] - to go to <path>" << endl;
    cout << "mexit [exit code] [-h|--help] - to exit with exit code" << endl;
    cout << "or run external programs" << endl;
}

bool empty_input(string comm, string u_input) {
    return (comm == u_input);
}

bool is_help(string u_input) {
    string check = u_input.substr(u_input.find(' ') + 1);
    return (check == "-h"|| check == "--help");
}

void incorrect_arg(string comm, int &err) {
    cout << "Incorrect arguments for " << comm << endl;
    err = 1;
}

bool is_code(const string &code)
{
    int a = 0;
    for(int i=0; i < code.length(); i++) {
        if(isdigit(code[i])) {
            a++;
        }
    } if (a == code.length()) {
        return true;
    } return false;
}

void merrno (string comm, string u_input, int &err) {
    if (empty_input(comm, u_input)) {
        cout << err << endl;
        err = 0;
    } else if (is_help(u_input)) {
        cout << "merrno displays the exit code of the previos program or command" << endl;
        cout << "or 0 if no command was run " << endl;
        err = 0;
    } else {
        incorrect_arg(comm, err);
    }
}

void mpwd(string comm, string u_input, int &err, string current_dir) {
    if (empty_input(comm, u_input)) {
        cout << current_dir << endl;
    } else if (is_help(u_input)) {
        cout << "mpwd displays current directory" << endl;
        err = 0;
    } else {
        incorrect_arg(comm, err);
    }
}

string mcd(string comm, string u_input, string current_dir, int &err) {
    string new_dir = u_input.substr(u_input.find(' ') + 1);
    string easy = current_dir + "/" + new_dir;
    if (empty_input(comm, u_input)) {
        err = 1;
        return "";
    } else if (is_help(u_input)) {
        cout << "mcd <path> changes cwd to path" << endl;
        err = 0;
        return "";
    } else if (new_dir == ".") {
        return current_dir;
    } else if (new_dir == "..") {
        return current_dir.substr(0, current_dir.find_last_of("/\\"));
    } else if (new_dir == "~") {
        char *home_dir = getenv("HOME");
        string home(home_dir);
        return home;
    } else if(new_dir[0] == '/' && is_directory(new_dir)) {
        return new_dir;
    } else if(is_directory(easy)) {
        return easy;
    } else {
        incorrect_arg(comm, err);
    }
}

void mexit(string comm, string u_input, int &err, int &exit_err) {

    string arg = u_input.substr(u_input.find(" ") + 1);
    if (empty_input(comm, u_input)) {
        cout << "Finished with exit code 0" << endl;
        err = 0;
    } else if (is_help(u_input)) {
        cout << "mexit terminates program" << endl;
        err = 0;
        exit_err = 1;
    } else if (is_code(arg)) {
        cout << "Finished with exit code " << arg << endl;
        err = stoi(arg);
    } else {
        incorrect_arg(comm, err);
        exit_err = 1;
    }
}


bool file_exists(string comm, string u_input) {
    wordexp_t inp;
    wordexp(u_input.c_str(), &inp, 0);
    char **in_parse = inp.we_wordv;
    if(exists(in_parse[1])) {
        return true;
    }
    return false;
}

void fork_exec(string comm, string u_input) {

    wordexp_t inp;
    wordexp(u_input.c_str(), &inp, 0);
    char **in_parse = inp.we_wordv;

    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1) {
        cout << "Unable to fork" << endl;
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        execve(comm.c_str(), in_parse, environ);
        exit(EXIT_FAILURE);
    }
}


int main() {

    auto p = current_path();
    string current_dir = p.string();
    string u_input;
    string comm;
    int err = 0;

    while (true) {
        cout << current_dir << " $ ";
        getline(cin, u_input);

        if (u_input.empty()) {
            continue;
        } else if (u_input == "-h"|| u_input == "--help") {
            help();
            continue;
        } else if (u_input[0] == '\"') {
            comm = u_input.substr(1, u_input.find_last_of('\"')-1);
        } else {
            comm = u_input.substr(0, u_input.find(' '));
        }

        if (comm == "merrno") {
            merrno(comm, u_input, err);
        } else if (comm == "mpwd") {
            mpwd(comm, u_input, err, current_dir);
        } else if (comm == "mcd") {
            string mcdout = mcd(comm, u_input, current_dir, err);
            if (mcdout.empty()) {
                continue;
            } else {
                current_dir = mcdout;
            }
        } else if (comm == "mexit") {
            int exit_err = 0;
            mexit(comm, u_input, err, exit_err);
            if (!exit_err) {
                cout << err << endl;
                break;
            }
        } else {
            if (auto file = fopen(comm.c_str(), "r")) {
                fclose(file);
                if (file_exists(comm, u_input)) {
                    fork_exec(comm, u_input);
            } else {
                    cout << "No such file" << endl;
                    err = 1;
                }
            } else {
                cout << u_input << ": command not found" << endl;
            }
        }
    }
}