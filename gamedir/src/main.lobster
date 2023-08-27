//
// This module is executed on engine startup.
import wisupport

// First: Set up any callbacks for events, frame notifications
def frame_begin():
   pass()
wi_set_begin_frame_fn(): frame_begin()

// Any miscellaneous setup.  Here we load an initial scene.
let scene = wi_global_scene()
wi_load_model(scene, "Content/models/Sponza/sponza.wiscene", false)

// Finally, call wi_start_game() to start the main loop.  This will not return
// until the game is exiting.
wi_start_game()

// Not much you can do here, game is already exiting.
print("bye")
