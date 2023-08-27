// Lobster initialization and utility functions.
#include "pch.h"
#include "lobutil.h"
#include "wibindings.h"

#include "lobster_headers.h"
#include "lobster/compiler.h"
#include "lobster/natreg.h"
#include "lobster/vmdata.h"

using namespace std;

namespace {
    lobster::NativeRegistry nfr;

    // The function that's the C++ main loop.  This function is live
    // as long as the game is running, and gets set by init.
    // A little confusing, but the call stack will be :
    // init_lobster -> Compile/RunTCC -> wi_start_game(lobster fn) -> main_loop.
    function<void()> main_loop(nullptr);

    lobster::VM *active_vm = nullptr;



    void lob_do_nothing(lobster::VM &, lobster::StackPtr)
    {
    }

    // Called at the beginning of a frame.
    lobster::Value frame_begin_fn(lob_do_nothing);
}

// Some stubs we need to make since LOBSTER_ENGINE=0
namespace lobster {
    FileLoader EnginePreInit(NativeRegistry &anfr) {
        anfr.DoneRegistering();
        return DefaultLoadFile;
    }
}

string BreakPoint(lobster::VM &, string_view reason) {
    //TODO: how to handle this when we don't have the imgui debugger?
    auto cstr = reason.data();
    printf("BREAKPOINT called: %s\n", cstr ? cstr : "<null>");
    return "";
}

extern "C" void GLFrame(lobster::StackPtr, lobster::VM &) 
{
}

namespace
{
    void push_wo_handle(lobster::StackPtr &sp, wo_handle h)
    {
        PushVec(sp, iint2{(iint)h.kind, h.name});
    }

    wo_handle pop_wo_handle(lobster::StackPtr &sp)
    {
        auto i2 = PopVec<iint2>(sp);
        return {(int)i2[0], i2[1]};
    }
}


void add_wl_builtins(lobster::NativeRegistry &anfr)
{
    using namespace lobster;
    anfr("wl_test", "", "", "I",
        "Test binding just to make sure we can compile a binding",
        [](StackPtr &, VM &) {
            return Value(12);
    });

    anfr("wi_start_game", "", "", "",
         "The lobster code should call this to start the game after any "
         "wanted function callbacks are set up.",
        [](StackPtr &, VM &) {
            main_loop();
            return NilVal();
    });

    anfr("wi_set_begin_frame_fn", "f", "L", "",
         "Sets the function that gets called at the beginning of the frame.",
        [](StackPtr &, VM &vm, Value &f) {
            assert(f.type >= lobster::V_FUNCTION);
            frame_begin_fn = f;
            active_vm = &vm;
            return NilVal();
    });

    anfr("wi_new_scene", "", "", "I}:2",
         "Creates a new empty scene and returns the handle for it.",
        [](StackPtr &sp, VM &) {
            push_wo_handle(sp, wbnd::new_scene());
    });

    anfr("wi_global_scene", "", "", "I}:2",
         "Returns the handle for the global scene.",
        [](StackPtr &sp, VM &) {
            push_wo_handle(sp, wbnd::global_scene());
    });

    anfr("wi_load_model", "scene,fname,attach_to_entity", "I}:2SB", "I}:2",
         "Loads model in fname into the given scene.  Returns"
         " the entity handle.",
        [](StackPtr &sp, VM &) {
            auto attach = Pop(sp).True();
            auto fname = Pop(sp);
            auto scene = pop_wo_handle(sp);
            push_wo_handle(sp, wbnd::load_model(scene,
                                                string(fname.sval()->strv()),
                                                attach));
    });

    anfr("wi_create_entity", "", "", "I}:2",
         "Creates an entity and returns the handle",
        [](StackPtr &sp, VM &) {
            push_wo_handle(sp, wbnd::create_entity());
    });

    anfr("wi_create_name_component", "scene,entity", "I}:2I}:2", "I}:2",
         "Creates a name component on the given entity.",
         [](StackPtr &sp, VM &){
        auto ent = pop_wo_handle(sp);
        auto scene = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::create_entity_name_component(scene, ent));
    });

    anfr("wi_nc_set_name", "name_comp,name", "I}:2S", "",
         "Sets the name for the given name component handle.",
        [](StackPtr &sp, VM &) {
            auto name = Pop(sp).sval()->strv();
            auto comp = pop_wo_handle(sp);
            wbnd::nc_set_name(comp, name);
    });

    anfr("wi_entity_find_by_name", "scene,name,ancestor_ent", "I}:2SI}:2", "I}:2",
         "Finds an entity by name in the given scene. Returns invalid entity if not found",
        [](StackPtr &sp, VM &) {
            auto ancestor = pop_wo_handle(sp);
            auto name     = Pop(sp).sval()->strv();
            auto scene    = pop_wo_handle(sp);
            push_wo_handle(sp, wbnd::entity_find_by_name(scene, name, ancestor));
    });

    anfr("wi_log", "level,msg", "IS", "",
         "Logs to WickedEnine backlog with the given wi::backlog::LogLevel",
        [](StackPtr &, VM &, Value &level, Value &msg) {
            wbnd::backlog((int)level.ival(), msg.sval()->strv());
            return NilVal();
    });
}

string run_lobster(lobster_options &args, function<void()> main)
{
    // Set this so it will be ready when the lobster code calls back into 
    main_loop = main;
    try {
        // For simplicity, at first only jit the code every time we start.
        // We can probably make a separate tool to make lobster compilation to 
        // c++ easier to integrate in the build later.
        //
        // This function of course owes much to Lobster's main.cpp
        RegisterCoreLanguageBuiltins(nfr);
        lobster::RegisterBuiltin(nfr, "wicked_lobster", add_wl_builtins);
        auto loader = lobster::EnginePreInit(nfr);

        // We expect the current directory to be gamedir, with a "modules" and
        // "data" directory underneath it.  These will be populated by scripts from 
        // whereever Lobster is installed on the system.  (that's a TODO)
        if (!InitPlatform(".", "", false, loader)) {
            return "Could not find location to read/write data on this platform!";
        }

        string bytecode_buffer;
        string_view src;
        string error_msg; 
        #if _DEBUG
        auto checks = lobster::RUNTIME_ASSERT_PLUS;
        #else
        auto checks = lobster::RUNTIME_ASSERT;
        #endif

        AddDataDir(".");
        AddDataDir("src");
        lobster::Compile(nfr, args.root_src, src, bytecode_buffer, nullptr, nullptr,
                         false, checks, nullptr, 10, true);
        lobster::RunTCC(nfr,
                        bytecode_buffer,
                        args.root_src,
                        nullptr,
                        move(args.program_args),
                        lobster::TraceMode::OFF,
                        false,
                        error_msg,
                        checks,
                        false);
        if (!error_msg.empty()) {
            return error_msg;
        }
    } catch (string const& err) {
        return err;
    }
    return "";

}

void lobster_begin_frame()
{
    active_vm->CallFunctionValue(frame_begin_fn);
}

void dump_lobster_stack()
{
    //TODO
    printf("LOBSTER STACK GOES HERE\n");
}
