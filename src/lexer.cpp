#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <regex>
#include "../include/util/bidirectional_hash.h"
#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/file_read.h"

using namespace std;

bool isInteger(string num) {
    std::regex integerPattern(
        "^[+-]?(0|[1-9][0-9]*)$"
    );
    return regex_match(num, integerPattern);
}

bool isFloat(string num) {
    std::regex floatPattern(
        "^[+-]?[0-9]+\\.[0-9]+$"
    );
    return regex_match(num, floatPattern);
}

void tokenize_line(string line, vector<Token>& tokens, int lineNo,
    BidirectionalHash<string, TokenType>& tokenMap) {
    stringstream ss(line);
    string t;
    int col = 0;

    while (ss >> ws) {
        if (ss.eof()) {
            break;
        }

        col = ss.tellg();
        if (ss.peek() == '"') {
            ss.get();
            col++;

            string strLiteral;
            getline(ss, strLiteral, '"');
            tokens.push_back(Token(TokenType::STRING, strLiteral, SourceLocation(lineNo, col)));
        } else {
            ss >> t;

            auto tokenType = tokenMap.getValue(t);
            if (tokenType.has_value()) {
                tokens.push_back(Token(tokenType.value(), t, SourceLocation(lineNo, col)));
            } else if (t == "True" || t == "False") {
                tokens.push_back(Token(TokenType::BOOL, t, SourceLocation(lineNo, col)));
            } else if (isFloat(t)) {
                tokens.push_back(Token(TokenType::FLOAT, t, SourceLocation(lineNo, col)));
            } else if (isInteger(t)) {
                tokens.push_back(Token(TokenType::INT, t, SourceLocation(lineNo, col)));
            } else {
                tokens.push_back(Token(TokenType::IDENTIFIER, t, SourceLocation(lineNo, col)));
            }            
        }


    }

}


vector<Token> tokenize(const string& filename) {
    vector<string> file_lines = read_file(filename);
    vector<Token> tokens;
    BidirectionalHash<string, TokenType> map;

    buildMap(map);

    int lines = file_lines.size();

    for (int i = 0; i < lines; i++) {
        tokenize_line(file_lines[i], tokens, i+1, map);
    }

    return tokens;
}