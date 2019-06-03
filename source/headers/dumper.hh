#ifndef DUMPER
#define DUMPER

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdint>

#include "utils.hh"

class Dumper {
public:
    /* Makes a raw hexadecimal string dump of the input data. */
    std::string RawDump(std::vector<int8_t>) const;
    
    /* Makes an ascii dump of the input data. */
    std::string AsciiDump(std::vector<int8_t>) const;
    
    /* Makes a formatted hexadecimal dump of the input data.  */
    std::string FormattedDump(std::vector<int8_t>) const;
};

#endif
