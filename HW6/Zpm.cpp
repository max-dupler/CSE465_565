// Copyright 2024 <Max Dupler>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <any>


using std::string, std::cout, std::endl, std::cerr;

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
    return 0;
}