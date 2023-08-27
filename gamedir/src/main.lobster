// These should be put in a separate support module.
def is_valid_handle(i: int2):
   return i[0] >= 0

def frame_begin():
   print("fram")

// Set up callbacks from the main game loop.
wi_set_begin_frame_fn(): frame_begin()

// Load an initial scene.
let scene = wi_global_scene()
let ent = wi_load_model(scene, "Content/models/Sponza/sponza.wiscene", true)
print("mr scene {scene}, ent = {ent}")

if is_valid_handle(ent):
   // This starts the game's main loop, and does not return until the game is exiting.
   wi_start_game()
else:
   print("not a good handle for scene entity: {ent}")

print("boom")
