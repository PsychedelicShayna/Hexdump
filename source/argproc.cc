#include "headers/argproc.hh"

std::vector<std::string> ArgumentProcessor::splitString_(std::string string, char splitter, uint32_t threshold) const {
    std::vector<std::string> split_buffer = std::vector<std::string>();
    std::string entry_buffer = std::string();
    
    bool skip = false;
    for(std::size_t i=0; i<string.size(); i++) {
        char* ichar = &string.at(i);
        
        if(*ichar == splitter && i != string.size()-1 && (split_buffer.size()+1) >= threshold && !skip) {
            split_buffer.push_back(entry_buffer);
            entry_buffer.clear();
            skip = true;            
        }
        
        if(skip) {
            split_buffer.at(split_buffer.size()-1).push_back(*ichar);
            continue;
        }
        
        if(*ichar == splitter) {
            split_buffer.push_back(entry_buffer);
            entry_buffer.clear();
        } else {
            entry_buffer.push_back(*ichar);
        }
    }
    
    if(entry_buffer.size() > 0) {
        split_buffer.push_back(entry_buffer);
        entry_buffer.clear();
    }
    
    return split_buffer;
}

bool ArgumentProcessor::supplied(std::string argument) const {
    return (std::find(argument_vec_.begin(), argument_vec_.end(), argument) != argument_vec_.end());
}

bool ArgumentProcessor::hasValue(std::string argument) const {
    return (argument_map_.find(argument) != argument_map_.end());
}

std::string ArgumentProcessor::value(std::string argument) const {
    return argument_map_.at(argument);
}

ArgumentProcessor::ArgumentProcessor(int argc, char* argv[]) {
    for(std::size_t i=0; i<argc; i++) {
        std::string argument = std::string(argv[i]);
        
        std::vector<std::string> argument_split = splitString_(argument, '=', 2);
        argument_vec_.push_back(argument_split.at(0));
                
        if(argument_split.size() > 1) {
            std::string key = argument_split.at(0);
            std::string value = argument_split.at(1);
            argument_map_.insert(std::pair<std::string, std::string>(key, value));
        } 
    }
}