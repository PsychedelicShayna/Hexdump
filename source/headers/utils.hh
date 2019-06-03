#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

bool ReadFile(std::string, std::vector<uint8_t>*);
std::string PadString(std::string, std::string, std::size_t, bool);

#endif

