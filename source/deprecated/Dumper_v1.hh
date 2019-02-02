#ifndef DUMPER
#define DUMPER

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

struct FormatInfo {
    uint16_t	cPerLine;  // Characters per line.
    uint16_t	cPerGroup; // Characters in every character grouping.
    int8_t	cGroupSep; // Character grouping separator.
    int8_t 	cPadSize;  // The amount of padding to add to the vertical offset bar.

    bool	vo; // Enable/Disable vertical offsets. (Default: Enabled)
    bool	ho; // Enable/Dsiable horizontal offsets. (Defaul: Enabled);    
    bool	ascii; // Enable/Disable ascii representation of bytes.    
    bool	raw; // Whether or not to dump raw hex (Default: false)
    std::string raw_s; // The raw separator string.
    
    FormatInfo() {
        cPerLine = 32;
        cPerGroup = 2;
        cGroupSep = ' ';
        cPadSize = 8;
        ascii = true;
        vo = true;
        ho = true;
        raw = false;
        raw_s = "";
    }
};

class HexDump {
public:
    std::string int_to_hex(uint32_t) const;
    std::string str_to_hex(std::string);
    std::string vec_to_hex(std::vector<int8_t>, std::string);
    
    std::string vec_to_ascii(std::vector<int8_t>);
    
    std::string render_vector(std::vector<std::string>) const;
    std::string uppercase(std::string) const;
     
    std::string padstr(std::string, std::string, uint32_t, bool) const;
    
    // Dumps data as a hexdump string.
    std::string dump(std::vector<int8_t>, FormatInfo) ;
};

#endif
