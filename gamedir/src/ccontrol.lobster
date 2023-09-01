// Reproducing the lua character controller lua example.
// After binding the basics, following the character controller
// example is a good way to guide areas to bind next.
import std
import wisupport

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
   target_height = 0.0
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

constructor character(mname: string, start_pos: float3, face: float3, controllable: bool):
   let rv = character{start_position: start_pos, face: face, controllable: controllable}
   rv.layer_mask = if controllable: Layers_Player else: Layers_NPC
   
   with_temp_scene() mscene:
      rv.model = mscene.load_model(mname, true) 
      mscene.get_layer_component(rv.model).set_layer_mask(rv.layer_mask)
      rv.state = "idle"
      rv.state_prev = rv.state

      for(mscene.get_humanoid_count()) i:
         let entity = mscene.get_humanoid_entity(i)
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

         info("ARF {rv}")

         //NEXT collider component


      scene.merge(mscene)
   return rv


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


wi_set_app_fixed_frame_fn():
   pass()


wi_start_game()
