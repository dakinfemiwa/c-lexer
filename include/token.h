#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include "./util/bidirectional_hash.h"

enum TokenType {
    STRING,
    INT,
    FLOAT,
    BOOL,
    STRINGTYPE,
    INTTYPE,
    FLOATTYPE,
    BOOLTYPE,    
    IDENTIFIER,
    EQ,
    NEQ,
    LT,
    GT,
    GE,
    LE,
    ASSIGN,
    ADD,
    SUBTRACT,
    SEMICOLON,
    MULTIPLY,
    DIVIDE,
    DIV,
    MOD,
    OUT,
    IN,
    LEFTBRACKET,
    RIGHTBRACKET,
    COMMENT
    
};


class SourceLocation {
    public:
        SourceLocation(int line, int column)
            :line(line), column(column) {}

        int getLine() {
            return line;
        }

        int getColumn() {
            return column;
        }

    private:
        int line;
        int column;
};


class Token {
    public:
        Token(TokenType type, const std::string& value, SourceLocation sourceLocation)
            : type(type), value(value), sourceLocation(sourceLocation) {}

        Token(TokenType type, SourceLocation sourceLocation)
            : type(type), value(std::nullopt), sourceLocation(sourceLocation) {}            
        
        TokenType getTokenType() const {
            return type;
        }

        const std::optional<std::string>& getValue() const {
            return value;
        }

        SourceLocation getSourceLocation() const {
            return sourceLocation;
        }


    private:
        TokenType type;
        std::optional<std::string> value;
        SourceLocation sourceLocation;
};

void buildMap(BidirectionalHash<std::string, TokenType>& tokenMap);


#endif