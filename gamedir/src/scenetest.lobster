import color
import core.quat
import wisupport

let gscene = global_scene()
var charent = INVALID_ENTITY
var cament = INVALID_ENTITY
var char_yaw = 0.0
var char_pitch = 0.0
var last_mouse = float2_0
let debug_msg = wi_sprite_font()
var first_frame = true

// NB - LH, so fwd is +z

// Get fwd vector from transform, excluding any pitch.  Will default
// to float3_z if.
def get_fwd_vector(t: wi_transform_component) -> float3:
   var rv = float3_z
   with_temp_object(t.world_matrix()) m:
      let fc = m.transform_vector(float3_z) * float3{1.0, 0.0, 1.0}
      if magnitude_squared(fc) >= 0.001:
         rv = normalize(fc)
   return rv

// Returns a forward vector for a given yaw, ignoring pitch.
def fwd_vector_from_yaw(y: float):
   let q = mk_quat(float3_y, y)
   return q.transform(float3_z)
   

def load_initial_scene():
   set_print_decimals(3)
   gscene.load_model("spudge/testlevel.wiscene", false)

   // Load up our character model, and attach the camera to it.
   // It's just a box right now.
   with_temp_scene() csc:
      charent = csc.load_model("spudge/fpchar.wiscene", true)
      assert charent.is_valid()
      cament = csc.find_entity_by_name("eyepoint", charent)
      assert cament.is_valid()
      gscene.merge(csc)

   // Move character to spawnpoint, and extract yaw, pitch, etc...
   let char_tr = gscene.get_transform_component(charent)
   let spawn = gscene.find_entity_by_name("spawnpoint")
   assert spawn.is_valid()
   char_tr.copy_from(gscene.get_transform_component(spawn))
   char_tr.update()
   let fwd = get_fwd_vector(char_tr)
   char_yaw = atan2(float2{fwd.z, fwd.x})

   let cc = gscene.create_camera_component(cament)
   cc.transform(gscene.get_transform_component(cament))
   cc.update()

   let rpath = wi_renderpath3d()
   rpath.set_camera(cc)
   rpath.add_font(debug_msg)

   let fp = wi_font_params()
   fp.set_position(float3{10.0, 300.0, 0.0})
   debug_msg.set_params(fp)

   last_mouse = input_get_pointer()
   input_hide_pointer(true)

wi_set_app_variable_frame_fn():
   if input_press(KEYBOARD_BUTTON_ESCAPE):
      wi_quit_game()
      return

   //TODO should it be better to check the input in the variable step, and only 
   // apply it in fixed step?
   let dt = delta_time()
   let spd = 5.0
   let rot_speed = 15.0

   if first_frame:
      first_frame = false
      last_mouse = input_get_pointer()

   let mpos = input_get_pointer()
   let mdiff = mpos - last_mouse
   last_mouse = mpos

   char_yaw += mdiff.x * rot_speed * dt
   char_pitch += mdiff.y * rot_speed * dt
   debug_msg.set_text("yaw={char_yaw} pitch={char_pitch}")

   let char_tr = gscene.get_transform_component(charent)
   let fwd = fwd_vector_from_yaw(char_yaw)
   let right = float3{fwd.z, 0.0, -fwd.x}
   var mv = float3_0

   if input_down('W'):
      mv += fwd
   if input_down('S'):
      mv -= fwd
   if input_down('A'):
      mv -= right
   if input_down('D'):
      mv += right

   mv *= spd * dt

   // Apply changes to character.
   let cam_tr = gscene.get_transform_component(cament)
   cam_tr.clear()
   cam_tr.rotate_roll_pitch_yaw(float3{radians(char_pitch), 0.0, 0.0})
   cam_tr.update()
   let newpos = char_tr.position() + mv
   char_tr.clear()
   char_tr.rotate_roll_pitch_yaw(float3{0.0, radians(char_yaw), 0.0})
   char_tr.translate(newpos)
   char_tr.update()
   
load_initial_scene()
wi_start_game()
