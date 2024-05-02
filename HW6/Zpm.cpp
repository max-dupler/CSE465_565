// Copyright 2024 <Max Dupler>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <vector>


using std::string, std::cout, std::endl, std::cerr;

class Interpreter {
    const string fileName;
    const std::unordered_map<string, std::regex> tokenSpecification = {
        {"INT_VAR", std::regex("[a-zA-Z_][a-zA-Z_0-9]*\\s")},
        {"STR_VAR", std::regex("[a-zA-Z_][a-zA-Z_0-9]*\\s")},
        {"ASSIGN", std::regex("(?<=\\s)\\=(?=\\s)")},
        {"PLUS_ASSIGN", std::regex("(?<=\\s)\\+=(?=\\s)")},
        {"MINUS_ASSIGN", std::regex("(?<=\\s)-=(?=\\s)")},
        {"MULT_ASSIGN", std::regex("(?<=\\s)\\*=(?=\\s)")},
        {"INT_VAR_VAL", std::regex("(?<=\\+=|-=|\\*=)\\s[a-zA-Z_][a-zA-Z_0-9]*")},
        {"STR_VAR_VAL", std::regex("(?<=\\+=)\\s[a-zA-Z_][a-zA-Z_0-9]*")},
        {"NUMBER", std::regex("(?<=\\s)-?\\d+(?=\\s)")},
        {"STRING", std::regex("\"[^\"]*\"")},
        {"SEMICOLON", std::regex("(?<=\\s);")},
        {"WS", std::regex("\\s+")},
        {"NEWLN", std::regex("\\n")}
    };
    std::unordered_map<string, string> variables;
    int lineNum = 0;

    std::vector<std::pair<std::string, std::string>> lexicalAnalysis(const std::string& line) {
        std::vector<std::pair<std::string, std::string>> tokens;

        for (const auto& [tokType, tokRegex] : tokenSpecification) {
            int pos = 0;
            std::smatch match;

            while (std::regex_search(line.substr(pos), match, tokRegex)) {
                if (tokType != "WS" && tokType != "NEWLN") {
                    tokens.emplace_back(tokType, match[0].str());
                    if (tokType == "INT_VAR" || tokType == "STR_VAR")
                        break;
                }
                pos += match.position() + match.length();
            }
        }
        return tokens;
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
    }

    return 0;
}