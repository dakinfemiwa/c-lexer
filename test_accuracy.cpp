#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "./include/lexer.h"

using namespace std;

struct TestCase {
    string name;
    string input;
    vector<TokenType> expectedTypes;
    vector<string> expectedValues;
};

void writeTestFile(const string& filename, const string& content) {
    ofstream file(filename);
    file << content;
    file.close();
}

bool runTest(const TestCase& test, int testNum) {
    // Write test input to file
    string testFile = "./test/temp_test.ap";
    writeTestFile(testFile, test.input);
    
    // Tokenize
    vector<Token> tokens = tokenize(testFile);
    
    // Check token count
    if (tokens.size() != test.expectedTypes.size()) {
        cout << "❌ Test " << testNum << " (" << test.name << ") FAILED:" << endl;
        cout << "   Expected " << test.expectedTypes.size() 
             << " tokens, got " << tokens.size() << endl;
        return false;
    }
    
    // Check each token
    for (size_t i = 0; i < tokens.size(); i++) {
        // Check type
        if (tokens[i].getTokenType() != test.expectedTypes[i]) {
            cout << "❌ Test " << testNum << " (" << test.name << ") FAILED:" << endl;
            cout << "   Token " << i << ": Expected type " << test.expectedTypes[i]
                 << ", got " << tokens[i].getTokenType() << endl;
            return false;
        }
        
        // Check value (if expected value provided)
        if (i < test.expectedValues.size() && !test.expectedValues[i].empty()) {
            string actualValue = tokens[i].getValue().has_value() 
                ? tokens[i].getValue().value() 
                : "";
            
            if (actualValue != test.expectedValues[i]) {
                cout << "❌ Test " << testNum << " (" << test.name << ") FAILED:" << endl;
                cout << "   Token " << i << ": Expected value \"" << test.expectedValues[i]
                     << "\", got \"" << actualValue << "\"" << endl;
                return false;
            }
        }
    }
    
    cout << "✓ Test " << testNum << " (" << test.name << ") PASSED" << endl;
    return true;
}

int main() {
    cout << "=== A+ Lexer Accuracy Test Suite ===" << endl << endl;
    
    vector<TestCase> tests = {
        // Test 1: Simple integer assignment
        {
            "Simple int assignment",
            "int x = 5 ;",
            {TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::SEMICOLON},
            {"int", "x", "=", "5", ";"}
        },
        
        // Test 2: Float assignment
        {
            "Float assignment",
            "float pi = 3.14 ;",
            {TokenType::FLOATTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::FLOAT, TokenType::SEMICOLON},
            {"float", "pi", "=", "3.14", ";"}
        },
        
        // Test 3: String with spaces
        {
            "String literal with spaces",
            "string msg = \"hello world\"",
            {TokenType::STRINGTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::STRING},
            {"string", "msg", "=", "hello world"}
        },
        
        // Test 4: Boolean expression
        {
            "Boolean comparison",
            "bool flag = 3 == 4",
            {TokenType::BOOLTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::EQ, TokenType::INT},
            {"bool", "flag", "=", "3", "==", "4"}
        },
        
        // Test 5: Multiple operators
        {
            "Arithmetic expression",
            "int result = 10 + 20 * 3",
            {TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::ADD, TokenType::INT, TokenType::MULTIPLY, TokenType::INT},
            {"int", "result", "=", "10", "+", "20", "*", "3"}
        },
        
        // Test 6: All comparison operators
        {
            "Comparison operators",
            "x < 5 ;",
            {TokenType::IDENTIFIER, TokenType::LT, TokenType::INT, TokenType::SEMICOLON},
            {"x", "<", "5", ";"}
        },
        
        // Test 7: Not equal operator
        {
            "Not equal operator",
            "x != 10",
            {TokenType::IDENTIFIER, TokenType::NEQ, TokenType::INT},
            {"x", "!=", "10"}
        },
        
        // Test 8: Greater than or equal
        {
            "Greater or equal operator",
            "y >= 100",
            {TokenType::IDENTIFIER, TokenType::GE, TokenType::INT},
            {"y", ">=", "100"}
        },
        
        // Test 9: Less than or equal
        {
            "Less or equal operator",
            "z <= 50",
            {TokenType::IDENTIFIER, TokenType::LE, TokenType::INT},
            {"z", "<=", "50"}
        },
        
        // Test 10: Division operators
        {
            "Division operators",
            "a = 10 / 2",
            {TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::DIVIDE, TokenType::INT},
            {"a", "=", "10", "/", "2"}
        },
        
        // Test 11: Integer division
        {
            "Integer division",
            "b = 10 // 3",
            {TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::DIV, TokenType::INT},
            {"b", "=", "10", "//", "3"}
        },
        
        // Test 12: Modulo operator
        {
            "Modulo operator",
            "c = 10 % 3",
            {TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::MOD, TokenType::INT},
            {"c", "=", "10", "%", "3"}
        },
        
        // Test 13: Boolean literals
        {
            "Boolean literals",
            "bool isTrue = True",
            {TokenType::BOOLTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::BOOL},
            {"bool", "isTrue", "=", "True"}
        },
        
        // Test 14: Parentheses
        {
            "Parentheses",
            "( x + 5 )",
            {TokenType::LEFTBRACKET, TokenType::IDENTIFIER, TokenType::ADD, TokenType::INT, TokenType::RIGHTBRACKET},
            {"(", "x", "+", "5", ")"}
        },
        
        // Test 15: Empty string
        {
            "Empty string literal",
            "string empty = \"\"",
            {TokenType::STRINGTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::STRING},
            {"string", "empty", "=", ""}
        },
        
        // Test 16: Negative numbers
        {
            "Negative integer",
            "int neg = -42",
            {TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT},
            {"int", "neg", "=", "-42"}
        },
        
        // Test 17: Negative float
        {
            "Negative float",
            "float negPi = -3.14",
            {TokenType::FLOATTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::FLOAT},
            {"float", "negPi", "=", "-3.14"}
        },
        
        // Test 18: Multiple statements
        {
            "Multiple statements",
            "int a = 1 ;\nint b = 2 ;",
            {TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::SEMICOLON, 
             TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INT, TokenType::SEMICOLON},
            {"int", "a", "=", "1", ";", "int", "b", "=", "2", ";"}
        },
        
        // Test 19: Complex expression
        {
            "Complex expression",
            "int x = ( 10 + 5 ) * 2",
            {TokenType::INTTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::LEFTBRACKET, TokenType::INT, 
             TokenType::ADD, TokenType::INT, TokenType::RIGHTBRACKET, TokenType::MULTIPLY, TokenType::INT},
            {"int", "x", "=", "(", "10", "+", "5", ")", "*", "2"}
        },
        
        // Test 20: String with numbers
        {
            "String containing numbers",
            "string code = \"abc123\"",
            {TokenType::STRINGTYPE, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::STRING},
            {"string", "code", "=", "abc123"}
        }
    };
    
    // Run all tests
    int passed = 0;
    int total = tests.size();
    
    for (size_t i = 0; i < tests.size(); i++) {
        if (runTest(tests[i], i + 1)) {
            passed++;
        }
    }
    
    // Summary
    cout << endl << "==================================" << endl;
    cout << "Results: " << passed << "/" << total << " tests passed" << endl;
    cout << "Accuracy: " << (100.0 * passed / total) << "%" << endl;
    
    if (passed == total) {
        cout << "🎉 All tests passed!" << endl;
    } else {
        cout << "⚠️  Some tests failed. Review output above." << endl;
    }
    
    return (passed == total) ? 0 : 1;
}
