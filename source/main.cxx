#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

// This function can generate a hexdump from the given input data, returning it in the form of a string.
std::string HexDump(const std::vector<uint8_t>& data) {
    std::stringstream buffer;
    std::string ascii_buffer;

    buffer << "Offset(h)   |01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|" << std::endl;
    buffer << std::string(8+4, ' ') << "|**|**|**|**|**|**|**|**|**|**|**|**|**|**|**|" << std::endl;

    for(std::size_t i=0; i<data.size(); ++i) {
        if(!(i % 15)) {
            const uintmax_t line_guide = (15 + 1) * (i / 15);
            buffer << std::setw(8);
            buffer << std::setfill('0');
            buffer << std::uppercase << std::hex << line_guide;
            buffer << std::string(4, ' ');
            buffer << "|";
        }

        buffer << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << static_cast<uint32_t>(data.at(i)) << '|';
        ascii_buffer.push_back((std::isspace(data.at(i)) || !std::isprint(data.at(i))) ? '.' : data.at(i));

        if(!((i+1) % 15)) {
            buffer << "    " << ascii_buffer << std::endl;
            ascii_buffer.clear();
        }

        if(i == data.size()-1 && ascii_buffer.size()) {
            uintmax_t highest_multiple = ((i / 15)*15) + 15;
            uintmax_t delta = highest_multiple - i;
            buffer << std::string((delta*2) + (delta-2), ' ') << "   " << ascii_buffer << std::endl;
            ascii_buffer.clear();
        }
    }

    return buffer.str();     
}

/*
* The main function in this program plays the role of acquiring the data that will
* be passed onto the HexDump function, either through reading a file specified
* via arguments, or by reading directly from stdin. Once the HexDump function
* is called, the result is printed to Stdout in the main function. */

int main(int argc, char** argv) {
    // This is a vector of bytes (8 bit ints) which will eventually store the target data to be hexdumped.
    std::vector<uint8_t> target_data;

    // Argument parsing loop.    
    for(std::size_t i=0; i<argc; ++i) {
        // Current argument as a string, for easier to read code.
        const std::string& argument(argv[i]);

        // If the file argument was specified, then proceed to read the file.
        if(argument == "-f" && i+1 < argc) {
            // Open a new input stream to the file.
            std::ifstream input_stream(argv[i+1], std::ios::binary);

            // If the stream is good, read the file into target_data, and close the stream.
            if(input_stream.good()) {
                target_data = std::vector<uint8_t>(
                    (std::istreambuf_iterator<char>(input_stream)),
                    (std::istreambuf_iterator<char>())  
                );
                
                input_stream.close();
            } else { // Otherwise print an error message to cerr, and return 1, exiting the program.
                std::cerr << "Could not open file \"" << argument << "\", stream wasn't good." << std::endl;
                return 1; 
            }
        }
    }

    // If the target_data vector is still empty, then read from stdin.
    if(!target_data.size()) {
        freopen(0, "rb", stdin); // Stdin has to be reopened in rb mode in order to accurately read bytes.

        // Reads the bytes from stdin into target_data.
        target_data = std::vector<uint8_t>(
            (std::istreambuf_iterator<char>(std::cin)),
            (std::istreambuf_iterator<char>())
        );
    }

    std::cout << HexDump(target_data) << std::endl;
    return 0;
}