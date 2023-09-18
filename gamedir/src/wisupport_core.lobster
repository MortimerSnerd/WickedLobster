// Wrappers for the raw builtin interface to make it easier to use.
//
// Warning: angles are in radians, not the default of degrees as was the case
//          with the built in Lobster engine.
import color

import core.matrix
import core.quat

namespace wi

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
   return wiraw.get_input_down(button, playerindex)

def input_press(button: int, playerindex = 0):
   return wiraw.get_input_press(button, playerindex)

def input_hold(button: int, frames = 30, continuous = false, playerindex = 0):
   return wiraw.get_input_hole(button, frames, continuous, playerindex)

def input_get_analog(axis: int, playerindex = 0):
   return wiraw.input_get_analog(axis, playerindex)

// Returns position, scroll delta and pressure of mouse pointer
def input_get_pointer() -> float2, float, float:
   let pk = wiraw.input_get_pointer()
   return float2{pk.x, pk.y}, pk.z, pk.w

// Sets the pointer position and other properties.
def input_set_pointer(pos: float2, scroll_delta = 0.0, pressure = 0.0):
   let v = float4{pos.x, pos.y, scroll_delta, pressure}
   wiraw.input_set_pointer(v)

def input_hide_pointer(v: bool):
   wiraw.input_hide_pointer(v)

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
   wiraw.backlog(lev_error, msg)

def warning(msg: string):
   wiraw.backlog(lev_warning, msg)

def info(msg: string):
   wiraw.backlog(lev_default, msg)

// Handle kinds used internally to tell the difference between the different
// handles.
enum wokind:
   wk_scene, wk_entity, wk_name_comp, wk_camera_comp, wk_transform_comp, wk_renderpath3,
   wk_timer, wk_sprite_font, wk_font_params, wk_humanoid, wk_layer, wk_collider,
   wk_matrix, wk_animation_comp, wk_sphere, wk_sphereintersection, wk_capsule, 
   wk_rigidbody, wk_object_comp, wk_hier_comp, wk_light_comp, wk_resource, wk_sound_comp,
   wk_sound, wk_sound_instance, wk_decal_comp

// Invalid entity sentinel.
let INVALID_ENTITY_HANDLE = int2{wk_entity, 0}

struct gresource: 
   handle: int2

   def set_outdated():
      wiraw.set_resource_outdated(handle)
   
constructor gresource(h: int2):
   assert h[0] == wk_resource
   return gresource{h}

struct matrix:
   handle: resource<alien>

   def transform(v: float4) -> float4:
      return wiraw.transform_vector(handle, v)

   def transform_pos(v: float3):
      let r = transform(float4{v.x, v.y, v.z, 1.0})
      return float3{r.x, r.y, r.z}

   def transform_vector(v: float3):
      let r = wiraw.transform_vector(handle, float4{v.x, v.y, v.z, 0.0})
      return float3{r.x, r.y, r.z}

   def assign(rhs: matrix):
      wiraw.assign_matrix(handle, rhs.handle)

   def assign_rows(r1 = float4_x, r2 = float4_y, r3 = float4_z, r4 = float4_w):
      wiraw.assign_rows(handle, r1, r2, r3, r4)

   def row(r: int):
      return wiraw.return_matrix_row(handle, r)

   def debug_string(ind=0):
      let ind0 = repeat_string("\t", ind)
      let ind1 = repeat_string("\t", ind+1)
      var rv = "{ind0}matrix{{\n"
      for(4) r:
         let v = row(r)
         rv += "{ind1}{v.x} {v.y} {v.z} {v.w}"
         if r == 3:
            rv += "}}\n"
         else:
            rv += "\n"
      return rv

   def identity():
      wiraw.identity_matrix(handle)

   def translation(v: float3):
      wiraw.translation_matrix(handle, v)

   def get_translation() -> float3:
      return wiraw.get_matrix_translation(handle)

   def rotation_euler(angles: float3):
      wiraw.rotation_euler_matrix(handle, angles)

   def rotation_x(a: float):
      wiraw.rotation_x_matrix(handle, a)

   def rotation_y(a: float):
      wiraw.rotation_y_matrix(handle, a)
   
   def rotation_z(a: float):
      wiraw.rotation_z_matrix(handle, a)

   def rotation_quat(q: quat):
      wiraw.rotation_quat_matrix(handle, q.as_float4())

   def scaling(scale: float3):
      wiraw.scaling_matrix(handle, scale)

   def look_to(eyepos: float3, dir: float3, up = float3_y):
      wiraw.look_to_matrix(handle, eyepos, dir, up)

   def look_at(eyepos: float3, focuspos: float3, up = float3_y):
      wiraw.look_at_matrix(handle, eyepos, focuspos, up)

   def multiply(rhs: matrix, result: matrix):
      wiraw.multiply_matrix(handle, rhs.handle, result.handle)

   def add(rhs: matrix, result: matrix):
      wiraw.add_matrix(handle, rhs.handle, result.handle)

   def transposed(result: matrix):
      wiraw.transpose_matrix(handle, result.handle)

   def inverted(result: matrix):
      wiraw.invert_matrix(handle, result.handle)

// Creates a new uninitialized matrix.
def matrix():
   return matrix{wiraw.create_matrix4x4()}

struct ecs_entity:
   handle: int2

   def is_valid() -> bool:
      return handle != INVALID_ENTITY_HANDLE

let INVALID_ENTITY = ecs_entity{INVALID_ENTITY_HANDLE}

struct primitive_ray:
   handle: resource<alien>

   def origin():
      return wiraw.get_primitive_ray_origin(handle)

   def set_origin(v):
      wiraw.set_primitive_ray_origin(handle, v)

   def t_min():
      return wiraw.get_primitive_ray_t_min(handle)

   def set_t_min(v):
      wiraw.set_primitive_ray_t_min(handle, v)

   def direction():
      return wiraw.get_primitive_ray_direction(handle)

   def set_direction(v):
      wiraw.set_primitive_ray_direction(handle, v)

   def t_max():
      return wiraw.get_primitive_ray_t_max(handle)

   def set_t_max(v):
      wiraw.set_primitive_ray_t_max(handle, v)

   def direction_inverse():
      return wiraw.get_primitive_ray_direction_inverse(handle)

   def set_direction_inverse(v):
      wiraw.set_primitive_ray_direction_inverse(handle, v)


def create_primitive_ray():
   return primitive_ray{wiraw.create_primitive_ray()}

def make_ray_from(origin: float3, direction: float3, tmin = 0.0, tmax = 1.0e6):
   return primitive_ray{wiraw.make_ray_from(origin, direction, tmin, tmax)}

struct primitive_capsule:
   handle: resource<alien>

   def base():
      return wiraw.get_primitive_capsule_base(handle)

   def set_base(v):
      wiraw.set_primitive_capsule_base(handle, v)

   def tip():
      return wiraw.get_primitive_capsule_tip(handle)

   def set_tip(v):
      wiraw.set_primitive_capsule_tip(handle, v)

   def radius():
      return wiraw.get_primitive_capsule_radius(handle)

   def set_radius(v):
      wiraw.set_primitive_capsule_radius(handle, v)

   // Returns bool, position, normal, penetration depth
   def intersects(other: primitive_capsule) -> bool, float3, float3, float:
      return wiraw.capsule_capsule_intersects(handle, other.handle)

   // Updates the capsule position by d_t.
   def translate(d_p: float3):
      set_base(base() + d_p)
      set_tip(tip() + d_p)


def create_primitive_capsule() -> primitive_capsule:
   return primitive_capsule{wiraw.create_primitive_capsule()}

struct primitive_sphere:
   handle: resource<alien>

   def center():
      return wiraw.get_primitive_sphere_center(handle)

   def set_center(v):
      wiraw.set_primitive_sphere_center(handle, v)

   def radius():
      return wiraw.get_primitive_sphere_radius(handle)

   def set_radius(v):
      wiraw.set_primitive_sphere_radius(handle, v)

   def delete():
      wiraw.delete_primitive_sphere(handle)

   def intersects(other: primitive_sphere) -> bool, float, float3:
      return wiraw.sphere_sphere_intersects(handle, other.handle)

   // Returns bool, dist, direction
   def intersects(other: primitive_capsule) -> bool, float, float3:
      return wiraw.sphere_capsule_intersects(handle, other.handle)

def create_primitive_sphere() -> primitive_sphere:
   return primitive_sphere{wiraw.create_primitive_sphere()}

struct sphere_intersection:
   handle: resource<alien>

   def entity():
      return ecs_entity{wiraw.get_sphere_intersection_result_entity(handle)}

   def set_entity(v):
      wiraw.set_sphere_intersection_result_entity(handle, v.handle)

   def position():
      return wiraw.get_sphere_intersection_result_position(handle)

   def set_position(v):
      wiraw.set_sphere_intersection_result_position(handle, v)

   def normal():
      return wiraw.get_sphere_intersection_result_normal(handle)

   def set_normal(v):
      wiraw.set_sphere_intersection_result_normal(handle, v)

   def velocity():
      return wiraw.get_sphere_intersection_result_velocity(handle)

   def set_velocity(v):
      wiraw.set_sphere_intersection_result_velocity(handle, v)

   def depth():
      return wiraw.get_sphere_intersection_result_depth(handle)

   def set_depth(v):
      wiraw.set_sphere_intersection_result_depth(handle, v)


struct ray_intersection:
   handle: resource<alien>

   def entity():
      return ecs_entity{wiraw.get_ray_intersection_entity(handle)}

   def set_entity(v: ecs_entity):
      wiraw.set_ray_intersection_entity(handle, v.handle)

   def position():
      return wiraw.get_ray_intersection_position(handle)

   def set_position(v):
      wiraw.set_ray_intersection_position(handle, v)

   def normal():
      return wiraw.get_ray_intersection_normal(handle)

   def set_normal(v):
      wiraw.set_ray_intersection_normal(handle, v)

   def velocity():
      return wiraw.get_ray_intersection_velocity(handle)

   def set_velocity(v):
      wiraw.set_ray_intersection_velocity(handle, v)

   def distance():
      return wiraw.get_ray_intersection_distance(handle)

   def set_distance(v):
      wiraw.set_ray_intersection_distance(handle, v)

   def subset_index():
      return wiraw.get_ray_intersection_subset_index(handle)

   def set_subset_index(v):
      wiraw.set_ray_intersection_subset_index(handle, v)

   def vertex_id0():
      return wiraw.get_ray_intersection_vertex_id0(handle)

   def set_vertex_id0(v):
      wiraw.set_ray_intersection_vertex_id0(handle, v)

   def vertex_id1():
      return wiraw.get_ray_intersection_vertex_id1(handle)

   def set_vertex_id1(v):
      wiraw.set_ray_intersection_vertex_id1(handle, v)

   def vertex_id2():
      return wiraw.get_ray_intersection_vertex_id2(handle)

   def set_vertex_id2(v):
      wiraw.set_ray_intersection_vertex_id2(handle, v)

   def bary():
      return wiraw.get_ray_intersection_bary(handle)

   def set_bary(v):
      wiraw.set_ray_intersection_bary(handle, v)

   def orientation():
      return matrix(wiraw.get_ray_intersection_orientation(handle))

   def set_orientation(v: matrix):
      wiraw.set_ray_intersection_orientation(handle, v.handle)

   def debug_string(indlev = 0):
      let ind0 = repeat_string("\t", indlev)
      let ind1 = repeat_string("\t", indlev+1)
      let ent = this.entity()
      return "{ind0}ray_intersection{{\n"+
             "{ind1}entity: {ent}\n" +  
             "{ind1}position: {position()}\n" +
             "{ind1}normal: {normal()}\n" + 
             "{ind1}velocity: {velocity()}\n" +
             "{ind1}distance: {distance()}\n" + 
             "{ind1}subset_index: {subset_index()}\n" +
             "{ind1}vertex_id0: {vertex_id0()}\n" + 
             "{ind1}vertex_id1: {vertex_id1()}\n" + 
             "{ind1}vertex_id2: {vertex_id2()}\n" + 
             "{ind1}bary: {bary()}\n{ind0}}}"

// Note: for components, when you get one, do what you need to do with it
// and then discard it.  These can be invalidated by any code that
// creates or removes components, and the result would probably be a crash.

// Base class for convenience, this is not how the C++ code is structred.
class ecs_component:
   handle: int2

class light_component: ecs_component
   def type():
      return wiraw.get_light_type(handle)

   def set_type(v):
      wiraw.set_light_type(handle, v)

   def color() -> color:
      let c =  wiraw.get_light_color(handle)
      return color{c.x, c.y, c.z, 1.0}

   def set_color(v: color):
      wiraw.set_light_color(handle, float3{v.x, v.y, v.z})

   def intensity():
      return wiraw.get_light_intensity(handle)

   def set_intensity(v):
      wiraw.set_light_intensity(handle, v)

   def range():
      return wiraw.get_light_range(handle)

   def set_range(v):
      wiraw.set_light_range(handle, v)

   def outer_cone_angle():
      return wiraw.get_light_outer_cone_angle(handle)

   def set_outer_cone_angle(v):
      wiraw.set_light_outer_cone_angle(handle, v)

   def inner_cone_angle():
      return wiraw.get_light_inner_cone_angle(handle)

   def set_inner_cone_angle(v):
      wiraw.set_light_inner_cone_angle(handle, v)

   def radius():
      return wiraw.get_light_radius(handle)

   def set_radius(v):
      wiraw.set_light_radius(handle, v)

   //NB renamed because can't override length()
   def get_length():
      return wiraw.get_light_length(handle)

   def set_length(v):
      wiraw.set_light_length(handle, v)

   def casts_shadow():
      return wiraw.get_light_casts_shadow(handle)

   def set_casts_shadow(v):
      wiraw.set_light_casts_shadow(handle, v)

   def volumetrics_enabled():
      return wiraw.get_light_volumetrics_enabled(handle)

   def set_volumetrics_enabled(v):
      wiraw.set_light_volumetrics_enabled(handle, v)

   def visualizer_enabled():
      return wiraw.get_light_visualizer_enabled(handle)

   def set_visualizer_enabled(v):
      wiraw.set_light_visualizer_enabled(handle, v)

   def is_static():
      return wiraw.get_light_is_static(handle)

   def set_is_static(v):
      wiraw.set_light_is_static(handle, v)

   def volumetric_clouds_enabled():
      return wiraw.get_light_volumetric_clouds_enabled(handle)

   def set_volumetric_clouds_enabled(v):
      wiraw.set_light_volumetric_clouds_enabled(handle, v)

constructor light_component(h: int2):
   assert h[0] == wk_light_comp
   return light_component{h}

// Hierarchy component.
class hierarchy_component: ecs_component
   def parent_id():
      return wiraw.get_hierarchy_parent_id(handle)

   def set_parent_id(v):
      wiraw.set_hierarchy_parent_id(handle, v)

   def layermask_bind():
      return wiraw.get_hierarchy_layermask_bind(handle)

   def set_layermask_bind(v):
      wiraw.set_hierarchy_layermask_bind(handle, v)

constructor hierarchy_component(h: int2):
   assert h[0] == wk_hier_comp
   return hierarchy_component{h}

// Name component.  This is only valid up up to the point that
// components are added/removed. 
class name_component: ecs_component
   def set_name(n: string):
      wiraw.nc_set_name(handle, n)

   def get_name() -> string:
      return wiraw.nc_get_name(handle)

constructor name_component(h: int2):
   assert h[0] == wk_name_comp
   return name_component{h}


class rigidbody_component: ecs_component
   def shape():
      return wiraw.get_rigidbody_physics_shape(handle)

   def set_shape(v):
      wiraw.set_rigidbody_physics_shape(handle, v)

   def mass():
      return wiraw.get_rigidbody_physics_mass(handle)

   def set_mass(v):
      wiraw.set_rigidbody_physics_mass(handle, v)

   def friction():
      return wiraw.get_rigidbody_physics_friction(handle)

   def set_friction(v):
      wiraw.set_rigidbody_physics_friction(handle, v)

   def restitution():
      return wiraw.get_rigidbody_physics_restitution(handle)

   def set_restitution(v):
      wiraw.set_rigidbody_physics_restitution(handle, v)

   def damping_linear():
      return wiraw.get_rigidbody_physics_damping_linear(handle)

   def set_damping_linear(v):
      wiraw.set_rigidbody_physics_damping_linear(handle, v)

   def damping_angular():
      return wiraw.get_rigidbody_physics_damping_angular(handle)

   def set_damping_angular(v):
      wiraw.set_rigidbody_physics_damping_angular(handle, v)

   def box_halfextents():
      return wiraw.get_rigidbody_physics_box_halfextents(handle)

   def set_box_halfextents(v):
      wiraw.set_rigidbody_physics_box_halfextents(handle, v)

   def sphere_radius():
      return wiraw.get_rigidbody_physics_sphere_radius(handle)

   def set_sphere_radius(v):
      wiraw.set_rigidbody_physics_sphere_radius(handle, v)

   def capsule_radius():
      return wiraw.get_rigidbody_physics_capsule_radius(handle)

   def set_capsule_radius(v):
      wiraw.set_rigidbody_physics_capsule_radius(handle, v)

   def capsule_height():
      return wiraw.get_rigidbody_physics_capsule_height(handle)

   def set_capsule_height(v):
      wiraw.set_rigidbody_physics_capsule_height(handle, v)

   def mesh_lod():
      return wiraw.get_rigidbody_physics_mesh_lod(handle)

   def set_mesh_lod(v):
      wiraw.set_rigidbody_physics_mesh_lod(handle, v)

   def disable_deactivation():
      return wiraw.get_rigidbody_physics_disable_deactivation(handle)

   def set_disable_deactivation(v):
      wiraw.set_rigidbody_physics_disable_deactivation(handle, v)

   def kinematic():
      return wiraw.get_rigidbody_physics_kinematic(handle)

   def set_kinematic(v):
      wiraw.set_rigidbody_physics_kinematic(handle, v)

constructor rigidbody_component(h: int2):
   assert h[0] == wk_rigidbody
   return rigidbody_component{h}

class camera_component: ecs_component
   def fov() -> float:
      return wiraw.camera_fov(handle)

   def set_fov(ang: float):
      wiraw.camera_set_fov(handle, ang)

   def zNear() -> float:
      return wiraw.camera_znear(handle)

   def set_zNear(f: float):
      wiraw.camera_set_znear(handle, f)

   def zFar() -> float:
      return wiraw.camera_zfar(handle)

   def set_zFar(f: float):
      wiraw.camera_set_zfar(handle, f)

   def dims() -> float2:
      return wiraw.camera_dims(handle)

   def set_dims(d: float2):
      wiraw.camera_set_dims(handle, d)

   def focal_length() -> float:
      return wiraw.camera_focal_length(handle)

   def set_focal_length(l: float):
      wiraw.camera_set_focal_length(handle, l)

   def update():
      wiraw.camera_update(handle)

   def eye():
      return wiraw.get_camera_eye(handle)

   def set_eye(v):
      wiraw.set_camera_eye(handle, v)

   def at():
      return wiraw.get_camera_at(handle)

   def set_at(v):
      wiraw.set_camera_at(handle, v)

   def up():
      return wiraw.get_camera_up(handle)

   def set_up(v):
      wiraw.set_camera_up(handle, v)

   def projection() -> matrix:
      return matrix{wiraw.get_camera_projection(handle)}

   def view() -> matrix:
      return matrix{wiraw.get_camera_view(handle)}

   def VP() -> matrix:
      return matrix{wiraw.get_camera_VP(handle)}

   def inverse_projection() -> matrix:
      return matrix{wiraw.get_camera_inverse_projection(handle)}

   def inverse_view() -> matrix:
      return matrix{wiraw.get_camera_inverse_view(handle)}

   def inverse_VP() -> matrix:
      return matrix{wiraw.get_camera_inverse_VP(handle)}

constructor camera_component(h: int2):
   assert h[0] == wk_camera_comp
   return camera_component{h}

class decal_component: ecs_component
   def slope_blend_power():
      return wiraw.get_decal_component_slope_blend_power(handle)

   def set_slope_blend_power(v):
      wiraw.set_decal_component_slope_blend_power(handle, v)

   def texture():
      return gresource(wiraw.get_decal_component_texture(handle))

   def set_texture(v: gresource):
      wiraw.set_decal_component_texture(handle, v.handle)

   def normal():
      return gresource(wiraw.get_decal_component_normal(handle))

   def set_normal(v: gresource):
      wiraw.set_decal_component_normal(handle, v.handle)

   def surfacemap():
      return gresource(wiraw.get_decal_component_surfacemap(handle))

   def set_surfacemap(v: gresource):
      wiraw.set_decal_component_surfacemap(handle, v.ent)

   def is_base_color_only_alpha():
      return wiraw.get_decal_component_is_base_color_only_alpha(handle)

   def set_is_base_color_only_alpha(v):
      wiraw.set_decal_component_is_base_color_only_alpha(handle, v)

constructor decal_component(h: int2):
   assert h[0] == wk_decal_comp
   return decal_component{h}

class transform_component: ecs_component
   def translate(v: float3):
      wiraw.transform_translate(handle, v)

   def clear():
      wiraw.transform_clear(handle)

   def dirty():
      return wiraw.get_transform_dirty(handle)

   def set_dirty(v):
      wiraw.set_transform_dirty(handle, v)

   // Decomposes transform into translation, rotation, scale
   def decompose() -> float3, quat, float3:
      let t, r, s = wiraw.decompose_transform(handle)
      return t, mk_quat(r), s

   def scaling() -> float3:
      return wiraw.transform_scaling(handle)

   def rotate(q: quat):
      wiraw.transform_rotate(handle, q.as_float4())

   def position() -> float3:
      return wiraw.transform_position(handle)

   def rotation() -> quat:
      return mk_quat(wiraw.transform_rotation(handle))

   def update():
      wiraw.transform_update_transform(handle)

   def rotate_roll_pitch_yaw(angles: float3):
      wiraw.transform_rotate_roll_pitch_yaw(handle, angles)

   def scale(s: float3):
      wiraw.transform_scale(handle, s)

   def lerp(a: transform_component, b: transform_component, t: float):
      wiraw.transform_lerp(handle, a.handle, b.handle, t)

   def scale_local():
      return wiraw.get_transform_scale_local(handle)

   def set_scale_local(v):
      wiraw.set_transform_scale_local(handle, v)

   def rotation_local():
      return mk_quat(wiraw.get_transform_rotation_local(handle))

   def set_rotation_local(v: quat):
      wiraw.set_transform_rotation_local(handle, v.as_float4)

   def translation_local():
      return wiraw.get_transform_translation_local(handle)

   def set_translation_local(v):
      wiraw.set_transform_translation_local(handle, v)



constructor transform_component(h: int2):
   assert h[0] == wk_transform_comp
   return transform_component{h}

// Transform not attached to scene or entity, used for calculations.
class free_transform: transform_component
   def delete():
      wiraw.delete_transform(handle)

// Creates a unattached transform to be used for calculations.
def create_transform():
   return free_transform{wiraw.create_transform()}


class animation_component: ecs_component
   def start():   
      return wiraw.get_animation_start(handle)

   def set_start(v):
      wiraw.set_animation_start(handle, v)

   def end():
      return wiraw.get_animation_end(handle)

   def set_end(v):
      wiraw.set_animation_end(handle, v)

   def timer():
      return wiraw.get_animation_timer(handle)

   def set_timer(v):
      wiraw.set_animation_timer(handle, v)

   def amount():
      return wiraw.get_animation_amount(handle)

   def set_amount(v):
      wiraw.set_animation_amount(handle, v)

   def speed():
      return wiraw.get_animation_speed(handle)

   def set_speed(v):
      wiraw.set_animation_speed(handle, v)

   def is_playing():
      return wiraw.is_animation_playing(handle)

   def is_looped():
      return wiraw.is_animation_looped(handle)

   def anim_length():
      return wiraw.get_animation_length(handle)

   def is_ended():
      return wiraw.get_is_animation_ended(handle)

   def play():
      wiraw.play_animation(handle)

   def pause():
      wiraw.pause_animation(handle)

   def stop():
      wiraw.stop_animation(handle)

   def set_looped(v: bool):
      wiraw.set_animation_looped(handle, v)

constructor animation_component(h: int2):
   assert(h[0] == wk_animation_comp)
   return animation_component{h}

class object_layer: ecs_component
   def layer_mask():
      return wiraw.get_layer_mask(handle)

   def set_layer_mask(v):
      wiraw.set_layer_mask(handle, v)

   def propagation_mask():
      return wiraw.get_layer_propagation_mask(handle)

   def set_propagation_mask(v):
      wiraw.set_layer_propagation_mask(handle, v)

   def effective_mask():
      return propagation_mask() & layer_mask()

constructor object_layer(h: int2):
   assert h[0] == wk_layer
   return object_layer{h}

// Bone names for the humanoid component
enum humanoid_bone_name:
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

class humanoid_component: ecs_component
   def default_look_direction():
      return wiraw.get_humanoid_default_look_direction(handle) 

   def set_default_look_direction(d: float3):
      wiraw.set_humanoid_default_look_direction(d)

   def head_rotation_max():
      return wiraw.get_humanoid_head_rotation_max(handle)

   def set_head_rotation_max(v):
      wiraw.set_humanoid_head_rotation_max(handle, v)

   def eye_rotation_max():
      return wiraw.get_humanoid_eye_rotation_max(handle)

   def set_eye_rotation_max(v):
      wiraw.set_humanoid_eye_rotation_max(handle, v)

   def head_rotation_speed():
      return wiraw.get_humanoid_head_rotation_speed(handle)

   def set_head_rotation_speed(v):
      wiraw.set_humanoid_head_rotation_speed(handle, v)

   def eye_rotation_speed():
      return wiraw.get_humanoid_eye_rotation_speed(handle)

   def set_eye_rotation_speed(v):
      wiraw.set_humanoid_eye_rotation_speed(handle, v)

   def look_at():
      return wiraw.get_humanoid_look_at(handle)

   def set_look_at(v):
      wiraw.set_humanoid_look_at(handle, v)

   def bone_count():
      return wiraw.humanoid_bone_count(handle)

   def bone(i: int):
      return ecs_entity{wiraw.humanoid_bone(handle, i)}

   def is_lookat_enabled():
      return wiraw.humanoid_is_lookat_enabled(handle)

   def set_lookat_enabled(v: bool):
      wiraw.humanoid_set_lookat_enabled(handle, v)


constructor humanoid_component(h: int2):
   assert h[0] == wk_humanoid
   return humanoid_component{h}
   

enum collider_shape:
   cs_spehere, cs_capsule, cs_plane

class collider_component: ecs_component
   def shape():
      return wiraw.get_collider_shape(handle)

   // Return value valid only as long as there are not ecs changes on the enity.
   def capsule() -> primitive_capsule:
      return primitive_capsule{wiraw.get_collider_capsule(handle)}

   def set_shape(s: int):
      wiraw.set_collider_shape(handle, s)

   def radius():
      return wiraw.get_collider_radius(handle)

   def set_radius(v: float):
      wiraw.set_collider_radius(handle, v)

   def offset():
      return wiraw.get_collider_offset(handle)

   def set_offset(v: float3):
      wiraw.set_collider_offset(handle, v)

   def tail():
      return wiraw.get_collider_tail(handle)

   def set_tail(v: float3):
      wiraw.set_collider_tail(handle, v)

   def set_gpu_enabled(v: bool):
      wiraw.set_collider_is_gpu_enabled(handle, v)

   def set_cpu_enabled(v: bool):
      wiraw.set_collider_is_cpu_enabled(handle, v)


constructor collider_component(h: int2):
   assert h[0] == wk_collider
   return collider_component{h}

class object_component: ecs_component
   def mesh_id():
      return ecs_entity{wiraw.get_object_mesh_id(handle)}

   def set_mesh_id(v: ecs_entity):
      wiraw.set_object_mesh_id(handle, v.handle)

   def cascade_mask():
      return wiraw.get_object_cascade_mask(handle)

   def set_cascade_mask(v):
      wiraw.set_object_cascade_mask(handle, v)

   def filter_mask():
      return wiraw.get_object_filter_mask(handle)

   def set_filter_mask(v):
      wiraw.set_object_filter_mask(handle, v)

   def color():
      return wiraw.get_object_color(handle)

   def set_color(v):
      wiraw.set_object_color(handle, v)

   def emissive_color():
      return wiraw.get_object_emissive_color(handle)

   def set_emissive_color(v):
      wiraw.set_object_emissive_color(handle, v)

   def user_stencil_ref():
      return wiraw.get_object_user_stencil_ref(handle)

   def set_user_stencil_ref(v):
      wiraw.set_object_user_stencil_ref(handle, v)

   def lod_distance_multiplier():
      return wiraw.get_object_lod_distance_multiplier(handle)

   def set_lod_distance_multiplier(v):
      wiraw.set_object_lod_distance_multiplier(handle, v)

   def draw_distance():
      return wiraw.get_object_draw_distance(handle)

   def set_draw_distance(v):
      wiraw.set_object_draw_distance(handle, v)

   def lightmap_width():
      return wiraw.get_object_lightmap_width(handle)

   def set_lightmap_width(v):
      wiraw.set_object_lightmap_width(handle, v)

   def lightmap_height():
      return wiraw.get_object_lightmap_height(handle)

   def set_lightmap_height(v):
      wiraw.set_object_lightmap_height(handle, v)

   def sort_priority():
      return wiraw.get_object_sort_priority(handle)

   def set_sort_priority(v):
      wiraw.set_object_sort_priority(handle, v)

constructor object_component(h: int2):
   assert h[0] == wk_object_comp
   return object_component{h}

struct sound_instance:
   handle: int2

   def loop_begin():
      return wiraw.get_sound_instance_loop_begin(handle)

   def set_loop_begin(v):
      wiraw.set_sound_instance_loop_begin(handle, v)

   def loop_length():
      return wiraw.get_sound_instance_loop_length(handle)

   def set_loop_length(v):
      wiraw.set_sound_instance_loop_length(handle, v)

   def reverb_enabled():
      return wiraw.get_sound_instance_reverb_enabled(handle)

   def set_reverb_enabled(v):
      wiraw.set_sound_instance_reverb_enabled(handle, v)

   def instance_valid():
      return wiraw.sound_instance_is_valid(handle)

constructor sound_instance(h: int2):
   assert h[0] == wk_sound_instance
   return sound_instance{h}

class sound_component: ecs_component
   def filename():
      return wiraw.get_sound_component_filename(handle)

   def set_filename(v):
      wiraw.set_sound_component_filename(handle, v)

   // NB: rename from resource, since that is a type name.
   def wresource():
      return gresource(wiraw.get_sound_component_resource(handle))

   def set_wresource(v: gresource):
      wiraw.set_sound_component_resource(handle, v.handle)

   def instance():
      return sound_instance(wiraw.get_sound_component_instance(handle))

   def set_instance(v: sound_instance):
      wiraw.set_sound_component_instance(handle, v.handle)

   // NB: renamed from volume to avoid clash with builtin.
   def get_volume():
      return wiraw.get_sound_component_volume(handle)

   def set_volume(v):
      wiraw.set_sound_component_volume(handle, v)

   def is_playing():
      return wiraw.get_sound_component_is_playing(handle)

   def set_is_playing(v):
      wiraw.set_sound_component_is_playing(handle, v)

   def is_looped():
      return wiraw.get_sound_component_is_looped(handle)

   def set_is_looped(v):
      wiraw.set_sound_component_is_looped(handle, v)

   def is_disable_3d():
      return wiraw.get_sound_component_is_disable_3d(handle)

   def set_is_disable_3d(v):
      wiraw.set_sound_component_is_disable_3d(handle, v)

constructor sound_component(h: int2):
   assert h[0] == wk_sound_comp
   return sound_component{h}


enum intersect_filter:
		FILTER_NONE = 0,
		FILTER_OPAQUE = 1 << 0,
		FILTER_TRANSPARENT = 1 << 1,
		FILTER_WATER = 1 << 2,
		FILTER_NAVIGATION_MESH = 1 << 3,
		FILTER_OBJECT_ALL = FILTER_OPAQUE | FILTER_TRANSPARENT | FILTER_WATER | FILTER_NAVIGATION_MESH,
		FILTER_COLLIDER = 1 << 4,
		FILTER_ALL = ~0

enum light_type:
   LIGHT_DIRECTIONAL,
   LIGHT_POINT, 
   LIGHT_SPOT



// Wrapper for scenes.  This can be saved long term, 
// it is only invalidated when the scene is deleted.
class scene:
   handle: resource<alien>   

   def component_attach(entity: ecs_entity, parent: ecs_entity, child_already_in_local_space: bool):
      wiraw.component_attach(handle, entity.handle, parent.handle, child_already_in_local_space)

   def create_transform_entity(name: string):
      return ecs_entity{wiraw.create_transform_entity(handle, name)}

   def create_object_entity(name: string):
      return ecs_entity{wiraw.create_object_entity(handle, name)}

   def create_mesh_entity(name: string):
      return ecs_entity{wiraw.create_mesh_entity(handle, name)}

   def create_light_entity(name: string, position = float3_0, color = float3_1, intensity = 1.0, range = 10.0, type = LIGHT_POINT, outer_cone_angle = math_pi/4.0, inner_cone_angle = 0.0):
      return ecs_entity{wiraw.create_light_entity(handle, position, color, intensity, range, type, outer_cone_angle, inner_cone_angle)}

   def create_force_entity(name: string, position: float3):
      return ecs_entity{wiraw.create_force_entity(handle, name, position)}

   def create_environment_probe_entity(name: string, position: float3):
      return ecs_entity{wiraw.create_environment_probe_entity(handle, name, position)}

   def create_emitter_entity(name: string, position: float3):
      return ecs_entity{wiraw.create_emitter_entity(handle, name, position)}

   def create_cube_entity(name: string):
      return ecs_entity{wiraw.create_cube_entity(handle, name)}

   def create_plane_entity(name: string):
      return ecs_entity{wiraw.create_plane_entity(handle, name)}

   // Creates an entity with a decal in the given scene.
   def create_decal_entity(name: string, texture: string, normal_map = ""):
      return ecs_entity{wiraw.create_decal_entity(handle, name, texture, normal_map)}

   // Creates a new decal component on the given entity and returns it.
   def create_decal_component(ent: ecs_entity):
      return decal_component(wiraw.create_decal_component(handle, ent.handle))

   // Returns the decal component associated with "ent", or
   // a null handle if there is none.
   def get_decal_component(ent: ecs_entity):
      return decal_component(wiraw.get_decal_component(handle, ent.handle))

   // Returns the number of entities in the scene that have the
   // decal component attached.
   def get_decal_count():
      return wiraw.entity_decal_count(handle)

   // Gets the nth entity that has a decal component, 
   // where n can range from 0 .. wiraw.entity_decal_count()-1
   def get_decal_entity(n: int):
      return ecs_entity{wiraw.entity_decal_get(handle, n)}

   // Creates a new sound component on the given entity and returns it.
   def create_sound_component(ent: ecs_entity):
      return sound_component(wiraw.create_sound_component(handle, ent.handle))

   // Returns the sound component associated with "ent", or
   // a null handle if there is none.
   def get_sound_component(ent: ecs_entity):
      return sound_component(wiraw.get_sound_component(handle, ent.handle))

   // Returns the number of entities in the scene that have the
   // sound component attached.
   def get_sound_count():
      return wiraw.entity_sound_count(handle)

   // Gets the nth entity that has a sound component, 
   // where n can range from 0 .. wiraw.entity_sound_count()-1
   def get_sound_entity(n: int):
      return ecs_entity{wiraw.entity_sound_get(handle, n)}

   // Creates a new entity with a sound component
   def create_sound_entity(name: string, filename: string, pos: float3) -> ecs_entity:
      return ecs_entity{wiraw.scene_create_sound_entity(handle, name, filename, pos)}

   // Creates a new light component on the given entity and returns it.
   def create_light_component(ent: ecs_entity):
      return light_component(wiraw.create_light_component(handle, ent.handle))

   // Returns the light component associated with "ent", or
   // a null handle if there is none.
   def get_light_component(ent: ecs_entity):
      return light_component(wiraw.get_light_component(handle, ent.handle))

   // Returns the number of entities in the scene that have the
   // light component attached.
   def get_light_count():
      return wiraw.entity_light_count(handle)

   // Gets the nth entity that has a light component, 
   // where n can range from 0 .. wiraw.entity_light_count()-1
   def get_light_entity(n: int):
      return ecs_entity{wiraw.entity_light_get(handle, n)}

   // Creates a new hierarchy component on the given entity and returns it.
   def create_hierarchy_component(ent: ecs_entity):
      return hierarchy_component(wiraw.create_hierarchy_component(handle, ent.handle))

   // Returns the hierarchy component associated with "ent", or
   // a null handle if there is none.
   def get_hierarchy_component(ent: ecs_entity):
      return hierarchy_component(wiraw.get_hierarchy_component(handle, ent.handle))

   // Returns the number of entities in the scene that have the
   // hierarchy component attached.
   def get_hierarchy_count():
      return wiraw.entity_hierarchy_count(handle)

   // Gets the nth entity that has a hierarchy component, 
   // where n can range from 0 .. wiraw.entity_hierarchy_count()-1
   def get_hierarchy_entity(n: int):
      return ecs_entity{wiraw.entity_hierarchy_get(handle, n)}

   def create_object_component(ent: ecs_entity):
      return object_component(wiraw.create_object_component(handle, ent.handle))

   def get_object_component(ent: ecs_entity):
      return object_component(wiraw.get_object_component(handle, ent.handle))

   def get_object_count():
      return wiraw.entity_object_count(handle)

   def get_object_entity(n: int):
      return ecs_entity{wiraw.entity_object_get(handle, n)}

   def create_rigidbody_component(ent: ecs_entity):
      return rigidbody_component(wiraw.create_rigidbody_component(handle, ent.handle))

   def get_rigidbody_component(ent: ecs_entity):
      return rigidbody_component(wiraw.get_rigidbody_component(handle, ent.handle))

   def get_rigidbody_count():
      return wiraw.entity_rigidbody_count(handle)

   def get_rigidbody_entity(n: int):
      return ecs_entity{wiraw.entity_rigidbody_get(handle, n)}

   def capsule_intersects(capsule: primitive_capsule, filter_mask = FILTER_OPAQUE, layer_mask = ~0, lod = 0) -> sphere_intersection:
      return sphere_intersection{wiraw.scene_capsule_intersects(handle, capsule.handle, filter_mask, layer_mask, lod)}

   def sphere_intersects(sphere: primitive_sphere, filter_mask = FILTER_OPAQUE, layer_mask = ~0, lod = 0) -> sphere_intersection:
      return sphere_intersection{wiraw.scene_sphere_intersects(handle, sphere.handle, filter_mask, layer_mask, lod)}

   def ray_intersects(capsule: primitive_ray, filter_mask = FILTER_OPAQUE, layer_mask = ~0, lod = 0) -> ray_intersection:
      return ray_intersection{wiraw.scene_ray_intersects(handle, capsule.handle, filter_mask, layer_mask, lod)}

   def retarget_animation(dest: ecs_entity, src: ecs_entity, bake_data: bool) -> ecs_entity:
      return ecs_entity{wiraw.retarget_animation(handle, dest.handle, src.handle, bake_data)}

   def create_animation_component(ent: ecs_entity):
      return animation_component(wiraw.create_animation_component(handle, ent.handle))

   def get_animation_component(ent: ecs_entity):
      return animation_component(wiraw.get_animation_component(handle, ent.handle))

   def get_animation_count():
      return wiraw.entity_animation_count(handle)

   def get_animation_entity(n: int):
      return ecs_entity{wiraw.entity_animation_get(handle, n)}

   def create_collider_component(ent: ecs_entity):
      return collider_component(wiraw.create_collider_component(handle, ent.handle))

   def get_collider_component(ent: ecs_entity):
      return collider_component(wiraw.get_collider_component(handle, ent.handle))

   def get_collider_count():
      return wiraw.entity_collider_count(handle)

   def get_collider_entity(n: int):
      return ecs_entity{wiraw.entity_collider_get(handle, n)}

   def is_descendant_entity(entity: ecs_entity, ancestor: ecs_entity):
      return wiraw.is_descendant_entity(handle, entity.handle, ancestor.handle)
      
   def remove_entity(entity: ecs_entity, recursive = true):
      wiraw.remove_entity(handle, entity.handle, recursive)

   def duplicate_entity(ent: ecs_entity):
      return ecs_entity{wiraw.duplicate_entity(handle, ent.handle)}

   // Loads a model. If "attached", it is rooted to an entity with a transform.
   def load_model(fname: string, attached: bool) -> ecs_entity:
      return ecs_entity{wiraw.load_model(handle, fname, attached)}

   def create_entity() -> ecs_entity:
      return ecs_entity{wiraw.create_entity()}

   def create_layer_component(ent: ecs_entity):
      return object_layer(wiraw.create_layer_component(handle, ent.handle))

   def get_layer_component(ent: ecs_entity):
      return object_layer(wiraw.get_layer_component(handle, ent.handle))

   def get_layer_count():
      return wiraw.entity_layer_count(handle)

   def get_layer_entity(n: int):
      return ecs_entity{wiraw.entity_layer_get(handle, n)}

   def create_humanoid_component(ent: ecs_entity):
      return humanoid_component(humanoid_component(wiraw.create_humanoid_component(handle, ent.handle)))

   def get_humanoid_component(ent):
      return humanoid_component(wiraw.get_humanoid_component(handle, ent.handle))

   def get_humanoid_count():
      return wiraw.entity_humanoid_count(handle)

   def get_humanoid_entity(n: int):
      return ecs_entity{wiraw.entity_humanoid_get(handle, n)}

   def create_camera_component(ent: ecs_entity) -> camera_component:
      return camera_component(wiraw.create_camera_component(handle, ent.handle))

   def get_camera_component(ent: ecs_entity) -> camera_component:
      return camera_component(wiraw.get_camera_component(handle, ent.handle))

   def get_camera_count() -> int:
      return wiraw.get_camera_count(handle)

   def get_camera_entity(n: int) -> ecs_entity:
      return ecs_entity{wiraw.get_camera_entity(handle, n)}

   def create_transform_component(ent: ecs_entity) -> transform_component:
      return transform_component(wiraw.create_transform_component(handle, ent.handle))

   def find_entity_by_name(name: string, ancestor = INVALID_ENTITY) -> ecs_entity:
      return ecs_entity{wiraw.find_entity_by_name(handle, name, ancestor.handle)}

   def get_transform_component(ent: ecs_entity) -> transform_component:
      return transform_component(wiraw.get_transform_component(handle, ent.handle))

   def create_name_component(ent: ecs_entity) -> name_component:
      return name_component(wiraw.create_name_component(handle, ent.handle))

   def get_name_component(ent: ecs_entity) -> name_component:
      return name_component(wiraw.get_name_component(handle, ent.handle))

   def get_names_count() -> int:
      return wiraw.entity_names_count(handle)

   def get_names_entity(i: int) -> ecs_entity:
      return ecs_entity{wiraw.entity_names_get(handle, i)}

   def merge(src: scene):
      wiraw.scene_merge(handle, src.handle)

   // Convenience method that sets the layer for the ecs_entity, creating the 
   // component if necessary.
   def set_layer(ent: ecs_entity, layer: int):
      var lc = get_layer_component(ent)
      if lc.is_empty():
         lc = create_layer_component(ent)
      lc.set_layer_mask(layer)


def new_scene() -> scene:
   return scene{wiraw.new_scene()}

def global_scene() -> scene:
   return scene{wiraw.get_global_scene()}


// Helper that calculates a capsule from the rididbody component data. 
def get_rigidbody_capsule(rb_tr: transform_component, rb: rigidbody_component) -> primitive_capsule:
   //TODO: there's no reason the capsule couldn't be rotated by the entity transform, 
   //  this is only correct for capsules running along the y axis.
   // For rigidbody capsule, height is the distance between the two sphere endpoints, 
   // does not include radius. This is also true for wi::primitive::Capsule
   // And the position we get for the transform will be the center of the capsule.
   let epos, _rot, escale = rb_tr.decompose()
   let cheight = rb.capsule_height()
   let cradius = rb.capsule_radius()*min(escale.x, escale.z)
   let vextent = float3_y*(cheight*0.5*escale.y)
   let rv = create_primitive_capsule()
   rv.set_base(epos - vextent)
   rv.set_tip(epos + vextent)
   rv.set_radius(cradius) 

   return rv
   

// Delta time for application fixed update.
def get_fixed_dt():
   return 1.0 / wiraw.get_fixed_update_rate()

enum_flags debug_draw_text_flags:
   dd_depth_test, dd_camera_facing, dd_camera_scaling

def draw_debug_text(text: string, pos: float3, flags = 0, color=float4{1.0, 1.0, 1.0, 1.0}, scaling = 1.0):
   wiraw.draw_debug_text(text, pos, flags, color, scaling)

struct timer:
   handle: int2

   def record():
      return wiraw.timer_record(handle)

   def elapsed_seconds():
      return wiraw.timer_elapsed_seconds(handle)

   def elapsed():
      return wiraw.timer_elapsed(handle)

   def delete():
      wiraw.delete_timer(handle)

constructor timer():
   return timer{wiraw.create_timer()}


struct font_params:
   handle: int2

   def delete():
      wiraw.delete_font_params(handle)

   def position():
      return wiraw.get_font_params_position(handle)

   def set_position(v):
      wiraw.set_font_params_position(handle, v)

   def size():
      return wiraw.font_params_get_size(handle)

   def set_size(s: int):
      wiraw.font_params_set_size(s)

   def scaling():
      return wiraw.get_font_params_scaling(handle)

   def set_scaling(v):
      wiraw.set_font_params_scaling(handle, v)

   def rotation():
      return wiraw.get_font_params_rotation(handle)

   def set_rotation(v):
      wiraw.set_font_params_rotation(handle, v)

   def spacing_x():
      return wiraw.get_font_params_spacing_x(handle)

   def set_spacing_x(v):
      wiraw.set_font_params_spacing_x(handle, v)

   def spacing_y():
      return wiraw.get_font_params_spacing_y(handle)

   def set_spacing_y(v):
      wiraw.set_font_params_spacing_y(handle, v)

   def h_align():
      return wiraw.get_font_params_h_align(handle)

   def set_h_align(v):
      wiraw.set_font_params_h_align(handle, v)

   def v_align():
      return wiraw.get_font_params_v_align(handle)

   def set_v_align(v):
      wiraw.set_font_params_v_align(handle, v)

   def color():
      let f4 = wiraw.get_font_params_color(handle)
      return color{f4[0], f4[1], f4[2], f4[3]}

   def set_color(v):
      if v is float4:
         wiraw.set_font_params_color(handle, v)
      else:
         wiraw.set_font_params_color(handle, float4{v[0], v[1], v[2], v[3]})

   def shadow_color():
      return wiraw.get_font_params_shadow_color(handle)

   def set_shadow_color(v):
      wiraw.set_font_params_shadow_color(handle, v)

   def h_wrap():
      return wiraw.get_font_params_h_wrap(handle)

   def set_h_wrap(v):
      wiraw.set_font_params_h_wrap(handle, v)

   def style():
      return wiraw.get_font_params_style(handle)

   def set_style(v):
      wiraw.set_font_params_style(handle, v)

   def softness():
      return wiraw.get_font_params_softness(handle)

   def set_softness(v):
      wiraw.set_font_params_softness(handle, v)

   def bolden():
      return wiraw.get_font_params_bolden(handle)

   def set_bolden(v):
      wiraw.set_font_params_bolden(handle, v)

   def shadow_offset_x():
      return wiraw.get_font_params_shadow_offset_x(handle)

   def set_shadow_offset_x(v):
      wiraw.set_font_params_shadow_offset_x(handle, v)

   def shadow_offset_y():
       return wiraw.get_font_params_shadow_offset_y(handle)

   def set_shadow_offset_y(v):
       wiraw.set_font_params_shadow_offset_y(handle, v)

   // position, size
   def cursor() -> float2, float2:
      return wiraw.get_font_params_cursor(handle)

   def set_cursor(pos, size):
      wiraw.set_font_params_cursor(handle, float4{pos.x, pos.y, size.x, size.y})

   def hdr_scaling():
      return wiraw.get_font_params_hdr_scaling(handle)

   def set_hdr_scaling(v):
      wiraw.set_font_params_hdr_scaling(handle, v)


constructor font_params():
   return font_params{wiraw.create_font_params()}


struct sprite_font:
   handle: int2

   def delete():
      wiraw.delete_sprite_font(handle)

   def set_params(p: font_params):
      wiraw.sprite_font_set_params(handle, p.handle)

   def text_size():
      return wiraw.sprite_font_text_size(handle)

   def set_text(txt: string):
      wiraw.sprite_font_set_text(handle, txt)

   def text() -> string:
      return wiraw.sprite_font_get_text(handle)

constructor sprite_font():
   return sprite_font{wiraw.create_sprite_font()}

// Settings for renderpath3d.set_ao
enum AO:
   AO_DISABLED	// no ambient occlusion
   AO_SSAO		// simple brute force screen space ambient occlusion
   AO_HBAO		// horizon based screen space ambient occlusion
   AO_MSAO		// multi scale screen space ambient occlusion
   AO_RTAO		// ray traced ambient occlusion


// wi::RenderPath3D
class renderpath3d:
   handle: int2

   def physical_dims() -> int2:
      return wiraw.get_renderpath_physical_dims(handle)

   def logical_dims() -> float2:
      return wiraw.get_rendrpath_logical_dims(handle)

   def set_camera(cc: camera_component):
      wiraw.renderpath3d_set_camera(handle, cc.handle)

   // Technically a RenderPath2d function.
   def add_font(sf: sprite_font, layer = ""):
      wiraw.renderpath_add_font(handle, sf.handle, layer)

   def get_font_order(sf: sprite_font) -> int:
      return wiraw.renderpath_get_font_order(handle, sf.handle)

   def set_font_order(sf: sprite_font, order: int):
      wiraw.renderpath_set_font_order(handle, sf.handle, order)

   def remove_font(sf: sprite_font):
      wiraw.renderpath_remove_font(handle, sf.handle)

   def clear_fonts():
      wiraw.renderpath_clear_fonts(handle)

   def exposure():
      return wiraw.get_renderpath3d_exposure(handle)

   def set_exposure(v):
      wiraw.set_renderpath3d_exposure(handle, v)

   def brightness():
      return wiraw.get_renderpath3d_brightness(handle)

   def set_brightness(v):
      wiraw.set_renderpath3d_brightness(handle, v)

   def contrast():
      return wiraw.get_renderpath3d_contrast(handle)

   def set_contrast(v):
      wiraw.set_renderpath3d_contrast(handle, v)

   def saturation():
      return wiraw.get_renderpath3d_saturation(handle)

   def set_saturation(v):
      wiraw.set_renderpath3d_saturation(handle, v)

   def bloom_threshold():
      return wiraw.get_renderpath3d_bloom_threshold(handle)

   def set_bloom_threshold(v):
      wiraw.set_renderpath3d_bloom_threshold(handle, v)

   def motion_blur_strength():
      return wiraw.get_renderpath3d_motion_blur_strength(handle)

   def set_motion_blur_strength(v):
      wiraw.set_renderpath3d_motion_blur_strength(handle, v)

   def depth_of_field_strength():
      return wiraw.get_renderpath3d_depth_of_field_strength(handle)

   def set_depth_of_field_strength(v):
      wiraw.set_renderpath3d_depth_of_field_strength(handle, v)

   def sharpen_filter_amount():
      return wiraw.get_renderpath3d_sharpen_filter_amount(handle)

   def set_sharpen_filter_amount(v):
      wiraw.set_renderpath3d_sharpen_filter_amount(handle, v)

   def outline_threshold():
      return wiraw.get_renderpath3d_outline_threshold(handle)

   def set_outline_threshold(v):
      wiraw.set_renderpath3d_outline_threshold(handle, v)

   def outline_thickness():
      return wiraw.get_renderpath3d_outline_thickness(handle)

   def set_outline_thickness(v):
      wiraw.set_renderpath3d_outline_thickness(handle, v)

   def outline_color():
      return wiraw.get_renderpath3d_outline_color(handle)

   def set_outline_color(v):
      wiraw.set_renderpath3d_outline_color(handle, v)

   def ao_range():
      return wiraw.get_renderpath3d_ao_range(handle)

   def set_ao_range(v):
      wiraw.set_renderpath3d_ao_range(handle, v)

   def ao_sample_count():
      return wiraw.get_renderpath3d_ao_sample_count(handle)

   def set_ao_sample_count(v):
      wiraw.set_renderpath3d_ao_sample_count(handle, v)

   def ao_power():
      return wiraw.get_renderpath3d_ao_power(handle)

   def set_ao_power(v):
      wiraw.set_renderpath3d_ao_power(handle, v)

   def chromatic_aberration_amount():
      return wiraw.get_renderpath3d_chromatic_aberration_amount(handle)

   def set_chromatic_aberration_amount(v):
      wiraw.set_renderpath3d_chromatic_aberration_amount(handle, v)

   def screen_space_shadow_sample_count():
      return wiraw.get_renderpath3d_screen_space_shadow_sample_count(handle)

   def set_screen_space_shadow_sample_count(v):
      wiraw.set_renderpath3d_screen_space_shadow_sample_count(handle, v)

   def screen_space_shadow_range():
      return wiraw.get_renderpath3d_screen_space_shadow_range(handle)

   def set_screen_space_shadow_range(v):
      wiraw.set_renderpath3d_screen_space_shadow_range(handle, v)

   def eye_adaption_key():
      return wiraw.get_renderpath3d_eye_adaption_key(handle)

   def set_eye_adaption_key(v):
      wiraw.set_renderpath3d_eye_adaption_key(handle, v)

   def eye_adaption_rate():
      return wiraw.get_renderpath3d_eye_adaption_rate(handle)

   def set_eye_adaption_rate(v):
      wiraw.set_renderpath3d_eye_adaption_rate(handle, v)

   def fsr_sharpness():
      return wiraw.get_renderpath3d_fsr_sharpness(handle)

   def set_fsr_sharpness(v):
      wiraw.set_renderpath3d_fsr_sharpness(handle, v)

   def fsr2_sharpness():
      return wiraw.get_renderpath3d_fsr2_sharpness(handle)

   def set_fsr2_sharpness(v):
      wiraw.set_renderpath3d_fsr2_sharpness(handle, v)

   def light_shafts_strength():
      return wiraw.get_renderpath3d_light_shafts_strength(handle)

   def set_light_shafts_strength(v):
      wiraw.set_renderpath3d_light_shafts_strength(handle, v)

   def raytraced_diffuse_image():
      return wiraw.get_renderpath3d_raytraced_diffuse_image(handle)

   def set_raytraced_diffuse_image(v):
      wiraw.set_renderpath3d_raytraced_diffuse_image(handle, v)

   def raytraced_reflections_range():
      return wiraw.get_renderpath3d_raytraced_reflections_range(handle)

   def set_raytraced_reflections_range(v):
      wiraw.set_renderpath3d_raytraced_reflections_range(handle, v)

   def reflection_roughness_cutoff():
      return wiraw.get_renderpath3d_reflection_roughness_cutoff(handle)

   def set_reflection_roughness_cutoff(v):
      wiraw.set_renderpath3d_reflection_roughness_cutoff(handle, v)

   def ssr_enabled():
      return wiraw.get_renderpath3d_ssr_enabled(handle)

   def set_ssr_enabled(v):
      wiraw.set_renderpath3d_ssr_enabled(handle, v)

   def raytraced_diffuse_enabled():
      return wiraw.get_renderpath3d_raytraced_diffuse_enabled(handle)

   def set_raytraced_diffuse_enabled(v):
      wiraw.set_renderpath3d_raytraced_diffuse_enabled(handle, v)

   def raytraced_reflection_enabled():
      return wiraw.get_renderpath3d_raytraced_reflection_enabled(handle)

   def set_raytraced_reflection_enabled(v):
      wiraw.set_renderpath3d_raytraced_reflection_enabled(handle, v)

   def shadows_enabled():
      return wiraw.get_renderpath3d_shadows_enabled(handle)

   def set_shadows_enabled(v):
      wiraw.set_renderpath3d_shadows_enabled(handle, v)

   def reflections_enabled():
      return wiraw.get_renderpath3d_reflections_enabled(handle)

   def set_reflections_enabled(v):
      wiraw.set_renderpath3d_reflections_enabled(handle, v)

   def fxaa_enabled():
      return wiraw.get_renderpath3d_fxaa_enabled(handle)

   def set_fxaa_enabled(v):
      wiraw.set_renderpath3d_fxaa_enabled(handle, v)

   def bloom_enabled():
      return wiraw.get_renderpath3d_bloom_enabled(handle)

   def set_bloom_enabled(v):
      wiraw.set_renderpath3d_bloom_enabled(handle, v)

   def color_grading_enabled():
      return wiraw.get_renderpath3d_color_grading_enabled(handle)

   def set_color_grading_enabled(v):
      wiraw.set_renderpath3d_color_grading_enabled(handle, v)

   def volume_lights_enabled():
      return wiraw.get_renderpath3d_volume_lights_enabled(handle)

   def set_volume_lights_enabled(v):
      wiraw.set_renderpath3d_volume_lights_enabled(handle, v)

   def light_shafts_enabled():
      return wiraw.get_renderpath3d_light_shafts_enabled(handle)

   def set_light_shafts_enabled(v):
      wiraw.set_renderpath3d_light_shafts_enabled(handle, v)

   def lens_flare_enabled():
      return wiraw.get_renderpath3d_lens_flare_enabled(handle)

   def set_lens_flare_enabled(v):
      wiraw.set_renderpath3d_lens_flare_enabled(handle, v)

   def motion_blur_enabled():
      return wiraw.get_renderpath3d_motion_blur_enabled(handle)

   def set_motion_blur_enabled(v):
      wiraw.set_renderpath3d_motion_blur_enabled(handle, v)

   def depth_of_field_enabled():
      return wiraw.get_renderpath3d_depth_of_field_enabled(handle)

   def set_depth_of_field_enabled(v):
      wiraw.set_renderpath3d_depth_of_field_enabled(handle, v)

   def eye_adaptation_enabled():
      return wiraw.get_renderpath3d_eye_adaptation_enabled(handle)

   def set_eye_adaptation_enabled(v):
      wiraw.set_renderpath3d_eye_adaptation_enabled(handle, v)

   def sharpen_filter_enabled():
      return wiraw.get_renderpath3d_sharpen_filter_enabled(handle)

   def set_sharpen_filter_enabled(v):
      wiraw.set_renderpath3d_sharpen_filter_enabled(handle, v)

   def outline_enabled():
      return wiraw.get_renderpath3d_outline_enabled(handle)

   def set_outline_enabled(v):
      wiraw.set_renderpath3d_outline_enabled(handle, v)

   def chromatic_aberration_enabled():
      return wiraw.get_renderpath3d_chromatic_aberration_enabled(handle)

   def set_chromatic_aberration_enabled(v):
      wiraw.set_renderpath3d_chromatic_aberration_enabled(handle, v)

   def dither_enabled():
      return wiraw.get_renderpath3d_dither_enabled(handle)

   def set_dither_enabled(v):
      wiraw.set_renderpath3d_dither_enabled(handle, v)

   def occlusion_culling_disabled():
      return wiraw.get_renderpath3d_occlusion_culling_disabled(handle)

   def set_occlusion_culling_disabled(v):
      wiraw.set_renderpath3d_occlusion_culling_disabled(handle, v)

   def scene_update_enabled():
      return wiraw.get_renderpath3d_scene_update_enabled(handle)

   def set_scene_update_enabled(v):
      wiraw.set_renderpath3d_scene_update_enabled(handle, v)

   def fsr_enabled():
      return wiraw.get_renderpath3d_fsr_enabled(handle)

   def set_fsr_enabled(v):
      wiraw.set_renderpath3d_fsr_enabled(handle, v)

   def fsr2_enabled():
      return wiraw.get_renderpath3d_fsr2_enabled(handle)

   def set_fsr2_enabled(v):
      wiraw.set_renderpath3d_fsr2_enabled(handle, v)

   def vxgi_resolve_full_resolution_enabled():
      return wiraw.get_renderpath3d_vxgi_resolve_full_resolution_enabled(handle)

   def set_vxgi_resolve_full_resolution_enabled(v):
      wiraw.set_renderpath3d_vxgi_resolve_full_resolution_enabled(handle, v)

   def ao_enabled():
      return wiraw.get_renderpath3d_ao_enabled(handle)

   def set_ao(v: int):
      wiraw.set_renderpath3d_ao(handle, v)


constructor renderpath3d():
   let h = wiraw.get_renderpath3d()
   assert(h[0] == wk_renderpath3)
   return renderpath3d{h}


// Some redirections needed for the namespace change, so there aren't 4
// or 5 functions under "wiraw" instead of the "wi" umbrella.
def set_app_variable_frame_fn(body):
   wiraw.set_app_variable_frame_fn(body)

def set_app_fixed_frame_fn(body):
   wiraw.set_app_variable_frame_fn(body)

def quit_game():
   wiraw.quit_game()

def start_game():
   wiraw.start_game()

def breakpoint():
   wiraw.breakpoint()

def delta_time():
   return wiraw.delta_time()

def logmsg(m):
   return wiraw.logmsg(m)

def app_is_active():
   return wiraw.app_is_active()

