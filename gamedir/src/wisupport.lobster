// Wrappers for the raw builtin interface to make it easier to use.

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

   def create_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_create_transform_component(handle, ent.handle))

   def entity_find_by_name(name: string, ancestor = INVALID_ENTITY) -> wi_entity:
      return wi_entity{wi_entity_find_by_name(handle, name, ancestor.handle)}

   def get_transform_component(ent: wi_entity) -> wi_transform_component:
      return wi_transform_component(wi_get_transform_component(handle, ent.handle))

def new_wi_scene() -> wi_scene:
   return wi_scene{wi_new_scene()}

def global_scene() -> wi_scene:
   return wi_scene{wi_global_scene()}
