#include "Dumper.h"

std::string HexDump::int_to_hex(uint32_t integer) const {
    std::stringstream conversion_stream; // Stream used to insert integer and extract hex.
    conversion_stream << std::hex; // Sets the stream to encode hex.
    conversion_stream << integer; // Adds the integer to the stream.
    
    std::string buffer; // Buffer for the stream output;
    conversion_stream >> buffer; // Extracts the output of the conversion stream, dumping it into the buffer.
    
    return buffer;
}

std::string HexDump::vec_to_hex(std::vector<int8_t> vec, std::string raw_sep="") {
    std::string buffer; // Buffer to store the hexadecimal characters.
    for(std::size_t i=0; i<vec.size(); i++) {
        int8_t ibyte = vec.at(i); // The current byte at the loop index.
        std::string ibyte_hex = int_to_hex((uint32_t)ibyte); // Converts the current byte into hex.
        buffer.append(ibyte_hex);
        if(raw_sep != "") buffer.append(raw_sep);
    }
    
    return buffer; // Returns the buffer with the hex encoded input string.
}

std::string HexDump::vec_to_ascii(std::vector<int8_t> vec)  {
    std::string buffer; // Buffer to store the ascii representation of the vector bytes.
    for(std::size_t i=0; i<vec.size(); i++) {
        int8_t ibyte = vec.at(i);
        int8_t char_to_add = '.';
        if(ibyte >= 32 && ibyte <= 126) char_to_add = vec.at(i);
        if(ibyte >= 161 && ibyte <= 255) char_to_add = vec.at(i);
        
        buffer.push_back(char_to_add);
    }
    return buffer;
}


std::string HexDump::render_vector(std::vector<std::string> vec) const {
    std::string buffer;
    
    for(uint32_t i=0; i<vec.size(); i++) {
        buffer.append(vec.at(i));
        buffer.append("\n");
    }
    
    return buffer;
}

std::string HexDump::uppercase(std::string target) const {
    std::string buffer;
    
    for(std::size_t i=0; i<target.size(); i++) {
        int8_t ichar = target.at(i);
        if(ichar >= 'a' && ichar <= 'z') {
            buffer.push_back(ichar - 32);
        } else {
            buffer.push_back(ichar);
        }
    }
    
    return buffer;
}

std::string HexDump::padstr(std::string target, std::string padding, uint32_t size, bool backwards=false) const {
    std::string buffer; // Buffer for constructing the padded string.
    
   if(!backwards) {
        buffer.append(target);
        while(buffer.size() < size) {
            buffer.append(padding);
        }
    } else {
        while((buffer.size() < size-target.size())) {
            buffer.append(padding);
        } buffer.append(target);    
    }
    return buffer;
}

std::string HexDump::dump(std::vector<int8_t> vec, FormatInfo fmt)  {
    std::vector<std::string> lines; // Contains each line of the hex dump.
    std::string vechex = vec_to_hex(vec, fmt.raw_s); // Converts the byte vector into a raw hex string.
    if(fmt.raw) return vechex;
    
    std::string vecasc = vec_to_ascii(vec); // Converts the byte vector into the ascii representation of the bytes.
    std::string line_buffer; // A buffer to build new lines.
    std::string a_line_buffer; // A buffer to build new ascii representations of the line_buffer;
    
    std::string horizontal_buffer; // Temporary buffer for creating the top horizontal offset line.
        
    for(uint32_t i=0; i<fmt.cPerLine/2; i++) {
        std::string ihex = uppercase(int_to_hex(i));
        horizontal_buffer.append(padstr(ihex, "0", 2, true));
        horizontal_buffer.append(" ");
    }
    
    std::string pad_builder; // Temporary string to build the padder.
    for(uint32_t i=0; i<fmt.cPadSize+3; i++) {
        pad_builder.push_back(fmt.cGroupSep);
    }
    
    horizontal_buffer = pad_builder + horizontal_buffer;
    
    if(fmt.ho) {
        lines.push_back(horizontal_buffer);
    }
    
    uint32_t ascii_index = 0;
    int32_t first_line_size = -1;
    
    for(uint32_t i=0; i<vechex.size(); i++) {
        int8_t ichar = vechex.at(i); // The current character at the loop index;
        
        // Performs this every cPerLines. E.g. every 32 characters, if cPerLine = 32.
        if(i % fmt.cPerLine == 0) {
            line_buffer = padstr(line_buffer, " ", round(horizontal_buffer.size()*1.3), false);
            
            //for(uint32_t i=0; i<first_line_size+5; i++) {
            //    line_buffer.push_back(' ');
            //}
            if(fmt.ascii) line_buffer.append(a_line_buffer)  ;          
            lines.push_back(line_buffer); // Appends the line buffer to the line list.
            
            line_buffer.clear(); // Clears the line buffer;
            a_line_buffer.clear(); // Clears the ascii line buffer.
                
            /* Adds the next vertical offset at the start of the new line */            
            if(fmt.vo) {
                uint32_t offset = (uint32_t)round(((double)i / (double)fmt.cPerLine/2l) * (double)fmt.cPerLine);
                std::string offset_str = int_to_hex(offset);
            
                offset_str = padstr(offset_str, "0", fmt.cPadSize, true);
                line_buffer.append(offset_str + "  ");
           }
        }
        
        if(i % fmt.cPerGroup == 0) {
            line_buffer.push_back(fmt.cGroupSep);
        }
        
        line_buffer.push_back(ichar);     
        if(i % 2) { 
           if(fmt.ascii) a_line_buffer.push_back(vecasc.at(ascii_index));
           ascii_index = (ascii_index+1) > vecasc.size()-1 ? ascii_index : ascii_index + 1;
        }
    }
    
    if(line_buffer.size() > 0) {
        line_buffer = padstr(line_buffer, " ", round(horizontal_buffer.size()*1.3), false);
    
        //if(first_line_size == -1) first_line_size = line_buffer.size();
        //for(uint32_t i=0; i<first_line_size+5; i++) {
        //    line_buffer.push_back(' ');
        //}
        
        if(fmt.ascii) line_buffer.append(a_line_buffer);
        lines.push_back(line_buffer);
    }
    
    return render_vector(lines);
}









