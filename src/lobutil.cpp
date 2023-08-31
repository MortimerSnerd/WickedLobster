// Lobster initialization and utility functions.
#include "pch.h"
#include "lobutil.h"
#include "wiMath.h"
#include "wibindings.h"

#include "lobster_headers.h"
#include "lobster/compiler.h"
#include "lobster/natreg.h"
#include "lobster/vmdata.h"

extern void break_impl();

using namespace std;

namespace {
    lobster::NativeRegistry nfr;

    // The function that's the C++ main loop.  This function is live
    // as long as the game is running, and gets set by init.
    // A little confusing, but the call stack will be :
    // init_lobster -> Compile/RunTCC -> wi_start_game(lobster fn) -> main_loop.
    function<void()> main_loop(nullptr);

    lobster::VM *active_vm = nullptr;


    // Dummy function so we don't have null function pointers.
    void lob_do_nothing(lobster::VM &, lobster::StackPtr)
    {
    }

    // Called by Application::FixedUpdate at...fixed intervals.
    lobster::Value app_fixed_update(lob_do_nothing);
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
    break_impl();
    return "";
}

extern "C" void GLFrame(lobster::StackPtr, lobster::VM &) 
{
}

namespace
{
    using namespace DirectX;
    void push_wo_iterator(lobster::StackPtr &sp, wo_iterator h)
    {
        PushVec(sp, int2{h.kind, h.ix});
    }

    wo_iterator pop_wo_iterator(lobster::StackPtr &sp)
    {
        auto i2 = PopVec<int2>(sp);
        return {i2[0], i2[1]};
    }

    void push_wo_handle(lobster::StackPtr &sp, wo_handle h)
    {
        PushVec(sp, iint2{(iint)h.kind, h.name});
    }

    wo_handle pop_wo_handle(lobster::StackPtr &sp)
    {
        auto i2 = PopVec<iint2>(sp);
        return {(int)i2[0], i2[1]};
    }

    void push_xmfloat2(lobster::StackPtr &sp, XMFLOAT2 const &v)
    {
        float2 lv = {v.x, v.y};
        PushVec(sp, lv);

    }

    void pop_xmfloat2(lobster::StackPtr &sp, XMFLOAT2 &dest)
    {
        auto f = PopVec<geom::float2>(sp);
        dest.x = f.x;
        dest.y = f.y;
    }

    void push_xmfloat3(lobster::StackPtr &sp, XMFLOAT3 const &v)
    {
        float3 lv = {v.x, v.y, v.z};
        PushVec(sp, lv);

    }

    void pop_xmfloat3(lobster::StackPtr &sp, XMFLOAT3 &dest)
    {
        auto f3 = PopVec<geom::float3>(sp);
        dest.x = f3.x;
        dest.y = f3.y;
        dest.z = f3.z;
    }

    void push_xmfloat4(lobster::StackPtr &sp, XMFLOAT4 const &v)
    {
        float4 lv = {v.x, v.y, v.z, v.w};
        PushVec(sp, lv);

    }

    void pop_xmfloat4(lobster::StackPtr &sp, XMFLOAT4 &dest)
    {
        auto f3 = PopVec<geom::float4>(sp);
        dest.x = f3.x;
        dest.y = f3.y;
        dest.z = f3.z;
        dest.w = f3.w; 
    }
}


void add_wl_builtins(lobster::NativeRegistry &anfr)
{
    using namespace lobster;
    anfr("wi_start_game", "", "", "",
         "The lobster code should call this to start the game after any "
         "wanted function callbacks are set up.",
        [](StackPtr &, VM &) {
            main_loop();
            return NilVal();
    });

    anfr("wi_set_app_fixed_frame_fn", "f", "L", "",
         "Sets the function that gets called at the beginning of the frame.",
        [](StackPtr &, VM &vm, Value &f) {
            assert(f.type >= lobster::V_FUNCTION);
            app_fixed_update = f;
            active_vm = &vm;
            return NilVal();
    });

    anfr("breakpoint", "", "", "",
         "Requests debugging breakpoint from native debugger",
        [](StackPtr &, VM &) {
            break_impl();
    });

    // Get generated boilerplate bindings generated by tools/bindgen.lobster
    #include "lobutil.inl"

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

void lobster_fixed_update()
{
    active_vm->CallFunctionValue(app_fixed_update);
}

void dump_lobster_stack()
{
    //TODO
    printf("LOBSTER STACK GOES HERE\n");
}
