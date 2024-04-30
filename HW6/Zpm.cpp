// Copyright 2024 <Max Dupler>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <any>
#include <vector>
#include <sstream>


using std::string, std::cout, std::endl, std::cerr;

std::vector<string> tokenize(const string line) {
    std::vector<string> tokens;
    std::istringstream sReader(line);
    string token;

    while(std::getline(sReader, token, ' ')) {
        tokens.push_back(token);
    }

    return tokens;
}

int main(int argc, char* argv[]) {
    // check if arguments are correct
    if (argc != 2) {
        cerr << "Usage: java Zpm <filename.zpm>" << endl;
        return 0;
    }

    // check if file exists
    string fName = argv[1];
    std::ifstream fReader = std::ifstream(fName);
    if (!fReader.good()) {
        cerr << "File does not exist or has an error" << endl;
    }

    string line;
    while (std::getline(fReader, line)) {
        if (!line.empty()) {
            std::vector<string> tokens = tokenize(line);
            for (const string token : tokens) {
                cout << token << " ";
            }
        }
        cout << endl;
    }
    return 0;
}