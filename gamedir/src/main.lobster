//
// This module is executed on engine startup.
import wisupport
import vec

var tim = 0.0
var camera = INVALID_ENTITY

// First: Set up any callbacks for events, frame notifications
def frame_begin():
   // Gently oscillate the camera up and down to see that the component code is
   // working.
   let a = sin(tim*14.0)*20.0 + 20.0
   let scene = global_scene()
   tim += 0.016  // no delta time yet
   if camera.is_valid():
      let t = scene.get_transform_component(camera)
      guard not t.is_empty() 
      t.clear()
      t.rotate(mk_quat(float3_y, a))
      t.translate(float3_y*a)
   
wi_set_begin_frame_fn(): frame_begin()

// Any miscellaneous setup.  Here we load an initial scene, and create
// a camera we can move around.
let scene = global_scene()
scene.load_model("Content/models/badbard.wiscene", false)
camera = scene.create_entity()
scene.create_name_component(camera).set_name("cambo")
let cc = scene.create_camera_component(camera)
cc.set_fov(radians(90.0))
cc.update()
wi_renderpath3d().set_camera(cc)
scene.create_transform_component(camera).translate(-float3_z*50.0)

// Finally, call wi_start_game() to start the main loop.  This will not return
// until the game is exiting.
wi_start_game()

// Not much you can do here, game is already exiting.
info("bye")
