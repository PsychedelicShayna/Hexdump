#include "headers/utils.hh"

bool ReadFile(std::string file_name, std::vector<uint8_t>* output) {
    std::ifstream input_stream(file_name, std::ios::binary);
    std::vector<uint8_t> input_stream_data;
    std::size_t input_stream_size;

    if(!input_stream.good()) {
        std::cout << "READFILE ERROR: The filestream isn't good for file \"" << file_name << "\"" << std::endl;
        return false;
    }
    
    try {
        input_stream.seekg(0, std::ifstream::end);
        input_stream_size = input_stream.tellg();
        input_stream.seekg(0, std::ifstream::beg);
    } catch(std::exception& exc) {
        std::cout << "READFILE EXCEPTION: Encountered exception \"" << exc.what() << "\" when evaluating file size." << std::endl;
        input_stream.close();
        return false; 
    }
    
    try {
        char input_stream_buffer[1];
        for(std::size_t i=0; i<input_stream_size; i++) {
            input_stream.read(input_stream_buffer, 1);
            input_stream_data.push_back((uint8_t)input_stream_buffer[0]);
        }
    } catch(std::exception& exc) {
        std::cout << "READFILE EXCEPTION: Encountered exception \"" << exc.what() << "\" when reading from file." << std::endl;
        return false;
    }
    
    input_stream.close();
    *output = input_stream_data;
    return true;
}

std::string PadString(std::string input_string, std::string pad_string, std::size_t pad_size, bool leftside=false) {
    std::string buffer = leftside ? std::string() : input_string;
    if(input_string.size() >= pad_size) return input_string;
    
    if(leftside) {
        while(buffer.size() < pad_size - input_string.size()) {
            buffer.append(pad_string);
        }
        
        buffer.append(input_string);
    } else {
        while(buffer.size() < pad_size) {
            buffer.append(pad_string);
        }
    }
    
    return buffer;
}