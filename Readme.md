# Summary
Project integrating the [Lobster Language](https://github.com/aardappel/lobster) with the [Wicked Engine](https://github.com/turanszkij/WickedEngine).

I enjoy the lobster language. The language is small and powerful, the
implementation is fast, and the builtin engine 
is easy to use for 2d. Doing 3d is certainly possible, but does require 
more heavy lifting to implement. I've experimented with loading existing 
simple formats, like Quake 2 BSP, and concluded it requires more work than
I have spare time for.

Looking around at the 3d engine landscape, I considered Wicked Engine a good 
choice for doing anything that needs to be 3d.  It looks great, has a pretty
clean C++ API, the Lua integration is very helpful, but I do miss working in Lobster.  

Looking at their codebases, I've gotten the idea that it should be possible to 
build a project that integrates the two without requiring changes to either 
project.  This is largely possible because Lobster has an option to just compile
the language code as a library, without the engine part.  And Wicked Engine 
produces a library as well.  

Once C++ side of the project is compiled, it should be able to load and execute
Lobster code without further trips to the C++ compiler when Lobster is run in JIT
mode.  

The binding will be for a subset of the Wicked Engine API.  The goal is not to 
be able to do everything from Lobster, but to be able to handle game logic
and orchestration from Lobster, and leave the heavier setup and things that
require sub-classing to the C++ side.

# Caveat
This is still exploratory and not remotely usable by anyone else yet. 

# Structure
This is still exploratory stage, so Windows only with me editing a Visual Studio
project to set things up.  This seems like an ideal candidate for a CMake setup, but
I'm going to defer going down that road until I make sure there aren't more
fundamental problems with the project itself.

How I expect this two work:  The Lobster and Wicked Engine repositories will 
live off in their own directories.  There are build system variables that can be set
to the locations of these two repos so the build can locate library and include
directories.  (Currently: User Defined Macros for the Visual Studio project)

Both Lobster and Wicked Engine have expectations on where to find resources
when they are run.  There will be a script that can build a deployment directory
by copying over what is needed in the correct structure.

Initially, I'm just going to make some hand bindings as I feel out how
practical this will be, but binding by hand is tedious and error prone. There
should be some sort of script that can generate bindings for the majority 
of the Wicked Engine API, hopefully leaving only a few special cases that
require manual bindings.

On the Lobster side, initially it's just going to Jit the code on startup.  
Being able to use the generated C++ for Lobster is desirable for a final
bit of performance gain, and will require some more investigation on how to 
integrate that with the build in a non-hacky way.

# oof - bad things and reminders
- had to change wicked engine lib to use multithreaded runtime (not mt dll), and
- add a preprocessor to set ITERATOR_DEBUG_LEVEL to the same level set in Lobster.

## Things to copy into gamedir
- WickedEngine
    - Content/
    - WickedEngine/shaders/
- Lobster
    - data/
    - modules/
