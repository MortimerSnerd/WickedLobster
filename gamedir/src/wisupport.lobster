// Wrappers for the raw builtin interface to make it easier to use.
//
// Warning: angles are in radians, not the default of degrees as was the case
//          with the built in Lobster engine.
import core.quat

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

// Name component.  This is only valid up up to the point that
// components are added/removed. 
class wi_name_component:
   handle: int2

   def set_name(n: string):
      wi_nc_set_name(handle, n)

constructor wi_name_component(h: int2):
   assert h[0] == wk_name_comp
   return wi_name_component{h}


class wi_camera_component:
   handle: int2

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

class wi_transform_component:
   handle: int2

   def is_empty():
      return handle[1] == 0

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
      
   def load_model(fname: string, attached: bool) -> wi_entity:
      return wi_entity{wi_load_model(handle, fname, attached)}

   def create_entity() -> wi_entity:
      return wi_entity{wi_create_entity()}

   def create_name_component(ent: wi_entity) -> wi_name_component:
      return wi_name_component(wi_create_name_component(handle, ent.handle))

   def create_camera_component(ent: wi_entity) -> wi_camera_component:
      return wi_camera_component(wi_create_camera_component(handle, ent.handle))

   def get_camera_component(ent: wi_entity) -> wi_camera_component:
      return wi_camera_component(wi_get_camera_component(handle, ent.handle))

   def create_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_create_transform_component(handle, ent.handle))

   def find_entity_by_name(name: string, ancestor = INVALID_ENTITY) -> wi_entity:
      return wi_entity{wi_find_entity_by_name(handle, name, ancestor.handle)}

   def get_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_get_transform_component(handle, ent.handle))


def new_wi_scene() -> wi_scene:
   return wi_scene{wi_new_scene()}

def global_scene() -> wi_scene:
   return wi_scene{wi_global_scene()}
