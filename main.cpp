#include <iostream>
#include "./include/lexer.h"

using namespace std;

int main() {
    try {
        vector<Token> tokens = tokenize("./test/files/file.ap");

        cout << tokens.size();

        for (const auto& token : tokens) {
            cout << "[LINE " << token.getSourceLocation().getLine() 
                 << ", COL " << token.getSourceLocation().getColumn() 
                 << "] TYPE: " << token.getTokenType();

            if (token.getValue().has_value()) {
                cout << " VALUE: " << token.getValue().value();
            }

            cout << "\n";

        }



        
    }
    catch (const exception& e) {
        cout << "Failed" << e.what() << endl;
    }

    return 0;
}