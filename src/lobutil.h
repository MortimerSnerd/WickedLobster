#ifndef LOBUTIL_H
#define LOBUTIL_H
#include "lobster/vmdata.h"

struct lobster_options 
{
    std::string root_src = "main.lobster";
    int runtime_checks = lobster::RUNTIME_ASSERT;
    std::vector<std::string> program_args = {};
};

// Initializes lobster, compiling the main source file if necessary, and making
// it ready to call into.
std::string init_lobster(lobster_options &args);


#endif
