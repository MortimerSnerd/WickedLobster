import color
import core.quat
import wisupport

let gscene = global_scene()
var charent = INVALID_ENTITY
var cament = INVALID_ENTITY
var char_yaw = 0.0

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
   wi_renderpath3d().set_camera(cc)

wi_set_app_fixed_frame_fn():
   //TODO should it be better to check the input in the variabled step, and only 
   // apply it in fixed step?
   let dt = delta_time()
   let spd = 5.0

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

   if magnitude(mv) > 0.0:
      char_tr.translate(normalize(mv) * spd * dt)
   
load_initial_scene()
wi_start_game()
