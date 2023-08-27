//
// This module is executed on engine startup.
import wisupport

// First: Set up any callbacks for events, frame notifications
def frame_begin():
   pass()
wi_set_begin_frame_fn(): frame_begin()

// Any miscellaneous setup.  Here we load an initial scene.
let scene = global_scene()
scene.load_model("Content/models/badbard.wiscene", false)

//DEBUG+
let ent = scene.create_entity()
let nc = scene.create_name_component(ent)
nc.set_name("bozo")
assert scene.entity_find_by_name("bozo").handle == ent.handle
error("pants on fire {nc}")
//DEBUG-



// Finally, call wi_start_game() to start the main loop.  This will not return
// until the game is exiting.
wi_start_game()

// Not much you can do here, game is already exiting.
print("bye")
