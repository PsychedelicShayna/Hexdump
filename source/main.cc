#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <ctime>

#include "headers/argproc.hh" // Argument processor class to process command line arguments.
#include "headers/dumper.hh" // Class that creates a dump of bianry data.

int main(int argc, char* argv[]) {
    freopen(0, "rb", stdin);
    ArgumentProcessor argProc(argc, argv);
    Dumper hexDumper = Dumper();
    
    std::vector<uint8_t> hexdump_input_data = std::vector<uint8_t>();

    if(argProc.supplied("-f")) {
        if(!argProc.hasValue("-f")) {
            std::cout << "The file argument must have a file specified along with it, e.g. -f=some_file.bin" << std::endl;
            std::cout << "For spaces within the file name, do \"-f=some file.bin\"" << std::endl;
            return 1;
        } else {
            std::string file_name = argProc.value("-f");
            if(!ReadFile(file_name, &hexdump_input_data)) {
                return 1;
            }
        }
    } else if(argProc.supplied("-t")) {
        if(!argProc.hasValue("-t")) {
            std::cout << "The text argument must have text specified along with it, e.g. -t=hello" << std::endl;
            std::cout << "For spaces within the text, do \"-t=Hello World\"" << std::endl;
            return 1;
        } else {
            std::string input_text = argProc.value("-t");
            hexdump_input_data = std::vector<uint8_t>(input_text.begin(), input_text.end());
        }    
    } else {
        std::vector<char> buffer_data (
            (std::istreambuf_iterator<char>(std::cin)),
            (std::istreambuf_iterator<char>())
        );
        
        hexdump_input_data = std::vector<uint8_t>(buffer_data.begin(), buffer_data.end());
    }
    
    if(argProc.supplied("-r")) {
        std::cout << hexDumper.RawDump(std::vector<int8_t>(hexdump_input_data.begin(), hexdump_input_data.end()));
    } else {
        std::cout << hexDumper.FormattedDump(std::vector<int8_t>(hexdump_input_data.begin(), hexdump_input_data.end()));
    }
    
    return 0;    
}
