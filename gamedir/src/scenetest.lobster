import color
import core.quat
import wisupport
let player_layer = 1 << 0
let static_layer = 1 << 1
let dynobjs_layer = 1 << 2
let g_accel = 39.0

let gscene = global_scene()
var charent = INVALID_ENTITY
var cament = INVALID_ENTITY
var char_yaw = 0.0
var char_pitch = 0.0
var char_vel = float3_0
var char_on_floor = false
var pinned_mouse_pos = float2_0
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
   
def place_at_spawnpoint(spawnent, ent):
   let ent_tr = gscene.get_transform_component(ent)
   // haha, don't copy the transform, we don't want to apply the spawnpoint's scaling.
   let sp_tr = gscene.get_transform_component(spawnent)
   let sp_pos, sp_rot = sp_tr.decompose()
   let ent_s = ent_tr.scaling()

   ent_tr.clear()
   ent_tr.rotate(sp_rot)
   ent_tr.translate(sp_pos)
   ent_tr.scale(ent_s)
   ent_tr.update()

def y_is_major_axis(norm):
   let na = abs(norm)
   return na.y >= na.x and na.y >= na.z

def looks_like_floor(norm):
   return norm.y > 0.0 and y_is_major_axis(norm)

def looks_like_ceiling(norm):
   return norm.y < 0.0 and y_is_major_axis(norm)

def load_initial_scene():
   set_print_decimals(3)
   gscene.load_model("spudge/testlevel.wiscene", false)

   // Load up our character model, and attach the camera to it.
   // It's just a box right now.
   with_temp_scene() csc:
      csc.load_model("spudge/fpchar.wiscene", false)
      charent = csc.find_entity_by_name("boxybrown")
      assert charent.is_valid()
      cament = csc.find_entity_by_name("eyepoint", charent)
      assert cament.is_valid()
      gscene.merge(csc)

   // Move character to spawnpoint, and extract yaw, pitch, etc...
   let char_tr = gscene.get_transform_component(charent)
   let spawn = gscene.find_entity_by_name("spawnpoint")
   assert spawn.is_valid()
   place_at_spawnpoint(spawn, charent)
   let fwd = get_fwd_vector(char_tr)
   char_yaw = atan2(float2{fwd.z, fwd.x})

   let cc = gscene.create_camera_component(cament)

   let rpath = wi_renderpath3d()
   rpath.set_camera(cc)
   rpath.add_font(debug_msg)
   rpath.set_ao(AO_SSAO)
   rpath.set_ao_power(0.25)

   let fp = wi_font_params()
   let sdim = rpath.physical_dims()
   fp.set_position(float3{10.0, float(sdim.y - 50), 0.0})
   debug_msg.set_params(fp)

   pinned_mouse_pos = input_get_pointer()
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
   var mpos = float2_0
   var mdiff = float2_0

   if first_frame:
      // pin the mouse to the center of the screen, so it won't go out of the window
      let center = float(wi_renderpath3d().physical_dims()) * 0.5
      pinned_mouse_pos = center
      input_set_pointer(pinned_mouse_pos)
      first_frame = false
      return
   else:
      mpos = input_get_pointer()
      mdiff = mpos - pinned_mouse_pos
      input_set_pointer(pinned_mouse_pos)

   char_yaw += mdiff.x * rot_speed * dt
   char_pitch = clamp(char_pitch + mdiff.y * rot_speed * dt, -45.0, 45.0)
   debug_msg.set_text("yaw={char_yaw} pitch={char_pitch}")

   let char_tr = gscene.get_transform_component(charent)
   let fwd = fwd_vector_from_yaw(char_yaw)
   let right = float3{fwd.z, 0.0, -fwd.x}
   var mv = float3_0

   if char_on_floor:
      if input_down('W'):
         mv += fwd
      if input_down('S'):
         mv -= fwd
      if input_down('A'):
         mv -= right
      if input_down('D'):
         mv += right

      if input_down(KEYBOARD_BUTTON_SPACE):
         let jump_speed = 10.0
         char_vel = float3{char_vel.x, jump_speed, char_vel.z}
         char_on_floor = false

   var yvel = char_vel.y
   if not char_on_floor:
      yvel -= g_accel*dt

   mv *= spd
   if magnitude_squared(mv) > 0.0:
      char_vel = float3{mv.x, yvel, mv.z}
   else:
      char_vel = float3{char_vel.x, yvel, char_vel.z}
      if char_on_floor:
         char_vel *= float3{0.9, 0.0, 0.9}

   // Testing scene intersection binding
   let char_rb = gscene.get_rigidbody_component(charent)
   var act_dp = char_vel*dt

   print("ctest v={char_vel} dp={act_dp} on_floor={char_on_floor}")
   char_on_floor = false
   with_temp_object(get_rigidbody_capsule(char_tr, char_rb)) cap:
      let start_pos = cap.base()
      cap.translate(act_dp)
      var touching_something = true
      var max_iters = 4
      while touching_something and max_iters > 0:
         max_iters--
         with_temp_object(gscene.capsule_intersects(cap, FILTER_OPAQUE, static_layer)) sin:
            let cent = sin.entity()
            let n = sin.normal()
            guard cent.is_valid():
               touching_something = false
            print("\ttouch {cent} {gscene.get_name_component(cent).get_name()} n={n} depth={sin.depth()}")
            cap.translate(n*sin.depth()*1.001)
            if n.looks_like_floor:
               char_on_floor = true
               char_vel = float3{char_vel.x, 0.0, char_vel.z}
            elif n.looks_like_ceiling:
               char_vel = float3{char_vel.x, 0.0, char_vel.z}

      act_dp = cap.base() - start_pos
      if char_on_floor:
         // Keep contact with the floor, rather than bouncing by a minute amount
         // every frame.
         act_dp -= float3_y*0.01

   // Set head pitch
   let cam_tr = gscene.get_transform_component(cament)
   cam_tr.set_rotation_local(mk_quat(float3_x, char_pitch))
   cam_tr.set_dirty(true)

   // Move and rotate the character.
   char_tr.set_translation_local(char_tr.translation_local() + act_dp)
   char_tr.set_rotation_local(mk_quat(float3_y, char_yaw))
   char_tr.set_dirty(true)


load_initial_scene()
wi_start_game()
