// Reproducing the lua character controller lua example.
// After binding the basics, following the character controller
// example is a good way to guide areas to bind next.
import std
import vec
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
   saved_pointer_pos = float2_0
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
   state = IDLE
   state_prev = IDLE
   humanoid = INVALID_ENTITY
   collider = INVALID_ENTITY
   root = INVALID_ENTITY

   def jump(f):
      force = float3{force.x, f, force.z}
      state = JUMP

   def move_direction(dir):
      with_temp_object(wi_matrix(), wi_matrix()) m1, m2:
         m1.rotation_y(target_rot_horizontal)
         m2.rotation_x(target_rot_vertical)
         m1.multiply(m2, m1)
         var tdir = m1.transform_pos(normalize(dir))
         tdir = float3{tdir.x, 0.0, tdir.y}
         let dp = dot(face, tdir)
         if dp < 0.0:
            m2.rotation_y(3.14591*0.01)
            face = m2.transform_normal(face)
         face_next = normalize(tdir)

         if dp > 0.0:
            var speed = 0.0
            if state == WALK:
               speed = walk_speed
            elif state == JOG:
               speed = jog_speed
            elif state == RUN:
               speed = run_speed
            elif state == SWIM:
               speed = swim_speed

            force += face*speed

   def update(dt: float):
      let model_tr = scene.get_transform_component(model)
      let saved_pos = model_tr.position()
      model_tr.clear()
      with_temp_object(wi_matrix()) m1:
         m1.look_to(float3_0, face, float3_y)
         m1.inverted(m1)
         model_tr.transform_by_matrix(m1)
      model_tr.scale(scale)
      model_tr.rotate_roll_pitch_yaw(rotation)
      model_tr.translate(saved_pos)
      model_tr.update()

      if controllable:
         var diff = float2(input_get_analog(GAMEPAD_ANALOG_THUMBSTICK_R)) * dt * 4.0

         if input_down(MOUSE_BUTTON_RIGHT):
            diff += (input_get_pointer() - saved_pointer_pos) * dt * 0.3
            input_set_pointer(saved_pointer_pos)
            input_hide_pointer(true)
         else:
            saved_pointer_pos = input_get_pointer()
            input_hide_pointer(false)

         target_rot_horizontal += diff.x
         target_rot_vertical = clamp(target_rot_vertical+diff.y, -math_pi*0.3, math_pi*0.4)

      // skipped expression handling line 501
      let current_anim = scene.get_animation_component(anims[state])
      if current_anim.is_valid():
         //current_anim.play()
         if state_prev != state:
            current_anim.set_timer(current_anim.start())
            state_prev = state

         if state == JUMP:
            if current_anim.timer() > current_anim.end():
               state = IDLE
         else:
            if magnitude(velocity) < 0.1 and state != SWIM_IDLE and state != SWIM:
               state = IDLE

      if dt > 0.2:
         return   // avoid processing too large delta times to avoid instability.

      // skip swimming 539

      if not wi_is_backlog_active():
         var lookdir = float3_0

         if input_down('A'):
            lookdir -= float3_x

         if input_down('D'):
            lookdir += float3_x

         if input_down('W'):
            lookdir += float3_z

         if input_down('S'):
            lookdir -= float3_z

         let analog = input_get_analog(GAMEPAD_ANALOG_THUMBSTICK_L)
         lookdir += float3{analog.x, 0.0, analog.y}

         if state != JUMP and state_prev != JUMP and velocity.y == 0.0:
            if magnitude(lookdir) > 0.0:
               if state == SWIM_IDLE:
                  state = SWIM
               else:
                  if input_down(KEYBOARD_BUTTON_LSHIFT) or input_down(GAMEPAD_BUTTON_6):
                     if input_down('E') or input_down(GAMEPAD_BUTTON_5):
                        state = RUN
                     else:
                        state = JOG
                  else:
                     state = WALK
               move_direction(lookdir)

            if input_press(KEYBOARD_BUTTON_SPACE) or input_press(GAMEPAD_BUTTON_3):
               jump(jump_speed)
         elif velocity.y > 0.0:
            move_direction(lookdir)
      
         velocity = force
      //DEBUG
      model_tr.translate(velocity*dt)
      velocity = velocity*0.9


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
      rv.state = IDLE
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
         
      //TODO line 397 in character controller, need expression controller

      rv.root = mscene.find_entity_by_name("Root", rv.model)

      let model_tr = mscene.get_transform_component(rv.model)
      if model_tr.is_valid():
         model_tr.clear()
         model_tr.scale(rv.scale)
         model_tr.rotate_roll_pitch_yaw(rv.rotation)
         model_tr.translate(rv.start_position)
         model_tr.update()

      let necktr = mscene.get_transform_component(rv.neck)
      rv.target_height = necktr.position().y

      scene.merge(mscene)

   rv.anims = map(animations): scene.retarget_animation(rv.humanoid, _, false)

   info("ARF {rv.model} {rv}")
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
      // Mouse scroll or gamepad triggers will move the camera distance.
      let mpos, iscroll, _pressure = input_get_pointer()
      let ltrigger = input_get_analog(GAMEPAD_ANALOG_TRIGGER_R)
      let rtrigger = input_get_analog(GAMEPAD_ANALOG_TRIGGER_L)
      var scroll = iscroll + rtrigger.x
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

      let cam_tr = scene.get_transform_component(camera)
      with_temp_object(create_transform(), wi_matrix()) targ_tr, m1:
         targ_tr.translate(float3{character_position.x, target_height, character_position.z})
         targ_tr.rotate_roll_pitch_yaw(float3{target_rot_vertical, target_rot_horizontal, 0.0})
         targ_tr.update()
         
         m1.translation(float3{side_offset, 0.0, -rest_distance})
         m1.multiply(targ_tr.world_matrix(), m1)
         cam_tr.clear()
         cam_tr.transform_by_matrix(m1)
         cam_tr.update()

         //TODO skipped camera collision detection for obstacles

         let cc = scene.get_camera_component(camera)
         cc.transform(cam_tr)

            


constructor third_person_camera(sc: wi_scene, player: character):
   let cam = sc.create_entity()
   let rpath = wi_renderpath3d()
   let cc = sc.create_camera_component(cam)
   let ct = sc.create_transform_component(cam)
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

let rpath = wi_renderpath3d()
rpath.set_light_shafts_strength(0.01)
rpath.set_ao(AO_MSAO)
rpath.set_ao_power(0.25)
rpath.set_outline_threshold(0.11)
rpath.set_outline_thickness(1.7)
rpath.set_outline_color(float4{0.0, 0.0, 0.0, 0.6})
rpath.set_bloom_threshold(5.0)

wi_set_app_variable_frame_fn():
   let dt = delta_time()
   player.update(dt)
   camera.update()

wi_start_game()
