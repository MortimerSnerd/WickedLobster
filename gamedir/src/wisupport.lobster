// Wrappers for the raw builtin interface to make it easier to use.
//
// Warning: angles are in radians, not the default of degrees as was the case
//          with the built in Lobster engine.
import color

import core.matrix
import core.quat


let math_pi = 3.14159265

// wi::input::BUTTON enum 
enum BUTTON:
   BUTTON_NONE = 0,

   MOUSE_BUTTON_LEFT,
   MOUSE_BUTTON_RIGHT,
   MOUSE_BUTTON_MIDDLE,

   KEYBOARD_BUTTON_UP,
   KEYBOARD_BUTTON_DOWN,
   KEYBOARD_BUTTON_LEFT,
   KEYBOARD_BUTTON_RIGHT,
   KEYBOARD_BUTTON_SPACE,
   KEYBOARD_BUTTON_RSHIFT,
   KEYBOARD_BUTTON_LSHIFT,
   KEYBOARD_BUTTON_F1,
   KEYBOARD_BUTTON_F2,
   KEYBOARD_BUTTON_F3,
   KEYBOARD_BUTTON_F4,
   KEYBOARD_BUTTON_F5,
   KEYBOARD_BUTTON_F6,
   KEYBOARD_BUTTON_F7,
   KEYBOARD_BUTTON_F8,
   KEYBOARD_BUTTON_F9,
   KEYBOARD_BUTTON_F10,
   KEYBOARD_BUTTON_F11,
   KEYBOARD_BUTTON_F12,
   KEYBOARD_BUTTON_ENTER,
   KEYBOARD_BUTTON_ESCAPE,
   KEYBOARD_BUTTON_HOME,
   KEYBOARD_BUTTON_RCONTROL,
   KEYBOARD_BUTTON_LCONTROL,
   KEYBOARD_BUTTON_DELETE,
   KEYBOARD_BUTTON_BACKSPACE,
   KEYBOARD_BUTTON_PAGEDOWN,
   KEYBOARD_BUTTON_PAGEUP,
   CHARACTER_RANGE_START = 65, // letter A
   GAMEPAD_RANGE_START = 256, // do not use!
   GAMEPAD_BUTTON_UP,
   GAMEPAD_BUTTON_LEFT,
   GAMEPAD_BUTTON_DOWN,
   GAMEPAD_BUTTON_RIGHT,
   GAMEPAD_BUTTON_1,
   GAMEPAD_BUTTON_2,
   GAMEPAD_BUTTON_3,
   GAMEPAD_BUTTON_4,
   GAMEPAD_BUTTON_5,
   GAMEPAD_BUTTON_6,
   GAMEPAD_BUTTON_7,
   GAMEPAD_BUTTON_8,
   GAMEPAD_BUTTON_9,
   GAMEPAD_BUTTON_10,
   GAMEPAD_BUTTON_11,
   GAMEPAD_BUTTON_12,
   GAMEPAD_BUTTON_13,
   GAMEPAD_BUTTON_14,
   GAMEPAD_RANGE_END // do not use!

// wi::input::GAMEPAD_ANALOG
enum GAMEPAD_ANALOG:
   GAMEPAD_ANALOG_THUMBSTICK_L,
   GAMEPAD_ANALOG_THUMBSTICK_R,
   GAMEPAD_ANALOG_TRIGGER_L,
   GAMEPAD_ANALOG_TRIGGER_R

// Input support functions that just replicate the default parameters of the C++ 
// version.
def input_down(button: int, playerindex = 0):
   return wi_input_down(button, playerindex)

def input_press(button: int, playerindex = 0):
   return wi_input_press(button, playerindex)

def input_hold(button: int, frames = 30, continuous = false, playerindex = 0):
   return wi_input_hole(button, frames, continuous, playerindex)

def input_get_analog(axis: int, playerindex = 0):
   return wi_input_get_analog(axis, playerindex)

// Returns position, scroll delta and pressure of mouse pointer
def input_get_pointer() -> float2, float, float:
   let pk = wi_input_get_pointer()
   return float2{pk.x, pk.y}, pk.z, pk.w

// Sets the pointer position and other properties.
def input_set_pointer(pos: float2, scroll_delta = 0.0, pressure = 0.0):
   let v = float4{pos.x, pos.y, scroll_delta, pressure}
   wi_input_set_pointer(v)

def input_hide_pointer(v: bool):
   wi_input_hide_pointer(v)

// Some utility functions that should probably go somewhere else once this settles
def float2(v: float4) -> float2:
   return float2{v.x, v.y}

def float3(v: float4) -> float3:
   return float3{v.x, v.y, v.z}

def float4(v: float3, f: float) -> float4:
   return float4{v.x, v.y, v.z, f}

// Mirror of wi::backlog::LogLevel
enum backlog_level:
   lev_none, lev_default, lev_warning, lev_error

// Logs to backlog with given levels.  For debug builds this also gets blasted
// out to stdout.
def error(msg: string):
   wi_backlog(lev_error, msg)

def warning(msg: string):
   wi_backlog(lev_warning, msg)

def info(msg: string):
   wi_backlog(lev_default, msg)

// Handle kinds used internally to tell the difference between the different
// handles.
enum wokind:
   wk_scene, wk_entity, wk_name_comp, wk_camera_comp, wk_transform_comp, wk_renderpath3,
   wk_timer, wk_sprite_font, wk_font_params, wk_humanoid, wk_layer, wk_collider,
   wk_matrix, wk_animation_comp, wk_sphere, wk_sphereintersection, wk_capsule, 
   wk_rigidbody

// Invalid entity sentinel.
let INVALID_ENTITY_HANDLE = int2{wk_entity, 0}

struct wi_primitive_capsule:
   handle: int2

   def delete():
      wi_delete_primitive_capsule(handle)

   def base():
      return wi_get_primitive_capsule_base(handle)

   def set_base(v):
      wi_set_primitive_capsule_base(handle, v)

   def tip():
      return wi_get_primitive_capsule_tip(handle)

   def set_tip(v):
      wi_set_primitive_capsule_tip(handle, v)

   def radius():
      return wi_get_primitive_capsule_radius(handle)

   def set_radius(v):
      wi_set_primitive_capsule_radius(handle, v)

   // Returns bool, position, normal, penetration depth
   def intersects(other: wi_primitive_capsule) -> bool, float3, float3, float:
      return wi_capsule_capsule_intersects(handle, other.handle)

   // Updates the capsule position by d_t.
   def translate(d_p: float3):
      set_base(base() + d_p)
      set_tip(tip() + d_p)


def create_primitive_capsule() -> wi_primitive_capsule:
   return wi_primitive_capsule{wi_create_primitive_capsule()}

struct wi_primitive_sphere:
   handle: int2

   def center():
      return wi_get_primitive_sphere_center(handle)

   def set_center(v):
      wi_set_primitive_sphere_center(handle, v)

   def radius():
      return wi_get_primitive_sphere_radius(handle)

   def set_radius(v):
      wi_set_primitive_sphere_radius(handle, v)

   def delete():
      wi_delete_primitive_sphere(handle)

   def intersects(other: wi_primitive_sphere) -> bool, float, float3:
      return wi_sphere_sphere_intersects(handle, other.handle)

   // Returns bool, dist, direction
   def intersects(other: wi_primitive_capsule) -> bool, float, float3:
      return wi_sphere_capsule_intersects(handle, other.handle)

def intersects(me:: wi_primitive_capsule, other: wi_primitive_sphere) -> bool, float, float3:
   return wi_capsule_sphere_intersects(handle, other.handle)

def create_primitive_sphere() -> wi_primitive_sphere:
   return wi_primitive_sphere{wi_create_primitive_sphere()}

struct wi_sphere_intersection:
   handle: int2

   def set_entity(v):
      wi_set_sphere_intersection_result_entity(handle, v)

   def position():
      return wi_get_sphere_intersection_result_position(handle)

   def set_position(v):
      wi_set_sphere_intersection_result_position(handle, v)

   def normal():
      return wi_get_sphere_intersection_result_normal(handle)

   def set_normal(v):
      wi_set_sphere_intersection_result_normal(handle, v)

   def velocity():
      return wi_get_sphere_intersection_result_velocity(handle)

   def set_velocity(v):
      wi_set_sphere_intersection_result_velocity(handle, v)

   def depth():
      return wi_get_sphere_intersection_result_depth(handle)

   def set_depth(v):
      wi_set_sphere_intersection_result_depth(handle, v)

   def delete():
      wi_delete_sphere_intersection_result(handle)


// Note: for components, when you get one, do what you need to do with it
// and then discard it.  These can be invalidated by any code that
// creates or removes components, and the result would probably be a crash.

// Base class for convenience, this is not how the C++ code is structred.
class wi_component:
   handle: int2

   def is_empty() -> bool:
      return handle[1] == 0

   def is_valid() -> bool:
      return not is_empty()

// Name component.  This is only valid up up to the point that
// components are added/removed. 
class wi_name_component: wi_component
   def set_name(n: string):
      wi_nc_set_name(handle, n)

   def get_name() -> string:
      return wi_nc_get_name(handle)

constructor wi_name_component(h: int2):
   assert h[0] == wk_name_comp
   return wi_name_component{h}


class wi_rigidbody_component: wi_component
   def shape():
      return wi_get_rigidbody_physics_shape(handle)

   def set_shape(v):
      wi_set_rigidbody_physics_shape(handle, v)

   def mass():
      return wi_get_rigidbody_physics_mass(handle)

   def set_mass(v):
      wi_set_rigidbody_physics_mass(handle, v)

   def friction():
      return wi_get_rigidbody_physics_friction(handle)

   def set_friction(v):
      wi_set_rigidbody_physics_friction(handle, v)

   def restitution():
      return wi_get_rigidbody_physics_restitution(handle)

   def set_restitution(v):
      wi_set_rigidbody_physics_restitution(handle, v)

   def damping_linear():
      return wi_get_rigidbody_physics_damping_linear(handle)

   def set_damping_linear(v):
      wi_set_rigidbody_physics_damping_linear(handle, v)

   def damping_angular():
      return wi_get_rigidbody_physics_damping_angular(handle)

   def set_damping_angular(v):
      wi_set_rigidbody_physics_damping_angular(handle, v)

   def box_halfextents():
      return wi_get_rigidbody_physics_box_halfextents(handle)

   def set_box_halfextents(v):
      wi_set_rigidbody_physics_box_halfextents(handle, v)

   def sphere_radius():
      return wi_get_rigidbody_physics_sphere_radius(handle)

   def set_sphere_radius(v):
      wi_set_rigidbody_physics_sphere_radius(handle, v)

   def capsule_radius():
      return wi_get_rigidbody_physics_capsule_radius(handle)

   def set_capsule_radius(v):
      wi_set_rigidbody_physics_capsule_radius(handle, v)

   def capsule_height():
      return wi_get_rigidbody_physics_capsule_height(handle)

   def set_capsule_height(v):
      wi_set_rigidbody_physics_capsule_height(handle, v)

   def mesh_lod():
      return wi_get_rigidbody_physics_mesh_lod(handle)

   def set_mesh_lod(v):
      wi_set_rigidbody_physics_mesh_lod(handle, v)

   def disable_deactivation():
      return wi_get_rigidbody_physics_disable_deactivation(handle)

   def set_disable_deactivation(v):
      wi_set_rigidbody_physics_disable_deactivation(handle, v)

   def kinematic():
      return wi_get_rigidbody_physics_kinematic(handle)

   def set_kinematic(v):
      wi_set_rigidbody_physics_kinematic(handle, v)

constructor wi_rigidbody_component(h: int2):
   assert h[0] == wk_rigidbody
   return wi_rigidbody_component{h}

class wi_camera_component: wi_component
   def fov() -> float:
      return wi_camera_fov(handle)

   def set_fov(ang: float):
      wi_camera_set_fov(handle, ang)

   def zNear() -> float:
      return wi_camera_znear(handle)

   def set_zNear(f: float):
      wi_camera_set_znear(handle, f)

   def zFar() -> float:
      return wi_camera_zfar(handle)

   def set_zFar(f: float):
      wi_camera_set_zfar(handle, f)

   def dims() -> float2:
      return wi_camera_dims(handle)

   def set_dims(d: float2):
      wi_camera_set_dims(handle, d)

   def focal_length() -> float:
      return wi_camera_focal_length(handle)

   def set_focal_length(l: float):
      wi_camera_set_focal_length(handle, l)

   def update():
      wi_camera_update(handle)

   def eye():
      return wi_get_camera_eye(handle)

   def set_eye(v):
      wi_set_camera_eye(handle, v)

   def at():
      return wi_get_camera_at(handle)

   def set_at(v):
      wi_set_camera_at(handle, v)

   def up():
      return wi_get_camera_up(handle)

   def set_up(v):
      wi_set_camera_up(handle, v)




constructor wi_camera_component(h: int2):
   assert h[0] == wk_camera_comp
   return wi_camera_component{h}

class wi_transform_component: wi_component
   def translate(v: float3):
      wi_transform_translate(handle, v)

   def clear():
      wi_transform_clear(handle)

   // Decomposes transform into translation, rotation, scale
   def decompose() -> float3, quat, float3:
      let t, r, s = wi_decompose_transform(handle)
      return t, mk_quat(r), s

   def scaling() -> float3:
      return wi_transform_scaling(handle)

   def rotate(q: quat):
      wi_transform_rotate(handle, q.as_float4())

   def position() -> float3:
      return wi_transform_position(handle)

   def rotation() -> quat:
      return mk_quat(wi_transform_rotation(handle))

   def update():
      wi_transform_update_transform(handle)

   def rotate_roll_pitch_yaw(angles: float3):
      wi_transform_rotate_roll_pitch_yaw(handle, angles)

   def scale(s: float3):
      wi_transform_scale(handle, s)

   def lerp(a: wi_transform_component, b: wi_transform_component, t: float):
      wi_transform_lerp(handle, a.handle, b.handle, t)


constructor wi_transform_component(h: int2):
   assert h[0] == wk_transform_comp
   return wi_transform_component{h}

// Transform not attached to scene or entity, used for calculations.
class wi_free_transform: wi_transform_component
   def delete():
      wi_delete_transform(handle)

// Creates a unattached transform to be used for calculations.
def create_transform():
   return wi_free_transform{wi_create_transform()}


class wi_animation_component: wi_component
   def start():   
      return wi_get_animation_start(handle)

   def set_start(v):
      wi_set_animation_start(handle, v)

   def end():
      return wi_get_animation_end(handle)

   def set_end(v):
      wi_set_animation_end(handle, v)

   def timer():
      return wi_get_animation_timer(handle)

   def set_timer(v):
      wi_set_animation_timer(handle, v)

   def amount():
      return wi_get_animation_amount(handle)

   def set_amount(v):
      wi_set_animation_amount(handle, v)

   def speed():
      return wi_get_animation_speed(handle)

   def set_speed(v):
      wi_set_animation_speed(handle, v)

   def is_playing():
      return wi_is_animation_playing(handle)

   def is_looped():
      return wi_is_animation_looped(handle)

   def anim_length():
      return wi_get_animation_length(handle)

   def is_ended():
      return wi_get_is_animation_ended(handle)

   def play():
      wi_play_animation(handle)

   def pause():
      wi_pause_animation(handle)

   def stop():
      wi_stop_animation(handle)

   def set_looped(v: bool):
      wi_set_animation_looped(handle, v)

constructor wi_animation_component(h: int2):
   assert(h[0] == wk_animation_comp)
   return wi_animation_component{h}

struct wi_entity:
   handle: int2

   def is_valid() -> bool:
      return handle != INVALID_ENTITY_HANDLE

let INVALID_ENTITY = wi_entity{INVALID_ENTITY_HANDLE}

class wi_layer: wi_component
   def layer_mask():
      return wi_get_layer_mask(handle)

   def set_layer_mask(v):
      wi_set_layer_mask(handle, v)

   def propagation_mask():
      return wi_get_layer_propagation_mask(handle)

   def set_propagation_mask(v):
      wi_set_layer_propagation_mask(handle, v)

   def effective_mask():
      return propagation_mask() & layer_mask()

constructor wi_layer(h: int2):
   assert h[0] == wk_layer
   return wi_layer{h}

// Bone names for the humanoid component
enum wi_humanoid_bone:
   hb_Hips,			// Required
   hb_Spine,			// Required
   hb_Chest,
   hb_UpperChest,
   hb_Neck,
   hb_Head,			// Required
   hb_LeftEye,
   hb_RightEye,
   hb_Jaw,
   hb_LeftUpperLeg,	// Required
   hb_LeftLowerLeg,	// Required
   hb_LeftFoot,		// Required
   hb_LeftToes,
   hb_RightUpperLeg,	// Required
   hb_RightLowerLeg,	// Required
   hb_RightFoot,		// Required
   hb_RightToes,
   hb_LeftShoulder,
   hb_LeftUpperArm,	// Required
   hb_LeftLowerArm,	// Required
   hb_LeftHand,		// Required
   hb_RightShoulder,
   hb_RightUpperArm,	// Required
   hb_RightLowerArm,	// Required
   hb_RightHand,		// Required
   hb_LeftThumbMetacarpal,
   hb_LeftThumbProximal,
   hb_LeftThumbDistal,
   hb_LeftIndexProximal,
   hb_LeftIndexIntermediate,
   hb_LeftIndexDistal,
   hb_LeftMiddleProximal,
   hb_LeftMiddleIntermediate,
   hb_LeftMiddleDistal,
   hb_LeftRingProximal,
   hb_LeftRingIntermediate,
   hb_LeftRingDistal,
   hb_LeftLittleProximal,
   hb_LeftLittleIntermediate,
   hb_LeftLittleDistal,
   hb_RightThumbMetacarpal,
   hb_RightThumbProximal,
   hb_RightThumbDistal,
   hb_RightIndexIntermediate,
   hb_RightIndexDistal,
   hb_RightIndexProximal,
   hb_RightMiddleProximal,
   hb_RightMiddleIntermediate,
   hb_RightMiddleDistal,
   hb_RightRingProximal,
   hb_RightRingIntermediate,
   hb_RightRingDistal,
   hb_RightLittleProximal,
   hb_RightLittleIntermediate,
   hb_RightLittleDistal

class wi_humanoid_component: wi_component
   def default_look_direction():
      return wi_get_humanoid_default_look_direction(handle) 

   def set_default_look_direction(d: float3):
      wi_set_humanoid_default_look_direction(d)

   def head_rotation_max():
      return wi_get_humanoid_head_rotation_max(handle)

   def set_head_rotation_max(v):
      wi_set_humanoid_head_rotation_max(handle, v)

   def eye_rotation_max():
      return wi_get_humanoid_eye_rotation_max(handle)

   def set_eye_rotation_max(v):
      wi_set_humanoid_eye_rotation_max(handle, v)

   def head_rotation_speed():
      return wi_get_humanoid_head_rotation_speed(handle)

   def set_head_rotation_speed(v):
      wi_set_humanoid_head_rotation_speed(handle, v)

   def eye_rotation_speed():
      return wi_get_humanoid_eye_rotation_speed(handle)

   def set_eye_rotation_speed(v):
      wi_set_humanoid_eye_rotation_speed(handle, v)

   def look_at():
      return wi_get_humanoid_look_at(handle)

   def set_look_at(v):
      wi_set_humanoid_look_at(handle, v)

   def bone_count():
      return wi_humanoid_bone_count(handle)

   def bone(i: int):
      return wi_entity{wi_humanoid_bone(handle, i)}

   def is_lookat_enabled():
      return wi_humanoid_is_lookat_enabled(handle)

   def set_lookat_enabled(v: bool):
      wi_humanoid_set_lookat_enabled(handle, v)


constructor wi_humanoid_component(h: int2):
   assert h[0] == wk_humanoid
   return wi_humanoid_component{h}
   

enum wi_collider_shape:
   cs_spehere, cs_capsule, cs_plane

class wi_collider_component: wi_component
   def shape():
      return wi_get_collider_shape(handle)

   // Return value valid only as long as there are not ecs changes on the enity.
   def capsule() -> wi_primitive_capsule:
      return wi_primitive_capsule{wi_get_collider_capsule(handle)}

   def set_shape(s: int):
      wi_set_collider_shape(handle, s)

   def radius():
      return wi_get_collider_radius(handle)

   def set_radius(v: float):
      wi_set_collider_radius(handle, v)

   def offset():
      return wi_get_collider_offset(handle)

   def set_offset(v: float3):
      wi_set_collider_offset(handle, v)

   def tail():
      return wi_get_collider_tail(handle)

   def set_tail(v: float3):
      wi_set_collider_tail(handle, v)

   def set_gpu_enabled(v: bool):
      wi_set_collider_is_gpu_enabled(handle, v)

   def set_cpu_enabled(v: bool):
      wi_set_collider_is_cpu_enabled(handle, v)


constructor wi_collider_component(h: int2):
   assert h[0] == wk_collider
   return wi_collider_component{h}

enum wi_filter:
		FILTER_NONE = 0,
		FILTER_OPAQUE = 1 << 0,
		FILTER_TRANSPARENT = 1 << 1,
		FILTER_WATER = 1 << 2,
		FILTER_NAVIGATION_MESH = 1 << 3,
		FILTER_OBJECT_ALL = FILTER_OPAQUE | FILTER_TRANSPARENT | FILTER_WATER | FILTER_NAVIGATION_MESH,
		FILTER_COLLIDER = 1 << 4,
		FILTER_ALL = ~0


// Wrapper for scenes.  This can be saved long term, 
// it is only invalidated when the scene is deleted.
class wi_scene:
   handle: int2   

   def create_rigidbody_component(ent: wi_entity):
      return wi_rigidbody_component(wi_create_rigidbody_component(handle, ent.handle))

   def get_rigidbody_component(ent: wi_entity):
      return wi_rigidbody_component(wi_get_rigidbody_component(handle, ent.handle))

   def get_rigidbody_count():
      return wi_entity_rigidbody_count(handle)

   def get_rigidbody_entity(n: int):
      return wi_entity{wi_entity_rigidbody_get(handle, n)}

   def capsule_intersects(capsule: wi_primitive_capsule, filter_mask = FILTER_OPAQUE, layer_mask = ~0, lod = 0) -> wi_sphere_intersection:
      return wi_sphere_intersection{wi_scene_capsule_intersects(handle, capsule.handle, filter_mask, layer_mask, lod)}

   def sphere_intersects(sphere: wi_primitive_sphere, filter_mask = FILTER_OPAQUE, layer_mask = ~0, lod = 0) -> wi_sphere_intersection:
      return wi_sphere_intersection{wi_scene_sphere_intersects(handle, sphere.handle, filter_mask, layer_mask, lod)}

   def retarget_animation(dest: wi_entity, src: wi_entity, bake_data: bool) -> wi_entity:
      return wi_entity{wi_retarget_animation(handle, dest.handle, src.handle, bake_data)}

   def create_animation_component(ent: wi_entity):
      return wi_animation_component(wi_create_animation_component(handle, ent.handle))

   def get_animation_component(ent: wi_entity):
      return wi_animation_component(wi_get_animation_component(handle, ent.handle))

   def get_animation_count():
      return wi_entity_animation_count(handle)

   def get_animation_entity(n: int):
      return wi_entity{wi_entity_animation_get(handle, n)}

   def create_collider_component(ent: wi_entity):
      return wi_collider_component(wi_create_collider_component(handle, ent.handle))

   def get_collider_component(ent: wi_entity):
      return wi_collider_component(wi_get_collider_component(handle, ent.handle))

   def get_collider_count():
      return wi_entity_collider_count(handle)

   def get_collider_entity(n: int):
      return wi_entity{wi_entity_collider_get(handle, n)}

   def is_descendant_entity(entity: wi_entity, ancestor: wi_entity):
      return wi_is_descendant_entity(handle, entity.handle, ancestor.handle)
      
   def remove_entity(entity: wi_entity, recursive = true):
      wi_remove_entity(handle, entity.handle, recursive)

   def duplicate_entity(ent: wi_entity):
      return wi_entity{wi_duplicate_entity(handle, ent.handle)}

   // Loads a model. If "attached", it is rooted to an entity with a transform.
   def load_model(fname: string, attached: bool) -> wi_entity:
      return wi_entity{wi_load_model(handle, fname, attached)}

   def create_entity() -> wi_entity:
      return wi_entity{wi_create_entity()}

   def create_layer_component(ent: wi_entity):
      return wi_layer(wi_create_layer_component(handle, ent.handle))

   def get_layer_component(ent: wi_entity):
      return wi_layer(wi_get_layer_component(handle, ent.handle))

   def get_layer_count():
      return wi_entity_layer_count(handle)

   def get_layer_entity(n: int):
      return wi_entity{wi_entity_layer_get(handle, n)}

   def create_humanoid_component(ent: wi_entity):
      return wi_humanoid_component(wi_humanoid_component(wi_create_humanoid_component(handle, ent.handle)))

   def get_humanoid_component(ent):
      return wi_humanoid_component(wi_get_humanoid_component(handle, ent.handle))

   def get_humanoid_count():
      return wi_entity_humanoid_count(handle)

   def get_humanoid_entity(n: int):
      return wi_entity{wi_entity_humanoid_get(handle, n)}

   def create_camera_component(ent: wi_entity) -> wi_camera_component:
      return wi_camera_component(wi_create_camera_component(handle, ent.handle))

   def get_camera_component(ent: wi_entity) -> wi_camera_component:
      return wi_camera_component(wi_get_camera_component(handle, ent.handle))

   def get_camera_count() -> int:
      return wi_get_camera_count(handle)

   def get_camera_entity(n: int) -> wi_entity:
      return wi_entity{wi_get_camera_entity(handle, n)}

   def create_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_create_transform_component(handle, ent.handle))

   def find_entity_by_name(name: string, ancestor = INVALID_ENTITY) -> wi_entity:
      return wi_entity{wi_find_entity_by_name(handle, name, ancestor.handle)}

   def get_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_get_transform_component(handle, ent.handle))

   def create_name_component(ent: wi_entity) -> wi_name_component:
      return wi_name_component(wi_create_name_component(handle, ent.handle))

   def get_name_component(ent: wi_entity) -> wi_name_component:
      return wi_name_component(wi_get_name_component(handle, ent.handle))

   def get_names_count() -> int:
      return wi_entity_names_count(handle)

   def get_names_entity(i: int) -> wi_entity:
      return wi_entity{wi_entity_names_get(handle, i)}

   def delete():
      guard handle[1] != 0
      wi_delete_scene(handle)
      handle = int2{wk_scene, 0}

   def merge(src: wi_scene):
      wi_scene_merge(handle, src.handle)

   // Convenience method that sets the layer for the entity, creating the 
   // component if necessary.
   def set_layer(ent: wi_entity, layer: int):
      var lc = get_layer_component(ent)
      if lc.is_empty():
         lc = create_layer_component(ent)
      lc.set_layer_mask(layer)


def new_wi_scene() -> wi_scene:
   return wi_scene{wi_new_scene()}

def global_scene() -> wi_scene:
   return wi_scene{wi_global_scene()}


def with_temp_scene(body):
   let scene = new_wi_scene()
   body(scene)
   scene.delete()

def with_temp_object(obj, body):
   body(obj)
   obj.delete()

def with_temp_object(obj, obj2, body):
   body(obj, obj2)
   obj2.delete()
   obj.delete()

// Helper that calculates a capsule from the rididbody component data.  Capsule must be deleted
// when you're done with it.  Assuming position is center of entity.
def get_rigidbody_capsule(rb_tr: wi_transform_component, rb: wi_rigidbody_component) -> wi_primitive_capsule:
   // The btCapsule is y axis aligned, so we assume that.
   let epos, _rot, escale = rb_tr.decompose()
   let cheight = rb.capsule_height()
   let cradius = rb.capsule_radius()
   let vextent = float3_y*cheight*0.5*escale.y
   let rv = create_primitive_capsule()
   rv.set_base(epos - vextent)
   rv.set_tip(epos + vextent)
   rv.set_radius(cradius)
   //print("RBC scale={escale} pos={rb_tr.position()} base={rv.base()} tip={rv.tip()}")
   return rv
   

// Delta time for application fixed update.
def get_fixed_dt():
   return 1.0 / wi_get_fixed_update_rate()

enum_flags debug_draw_text_flags:
   dd_depth_test, dd_camera_facing, dd_camera_scaling

def draw_debug_text(text: string, pos: float3, flags = 0, color=float4{1.0, 1.0, 1.0, 1.0}, scaling = 1.0):
   wi_draw_debug_text(text, pos, flags, color, scaling)

struct wi_timer:
   handle: int2

   def record():
      return wi_timer_record(handle)

   def elapsed_seconds():
      return wi_timer_elapsed_seconds(handle)

   def elapsed():
      return wi_timer_elapsed(handle)

   def delete():
      wi_delete_timer(handle)

constructor wi_timer():
   return wi_timer{wi_create_timer()}


struct wi_font_params:
   handle: int2

   def delete():
      wi_delete_font_params(handle)

   def position():
      return wi_get_font_params_position(handle)

   def set_position(v):
      wi_set_font_params_position(handle, v)

   def size():
      return wi_font_params_get_size(handle)

   def set_size(s: int):
      wi_font_params_set_size(s)

   def scaling():
      return wi_get_font_params_scaling(handle)

   def set_scaling(v):
      wi_set_font_params_scaling(handle, v)

   def rotation():
      return wi_get_font_params_rotation(handle)

   def set_rotation(v):
      wi_set_font_params_rotation(handle, v)

   def spacing_x():
      return wi_get_font_params_spacing_x(handle)

   def set_spacing_x(v):
      wi_set_font_params_spacing_x(handle, v)

   def spacing_y():
      return wi_get_font_params_spacing_y(handle)

   def set_spacing_y(v):
      wi_set_font_params_spacing_y(handle, v)

   def h_align():
      return wi_get_font_params_h_align(handle)

   def set_h_align(v):
      wi_set_font_params_h_align(handle, v)

   def v_align():
      return wi_get_font_params_v_align(handle)

   def set_v_align(v):
      wi_set_font_params_v_align(handle, v)

   def color():
      let f4 = wi_get_font_params_color(handle)
      return color{f4[0], f4[1], f4[2], f4[3]}

   def set_color(v):
      if v is float4:
         wi_set_font_params_color(handle, v)
      else:
         wi_set_font_params_color(handle, float4{v[0], v[1], v[2], v[3]})

   def shadow_color():
      return wi_get_font_params_shadow_color(handle)

   def set_shadow_color(v):
      wi_set_font_params_shadow_color(handle, v)

   def h_wrap():
      return wi_get_font_params_h_wrap(handle)

   def set_h_wrap(v):
      wi_set_font_params_h_wrap(handle, v)

   def style():
      return wi_get_font_params_style(handle)

   def set_style(v):
      wi_set_font_params_style(handle, v)

   def softness():
      return wi_get_font_params_softness(handle)

   def set_softness(v):
      wi_set_font_params_softness(handle, v)

   def bolden():
      return wi_get_font_params_bolden(handle)

   def set_bolden(v):
      wi_set_font_params_bolden(handle, v)

   def shadow_offset_x():
      return wi_get_font_params_shadow_offset_x(handle)

   def set_shadow_offset_x(v):
      wi_set_font_params_shadow_offset_x(handle, v)

   def shadow_offset_y():
       return wi_get_font_params_shadow_offset_y(handle)

   def set_shadow_offset_y(v):
       wi_set_font_params_shadow_offset_y(handle, v)

   // position, size
   def cursor() -> float2, float2:
      return wi_get_font_params_cursor(handle)

   def set_cursor(pos, size):
      wi_set_font_params_cursor(handle, float4{pos.x, pos.y, size.x, size.y})

   def hdr_scaling():
      return wi_get_font_params_hdr_scaling(handle)

   def set_hdr_scaling(v):
      wi_set_font_params_hdr_scaling(handle, v)


constructor wi_font_params():
   return wi_font_params{wi_create_font_params()}


struct wi_sprite_font:
   handle: int2

   def delete():
      wi_delete_sprite_font(handle)

   def set_params(p: wi_font_params):
      wi_sprite_font_set_params(handle, p.handle)

   def text_size():
      return wi_sprite_font_text_size(handle)

   def set_text(txt: string):
      wi_sprite_font_set_text(handle, txt)

   def text() -> string:
      return wi_sprite_font_get_text(handle)

constructor wi_sprite_font():
   return wi_sprite_font{wi_create_sprite_font()}

// Settings for renderpath3d.set_ao
enum AO:
   AO_DISABLED	// no ambient occlusion
   AO_SSAO		// simple brute force screen space ambient occlusion
   AO_HBAO		// horizon based screen space ambient occlusion
   AO_MSAO		// multi scale screen space ambient occlusion
   AO_RTAO		// ray traced ambient occlusion


// wi::RenderPath3D
class wi_renderpath3d:
   handle: int2

   def physical_dims() -> int2:
      return wi_get_renderpath_physical_dims(handle)

   def logical_dims() -> float2:
      return wi_get_rendrpath_logical_dims(handle)

   def set_camera(cc: wi_camera_component):
      wi_renderpath3d_set_camera(handle, cc.handle)

   // Technically a RenderPath2d function.
   def add_font(sf: wi_sprite_font, layer = ""):
      wi_renderpath_add_font(handle, sf.handle, layer)

   def get_font_order(sf: wi_sprite_font) -> int:
      return wi_renderpath_get_font_order(handle, sf.handle)

   def set_font_order(sf: wi_sprite_font, order: int):
      wi_renderpath_set_font_order(handle, sf.handle, order)

   def remove_font(sf: wi_sprite_font):
      wi_renderpath_remove_font(handle, sf.handle)

   def clear_fonts():
      wi_renderpath_clear_fonts(handle)

   def exposure():
      return wi_get_renderpath3d_exposure(handle)

   def set_exposure(v):
      wi_set_renderpath3d_exposure(handle, v)

   def brightness():
      return wi_get_renderpath3d_brightness(handle)

   def set_brightness(v):
      wi_set_renderpath3d_brightness(handle, v)

   def contrast():
      return wi_get_renderpath3d_contrast(handle)

   def set_contrast(v):
      wi_set_renderpath3d_contrast(handle, v)

   def saturation():
      return wi_get_renderpath3d_saturation(handle)

   def set_saturation(v):
      wi_set_renderpath3d_saturation(handle, v)

   def bloom_threshold():
      return wi_get_renderpath3d_bloom_threshold(handle)

   def set_bloom_threshold(v):
      wi_set_renderpath3d_bloom_threshold(handle, v)

   def motion_blur_strength():
      return wi_get_renderpath3d_motion_blur_strength(handle)

   def set_motion_blur_strength(v):
      wi_set_renderpath3d_motion_blur_strength(handle, v)

   def depth_of_field_strength():
      return wi_get_renderpath3d_depth_of_field_strength(handle)

   def set_depth_of_field_strength(v):
      wi_set_renderpath3d_depth_of_field_strength(handle, v)

   def sharpen_filter_amount():
      return wi_get_renderpath3d_sharpen_filter_amount(handle)

   def set_sharpen_filter_amount(v):
      wi_set_renderpath3d_sharpen_filter_amount(handle, v)

   def outline_threshold():
      return wi_get_renderpath3d_outline_threshold(handle)

   def set_outline_threshold(v):
      wi_set_renderpath3d_outline_threshold(handle, v)

   def outline_thickness():
      return wi_get_renderpath3d_outline_thickness(handle)

   def set_outline_thickness(v):
      wi_set_renderpath3d_outline_thickness(handle, v)

   def outline_color():
      return wi_get_renderpath3d_outline_color(handle)

   def set_outline_color(v):
      wi_set_renderpath3d_outline_color(handle, v)

   def ao_range():
      return wi_get_renderpath3d_ao_range(handle)

   def set_ao_range(v):
      wi_set_renderpath3d_ao_range(handle, v)

   def ao_sample_count():
      return wi_get_renderpath3d_ao_sample_count(handle)

   def set_ao_sample_count(v):
      wi_set_renderpath3d_ao_sample_count(handle, v)

   def ao_power():
      return wi_get_renderpath3d_ao_power(handle)

   def set_ao_power(v):
      wi_set_renderpath3d_ao_power(handle, v)

   def chromatic_aberration_amount():
      return wi_get_renderpath3d_chromatic_aberration_amount(handle)

   def set_chromatic_aberration_amount(v):
      wi_set_renderpath3d_chromatic_aberration_amount(handle, v)

   def screen_space_shadow_sample_count():
      return wi_get_renderpath3d_screen_space_shadow_sample_count(handle)

   def set_screen_space_shadow_sample_count(v):
      wi_set_renderpath3d_screen_space_shadow_sample_count(handle, v)

   def screen_space_shadow_range():
      return wi_get_renderpath3d_screen_space_shadow_range(handle)

   def set_screen_space_shadow_range(v):
      wi_set_renderpath3d_screen_space_shadow_range(handle, v)

   def eye_adaption_key():
      return wi_get_renderpath3d_eye_adaption_key(handle)

   def set_eye_adaption_key(v):
      wi_set_renderpath3d_eye_adaption_key(handle, v)

   def eye_adaption_rate():
      return wi_get_renderpath3d_eye_adaption_rate(handle)

   def set_eye_adaption_rate(v):
      wi_set_renderpath3d_eye_adaption_rate(handle, v)

   def fsr_sharpness():
      return wi_get_renderpath3d_fsr_sharpness(handle)

   def set_fsr_sharpness(v):
      wi_set_renderpath3d_fsr_sharpness(handle, v)

   def fsr2_sharpness():
      return wi_get_renderpath3d_fsr2_sharpness(handle)

   def set_fsr2_sharpness(v):
      wi_set_renderpath3d_fsr2_sharpness(handle, v)

   def light_shafts_strength():
      return wi_get_renderpath3d_light_shafts_strength(handle)

   def set_light_shafts_strength(v):
      wi_set_renderpath3d_light_shafts_strength(handle, v)

   def raytraced_diffuse_image():
      return wi_get_renderpath3d_raytraced_diffuse_image(handle)

   def set_raytraced_diffuse_image(v):
      wi_set_renderpath3d_raytraced_diffuse_image(handle, v)

   def raytraced_reflections_range():
      return wi_get_renderpath3d_raytraced_reflections_range(handle)

   def set_raytraced_reflections_range(v):
      wi_set_renderpath3d_raytraced_reflections_range(handle, v)

   def reflection_roughness_cutoff():
      return wi_get_renderpath3d_reflection_roughness_cutoff(handle)

   def set_reflection_roughness_cutoff(v):
      wi_set_renderpath3d_reflection_roughness_cutoff(handle, v)

   def ssr_enabled():
      return wi_get_renderpath3d_ssr_enabled(handle)

   def set_ssr_enabled(v):
      wi_set_renderpath3d_ssr_enabled(handle, v)

   def raytraced_diffuse_enabled():
      return wi_get_renderpath3d_raytraced_diffuse_enabled(handle)

   def set_raytraced_diffuse_enabled(v):
      wi_set_renderpath3d_raytraced_diffuse_enabled(handle, v)

   def raytraced_reflection_enabled():
      return wi_get_renderpath3d_raytraced_reflection_enabled(handle)

   def set_raytraced_reflection_enabled(v):
      wi_set_renderpath3d_raytraced_reflection_enabled(handle, v)

   def shadows_enabled():
      return wi_get_renderpath3d_shadows_enabled(handle)

   def set_shadows_enabled(v):
      wi_set_renderpath3d_shadows_enabled(handle, v)

   def reflections_enabled():
      return wi_get_renderpath3d_reflections_enabled(handle)

   def set_reflections_enabled(v):
      wi_set_renderpath3d_reflections_enabled(handle, v)

   def fxaa_enabled():
      return wi_get_renderpath3d_fxaa_enabled(handle)

   def set_fxaa_enabled(v):
      wi_set_renderpath3d_fxaa_enabled(handle, v)

   def bloom_enabled():
      return wi_get_renderpath3d_bloom_enabled(handle)

   def set_bloom_enabled(v):
      wi_set_renderpath3d_bloom_enabled(handle, v)

   def color_grading_enabled():
      return wi_get_renderpath3d_color_grading_enabled(handle)

   def set_color_grading_enabled(v):
      wi_set_renderpath3d_color_grading_enabled(handle, v)

   def volume_lights_enabled():
      return wi_get_renderpath3d_volume_lights_enabled(handle)

   def set_volume_lights_enabled(v):
      wi_set_renderpath3d_volume_lights_enabled(handle, v)

   def light_shafts_enabled():
      return wi_get_renderpath3d_light_shafts_enabled(handle)

   def set_light_shafts_enabled(v):
      wi_set_renderpath3d_light_shafts_enabled(handle, v)

   def lens_flare_enabled():
      return wi_get_renderpath3d_lens_flare_enabled(handle)

   def set_lens_flare_enabled(v):
      wi_set_renderpath3d_lens_flare_enabled(handle, v)

   def motion_blur_enabled():
      return wi_get_renderpath3d_motion_blur_enabled(handle)

   def set_motion_blur_enabled(v):
      wi_set_renderpath3d_motion_blur_enabled(handle, v)

   def depth_of_field_enabled():
      return wi_get_renderpath3d_depth_of_field_enabled(handle)

   def set_depth_of_field_enabled(v):
      wi_set_renderpath3d_depth_of_field_enabled(handle, v)

   def eye_adaptation_enabled():
      return wi_get_renderpath3d_eye_adaptation_enabled(handle)

   def set_eye_adaptation_enabled(v):
      wi_set_renderpath3d_eye_adaptation_enabled(handle, v)

   def sharpen_filter_enabled():
      return wi_get_renderpath3d_sharpen_filter_enabled(handle)

   def set_sharpen_filter_enabled(v):
      wi_set_renderpath3d_sharpen_filter_enabled(handle, v)

   def outline_enabled():
      return wi_get_renderpath3d_outline_enabled(handle)

   def set_outline_enabled(v):
      wi_set_renderpath3d_outline_enabled(handle, v)

   def chromatic_aberration_enabled():
      return wi_get_renderpath3d_chromatic_aberration_enabled(handle)

   def set_chromatic_aberration_enabled(v):
      wi_set_renderpath3d_chromatic_aberration_enabled(handle, v)

   def dither_enabled():
      return wi_get_renderpath3d_dither_enabled(handle)

   def set_dither_enabled(v):
      wi_set_renderpath3d_dither_enabled(handle, v)

   def occlusion_culling_disabled():
      return wi_get_renderpath3d_occlusion_culling_disabled(handle)

   def set_occlusion_culling_disabled(v):
      wi_set_renderpath3d_occlusion_culling_disabled(handle, v)

   def scene_update_enabled():
      return wi_get_renderpath3d_scene_update_enabled(handle)

   def set_scene_update_enabled(v):
      wi_set_renderpath3d_scene_update_enabled(handle, v)

   def fsr_enabled():
      return wi_get_renderpath3d_fsr_enabled(handle)

   def set_fsr_enabled(v):
      wi_set_renderpath3d_fsr_enabled(handle, v)

   def fsr2_enabled():
      return wi_get_renderpath3d_fsr2_enabled(handle)

   def set_fsr2_enabled(v):
      wi_set_renderpath3d_fsr2_enabled(handle, v)

   def vxgi_resolve_full_resolution_enabled():
      return wi_get_renderpath3d_vxgi_resolve_full_resolution_enabled(handle)

   def set_vxgi_resolve_full_resolution_enabled(v):
      wi_set_renderpath3d_vxgi_resolve_full_resolution_enabled(handle, v)

   def ao_enabled():
      return wi_get_renderpath3d_ao_enabled(handle)

   def set_ao(v: int):
      wi_set_renderpath3d_ao(handle, v)


constructor wi_renderpath3d():
   let h = wi_get_renderpath3d()
   assert(h[0] == wk_renderpath3)
   return wi_renderpath3d{h}

struct wi_matrix:
   handle: int2

   def transform(v: float4) -> float4:
      return wi_transform_vector(handle, v)

   def transform_pos(v: float3):
      let r = transform(float4{v.x, v.y, v.z, 1.0})
      return float3{r.x, r.y, r.z}

   def transform_vector(v: float3):
      let r = transform(float4{v.x, v.y, v.z, 0.0})
      return float3{r.x, r.y, r.z}

   def delete():
      wi_delete_matrix(handle)

   def assign(rhs: wi_matrix):
      wi_assign_matrix(handle, rhs.handle)

   def assign_rows(r1 = float4_x, r2 = float4_y, r3 = float4_z, r4 = float4_w):
      wi_assign_rows(handle, r1, r2, r3, r4)

   def row(r: int):
      return wi_return_matrix_row(handle, r)

   def identity():
      wi_identity_matrix(handle)

   def translation(v: float3):
      wi_translation_matrix(handle, v)

   def get_translation() -> float3:
      return wi_get_matrix_translation(handle)

   def rotation_euler(angles: float3):
      wi_rotation_euler_matrix(handle, angles)

   def rotation_x(a: float):
      wi_rotation_x_matrix(handle, a)

   def rotation_y(a: float):
      wi_rotation_y_matrix(handle, a)
   
   def rotation_z(a: float):
      wi_rotation_z_matrix(handle, a)

   def rotation_quat(q: quat):
      wi_rotation_quat_matrix(handle, q.as_float4())

   def scaling(scale: float3):
      wi_scaling_matrix(handle, scale)

   def look_to(eyepos: float3, dir: float3, up = float3_y):
      wi_look_to_matrix(handle, eyepos, dir, up)

   def look_at(eyepos: float3, focuspos: float3, up = float3_y):
      wi_look_at_matrix(handle, eyepos, focuspos, up)

   def multiply(rhs: wi_matrix, result: wi_matrix):
      wi_multiply_matrix(handle, rhs.handle, result.handle)

   def add(rhs: wi_matrix, result: wi_matrix):
      wi_add_matrix(handle, rhs.handle, result.handle)

   def transposed(result: wi_matrix):
      wi_transpose_matrix(handle, result.handle)

   def inverted(result: wi_matrix):
      wi_invert_matrix(handle, result.handle)

// Creates a new uninitialized matrix.
def wi_matrix():
   return wi_matrix{wi_create_matrix4x4()}

def local_matrix(me:: wi_transform_component) -> wi_matrix:
   return wi_matrix{wi_get_transform_local_matrix(handle)}

def world_matrix(me:: wi_transform_component) -> wi_matrix:
   return wi_matrix{wi_get_transform_world_matrix(handle)}

def transform_by_matrix(me:: wi_transform_component, mat: wi_matrix):
   wi_transform_transform_matrix(handle, mat.handle)

def transform(me:: wi_camera_component, mat: wi_matrix):
   wi_transform_camera_set_matrix(handle, mat.handle)

def transform(me:: wi_camera_component, tr: wi_transform_component):
   wi_transform_camera(handle, tr.handle)

// Copies the transform information from another transform.
def copy_from(me:: wi_transform_component, other: wi_transform_component):
   with_temp_object(other.world_matrix()) om:
      clear()
      transform_by_matrix(om)

def entity(me:: wi_sphere_intersection):
   return wi_entity{wi_get_sphere_intersection_result_entity(handle)}


