#ifndef LOBUTIL_H
#define LOBUTIL_H

struct lobster_options 
{
    std::string root_src = "main.lobster";
    std::vector<std::string> program_args = {};
};

// Tags for wicked objects we may keep references to.
enum WOKIND {
    WK_SCENE, WK_ENTITY
};

// A handle for a wicked object that can be passed in and out of lobster as an int2.
struct wo_handle
{
    int kind;       // WOKIND, or -WOKIND if it is an invalid handle of that kind.
    int64_t name;   // Unique id or array index for the object.
};

// Initializes lobster, compiling the main source file if necessary, and making
// it ready to call into.
std::string run_lobster(lobster_options &args, std::function<void()> main);

// Dumps a lobster stack to stdout.
void dump_lobster_stack();

// Called at the beginning of each frame.
void lobster_begin_frame();

#endif
