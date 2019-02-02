#include "headers/dumper.hh"

std::string Dumper::RawDump(std::vector<int8_t> data) const {
    std::stringstream buffer = std::stringstream();
    
    for(std::size_t i=0; i<data.size(); i++) {
        int8_t* ibyte = &data.at(i);
        buffer << std::uppercase << std::hex << (uint32_t)*ibyte;
    }
    
    std::string buffer_output;
    buffer >> buffer_output;
    
    return buffer_output;
}

std::string Dumper::AsciiDump(std::vector<int8_t> data) const {
    std::string buffer = std::string();
    
    for(std::size_t i=0; i<data.size(); i++) {
        int8_t* ibyte = &data.at(i);
        if((*ibyte >= 33 && *ibyte <= 126)) buffer.push_back(*ibyte);
        else buffer.push_back('.');
    }

    return buffer;
}

std::string Dumper::FormattedDump(std::vector<int8_t> data) const {
    std::vector<std::string> formatted_lines;
    
    std::string data_hexadecimal = RawDump(data);
    std::string data_ascii = AsciiDump(data);
    
    std::string formatted_line_buffer_hex;
    std::string formatted_line_buffer_asc;
    
    std::string horizontal_offset_line;
    
    for(std::size_t i=0; i<16; i++) {
        std::stringstream conv_buffer = std::stringstream();
        std::string i_as_hex = std::string();
        
        conv_buffer << std::uppercase << std::hex <<  i;
        conv_buffer >> i_as_hex;
        conv_buffer.clear();
        
        std::string buffer = std::string();
        buffer.append(PadString(i_as_hex, "0", 2, true));
        buffer.append(" ");
        horizontal_offset_line.append(buffer);
    }
    
    horizontal_offset_line = PadString(horizontal_offset_line, " ", 10, true);
    horizontal_offset_line = "Offset(h)  " + horizontal_offset_line + "\n";
    
    formatted_lines.push_back(horizontal_offset_line);
    
    uint32_t data_ascii_index = 0;
    
    uint32_t current_line_offset = 0;
        
    for(std::size_t i=0; i<data_hexadecimal.size(); i++) {
        char* ichar = &data_hexadecimal.at(i);
        
        if((i % 32) == 0 && i != 0) {
            formatted_line_buffer_hex = PadString(formatted_line_buffer_hex, " ", round(horizontal_offset_line.size()*0.9), false);
            formatted_line_buffer_hex.append(formatted_line_buffer_asc);
            
            std::stringstream conversion_buffer = std::stringstream();
            std::string current_line_offset_hex;
            
            conversion_buffer << std::hex;
            conversion_buffer << std::uppercase;
            conversion_buffer << current_line_offset;
            conversion_buffer >> current_line_offset_hex;
            
            current_line_offset_hex = PadString(current_line_offset_hex, "0", 8, true) + "  ";
            formatted_line_buffer_hex = current_line_offset_hex + formatted_line_buffer_hex;
        
            formatted_lines.push_back(formatted_line_buffer_hex);
            
            formatted_line_buffer_hex.clear();
            formatted_line_buffer_asc.clear();
            current_line_offset = i/2;
        }
        
        if(!(i % 2)) {
            formatted_line_buffer_asc.push_back(data_ascii.at(data_ascii_index));
            if((data_ascii_index + 1) < data_ascii.size()) data_ascii_index++;
            formatted_line_buffer_hex.push_back(' ');
        }
        
        formatted_line_buffer_hex.push_back(*ichar);
    }
    
    if(formatted_line_buffer_hex.size() > 0) {
        formatted_line_buffer_hex = PadString(formatted_line_buffer_hex, " ", round(horizontal_offset_line.size()*0.9), false);
        formatted_line_buffer_hex.append(formatted_line_buffer_asc);
        
        std::stringstream conversion_buffer = std::stringstream();
        std::string current_line_offset_hex;
            
        conversion_buffer << std::hex;
        conversion_buffer << std::uppercase;
        conversion_buffer << current_line_offset;
        conversion_buffer >> current_line_offset_hex;
            
        current_line_offset_hex = PadString(current_line_offset_hex, "0", 8, true) + "  ";
        formatted_line_buffer_hex = current_line_offset_hex + formatted_line_buffer_hex;
        
        formatted_lines.push_back(formatted_line_buffer_hex);  
        
        formatted_line_buffer_hex.clear();
        formatted_line_buffer_asc.clear();
        
    }
    
    std::string buffer = std::string();
    
    for(std::size_t i=0; i<formatted_lines.size(); i++) {
        std::string* line = &formatted_lines.at(i);
        buffer.append(*line);
        buffer.push_back('\n');
    }
    
    return buffer;
}