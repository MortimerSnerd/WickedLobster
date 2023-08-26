// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
//#include "framework.h"

// A lot of standard stuff.  Sadly, need to avoid pulling Lobster and Wicked Engine
// headers into here, because they're both dumping float2, int2, etc definitions
// out into the global namespace, so they can not play nice together.  

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <csetjmp>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <array>
#include <type_traits>
#include <memory>
#include <optional>
#include <charconv>
#include <cinttypes>
#include <thread>
#include <future>
#include <sstream>
#include <iostream>
#include <iomanip>

#endif //PCH_H
