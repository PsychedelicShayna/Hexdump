#ifndef ARGUMENT_PROCESSOR
#define ARGUMENT_PROCESSOR

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

class ArgumentProcessor {
private:
    std::map<std::string, std::string>		argument_map_;
    std::vector<std::string>			argument_vec_;
    
    std::vector<std::string> splitString_(std::string, char, uint32_t) const;
    
public:
    bool supplied(std::string) const;
    bool hasValue(std::string) const;
    std::string value(std::string) const;
    
    ArgumentProcessor(int argc, char* argv[]);
};

#endif