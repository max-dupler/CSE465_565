// Copyright 2024 <Max Dupler>
// parts of this program were assisted by ChatGPT


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

class Zpm {
private:
    // Map to store variables and their values
    static std::unordered_map<std::string, std::string> variables;

    static std::vector<std::string> tokenize(const std::string& line) {
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static std::string parseValue(const std::string& value) {
        try {
            std::size_t pos;
            int parsedValue = std::stoi(value, &pos);
            if (pos == value.size()) {
                return std::to_string(parsedValue);
            } else {
                if (value.front() == '"' && value.back() == '"' && value.size() >= 2) {
                    return value.substr(1, value.size() - 2);
                } else {
                    auto it = variables.find(value);
                    if (it != variables.end()) {
                        return it->second;
                    }
                }
            }
        } catch (std::invalid_argument&) {
        } catch (std::out_of_range&) {
        }
        return value;
    }

public:

    static void interpret(const std::string& line, int lineNum) {
        if (line.empty()) {
            return;
        }

        std::vector<std::string> parts = tokenize(line);
        // Check for syntax errors
        if (parts.size() < 3 || (parts.back() != ";" && parts.back() != "ENDFOR")) {
            throw std::runtime_error("Syntax Error");
        }
        if (parts[0] == "PRINT") {
            printVariables(parts[1], lineNum);
        } else if (parts[0] == "FOR") {
            forLoop(parts, lineNum);
        } else {
            assignment(parts, lineNum);
        }
    }


    static void assignment(const std::vector<std::string>& parts, int lineNum) {
        std::string variable = parts[0];
        std::string operation = parts[1];
        std::string value = parts[2];

        if (operation == "=") {
            variables[variable] = parseValue(value);
        } else {
            auto it = variables.find(variable);
            if (it == variables.end()) {
                throw std::runtime_error("Runtime Error: Variable not found");
            }
            std::string currentValue = it->second;
            std::string parsedValue = parseValue(value);
            if (operation == "+=") {
                if (variables.find(parsedValue) != variables.end()) {
                    parsedValue = variables[parsedValue];
                }
                currentValue += parsedValue;
            } else if (operation == "-=") {
                if (variables.find(parsedValue) != variables.end()) {
                    parsedValue = variables[parsedValue];
                }
                currentValue.erase(currentValue.find(parsedValue), parsedValue.length());
            } else if (operation == "*=") {
                if (variables.find(parsedValue) != variables.end()) {
                    parsedValue = variables[parsedValue];
                }
                currentValue += parsedValue;
            } else {
                throw std::runtime_error("Syntax Error: Invalid operation");
            }
            variables[variable] = currentValue;
        }
    }

    static void forLoop(const std::vector<std::string>& parts, int lineNum) {
        int numLoops = std::stoi(parts[1]);

        for (int i = 0; i < numLoops; i++) {
            std::string statement;
            for (std::size_t j = 2; j < parts.size(); j++) {
                if (parts[j] == ";") {
                    interpret(statement, lineNum);
                    statement.clear();
                } else if (parts[j] == "ENDFOR") {
                    break;
                } else {
                    statement += parts[j] + " ";
                }
            }
        }

        if (parts.back() != "ENDFOR") {
            throw std::runtime_error("Syntax Error");
        }
    }

    static void printVariables(const std::string& variable, int lineNum) {
        auto it = variables.find(variable);
        if (it == variables.end()) {
            throw std::runtime_error("Runtime Error");
        } else {
            std::cout << variable << "=" << it->second << std::endl;
        }
    }

    static int main(int argc, char* argv[]) {
        if (argc < 2) {
            std::cerr << "Usage: ./Zpm <filename.zpm>" << std::endl;
            return 1;
        }

        std::string fileName = argv[1];
        int lineNum = 0;

        std::ifstream fileStream(fileName);
        if (!fileStream.is_open()) {
            std::cerr << "Error: Unable to open file " << fileName << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(fileStream, line)) {
            lineNum++;
            try {
                interpret(line, lineNum);
            } catch (const std::exception& e) {
                std::cerr << "Error: Line " << lineNum << std::endl;
                return 1;
            }
        }

        return 0;
    }
};

std::unordered_map<std::string, std::string> Zpm::variables;

int main(int argc, char* argv[]) {
    Zpm::main(argc, argv);
    return 0;
}
