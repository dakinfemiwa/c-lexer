#include <string>
#include <optional>
#include "../../include/token.h"
#include "../../include/util/bidirectional_hash.h"

void buildMap(BidirectionalHash<std::string, TokenType>& tokenMap) {
    tokenMap.insert("string", TokenType::STRINGTYPE);
    tokenMap.insert("int", TokenType::INTTYPE);
    tokenMap.insert("float", TokenType::FLOATTYPE);
    tokenMap.insert("bool", TokenType::BOOLTYPE);
    tokenMap.insert("==", TokenType::EQ);
    tokenMap.insert("!=", TokenType::NEQ);
    tokenMap.insert("<", TokenType::LT);
    tokenMap.insert(">", TokenType::GT);    
    tokenMap.insert("<=", TokenType::LE);
    tokenMap.insert(">=", TokenType::GE);
    tokenMap.insert("=", TokenType::ASSIGN);
    tokenMap.insert("+", TokenType::ADD);
    tokenMap.insert("-", TokenType::SUBTRACT);
    tokenMap.insert("*", TokenType::MULTIPLY);
    tokenMap.insert("/", TokenType::DIVIDE);
    tokenMap.insert("//", TokenType::DIV);
    tokenMap.insert("%", TokenType::MOD);
    tokenMap.insert("out", TokenType::OUT);
    tokenMap.insert("in", TokenType::IN);
    tokenMap.insert("(", TokenType::LEFTBRACKET);
    tokenMap.insert(")", TokenType::RIGHTBRACKET);
    tokenMap.insert(";", TokenType::SEMICOLON);    
    tokenMap.insert("--", TokenType::COMMENT);

    

}