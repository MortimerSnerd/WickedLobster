// Main import for wisupport.  Helper functions in the global 
// namespace go here, and other functions and types under the "wi"
// namespace go into wisupport_core.lobster.
import wisupport_core

// Lots of things have handle members that are invalid if handle[1] == 0
def is_empty(x) -> bool:
   return x.handle[1] == 0

def has_value(x) -> bool:
   return not is_empty(x)

def intersects(ray:: wi.primitive_ray, other: wi.primitive_capsule) -> bool, float, float3:
   return wiraw.ray_capsule_intersects(handle, other.handle)

def intersects(me:: wi.primitive_capsule, other: wi.primitive_sphere) -> bool, float, float3:
   return wiraw.capsule_sphere_intersects(handle, other.handle)

def intersects(ray:: wi.primitive_ray, other: wi.primitive_sphere) -> bool, float, float3:
   return wiraw.ray_capsule_intersects(handle, other.handle)

def local_matrix(me:: wi.transform_component) -> wi.matrix:
   return wi.matrix{wiraw.get_transform_local_matrix(handle)}

def world_matrix(me:: wi.transform_component) -> wi.matrix:
   return wi.matrix{wiraw.get_transform_world_matrix(handle)}

def transform_by_matrix(me:: wi.transform_component, mat: wi.matrix):
   wiraw.transform_transform_matrix(handle, mat.handle)

def transform(me:: wi.camera_component, mat: wi.matrix):
   wiraw.transform_camera_set_matrix(handle, mat.handle)

def transform(me:: wi.camera_component, tr: wi.transform_component):
   wiraw.transform_camera(handle, tr.handle)

// Copies the transform information from another transform.
def copy_from(me:: wi.transform_component, other: wi.transform_component):
   with_temp_object(other.world_matrix()) om:
      clear()
      transform_by_matrix(om)

def debug_string(me:: wi.sphere_intersection, indlev = 0):
   let ind0 = repeat_string("\t", indlev)
   let ind1 = repeat_string("\t", indlev+1)
   return "{ind0}sphere_intersection{{\n{ind1}entity: {entity()},\n" + 
          "{ind1}position: {position()},\n{ind1}n={normal()}\n" +
          "{ind1}velocity: {velocity()}\n{ind1}depth: {depth()}\n{ind0}}}"
      

