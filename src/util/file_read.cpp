#include <fstream>
#include <sstream>
#include <vector>
#include "../../include/file_read.h"

using namespace std;

vector<string> read_file(const string& filename) {
    ifstream inFile(filename);
    vector<string> lines;

    if (!inFile.is_open()) {
        return lines;
    }

    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    return lines;
}

void splitLines(string line, vector<string>& words) {
    stringstream ss(line);
    string t;

    while (ss >> t) {
        words.push_back(t);
    }
}