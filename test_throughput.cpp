#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include "./include/lexer.h"

using namespace std;
using namespace chrono;

struct BenchmarkResult {
    int totalTokens;
    long long durationMs;
    double tokensPerSecond;
    
    // Breakdown by type
    int keywords;
    int operators;
    int literals;
    int identifiers;
    int punctuation;
};

BenchmarkResult runBenchmark(const string& filename, const string& description) {
    cout << "Running: " << description << "..." << flush;
    
    auto start = high_resolution_clock::now();
    vector<Token> tokens = tokenize(filename);
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(end - start).count();
    
    BenchmarkResult result;
    result.totalTokens = tokens.size();
    result.durationMs = duration;
    result.tokensPerSecond = (duration > 0) ? (tokens.size() * 1000.0 / duration) : 0;
    
    // Categorize tokens
    result.keywords = 0;
    result.operators = 0;
    result.literals = 0;
    result.identifiers = 0;
    result.punctuation = 0;
    
    for (const auto& tok : tokens) {
        int type = tok.getTokenType();
        
        // Keywords: STRINGTYPE(4), INTTYPE(5), FLOATTYPE(6), BOOLTYPE(7)
        if (type >= 4 && type <= 7) {
            result.keywords++;
        }
        // Operators: EQ(9) through MOD(22), plus ASSIGN(15)
        else if ((type >= 9 && type <= 14) || type == 15 || (type >= 16 && type <= 22)) {
            result.operators++;
        }
        // Literals: STRING(0), INT(1), FLOAT(2), BOOL(3)
        else if (type >= 0 && type <= 3) {
            result.literals++;
        }
        // Identifier: IDENTIFIER(8)
        else if (type == 8) {
            result.identifiers++;
        }
        // Punctuation: SEMICOLON(18), LEFTBRACKET(25), RIGHTBRACKET(26)
        else if (type == 18 || type == 25 || type == 26) {
            result.punctuation++;
        }
    }
    
    cout << " Done!" << endl;
    return result;
}

void printResults(const string& name, const BenchmarkResult& result) {
    cout << "\n--- " << name << " ---" << endl;
    cout << "Total tokens:     " << result.totalTokens << endl;
    cout << "Time taken:       " << result.durationMs << " ms" << endl;
    cout << "Throughput:       " << fixed << setprecision(2) 
         << result.tokensPerSecond << " tokens/second" << endl;
    
    cout << "\nBreakdown:" << endl;
    cout << "  Keywords:       " << result.keywords 
         << " (" << (100.0 * result.keywords / result.totalTokens) << "%)" << endl;
    cout << "  Operators:      " << result.operators 
         << " (" << (100.0 * result.operators / result.totalTokens) << "%)" << endl;
    cout << "  Literals:       " << result.literals 
         << " (" << (100.0 * result.literals / result.totalTokens) << "%)" << endl;
    cout << "  Identifiers:    " << result.identifiers 
         << " (" << (100.0 * result.identifiers / result.totalTokens) << "%)" << endl;
    cout << "  Punctuation:    " << result.punctuation 
         << " (" << (100.0 * result.punctuation / result.totalTokens) << "%)" << endl;
}

void generateTestFile(const string& filename, int numLines) {
    ofstream file(filename);
    
    // Generate various types of statements
    for (int i = 0; i < numLines; i++) {
        int statementType = i % 5;
        
        switch (statementType) {
            case 0:  // Integer assignment
                file << "int var" << i << " = " << i << " ;\n";
                break;
            case 1:  // Float assignment
                file << "float pi" << i << " = 3.14 ;\n";
                break;
            case 2:  // String assignment
                file << "string msg" << i << " = \"test message " << i << "\" ;\n";
                break;
            case 3:  // Boolean expression
                file << "bool flag" << i << " = " << i << " == " << (i+1) << " ;\n";
                break;
            case 4:  // Arithmetic expression
                file << "int calc" << i << " = ( " << i << " + 10 ) * 2 ;\n";
                break;
        }
    }
    
    file.close();
}

int main() {
    cout << "=== A+ Lexer Throughput Benchmark ===" << endl << endl;
    
    // Create test files of different sizes
    cout << "Generating test files..." << endl;
    generateTestFile("./test/small_bench.ap", 100);
    generateTestFile("./test/medium_bench.ap", 1000);
    generateTestFile("./test/large_bench.ap", 10000);
    generateTestFile("./test/xlarge_bench.ap", 50000);
    cout << "Test files generated." << endl << endl;
    
    // Run benchmarks
    vector<pair<string, string>> benchmarks = {
        {"./test/small_bench.ap", "Small file (100 lines)"},
        {"./test/medium_bench.ap", "Medium file (1,000 lines)"},
        {"./test/large_bench.ap", "Large file (10,000 lines)"},
        {"./test/xlarge_bench.ap", "Extra Large file (50,000 lines)"}
    };
    
    vector<BenchmarkResult> results;
    
    for (const auto& bench : benchmarks) {
        results.push_back(runBenchmark(bench.first, bench.second));
    }
    
    // Print all results
    cout << "\n========================================" << endl;
    cout << "RESULTS" << endl;
    cout << "========================================" << endl;
    
    for (size_t i = 0; i < benchmarks.size(); i++) {
        printResults(benchmarks[i].second, results[i]);
    }
    
    // Summary comparison
    cout << "\n========================================" << endl;
    cout << "SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << left << setw(25) << "Test" 
         << right << setw(12) << "Tokens" 
         << setw(12) << "Time (ms)" 
         << setw(18) << "Tokens/sec" << endl;
    cout << string(67, '-') << endl;
    
    for (size_t i = 0; i < benchmarks.size(); i++) {
        cout << left << setw(25) << benchmarks[i].second
             << right << setw(12) << results[i].totalTokens
             << setw(12) << results[i].durationMs
             << setw(18) << fixed << setprecision(2) << results[i].tokensPerSecond
             << endl;
    }
    
    // Average throughput
    double avgThroughput = 0;
    for (const auto& result : results) {
        avgThroughput += result.tokensPerSecond;
    }
    avgThroughput /= results.size();
    
    cout << "\nAverage throughput: " << fixed << setprecision(2) 
         << avgThroughput << " tokens/second" << endl;
    
    return 0;
}
