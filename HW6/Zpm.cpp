// Copyright 2024 <Max Dupler>
// part of this program was assisted by ChatGPT
// specific parts of the program assisted by chatGPT:
//      - Regex use
//      - fixing errors
//      - comment generation
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
        {"ASSIGN",      "\\s=\\s"},
        {"PLUS_ASSIGN", "\\s\\+=\\s"},
        {"MINUS_ASSIGN","\\s-=\\s"},
        {"MULT_ASSIGN", "\\s\\*=\\s"},
        {"INT_VAR_VAL", "(\\+=|-=|\\*=)\\s[a-zA-Z_][a-zA-Z_0-9]*"},
        {"STR_VAR_VAL", "\\+=\\s[a-zA-Z_][a-zA-Z_0-9]*"},
        {"NUMBER",      "\\s-?\\d+\\s"},
        {"STRING",      "\"[^\"]*\""},
        {"SEMICOLON",   "\\s;"},
        {"WS",          "\\s+"},
        {"NEWLN",       "\\n"}
    };
    std::unordered_map<string, string> variables;
    int lineNum = 0;

    vector<pair<string, string>> lexicalAnalysis(const string& line){
        vector<pair<string, string>> tokens;

        for (const auto& tokSpec : TOKEN_SPECIFICATION) {
            int pos = 0;
            std::regex pattern(tokSpec.second);

            while (pos < line.length()) {
                std::smatch match;
                if (std::regex_search(line.cbegin() + pos, line.cend(), match, pattern)) {
                    if (tokSpec.first != "WS" && tokSpec.first != "NEWLN") {
                        tokens.emplace_back(tokSpec.first, match[0]);
                        if (tokSpec.first == "INT_VAR" || tokSpec.first == "STR_VAR") {
                            break;
                        }
                    }
                    pos += match.position() + match.length();
                } else {
                    ++pos;
                }
            }
        }
        return tokens;
    }

    void parse(const vector<pair<string, string>> & tokens) {
        return;
    }

    void run(string& fileName) {
        int lineNum = 0;
        std::ifstream fReader = std::ifstream(fileName);
        if (!fReader.good()) {
            cerr << "File does not exist or has an error" << endl;
            return;
        }

        string line;
        vector<pair<string, string>> tokens;
        while (std::getline(fReader, line)) {
            ++lineNum;
            tokens = lexicalAnalysis(line);
            for (const auto& token : tokens) {
                cout << "Type: " << token.first << ", Value: " << token.second << endl;
            }
        }

    }
    
};

int main(int argc, char* argv[]) {
    // check if arguments are correct
    if (argc != 2) {
        cerr << "Usage: java Zpm <filename.zpm>" << endl;
        return 0;
    }

    Interpreter interpreter;
    string fName = argv[1];
    interpreter.run(fName);

    return 0;
}