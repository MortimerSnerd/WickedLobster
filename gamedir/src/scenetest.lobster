import color
import core.quat
import wisupport
let player_layer = 1 << 0
let static_layer = 1 << 1
let dynobjs_layer = 1 << 2
let g_accel = 39.0

let gscene = wi.global_scene()
var charent = INVALID_ENTITY
var cament = INVALID_ENTITY
var char_yaw = 0.0
var char_pitch = 0.0
var char_vel = float3_0
var char_on_floor = false
var pinned_mouse_pos = float2_0
let debug_msg = wi.sprite_font()
var first_frame = true

// NB - LH, so fwd is +z

// Get fwd vector from transform, excluding any pitch.  Will default
// to float3_z if.
def get_fwd_vector(t: wi.transform_component) -> float3:
   var rv = float3_z
   let m = t.world_matrix()
   let fc = m.transform_vector(float3_z) * float3{1.0, 0.0, 1.0}
   if magnitude_squared(fc) >= 0.001:
      rv = normalize(fc)
   return rv

// Get the vector the transform is looking at. 
def get_look_vector(t: wi.transform_component) -> float3:
   var rv = float3_z
   let m = t.world_matrix()
   let fc = m.transform_vector(float3_z)
   if magnitude_squared(fc) >= 0.001:
      rv = normalize(fc)
   return rv

// Returns a ray pointing from the camera to the direction being looked
// at, with the given maxlen. 
def get_look_ray(maxlen = 1.0e6) -> wi.primitive_ray:
   let cam_tr = gscene.get_transform_component(cament)
   let dir = get_look_vector(cam_tr)
   return wi.make_ray_from(cam_tr.position(), dir, 0.0, maxlen)

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
   let csc = wi.new_scene()
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

   let rpath = wi.renderpath3d()
   rpath.set_camera(cc)
   rpath.add_font(debug_msg)
   rpath.set_ao(wi.AO_SSAO)
   rpath.set_ao_power(0.25)

   let fp = wi.font_params()
   let sdim = rpath.physical_dims()
   fp.set_position(float3{10.0, float(sdim.y - 50), 0.0})
   debug_msg.set_params(fp)

   pinned_mouse_pos = wi.input_get_pointer()
   wi.input_hide_pointer(true)

def splat_decal(decal: wi.ecs_entity, pos: float3, normal: float3, on: wi.ecs_entity, rot = 0.0, scale = 1.0):
   let decaltr = gscene.get_transform_component(decal)
   decaltr.translate(pos)
   decaltr.rotate(mk_quat(normal, rot))
   decaltr.scale(float3_1*scale)
   gscene.component_attach(decal, on, false)

   // Restrict layer to what we're attached to
   let onlayer = gscene.get_layer_component(on)
   if onlayer.has_value():
      let dlayer = gscene.get_layer_component(decal)
      dlayer.set_layer_mask(onlayer.layer_mask())


wi.set_app_variable_frame_fn():
   if wi.input_press(wi.KEYBOARD_BUTTON_ESCAPE):
      wi.quit_game()
      return
   
   if wi.app_is_active():
      wi.input_hide_pointer(true)
   else:
      wi.input_hide_pointer(false)
      first_frame = true
      

   //TODO should it be better to check the input in the variable step, and only 
   // apply it in fixed step?
   let dt = wi.delta_time()
   let spd = 5.0
   let rot_speed = 15.0
   var mpos = float2_0
   var mdiff = float2_0

   //logmsg("FRAME dt={dt}")

   if first_frame:
      // pin the mouse to the center of the screen, so it won't go out of the window
      let center = float(wi.renderpath3d().physical_dims()) * 0.5
      pinned_mouse_pos = center
      wi.input_set_pointer(pinned_mouse_pos)
      first_frame = false
      return
   else:
      mpos = wi.input_get_pointer()
      mdiff = mpos - pinned_mouse_pos
      wi.input_set_pointer(pinned_mouse_pos)

   char_yaw += mdiff.x * rot_speed * dt
   char_pitch = clamp(char_pitch + mdiff.y * rot_speed * dt, -45.0, 45.0)
   debug_msg.set_text("yaw={char_yaw} pitch={char_pitch}")

   let char_tr = gscene.get_transform_component(charent)
   let fwd = fwd_vector_from_yaw(char_yaw)
   let right = float3{fwd.z, 0.0, -fwd.x}
   var mv = float3_0

   if char_on_floor:
      if wi.input_down('W'):
         mv += fwd
      if wi.input_down('S'):
         mv -= fwd
      if wi.input_down('A'):
         mv -= right
      if wi.input_down('D'):
         mv += right

      if wi.input_down(wi.KEYBOARD_BUTTON_SPACE):
         let jump_speed = 15.0
         char_vel = float3{char_vel.x, jump_speed, char_vel.z}
         char_on_floor = false

      if wi.input_press('F'):
         // Just for testing, not a great idea to litter the place with one shot sound entities.
         let snd = gscene.create_sound_entity("efct", "spudge/testsound.wav", char_tr.position())
         let sc = gscene.get_sound_component(snd)
         sc.set_is_looped(false)
         sc.set_is_playing(true)

      if wi.input_press(wi.MOUSE_BUTTON_LEFT):
         //DEBUG play with rays
         let ray = get_look_ray()
         let ir = gscene.ray_intersects(ray, wi.FILTER_OPAQUE, ~player_layer)
         wi.logmsg("PICK {ir.debug_string()}")
         if ir.entity.is_valid():
            let ent = gscene.create_decal_entity("spot", "spudge/spot.png")
            splat_decal(ent, ir.position(), ir.normal(), ir.entity(), rnd_float()*360.0, 0.2)


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

   let started_on_floor = char_on_floor
   char_on_floor = false
   let cap = wi.get_rigidbody_capsule(char_tr, char_rb)
   //logmsg("\tctest capbase = {cap.base()}, tip={cap.tip()}, rad={cap.radius()}, v={char_vel} dp={act_dp} on_floor={char_on_floor}")
   let start_pos = cap.base()
   cap.translate(act_dp)
   var touching_possible = true
   var max_iters = 4
   while touching_possible and max_iters > 0:
      max_iters--
      let sin = gscene.capsule_intersects(cap, wi.FILTER_COLLIDER|wi.FILTER_NAVIGATION_MESH|wi.FILTER_OPAQUE, 
                                          static_layer|dynobjs_layer)
      let cent = sin.entity()
      guard cent.is_valid():
         touching_possible = false

      //logmsg("\t\ttouch base={cap.base()}")
      //logmsg(sin.debug_string(3))
      let n = sin.normal()
      cap.translate(n*sin.depth())
      if n.looks_like_floor:
         if not started_on_floor:
            let decal = gscene.create_decal_entity("spot", "spudge/spot.png")
            splat_decal(decal, cap.base(), n, cent, rnd_float()*360.0, 0.2)

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
wi.start_game()
