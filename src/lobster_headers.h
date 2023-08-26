#ifndef LOBSTER_HEADERS_H
#define LOBSTER_HEADERS_H

// All of the headers needed for lobster.  A little complicated, and you can't
// include this in any unit that includes wicked headers.  This does open some
// namespaces, so beware.
using namespace std;

#include "gsl/gsl-lite.hpp"

using gsl::span;

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/flexbuffers.h"

#include "lobster/wentropy.h"
#include "lobster/tools.h"
#include "lobster/dllist.h"
#include "lobster/rng_hash.h"
#include "lobster/string_tools.h"
#include "lobster/accumulator.h"
#include "lobster/resource_manager.h"
#include "lobster/small_vector.h"
#include "lobster/packed_vector.h"
#include "lobster/varint.h"

#include "lobster/platform.h"
#include "lobster/slaballoc.h"
#include "lobster/geom.h"
#include "lobster/unicode.h"

using namespace geom;

#ifndef VM_JIT_MODE
    #if defined(BUILD_CONTEXT_compiled_lobster) || \
        defined(__IOS__) || \
        defined(__ANDROID__) || \
        defined(__EMSCRIPTEN__)
        #define VM_JIT_MODE 0
    #else
        #define VM_JIT_MODE 1
    #endif
#endif
#define LOBSTER_ENGINE 0

#endif


