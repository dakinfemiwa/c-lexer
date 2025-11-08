#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

std::vector<std::string> read_file(const std::string& filename);

std::vector<std::string> splitLines(std::string line);

#endif