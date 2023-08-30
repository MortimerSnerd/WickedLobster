// Wrappers for the raw builtin interface to make it easier to use.
//
// Warning: angles are in radians, not the default of degrees as was the case
//          with the built in Lobster engine.
import core.quat

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
   wk_scene, wk_entity, wk_name_comp, wk_camera_comp, wk_transform_comp, wk_renderpath3

// Invalid entity sentinel.
let INVALID_ENTITY_HANDLE = int2{wk_entity, 0}

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


constructor wi_camera_component(h: int2):
   assert h[0] == wk_camera_comp
   return wi_camera_component{h}

class wi_transform_component: wi_component
   def translate(v: float3):
      wi_transform_translate(handle, v)

   def clear():
      wi_transform_clear(handle)

   def rotate(q: quat):
      wi_transform_rotate(handle, q.as_float4())

   def position() -> float3:
      return wi_transform_position(handle)

   def rotation() -> float4:
      return wi_transform_rotation(handle)

   def update_transform():
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

// wi::RenderPath3D
class wi_renderpath3d:
   handle: int2

   def set_camera(cc: wi_camera_component):
      wi_renderpath3d_set_camera(handle, cc.handle)

constructor wi_renderpath3d():
   let h = wi_get_renderpath3d()
   assert(h[0] == wk_renderpath3)
   return wi_renderpath3d{h}

struct wi_entity:
   handle: int2

   def is_valid() -> bool:
      return handle != INVALID_ENTITY_HANDLE

let INVALID_ENTITY = wi_entity{INVALID_ENTITY_HANDLE}

// Wrapper for scenes.  This can be saved long term, 
// it is only invalidated when the scene is deleted.
class wi_scene:
   handle: int2   
      
   // Loads a model. If "attached", it is rooted to an entity with a transform.
   def load_model(fname: string, attached: bool) -> wi_entity:
      return wi_entity{wi_load_model(handle, fname, attached)}

   def create_entity() -> wi_entity:
      return wi_entity{wi_create_entity()}

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

def new_wi_scene() -> wi_scene:
   return wi_scene{wi_new_scene()}

def global_scene() -> wi_scene:
   return wi_scene{wi_global_scene()}

def with_temp_scene(body):
   let scene = new_wi_scene()
   body(scene)
   scene.delete()

// Delta time for application fixed update.
def get_fixed_dt():
   return 1.0 / wi_get_fixed_update_rate()

def draw_debug_text(text: string, pos: float3, color=float4{1.0, 1.0, 1.0, 1.0}, scaling = 1.0):
   wi_draw_debug_text(text, pos, color, scaling)
