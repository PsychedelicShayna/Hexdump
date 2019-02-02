#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <ctime>

#include "headers/argproc.hh" // Argument processor class to process command line arguments.
#include "headers/dumper.hh" // Class that creates a dump of bianry data.

/*
    HexDump Input Modes --
    default: Reads from STDIN
    -f=(filepath) The input file.
    -t=(text) Text to hexdump.
        
    HexDump Output Modes -- 
    default: Writes to STDOUT
    -o=(filepath) The output file.
    
    HexDump Format Modes --
    -w=(number) The amount of bytes per line. 
    -a=(boolean) Show or hide ascii representation (default=1).
    -gh=(boolean) Show or hide the horizontal byte grouping (default=1).
    -gv=(boolean) Show or hide the vertical byte grouping (default=1).
    -gb=(number) The amount of bytes per byte grouping (default=1).
    -r=(boolean) Dump a raw string of unformatted, pure hex.
    -rs=(string) The byte separator used for the raw dump (default=none)
    -gc=(string) The separator for byte groupings.
    -vp(number) The amount of vertical padding.
*/

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

#ifdef OLD
int main(int argc, char* argv[]) {    
    srand(unix_timestamp()); // Seeds rand() with the unix epoch timestamp.
    ArgumentProcessor argproc(argv, argc); // Processes command line arguments.
    HexDump hexDump = HexDump(); 
    FormatInfo formatInfo = FormatInfo(); // 
    // This is the byte vector that will eventually be fed into the dumper.
    std::vector<int8_t> hexdump_input_data;
    
    /* This section checks for */
    if(argproc.argument_supplied("-f")) {
        #ifdef FileLoad
        if(argproc.argument_value("-f") == "") {
            std::cout << "Please supply a valid file path." << std::endl;
            return 1;
        }
        
        std::string file_name = argproc.argument_value("-f");
        std::string file_data;
        read_file(file_name, &file_data);
        std::vector<int8_t> data = std::vector<int8_t>(file_data.begin(), file_data.end());
        hexdump_input_data = data;
        #endif
    } else if(argproc.argument_supplied("-t")) {
        std::cout << "Yes" << std::endl;
        if(argproc.argument_value("-t") == "") {
            std::cout << "Please supply some text" << std::endl;
            return 1;
        }
        
        std::string data = argproc.argument_value("-t");
        hexdump_input_data = std::vector<int8_t>(data.begin(), data.end());
    }  else {
        freopen(0, "rb", stdin);
        std::string stdin_data((std::istreambuf_iterator<char>(std::cin)), (std::istreambuf_iterator<char>()));
        hexdump_input_data = std::vector<int8_t>(stdin_data.begin(), stdin_data.end());    
    }
   
   
    
    if(argproc.argument_supplied("-vp")) {
        if(argproc.argument_value("-vp") == "") {
            std::cout << "Please supply a valid number" << std::endl;
            return 1;
        }
        try { uint32_t value = std::stoi(argproc.argument_value("-vp")); formatInfo.cPadSize = value; }
        catch(std::exception& exc) {std::cout << "Invalid number" << std::endl;}
    }    
    
    if(argproc.argument_supplied("-gc")) {
        if(argproc.argument_value("-gc") == "") {
            std::cout << "Please supply valid text." << std::endl;
            return 1;
        }
        else if (argproc.argument_value("-gc").size() > 1) {
            std::cout << "The separator is too big. Must be a single character." << std::endl;
            return 1;
        }
        
        formatInfo.cGroupSep = argproc.argument_value("-gc").at(0);
    }
    
    if(argproc.argument_supplied("-rs")) {
        if(argproc.argument_value("-rs") == "") std::cout << "Please supply valid text." << std::endl;
        formatInfo.raw_s = argproc.argument_value("-rs");
    }
    
    if(argproc.argument_supplied("-r")) {
        if(argproc.argument_value("-r") == "") std::cout << "Please supply a valid boolean." << std::endl;
        try { bool rawh = (bool)std::stoi(argproc.argument_value("-r")); formatInfo.raw = rawh; }
        catch (std::exception& exc) {std::cout << "Invalid boolean.  \'" << argproc.argument_value("-r") << "\"" << std::endl; return 1; }
    }
    
    if(argproc.argument_supplied("-gb")) {
        if(argproc.argument_value("-gb") == "") std::cout << "Please supply a valid number." << std::endl;
        try { bool cpl = std::stoi(argproc.argument_value("-gb")); formatInfo.cPerGroup = cpl; }
        catch (std::exception& exc) {std::cout << "Invalid number  \'" << argproc.argument_value("-gb") << "\"" << std::endl; return 1; }
    }
    
    if(argproc.argument_supplied("-w")) {
        if(argproc.argument_value("-w") == "") std::cout << "Please supply a valid number" << std::endl;
        try { uint32_t bpl = std::stoi(argproc.argument_value("-w")); formatInfo.cPerLine = bpl; }
        catch (std::exception& exc) {std::cout << "Invalid number \'" << argproc.argument_value("-w") << "\"" << std::endl; return 1; }
    }

    if(argproc.argument_supplied("-a")) {
        if(argproc.argument_value("-a") == "") std::cout << "Please supply a valid boolean." << std::endl;
        try { bool ascii = (bool)std::stoi(argproc.argument_value("-a")); formatInfo.ascii = ascii; }
        catch (std::exception& exc) {std::cout << "Invalid boolean \'" << argproc.argument_value("-a") << "\"" << std::endl; return 1; }
    }
    
    if(argproc.argument_supplied("-gh")) {
        if(argproc.argument_value("-gh") == "") std::cout << "Please supply a valid boolean." << std::endl;
        try { bool ghtoggle = (bool)std::stoi(argproc.argument_value("-gh")); formatInfo.ho = ghtoggle; }
        catch (std::exception& exc) {std::cout << "Invalid boolean \'" << argproc.argument_value("-gh") << "\"" << std::endl; return 1; }
    }
    
    
    if(argproc.argument_supplied("-gv")) {
        if(argproc.argument_value("-gv") == "") std::cout << "Please supply a valid boolean." << std::endl;
        try { bool gvtoggle = (bool)std::stoi(argproc.argument_value("-gv")); formatInfo.vo = gvtoggle; }
        catch (std::exception& exc) {std::cout << "Invalid boolean \'" << argproc.argument_value("-gv") << "\"" << std::endl; return 1; }
    }
    

    HexDump hexDump;
    std::string output = hexDump.dump(hexdump_input_data, formatInfo);    
    
    std::cout << output;
    
    return 0;
}

#endif