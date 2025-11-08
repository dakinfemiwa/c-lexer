#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "./token.h"


std::vector<Token> tokenize(const std::string& filename);

#endif
