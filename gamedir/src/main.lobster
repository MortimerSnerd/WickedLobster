//
// This module is executed on engine startup.
import wisupport
import vec

var tim = 0.0
var camera = INVALID_ENTITY

// First: Set up any callbacks for events, frame notifications
def app_fixed_frame():
   // Gently oscillate the camera up and down to see that the component code is
   // working.
   let a = sin(tim*14.0)*20.0 + 20.0
   let scene = global_scene()
   tim += get_fixed_dt()
   if camera.is_valid():
      let t = scene.get_transform_component(camera)
      guard not t.is_empty() 
      t.clear()
      t.rotate(mk_quat(float3_y, a*4.9))
      t.translate(float3_y*a)

   if input_press(KEYBOARD_BUTTON_F5):
      tim = 0.0

   draw_debug_text("Eat more cheese", float3{0.0, 2.0, 2.0})
   
wi_set_app_fixed_frame_fn(): app_fixed_frame()

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
info("FDT = {get_fixed_dt()} rate = {wi_get_fixed_update_rate()}")

with_temp_scene() tscene:
   let teapot = tscene.load_model("Content/models/teapot.wiscene", true)
   let tt = tscene.get_transform_component(teapot)
   tt.translate(float3{20.0, 7.0, 1.0})
   scene.merge(tscene)

// Finally, call wi_start_game() to start the main loop.  This will not return
// until the game is exiting.
wi_start_game()

// Not much you can do here, game is already exiting.
info("bye")


