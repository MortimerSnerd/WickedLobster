# WickedLobster
Exploratory project integrating the [Lobster Language](https://github.com/aardappel/lobster) 
with the [Wicked Engine](https://github.com/turanszkij/WickedEngine).  

## Status
I'm still getting the overall structure in place, so this is just a skeleton that
is in pre-alpha state.  I'm checking it in mainly to have it backed up at this point,
it's not usable by others yet. 

## Why

The short version - I like Lobster, but I don't have the time to write all
of the support code that's really required for a 3d game.

When I looked around for a 3d engine, Wicked Engine seemed like the best match
for me.  Very well done, does a lot while not feeling as huge as Unreal.  Has
Lua integration, and I'm comfortable with C++ so I don't mind working directly
with the Wicked Engine API's. 

One interesting thing about Lobster is that it allows you to compile just
the language, without the builtin engine. One day, one of my neurons
fired and I thought about taking the Lobster language libary and putting it
with the Wicked Engine library.

## Goals

- Bind just enough of the Wicked Engine API so game logic and control can be 
  done in Lobster.  It's not intended to expose every feature to Lobster. 
  Some things are better left to C++.
- I want to keep Lobster and Wicked Engine out of the tree, without having
  to make modifications to them.  At the moment, I'm doing this with build
  variables that have the path to external Lobster and Wicked Engine directories.
- The directory the game will run from "gamedir" needs data directories
  from both Lobster and Wicked Engine.  I've just copied mine manually, 
  but it would be better to build a script to do that. 


## oof - bad things and reminders
- had to change wicked engine lib to use multithreaded runtime (not mt dll), and
  add a preprocessor to set ITERATOR_DEBUG_LEVEL to the same level set in Lobster.

### Things to copy into gamedir
- WickedEngine
    - Content/
    - WickedEngine/shaders/
- Lobster
    - data/
    - modules/
