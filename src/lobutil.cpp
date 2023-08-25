// Lobster initialization and utility functions.
#include "pch.h"
#include "lobster/compiler.h"
#include "lobster/natreg.h"
#include "lobster/vmdata.h"

namespace {
    lobster::NativeRegistry nfr;
}

// Some stubs we need to make since LOBSTER_ENGINE=0
namespace lobster {
    FileLoader EnginePreInit(NativeRegistry &anfr) {
        anfr.DoneRegistering();
        return DefaultLoadFile;
    }
}

std::string BreakPoint(lobster::VM &, string_view reason) {
    //TODO: how to handle this when we don't have the imgui debugger?
    auto cstr = reason.data();
    printf("BREAKPOINT called: %s\n", cstr ? cstr : "<null>");
    return "";
}

extern "C" void GLFrame(lobster::StackPtr, lobster::VM &) 
{
}


void add_wl_builtins(lobster::NativeRegistry &anfr)
{
    using namespace lobster;
    anfr("wl_test", "", "", "I",
        "Test binding just to make sure we can compile a binding",
        [](StackPtr &, VM &) {
            return Value(12);
    });
}


std::string init_lobster(lobster_options& args)
{
    try {
        // For simplicity, at first only jit the code every time we start.
        // We can probably make a separate tool to make lobster compilation to 
        // c++ easier to integrate in the build later.
        //
        // This function of course owes much to Lobster's main.cpp
        RegisterCoreLanguageBuiltins(nfr);
        lobster::RegisterBuiltin(nfr, "wicked_lobster", add_wl_builtins);
        auto loader = lobster::EnginePreInit(nfr);

        // We expect the current directory to be gamedir\src, with a "modules" and
        // "data" directory underneath it.  These will be populated by scripts from 
        // whereever Lobster is installed on the system.  (that's a TODO)
        if (!InitPlatform(".", args.root_src, false, loader)) {
            return "Could not find location to read/write data on this platform!";
        }

        std::string bytecode_buffer;
        std::string_view src;
        std::string error_msg; 

        lobster::Compile(nfr, args.root_src, src, bytecode_buffer, nullptr, nullptr,
                         false, args.runtime_checks, nullptr, 10, true);
        lobster::RunTCC(nfr,
                        bytecode_buffer,
                        args.root_src,
                        nullptr,
                        std::move(args.program_args),
                        lobster::TraceMode::OFF,
                        false,
                        error_msg,
                        args.runtime_checks,
                        false);
        if (!error_msg.empty()) {
            return error_msg;
        }
    } catch (std::string const& err) {
        return err;
    }
    return "";

}


