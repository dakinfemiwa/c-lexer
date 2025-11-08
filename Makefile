CXX = g++
CXXFLAGS = -std=c++17 -I.

SOURCES = main.cpp src/lexer.cpp src/util/token.cpp src/util/file_read.cpp
LIB_SOURCES = src/lexer.cpp src/util/token.cpp src/util/file_read.cpp
TARGET = compiler

all: $(TARGET)

$(TARGET) : $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test-accuracy: test_accuracy.cpp $(LIB_SOURCES)
	$(CXX) $(CXXFLAGS) test_accuracy.cpp $(LIB_SOURCES) -o test_accuracy
	./test_accuracy

test-throughput: test_throughput.cpp $(LIB_SOURCES)
	$(CXX) $(CXXFLAGS) test_throughput.cpp $(LIB_SOURCES) -o test_throughput
	./test_throughput

test: test-accuracy test-throughput

clean:
	rm -f $(TARGET) test_accuracy test_throughput
	rm -f ./test/temp_test.ap ./test/*_bench.ap

run: $(TARGET)
	./$(TARGET)AGS = -std=c++17 -I.

SOURCES = main.cpp src/lexer.cpp src/util/token.cpp src/util/file_read.cpp
TARGET = compiler

all: $(TARGET)

$(TARGET) : $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	 ./$(TARGET)