// Reproducing the lua character controller lua example.
// After binding the basics, following the character controller
// example is a good way to guide areas to bind next.
import std
import wisupport
import core.matrix

let scene = global_scene()
enum animation_names:
   IDLE, WALK, JOG, RUN, JUMP, SWIM_IDLE, SWIM, DANCE, WAVE

var animations = [] :: wi_entity

//TODO should be bound
let MoodRelaxed = 3

enum_flags Layers:
   Layers_Player, Layers_NPC 

class character:
   model = INVALID_ENTITY
   target_rot_horizontal = 0.0
   target_rot_vertical = 0.0
   target_height = 1.0
   anims = [] :: wi_entity
   anim_amount = 1.0
   neck = INVALID_ENTITY
   head = INVALID_ENTITY
   left_hand = INVALID_ENTITY
   right_hand = INVALID_ENTITY
   left_foot = INVALID_ENTITY
   right_foot = INVALID_ENTITY
   left_toes = INVALID_ENTITY
   right_toes = INVALID_ENTITY
   face = float3_z   // z forward
   face_next = float3_z
   force = float3_0
   velocity = float3_0
   saved_pointer_pos = float3_0
   walk_speed = 0.2
   jog_speed = 0.4
   run_speed = 0.8
   jump_speed = 8.0
   swim_speed = 0.5
   layer_mask = 0xf
   scale = float3_1
   rotation = float3{0.0, 3.14, 0.0}
   start_position = float3_y
   position = float3_0
   controllable = true
   fixed_update_remain = 0.0
   root_bone_offset = 0.0
   foot_placed_left = false
   foot_placed_right = false
   mood = MoodRelaxed
   mood_amount = 1.0
   state = ""
   state_prev = ""
   humanoid = INVALID_ENTITY
   collider = INVALID_ENTITY

def first_where(count: int, test):
   for(count) i:
      if test(i):
         return i
   return -1

constructor character(mname: string, start_pos: float3, face: float3, controllable: bool):
   let rv = character{start_position: start_pos, face: face, controllable: controllable}
   rv.layer_mask = if controllable: Layers_Player else: Layers_NPC
   
   with_temp_scene() mscene:
      rv.model = mscene.load_model(mname, true) 
      mscene.get_layer_component(rv.model).set_layer_mask(rv.layer_mask)
      rv.state = "idle"
      rv.state_prev = rv.state

      let humix = first_where(mscene.get_humanoid_count()): 
         let ent = mscene.get_humanoid_entity(_)
         mscene.is_descendant_entity(ent, rv.model)

      if humix >= 0:
         let entity = mscene.get_humanoid_entity(humix)
         guard mscene.is_descendant_entity(entity, rv.model)
         rv.humanoid = entity
         let humanoid = mscene.get_humanoid_component(entity)
         assert humanoid.is_valid()
         humanoid.set_lookat_enabled(false)
         rv.neck = humanoid.bone(hb_Neck)
         rv.head = humanoid.bone(hb_Head)
         rv.left_hand = humanoid.bone(hb_LeftHand)
         rv.right_hand = humanoid.bone(hb_RightHand)
         rv.left_foot = humanoid.bone(hb_LeftFoot)
         rv.right_foot = humanoid.bone(hb_RightFoot)
         rv.left_toes = humanoid.bone(hb_LeftToes)
         rv.right_toes = humanoid.bone(hb_RightToes)

         if mscene.get_collider_component(entity).is_empty():
            let collider = mscene.create_collider_component(entity)
            collider.set_cpu_enabled(false)
            collider.set_gpu_enabled(true)
            collider.set_shape(cs_capsule)
            collider.set_radius(0.3)
            collider.set_offset(float3_y*collider.radius())
            collider.set_tail(float3_y*1.4)
            let head_transform = mscene.get_transform_component(rv.head)
            if head_transform.is_valid():
               collider.set_tail(head_transform.position())
         rv.collider = entity
      else:
         warning("character: No humanoid component found for {mname}")
         
      //TODO line 397 in character controller
      let necktr = mscene.get_transform_component(rv.neck)
      rv.target_height = necktr.position().y

      scene.merge(mscene)

   info("ARF {rv}")
   return rv

class third_person_camera:
   camera = INVALID_ENTITY
   character: character
   side_offset = 0.2
   rest_distance = 1.0
   rest_distance_new = 1.0
   min_distance = 0.5
   zoom_speed = 0.3
   target_rot_horizontal = 0.0
   target_rot_vertical = 0.0
   target_height = 1.0

   def update():
      // Mouse scroll or gamepad trigggers will move the camera distance.
      let mpos, iscroll, _pressure = input_get_pointer()
      let ltrigger = input_get_analog(GAMEPAD_ANALOG_TRIGGER_R)
      let rtrigger = input_get_analog(GAMEPAD_ANALOG_TRIGGER_L)
      var scroll = iscroll + rtrigger.x
      print("scronk p={mpos} {scroll}")
      scroll -= ltrigger.x
      scroll *= zoom_speed
      rest_distance_new = max(rest_distance_new - scroll, min_distance)
      rest_distance = lerp(rest_distance, rest_distance_new, 0.1)

      // This will allow some smoothing for certain movements of camera target.
      let character_transform = scene.get_transform_component(character.model)
      let character_position = character_transform.position()

      target_rot_horizontal = lerp(target_rot_horizontal, character.target_rot_horizontal, 0.1)
      target_rot_vertical = lerp(target_rot_vertical, character.target_rot_vertical, 0.1)
      target_height = lerp(target_height, character_position.y + character.target_height, 0.1)

      let arm = rotation_4x4(float3_y, degrees(target_rot_horizontal)) * float4{0.0, 0.0, rest_distance, 1.0}
      let cam_pos = character_position + float3{arm.x, target_height, arm.z}
      let ccam = scene.get_camera_component(camera)

      ccam.set_eye(cam_pos)
      ccam.set_at(normalize(character_position + float3_y*character.target_height - cam_pos))
      ccam.set_up(float3_y)
      ccam.update()

      //
      //let camera_transform = scene.get_transform_component(camera)
      //with_temp_object(create_transform(), wi_matrix()) target_transform, mat:
      //   info("BARFAGE {character_position}")
      //   target_transform.translate(float3{rnd_float() * 5.5 + character_position.x, target_height, character_position.z})
      //   target_transform.rotate_roll_pitch_yaw(float3{target_rot_vertical, target_rot_horizontal, 0.0})
      //   target_transform.update()
      //
      //   with_temp_object(target_transform.world_matrix()) tworld:
      //      mat.translation(float3{side_offset, 0.0, -rest_distance})
      //      mat.multiply(tworld, mat)
      //      //camera_transform.clear()
      //      //camera_transform.transform_by_matrix(mat)
      //      //camera_transform.update()
      //      let cc = scene.get_camera_component(camera)
      //      cc.set_transform_from(mat)
      //      cc.update()
            


constructor third_person_camera(sc: wi_scene, player: character):
   let cam = sc.create_entity()
   let rpath = wi_renderpath3d()
   let cc = sc.create_camera_component(cam)
   rpath.set_camera(cc)

   return third_person_camera{
      camera: cam,
      character: player}


def load_animations(fname):
   with_temp_scene() anim_scene:
      anim_scene.load_model(fname, false)
      animations = map(["idle", "walk", "jog", "run", "jump", "swim_idle", "swim", "dance", "wave"]):
         anim_scene.find_entity_by_name(_)
      scene.merge(anim_scene)

// On load init.
let script_dir = "Content/scripts/character_controller"
global_scene().load_model("{script_dir}/assets/level.wiscene", false)
load_animations("{script_dir}/assets/animations.wiscene")
let player = character("{script_dir}/assets/character.wiscene", float3_y*0.5, float3_z, true)
let camera = third_person_camera(global_scene(), player)


wi_set_app_variable_frame_fn():
   let dt = delta_time()
   camera.update()
   error("TF {test_function()}")


wi_start_game()
