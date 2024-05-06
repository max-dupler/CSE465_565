// Copyright 2024 <Max Dupler>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <vector>


using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::pair;
using std::vector;

class Interpreter {
public:
    const string fileName;
    const vector<pair<string, string>> TOKEN_SPECIFICATION = {
        {"INT_VAR",     "[a-zA-Z_][a-zA-Z_0-9]*\\s"},
        {"STR_VAR",     "[a-zA-Z_][a-zA-Z_0-9]*\\s"},
        {"ASSIGN",      "(?<=\\s)\\=(?=\\s)"},
        {"PLUS_ASSIGN", "(?<=\\s)\\+=(?=\\s)"},
        {"MINUS_ASSIGN","(?<=\\s)-=(?=\\s)"},
        {"MULT_ASSIGN", "(?<=\\s)\\*=(?=\\s)"},
        {"INT_VAR_VAL", "(?<=\\+=|-=|\\*=)\\s[a-zA-Z_][a-zA-Z_0-9]*"},
        {"STR_VAR_VAL", "(?<=\\+=)\\s[a-zA-Z_][a-zA-Z_0-9]*"},
        {"NUMBER",      "(?<=\\s)-?\\d+(?=\\s)"},
        {"STRING",      "\"[^\"]*\""},
        {"SEMICOLON",   "(?<=\\s);"},
        {"WS",          "\\s+"},
        {"NEWLN",       "\\n"}
    };
    std::unordered_map<string, string> variables;
    int lineNum = 0;

    vector<pair<string, string>> lexicalAnalysis(const string& line){
        vector<pair<string, string>> tokens;
        return tokens;
    }

    void parse(const vector<pair<string, string>> & tokens) {
        return;
    }
    
};

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
        return 0;
    }

    return 0;
}