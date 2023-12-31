// GENERATED for inclusion into lobutils.cpp, do not edit.
anfr("get_transform_component", "scene,entity", "R:alienI}:2", "I}:2",
"Returns the transform component for 'entity' if it exists, or int2{?, 0} if there is none.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_transform_component(scene, entity));
});

anfr("new_scene", "", "", "R:alien",
"Creates a new empty scene.",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::new_scene());
});

anfr("get_global_scene", "", "", "R:alien",
"Returns the global scene",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::get_global_scene());
});

anfr("is_descendant_entity", "scene,entity,ancestor", "R:alienI}:2I}:2", "B",
"Returns true if 'entity' is descendant of 'ancestor'",
   [](StackPtr& sp, VM& vm) {
auto ancestor = pop_wo_handle(sp);
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::is_descendant_entity(scene, entity, ancestor)));
});

anfr("retarget_animation", "scene,dest_entity,src_entity,bake_data", "R:alienI}:2I}:2B", "I}:2",
"Retargets an animation from one humanoid to another and returns resulting entity",
   [](StackPtr& sp, VM& vm) {
auto bake_data = Pop(sp).True();
auto src_entity = pop_wo_handle(sp);
auto dest_entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::retarget_animation(scene, dest_entity, src_entity, bake_data));
});

anfr("remove_entity", "scene,entity,recursive", "R:alienI}:2B", "",
"Deletes an entity from the scene",
   [](StackPtr& sp, VM& vm) {
auto recursive = Pop(sp).True();
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
wbnd::remove_entity(scene, entity, recursive);
});

anfr("duplicate_entity", "scene,entity", "R:alienI}:2", "I}:2",
"Duplicates an entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::duplicate_entity(scene, entity));
});

anfr("scene_merge", "dest,src", "R:alienR:alien", "",
"Merges src scene into dest scene.",
   [](StackPtr& sp, VM& vm) {
auto src = pop_alien(sp);
auto dest = pop_alien(sp);
wbnd::scene_merge(dest, src);
});

anfr("create_transform_entity", "scene,name", "R:alienS", "I}:2",
"Creates an entity with a transform component",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_transform_entity(scene, name));
});

anfr("create_object_entity", "scene,name", "R:alienS", "I}:2",
"Creates an entity with a object component",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_object_entity(scene, name));
});

anfr("create_mesh_entity", "scene,name", "R:alienS", "I}:2",
"Creates an entity with a mesh component",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_mesh_entity(scene, name));
});

anfr("create_light_entity", "scene,name,position,color,intensity,range,type,outer_cone_angle,inner_cone_angle", "R:alienSF}:3F}:3FFIFF", "I}:2",
"Creates an entity with a light component",
   [](StackPtr& sp, VM& vm) {
auto inner_cone_angle = Pop(sp).fltval();
auto outer_cone_angle = Pop(sp).fltval();
auto type = (int32_t)Pop(sp).ival();
auto range = Pop(sp).fltval();
auto intensity = Pop(sp).fltval();
XMFLOAT3 color;
pop_xmfloat3(sp,color);
XMFLOAT3 position;
pop_xmfloat3(sp,position);
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_light_entity(scene, name, position, color, intensity, range, type, outer_cone_angle, inner_cone_angle));
});

anfr("create_force_entity", "scene,name,position", "R:alienSF}:3", "I}:2",
"Creates an entity with a force component",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 position;
pop_xmfloat3(sp,position);
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_force_entity(scene, name, position));
});

anfr("create_environment_probe_entity", "scene,name,position", "R:alienSF}:3", "I}:2",
"Creates an entity with a environment_probe component",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 position;
pop_xmfloat3(sp,position);
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_environment_probe_entity(scene, name, position));
});

anfr("create_emitter_entity", "scene,name,position", "R:alienSF}:3", "I}:2",
"Creates an entity with a emitter component",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 position;
pop_xmfloat3(sp,position);
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_emitter_entity(scene, name, position));
});

anfr("create_cube_entity", "scene,name", "R:alienS", "I}:2",
"Creates an entity with a cube component",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_cube_entity(scene, name));
});

anfr("create_plane_entity", "scene,name", "R:alienS", "I}:2",
"Creates an entity with a plane component",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_plane_entity(scene, name));
});

anfr("component_attach", "scene,entity,parent,child_already_in_local_space", "R:alienI}:2I}:2B", "",
"Attaches an entity to a parent",
   [](StackPtr& sp, VM& vm) {
auto child_already_in_local_space = Pop(sp).True();
auto parent = pop_wo_handle(sp);
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
wbnd::component_attach(scene, entity, parent, child_already_in_local_space);
});

anfr("create_primitive_ray", "", "", "R:alien",
"",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_primitive_ray());
});

anfr("set_primitive_ray_origin", "primitive_ray,v", "R:alienF}:3", "",
"Sets primitive_ray.origin",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_ray = pop_alien(sp);
wbnd::set_primitive_ray_origin(primitive_ray, v);
});

anfr("get_primitive_ray_origin", "primitive_ray", "R:alien", "F}:3",
"Gets primitive_ray.origin",
   [](StackPtr& sp, VM& vm) {
auto primitive_ray = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_ray_origin(primitive_ray));
});

anfr("set_primitive_ray_t_min", "primitive_ray,v", "R:alienF", "",
"Sets primitive_ray.t_min",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto primitive_ray = pop_alien(sp);
wbnd::set_primitive_ray_t_min(primitive_ray, v);
});

anfr("get_primitive_ray_t_min", "primitive_ray", "R:alien", "F",
"Gets primitive_ray.t_min",
   [](StackPtr& sp, VM& vm) {
auto primitive_ray = pop_alien(sp);
Push(sp, Value(wbnd::get_primitive_ray_t_min(primitive_ray)));
});

anfr("set_primitive_ray_direction", "primitive_ray,v", "R:alienF}:3", "",
"Sets primitive_ray.direction",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_ray = pop_alien(sp);
wbnd::set_primitive_ray_direction(primitive_ray, v);
});

anfr("get_primitive_ray_direction", "primitive_ray", "R:alien", "F}:3",
"Gets primitive_ray.direction",
   [](StackPtr& sp, VM& vm) {
auto primitive_ray = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_ray_direction(primitive_ray));
});

anfr("set_primitive_ray_t_max", "primitive_ray,v", "R:alienF", "",
"Sets primitive_ray.t_max",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto primitive_ray = pop_alien(sp);
wbnd::set_primitive_ray_t_max(primitive_ray, v);
});

anfr("get_primitive_ray_t_max", "primitive_ray", "R:alien", "F",
"Gets primitive_ray.t_max",
   [](StackPtr& sp, VM& vm) {
auto primitive_ray = pop_alien(sp);
Push(sp, Value(wbnd::get_primitive_ray_t_max(primitive_ray)));
});

anfr("set_primitive_ray_direction_inverse", "primitive_ray,v", "R:alienF}:3", "",
"Sets primitive_ray.direction_inverse",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_ray = pop_alien(sp);
wbnd::set_primitive_ray_direction_inverse(primitive_ray, v);
});

anfr("get_primitive_ray_direction_inverse", "primitive_ray", "R:alien", "F}:3",
"Gets primitive_ray.direction_inverse",
   [](StackPtr& sp, VM& vm) {
auto primitive_ray = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_ray_direction_inverse(primitive_ray));
});

anfr("make_ray_from", "origin,direction,tmin,tmax", "F}:3F}:3FF", "R:alien",
"Creates a ray from the passed parameters",
   [](StackPtr& sp, VM& vm) {
auto tmax = Pop(sp).fltval();
auto tmin = Pop(sp).fltval();
XMFLOAT3 direction;
pop_xmfloat3(sp,direction);
XMFLOAT3 origin;
pop_xmfloat3(sp,origin);
push_alien(sp, vm, wbnd::make_ray_from(origin, direction, tmin, tmax));
});

anfr("ray_capsule_intersects", "ray,capsule", "R:alienR:alien", "BFF}:3",
"Tests intersection between a ray and capsule, returns bool, dist, direction",
   [](StackPtr& sp, VM& vm) {
auto capsule = pop_alien(sp);
auto ray = pop_alien(sp);
float retval2;
XMFLOAT3 retval3;
Push(sp, Value(wbnd::ray_capsule_intersects(ray, capsule, retval2, retval3)));
Push(sp, Value(retval2));
push_xmfloat3(sp, retval3);
});

anfr("ray_sphere_intersects", "ray,sphere", "R:alienR:alien", "BFF}:3",
"Tests intersection between a ray and sphere, returns bool, dist, direction",
   [](StackPtr& sp, VM& vm) {
auto sphere = pop_alien(sp);
auto ray = pop_alien(sp);
float retval2;
XMFLOAT3 retval3;
Push(sp, Value(wbnd::ray_sphere_intersects(ray, sphere, retval2, retval3)));
Push(sp, Value(retval2));
push_xmfloat3(sp, retval3);
});

anfr("create_ray_intersection", "", "", "R:alien",
"",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_ray_intersection());
});

anfr("set_ray_intersection_entity", "ray_intersection,v", "R:alienI}:2", "",
"Sets ray_intersection.entity",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_entity(ray_intersection, v);
});

anfr("get_ray_intersection_entity", "ray_intersection", "R:alien", "I}:2",
"Gets ray_intersection.entity",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_wo_handle(sp, wbnd::get_ray_intersection_entity(ray_intersection));
});

anfr("set_ray_intersection_position", "ray_intersection,v", "R:alienF}:3", "",
"Sets ray_intersection.position",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_position(ray_intersection, v);
});

anfr("get_ray_intersection_position", "ray_intersection", "R:alien", "F}:3",
"Gets ray_intersection.position",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_ray_intersection_position(ray_intersection));
});

anfr("set_ray_intersection_normal", "ray_intersection,v", "R:alienF}:3", "",
"Sets ray_intersection.normal",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_normal(ray_intersection, v);
});

anfr("get_ray_intersection_normal", "ray_intersection", "R:alien", "F}:3",
"Gets ray_intersection.normal",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_ray_intersection_normal(ray_intersection));
});

anfr("set_ray_intersection_velocity", "ray_intersection,v", "R:alienF}:3", "",
"Sets ray_intersection.velocity",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_velocity(ray_intersection, v);
});

anfr("get_ray_intersection_velocity", "ray_intersection", "R:alien", "F}:3",
"Gets ray_intersection.velocity",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_ray_intersection_velocity(ray_intersection));
});

anfr("set_ray_intersection_distance", "ray_intersection,v", "R:alienF", "",
"Sets ray_intersection.distance",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_distance(ray_intersection, v);
});

anfr("get_ray_intersection_distance", "ray_intersection", "R:alien", "F",
"Gets ray_intersection.distance",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
Push(sp, Value(wbnd::get_ray_intersection_distance(ray_intersection)));
});

anfr("set_ray_intersection_subset_index", "ray_intersection,v", "R:alienI", "",
"Sets ray_intersection.subset_index",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_subset_index(ray_intersection, v);
});

anfr("get_ray_intersection_subset_index", "ray_intersection", "R:alien", "I",
"Gets ray_intersection.subset_index",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
Push(sp, Value(wbnd::get_ray_intersection_subset_index(ray_intersection)));
});

anfr("set_ray_intersection_vertex_id0", "ray_intersection,v", "R:alienI", "",
"Sets ray_intersection.vertex_id0",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_vertex_id0(ray_intersection, v);
});

anfr("get_ray_intersection_vertex_id0", "ray_intersection", "R:alien", "I",
"Gets ray_intersection.vertex_id0",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
Push(sp, Value(wbnd::get_ray_intersection_vertex_id0(ray_intersection)));
});

anfr("set_ray_intersection_vertex_id1", "ray_intersection,v", "R:alienI", "",
"Sets ray_intersection.vertex_id1",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_vertex_id1(ray_intersection, v);
});

anfr("get_ray_intersection_vertex_id1", "ray_intersection", "R:alien", "I",
"Gets ray_intersection.vertex_id1",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
Push(sp, Value(wbnd::get_ray_intersection_vertex_id1(ray_intersection)));
});

anfr("set_ray_intersection_vertex_id2", "ray_intersection,v", "R:alienI", "",
"Sets ray_intersection.vertex_id2",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_vertex_id2(ray_intersection, v);
});

anfr("get_ray_intersection_vertex_id2", "ray_intersection", "R:alien", "I",
"Gets ray_intersection.vertex_id2",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
Push(sp, Value(wbnd::get_ray_intersection_vertex_id2(ray_intersection)));
});

anfr("set_ray_intersection_bary", "ray_intersection,v", "R:alienF}:2", "",
"Sets ray_intersection.bary",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 v;
pop_xmfloat2(sp,v);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_bary(ray_intersection, v);
});

anfr("get_ray_intersection_bary", "ray_intersection", "R:alien", "F}:2",
"Gets ray_intersection.bary",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_xmfloat2(sp, wbnd::get_ray_intersection_bary(ray_intersection));
});

anfr("set_ray_intersection_orientation", "ray_intersection,v", "R:alienI}:2", "",
"Sets ray_intersection.orientation",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto ray_intersection = pop_alien(sp);
wbnd::set_ray_intersection_orientation(ray_intersection, v);
});

anfr("get_ray_intersection_orientation", "ray_intersection", "R:alien", "I}:2",
"Gets ray_intersection.orientation",
   [](StackPtr& sp, VM& vm) {
auto ray_intersection = pop_alien(sp);
push_wo_handle(sp, wbnd::get_ray_intersection_orientation(ray_intersection));
});

anfr("load_model", "scene,fname,attach", "R:alienSB", "I}:2",
"Loads the model from the file into the given scene. Returns valid entity handle if attached==true",
   [](StackPtr& sp, VM& vm) {
auto attach = Pop(sp).True();
auto fname = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::load_model(scene, fname, attach));
});

anfr("create_entity", "", "", "I}:2",
"Creates a new empty entity",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_entity());
});

anfr("create_layer_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a layer component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_layer_component(scene, entity));
});

anfr("get_layer_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the layer component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_layer_component(scene, entity));
});

anfr("entity_layer_count", "scene", "R:alien", "I",
"Returns the number of entities that have a layer component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_layer_count(scene)));
});

anfr("entity_layer_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a layer component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_layer_get(scene, n));
});

anfr("create_humanoid_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a humanoid component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_humanoid_component(scene, entity));
});

anfr("get_humanoid_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the humanoid component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_humanoid_component(scene, entity));
});

anfr("entity_humanoid_count", "scene", "R:alien", "I",
"Returns the number of entities that have a humanoid component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_humanoid_count(scene)));
});

anfr("entity_humanoid_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a humanoid component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_humanoid_get(scene, n));
});

anfr("create_name_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a name component for the given entity, and returns a the handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_name_component(scene, entity));
});

anfr("nc_set_name", "name_comp,name", "I}:2S", "",
"Sets the name for a name component.",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto name_comp = pop_wo_handle(sp);
wbnd::nc_set_name(name_comp, name);
});

anfr("nc_get_name", "name_comp", "I}:2", "S",
"Gets the name of a name component",
   [](StackPtr& sp, VM& vm) {
auto name_comp = pop_wo_handle(sp);
Push(sp, Value(vm.NewString(wbnd::nc_get_name(name_comp))));
});

anfr("get_name_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the name component for the given entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_name_component(scene, entity));
});

anfr("entity_names_count", "scene", "R:alien", "I",
"Returns number of entities that have name components.",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_names_count(scene)));
});

anfr("entity_names_get", "scene,n", "R:alienI", "I}:2",
"Returns entity #n that has a name component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_names_get(scene, n));
});

anfr("find_entity_by_name", "scene,name,ancestor_entity", "R:alienSI}:2", "I}:2",
"Searches scene for an entity by name. Returns INVALID_ENTITY if not found.",
   [](StackPtr& sp, VM& vm) {
auto ancestor_entity = pop_wo_handle(sp);
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::find_entity_by_name(scene, name, ancestor_entity));
});

anfr("backlog", "level,msg", "IS", "",
"Logs to Wicked Engine backlog with given log level",
   [](StackPtr& sp, VM& vm) {
auto msg = Pop(sp).sval()->strv();
auto level = (int32_t)Pop(sp).ival();
wbnd::backlog(level, msg);
});

anfr("is_backlog_active", "", "", "B",
"Returns true if the backlog is active",
   [](StackPtr& sp, VM& vm) {
Push(sp, Value(wbnd::is_backlog_active()));
});

anfr("create_camera_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a camera component on an entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_camera_component(scene, entity));
});

anfr("set_transform_scale_local", "transform,v", "I}:2F}:3", "",
"Sets transform.scale_local",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto transform = pop_wo_handle(sp);
wbnd::set_transform_scale_local(transform, v);
});

anfr("get_transform_scale_local", "transform", "I}:2", "F}:3",
"Gets transform.scale_local",
   [](StackPtr& sp, VM& vm) {
auto transform = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_transform_scale_local(transform));
});

anfr("set_transform_rotation_local", "transform,v", "I}:2F}:4", "",
"Sets transform.rotation_local",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto transform = pop_wo_handle(sp);
wbnd::set_transform_rotation_local(transform, v);
});

anfr("get_transform_rotation_local", "transform", "I}:2", "F}:4",
"Gets transform.rotation_local",
   [](StackPtr& sp, VM& vm) {
auto transform = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_transform_rotation_local(transform));
});

anfr("set_transform_translation_local", "transform,v", "I}:2F}:3", "",
"Sets transform.translation_local",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto transform = pop_wo_handle(sp);
wbnd::set_transform_translation_local(transform, v);
});

anfr("get_transform_translation_local", "transform", "I}:2", "F}:3",
"Gets transform.translation_local",
   [](StackPtr& sp, VM& vm) {
auto transform = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_transform_translation_local(transform));
});

anfr("set_transform_dirty", "transform,v", "I}:2B", "",
"Sets transform.dirty",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto transform = pop_wo_handle(sp);
wbnd::set_transform_dirty(transform, v);
});

anfr("get_transform_dirty", "transform", "I}:2", "B",
"Gets transform.dirty",
   [](StackPtr& sp, VM& vm) {
auto transform = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_transform_dirty(transform)));
});

anfr("create_transform_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a transform component on an entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_transform_component(scene, entity));
});

anfr("create_transform", "", "", "I}:2",
"Creates a transform component attached to no scene or entity.  Seems to be used primarly for calculations from scripts",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_transform());
});

anfr("delete_transform", "trans", "I}:2", "",
"Deletes a transform created by create_transform()",
   [](StackPtr& sp, VM& vm) {
auto trans = pop_wo_handle(sp);
wbnd::delete_transform(trans);
});

anfr("get_fixed_update_rate", "", "", "F",
"Returns the application fixed frame update rate",
   [](StackPtr& sp, VM& vm) {
Push(sp, Value(wbnd::get_fixed_update_rate()));
});

anfr("renderpath3d_set_camera", "rpath,cam_component", "I}:2I}:2", "",
"Sets the camera component used by the 3d renderpath",
   [](StackPtr& sp, VM& vm) {
auto cam_component = pop_wo_handle(sp);
auto rpath = pop_wo_handle(sp);
wbnd::renderpath3d_set_camera(rpath, cam_component);
});

anfr("transform_translate", "trans_component,v", "I}:2F}:3", "",
"Tranlates transform by 'vec'",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_translate(trans_component, v);
});

anfr("transform_rotate", "trans_component,quat", "I}:2F}:4", "",
"Rotates transform around given quaternion",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 quat;
pop_xmfloat4(sp,quat);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_rotate(trans_component, quat);
});

anfr("transform_position", "tcomp", "I}:2", "F}:3",
"Gets transform position",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::transform_position(tcomp));
});

anfr("transform_rotation", "tcomp", "I}:2", "F}:4",
"Gets transform rotation",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::transform_rotation(tcomp));
});

anfr("transform_scaling", "tcomp", "I}:2", "F}:3",
"Gets the transform's scaling",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::transform_scaling(tcomp));
});

anfr("decompose_transform", "tcomp", "I}:2", "F}:3F}:4F}:3",
"Decomposes transform pieces into position, rotation, scale",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
XMFLOAT4 retval2;
XMFLOAT3 retval3;
push_xmfloat3(sp, wbnd::decompose_transform(tcomp, retval2, retval3));
push_xmfloat4(sp, retval2);
push_xmfloat3(sp, retval3);
});

anfr("transform_update_transform", "tcomp", "I}:2", "",
"Applies local space to world space matrix for transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
wbnd::transform_update_transform(tcomp);
});

anfr("transform_clear", "trans_comp", "I}:2", "",
"Clears the transform component's transform.",
   [](StackPtr& sp, VM& vm) {
auto trans_comp = pop_wo_handle(sp);
wbnd::transform_clear(trans_comp);
});

anfr("transform_rotate_roll_pitch_yaw", "tcomp,angles", "I}:2F}:3", "",
"Apply euler rotation to transform",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 angles;
pop_xmfloat3(sp,angles);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_rotate_roll_pitch_yaw(tcomp, angles);
});

anfr("transform_scale", "tcomp,scale", "I}:2F}:3", "",
"Apply scale to transform",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 scale;
pop_xmfloat3(sp,scale);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_scale(tcomp, scale);
});

anfr("transform_lerp", "tcomp,a,b,t", "I}:2I}:2I}:2F", "",
"Set this transform to be the linear interpolation of transforms 'a' and 'b'",
   [](StackPtr& sp, VM& vm) {
auto t = Pop(sp).fltval();
auto b = pop_wo_handle(sp);
auto a = pop_wo_handle(sp);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_lerp(tcomp, a, b, t);
});

anfr("get_transform_local_matrix", "tcomp", "I}:2", "R:alien",
"gets the local matrix for the transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_transform_local_matrix(tcomp));
});

anfr("get_transform_world_matrix", "tcomp", "I}:2", "R:alien",
"gets the world matrix for the transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_transform_world_matrix(tcomp));
});

anfr("transform_transform_matrix", "tcomp,matrix", "I}:2R:alien", "",
"Trasforms the transform by the given matrix",
   [](StackPtr& sp, VM& vm) {
auto matrix = pop_alien(sp);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_transform_matrix(tcomp, matrix);
});

anfr("camera_fov", "tcomp", "I}:2", "F",
"Gets camera component fov",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_fov(tcomp)));
});

anfr("camera_set_fov", "tcomp,fov", "I}:2F", "",
"Sets camera component fov, in radians.",
   [](StackPtr& sp, VM& vm) {
auto fov = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_fov(tcomp, fov);
});

anfr("camera_get_dims", "tcomp", "I}:2", "F}:2",
"Gets camera plane dims",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::camera_get_dims(tcomp));
});

anfr("camera_set_dims", "tcomp,dims", "I}:2F}:2", "",
"Sets camera plane dims",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 dims;
pop_xmfloat2(sp,dims);
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_dims(tcomp, dims);
});

anfr("camera_znear", "tcomp", "I}:2", "F",
"Gets the camera zNear",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_znear(tcomp)));
});

anfr("camera_set_znear", "tcomp,znear", "I}:2F", "",
"Sets the camera zNear",
   [](StackPtr& sp, VM& vm) {
auto znear = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_znear(tcomp, znear);
});

anfr("camera_zfar", "tcomp", "I}:2", "F",
"Gets the camera zFar",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_zfar(tcomp)));
});

anfr("camera_set_zfar", "tcomp,zfar", "I}:2F", "",
"Sets the camera zFar",
   [](StackPtr& sp, VM& vm) {
auto zfar = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_zfar(tcomp, zfar);
});

anfr("camera_focal_length", "tcomp", "I}:2", "F",
"Gets the camera focal length",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_focal_length(tcomp)));
});

anfr("camera_set_focal_length", "tcomp,l", "I}:2F", "",
"Sets the camera focal length",
   [](StackPtr& sp, VM& vm) {
auto l = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_focal_length(tcomp, l);
});

anfr("camera_update", "tcomp", "I}:2", "",
"Updates the camera transforms",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
wbnd::camera_update(tcomp);
});

anfr("transform_camera", "camera,tcomp", "I}:2I}:2", "",
"Sets the camera transform from another transform component",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
auto camera = pop_wo_handle(sp);
wbnd::transform_camera(camera, tcomp);
});

anfr("transform_camera_set_matrix", "camera,matrix", "I}:2R:alien", "",
"Sets the camera's transform from the matris",
   [](StackPtr& sp, VM& vm) {
auto matrix = pop_alien(sp);
auto camera = pop_wo_handle(sp);
wbnd::transform_camera_set_matrix(camera, matrix);
});

anfr("get_camera_component", "scene,ent", "R:alienI}:2", "I}:2",
"Gets the camera component of an entity",
   [](StackPtr& sp, VM& vm) {
auto ent = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_camera_component(scene, ent));
});

anfr("get_camera_count", "scene", "R:alien", "I",
"Returns the number of cameras in the scene",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::get_camera_count(scene)));
});

anfr("get_camera_entity", "scene,n", "R:alienI", "I}:2",
"returns entity holding the nth camera in the scene",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_camera_entity(scene, n));
});

anfr("set_camera_eye", "camera,v", "I}:2F}:3", "",
"Sets camera.eye",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_eye(camera, v);
});

anfr("get_camera_eye", "camera", "I}:2", "F}:3",
"Gets camera.eye",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_eye(camera));
});

anfr("set_camera_at", "camera,v", "I}:2F}:3", "",
"Sets camera.at",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_at(camera, v);
});

anfr("get_camera_at", "camera", "I}:2", "F}:3",
"Gets camera.at",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_at(camera));
});

anfr("set_camera_up", "camera,v", "I}:2F}:3", "",
"Sets camera.up",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_up(camera, v);
});

anfr("get_camera_up", "camera", "I}:2", "F}:3",
"Gets camera.up",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_up(camera));
});

anfr("get_camera_projection", "tcomp", "I}:2", "R:alien",
"Gets the camera projection matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_projection(tcomp));
});

anfr("get_camera_view", "tcomp", "I}:2", "R:alien",
"Gets the camera view matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_view(tcomp));
});

anfr("get_camera_VP", "tcomp", "I}:2", "R:alien",
"Gets the camera VP matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_VP(tcomp));
});

anfr("get_camera_inverse_projection", "tcomp", "I}:2", "R:alien",
"Gets the camera inverse projection matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_inverse_projection(tcomp));
});

anfr("get_camera_inverse_view", "tcomp", "I}:2", "R:alien",
"Gets the camera inverse view matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_inverse_view(tcomp));
});

anfr("get_camera_inverse_VP", "tcomp", "I}:2", "R:alien",
"Gets the camera inverse VP matrix.  Matrix valid as long as camera component exists.",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_camera_inverse_VP(tcomp));
});

anfr("get_input_down", "button,playerindex", "II", "B",
"Check if a button is down",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::get_input_down(button, playerindex)));
});

anfr("get_input_press", "button,playerindex", "II", "B",
"Check if a button is pressed once",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::get_input_press(button, playerindex)));
});

anfr("get_input_hold", "button,frames,continuous,playerindex", "IIBI", "B",
"Check if a button is held down",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto continuous = Pop(sp).True();
auto frames = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::get_input_hold(button, frames, continuous, playerindex)));
});

anfr("input_get_pointer", "", "", "F}:4",
"get pointer position (eg. mouse pointer) (.xy) + scroll delta (.z) + pressure (.w)",
   [](StackPtr& sp, VM& vm) {
push_xmfloat4(sp, wbnd::input_get_pointer());
});

anfr("input_set_pointer", "props", "F}:4", "",
"sets pointer position",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 props;
pop_xmfloat4(sp,props);
wbnd::input_set_pointer(props);
});

anfr("input_hide_pointer", "value", "B", "",
"Hides/shows pointer",
   [](StackPtr& sp, VM& vm) {
auto value = Pop(sp).True();
wbnd::input_hide_pointer(value);
});

anfr("input_get_analog", "axis,playerindex", "II", "F}:4",
"Reads input from analog controller axis",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto axis = (int32_t)Pop(sp).ival();
push_xmfloat4(sp, wbnd::input_get_analog(axis, playerindex));
});

anfr("draw_debug_text", "text,pos,flags,color,scaling", "SF}:3IF}:4F", "",
"Renders debug text in the next frame",
   [](StackPtr& sp, VM& vm) {
auto scaling = Pop(sp).fltval();
XMFLOAT4 color;
pop_xmfloat4(sp,color);
auto flags = (int32_t)Pop(sp).ival();
XMFLOAT3 pos;
pop_xmfloat3(sp,pos);
auto text = Pop(sp).sval()->strv();
wbnd::draw_debug_text(text, pos, flags, color, scaling);
});

anfr("create_timer", "", "", "I}:2",
"Creates a wi::Timer",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_timer());
});

anfr("delete_timer", "timer", "I}:2", "",
"Deletes a timer created with create_timer",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
wbnd::delete_timer(timer);
});

anfr("timer_record", "timer", "I}:2", "",
"Records a reference timestamp",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
wbnd::timer_record(timer);
});

anfr("timer_elapsed_seconds", "time", "I}:2", "F",
"Elapsed time since creation or last record call.",
   [](StackPtr& sp, VM& vm) {
auto time = pop_wo_handle(sp);
Push(sp, Value(wbnd::timer_elapsed_seconds(time)));
});

anfr("timer_elapsed", "timer", "I}:2", "F",
"Elapsed time in milliseconds since creation or later record() call",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
Push(sp, Value(wbnd::timer_elapsed(timer)));
});

anfr("create_font_params", "", "", "I}:2",
"",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_font_params());
});

anfr("delete_font_params", "font_params", "I}:2", "",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
wbnd::delete_font_params(font_params);
});

anfr("set_font_params_position", "font_params,v", "I}:2F}:3", "",
"Sets font_params.position",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_position(font_params, v);
});

anfr("get_font_params_position", "font_params", "I}:2", "F}:3",
"Gets font_params.position",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_font_params_position(font_params));
});

anfr("set_font_params_size", "font_params,v", "I}:2I", "",
"Sets font_params.size",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_size(font_params, v);
});

anfr("get_font_params_size", "font_params", "I}:2", "I",
"Gets font_params.size",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_size(font_params)));
});

anfr("set_font_params_scaling", "font_params,v", "I}:2F", "",
"Sets font_params.scaling",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_scaling(font_params, v);
});

anfr("get_font_params_scaling", "font_params", "I}:2", "F",
"Gets font_params.scaling",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_scaling(font_params)));
});

anfr("set_font_params_rotation", "font_params,v", "I}:2F", "",
"Sets font_params.rotation",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_rotation(font_params, v);
});

anfr("get_font_params_rotation", "font_params", "I}:2", "F",
"Gets font_params.rotation",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_rotation(font_params)));
});

anfr("set_font_params_spacing_x", "font_params,v", "I}:2F", "",
"Sets font_params.spacing_x",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_spacing_x(font_params, v);
});

anfr("get_font_params_spacing_x", "font_params", "I}:2", "F",
"Gets font_params.spacing_x",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_spacing_x(font_params)));
});

anfr("set_font_params_spacing_y", "font_params,v", "I}:2F", "",
"Sets font_params.spacing_y",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_spacing_y(font_params, v);
});

anfr("get_font_params_spacing_y", "font_params", "I}:2", "F",
"Gets font_params.spacing_y",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_spacing_y(font_params)));
});

anfr("set_font_params_h_align", "font_params,v", "I}:2I", "",
"Sets font_params.h_align",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_h_align(font_params, v);
});

anfr("get_font_params_h_align", "font_params", "I}:2", "I",
"Gets font_params.h_align",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_h_align(font_params)));
});

anfr("set_font_params_v_align", "font_params,v", "I}:2I", "",
"Sets font_params.v_align",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_v_align(font_params, v);
});

anfr("get_font_params_v_align", "font_params", "I}:2", "I",
"Gets font_params.v_align",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_v_align(font_params)));
});

anfr("set_font_params_color", "font_params,v", "I}:2F}:4", "",
"Sets font_params.color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_color(font_params, v);
});

anfr("get_font_params_color", "font_params", "I}:2", "F}:4",
"Gets font_params.color",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_color(font_params));
});

anfr("set_font_params_shadow_color", "font_params,v", "I}:2F}:4", "",
"Sets font_params.shadow_color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_color(font_params, v);
});

anfr("get_font_params_shadow_color", "font_params", "I}:2", "F}:4",
"Gets font_params.shadow_color",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_shadow_color(font_params));
});

anfr("set_font_params_h_wrap", "font_params,v", "I}:2F", "",
"Sets font_params.h_wrap",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_h_wrap(font_params, v);
});

anfr("get_font_params_h_wrap", "font_params", "I}:2", "F",
"Gets font_params.h_wrap",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_h_wrap(font_params)));
});

anfr("set_font_params_style", "font_params,v", "I}:2I", "",
"Sets font_params.style",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_style(font_params, v);
});

anfr("get_font_params_style", "font_params", "I}:2", "I",
"Gets font_params.style",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_style(font_params)));
});

anfr("set_font_params_softness", "font_params,v", "I}:2F", "",
"Sets font_params.softness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_softness(font_params, v);
});

anfr("get_font_params_softness", "font_params", "I}:2", "F",
"Gets font_params.softness",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_softness(font_params)));
});

anfr("set_font_params_bolden", "font_params,v", "I}:2F", "",
"Sets font_params.bolden",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_bolden(font_params, v);
});

anfr("get_font_params_bolden", "font_params", "I}:2", "F",
"Gets font_params.bolden",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_bolden(font_params)));
});

anfr("set_font_params_shadow_softness", "font_params,v", "I}:2F", "",
"Sets font_params.shadow_softness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_softness(font_params, v);
});

anfr("get_font_params_shadow_softness", "font_params", "I}:2", "F",
"Gets font_params.shadow_softness",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_softness(font_params)));
});

anfr("set_font_params_shadow_bolden", "font_params,v", "I}:2F", "",
"Sets font_params.shadow_bolden",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_bolden(font_params, v);
});

anfr("get_font_params_shadow_bolden", "font_params", "I}:2", "F",
"Gets font_params.shadow_bolden",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_bolden(font_params)));
});

anfr("set_font_params_shadow_offset_x", "font_params,v", "I}:2F", "",
"Sets font_params.shadow_offset_x",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_offset_x(font_params, v);
});

anfr("get_font_params_shadow_offset_x", "font_params", "I}:2", "F",
"Gets font_params.shadow_offset_x",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_offset_x(font_params)));
});

anfr("set_font_params_shadow_offset_y", "font_params,v", "I}:2F", "",
"Sets font_params.shadow_offset_y",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_offset_y(font_params, v);
});

anfr("get_font_params_shadow_offset_y", "font_params", "I}:2", "F",
"Gets font_params.shadow_offset_y",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_offset_y(font_params)));
});

anfr("set_font_params_cursor", "font_params,v", "I}:2F}:4", "",
"Sets font_params.cursor",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_cursor(font_params, v);
});

anfr("get_font_params_cursor", "font_params", "I}:2", "F}:4",
"Gets font_params.cursor",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_cursor(font_params));
});

anfr("set_font_params_hdr_scaling", "font_params,v", "I}:2F", "",
"Sets font_params.hdr_scaling",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_hdr_scaling(font_params, v);
});

anfr("get_font_params_hdr_scaling", "font_params", "I}:2", "F",
"Gets font_params.hdr_scaling",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_hdr_scaling(font_params)));
});

anfr("create_sprite_font", "", "", "I}:2",
"Creates a SpriteFont",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_sprite_font());
});

anfr("sprite_font_set_params", "font,font_params", "I}:2I}:2", "",
"Sets the font_params for a sprite font",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_params(font, font_params);
});

anfr("delete_sprite_font", "font", "I}:2", "",
"Deletes a SpriteFont",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
wbnd::delete_sprite_font(font);
});

anfr("sprite_font_set_hidden", "font,value", "I}:2B", "",
"Changes fonts hidden state",
   [](StackPtr& sp, VM& vm) {
auto value = Pop(sp).True();
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_hidden(font, value);
});

anfr("sprite_font_text_size", "font", "I}:2", "F}:2",
"Returns dimensions of the text",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::sprite_font_text_size(font));
});

anfr("sprite_font_set_text", "font,txt", "I}:2S", "",
"Sets the text TODO is non-wstring version of this utf8 friendly?",
   [](StackPtr& sp, VM& vm) {
auto txt = Pop(sp).sval()->strv();
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_text(font, txt);
});

anfr("sprite_font_get_text", "font", "I}:2", "S",
"Gets the text",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
Push(sp, Value(vm.NewString(wbnd::sprite_font_get_text(font))));
});

anfr("set_humanoid_default_look_direction", "humanoid,v", "I}:2F}:3", "",
"Sets humanoid.default_look_direction",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_default_look_direction(humanoid, v);
});

anfr("get_humanoid_default_look_direction", "humanoid", "I}:2", "F}:3",
"Gets humanoid.default_look_direction",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_humanoid_default_look_direction(humanoid));
});

anfr("set_humanoid_head_rotation_max", "humanoid,v", "I}:2F}:2", "",
"Sets humanoid.head_rotation_max",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 v;
pop_xmfloat2(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_head_rotation_max(humanoid, v);
});

anfr("get_humanoid_head_rotation_max", "humanoid", "I}:2", "F}:2",
"Gets humanoid.head_rotation_max",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::get_humanoid_head_rotation_max(humanoid));
});

anfr("set_humanoid_head_rotation_speed", "humanoid,v", "I}:2F", "",
"Sets humanoid.head_rotation_speed",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_head_rotation_speed(humanoid, v);
});

anfr("get_humanoid_head_rotation_speed", "humanoid", "I}:2", "F",
"Gets humanoid.head_rotation_speed",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_humanoid_head_rotation_speed(humanoid)));
});

anfr("set_humanoid_eye_rotation_max", "humanoid,v", "I}:2F}:2", "",
"Sets humanoid.eye_rotation_max",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 v;
pop_xmfloat2(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_eye_rotation_max(humanoid, v);
});

anfr("get_humanoid_eye_rotation_max", "humanoid", "I}:2", "F}:2",
"Gets humanoid.eye_rotation_max",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::get_humanoid_eye_rotation_max(humanoid));
});

anfr("set_humanoid_eye_rotation_speed", "humanoid,v", "I}:2F", "",
"Sets humanoid.eye_rotation_speed",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_eye_rotation_speed(humanoid, v);
});

anfr("get_humanoid_eye_rotation_speed", "humanoid", "I}:2", "F",
"Gets humanoid.eye_rotation_speed",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_humanoid_eye_rotation_speed(humanoid)));
});

anfr("set_humanoid_look_at", "humanoid,v", "I}:2F}:3", "",
"Sets humanoid.look_at",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_look_at(humanoid, v);
});

anfr("get_humanoid_look_at", "humanoid", "I}:2", "F}:3",
"Gets humanoid.look_at",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_humanoid_look_at(humanoid));
});

anfr("humanoid_bone_count", "hum", "I}:2", "I",
"Returns number of bones in humanoid component",
   [](StackPtr& sp, VM& vm) {
auto hum = pop_wo_handle(sp);
Push(sp, Value(wbnd::humanoid_bone_count(hum)));
});

anfr("humanoid_bone", "hum,i", "I}:2I", "I}:2",
"Returns entity for bone with the given HumanoidBone name",
   [](StackPtr& sp, VM& vm) {
auto i = (int32_t)Pop(sp).ival();
auto hum = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::humanoid_bone(hum, i));
});

anfr("humanoid_is_lookat_enabled", "hum", "I}:2", "B",
"Is lookat enabled?",
   [](StackPtr& sp, VM& vm) {
auto hum = pop_wo_handle(sp);
Push(sp, Value(wbnd::humanoid_is_lookat_enabled(hum)));
});

anfr("humanoid_set_lookat_enabled", "hum,v", "I}:2B", "",
"Sets lookat for humanoid component",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto hum = pop_wo_handle(sp);
wbnd::humanoid_set_lookat_enabled(hum, v);
});

anfr("set_layer_mask", "layer,v", "I}:2I", "",
"Sets layer.mask",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto layer = pop_wo_handle(sp);
wbnd::set_layer_mask(layer, v);
});

anfr("get_layer_mask", "layer", "I}:2", "I",
"Gets layer.mask",
   [](StackPtr& sp, VM& vm) {
auto layer = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_layer_mask(layer)));
});

anfr("set_layer_propagation_mask", "layer,v", "I}:2I", "",
"Sets layer.propagation_mask",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto layer = pop_wo_handle(sp);
wbnd::set_layer_propagation_mask(layer, v);
});

anfr("get_layer_propagation_mask", "layer", "I}:2", "I",
"Gets layer.propagation_mask",
   [](StackPtr& sp, VM& vm) {
auto layer = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_layer_propagation_mask(layer)));
});

anfr("get_renderpath3d", "", "", "I}:2",
"Returns the games RenderPath3d",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::get_renderpath3d());
});

anfr("renderpath_add_font", "path,sprite_font,layer", "I}:2I}:2S", "",
"Adds a sprite font to the renderpath",
   [](StackPtr& sp, VM& vm) {
auto layer = Pop(sp).sval()->strv();
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_add_font(path, sprite_font, layer);
});

anfr("renderpath_remove_font", "path,sprite_font", "I}:2I}:2", "",
"Removes a sprite font from the renderpath",
   [](StackPtr& sp, VM& vm) {
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_remove_font(path, sprite_font);
});

anfr("renderpath_clear_fonts", "path", "I}:2", "",
"Clears all fonts from renderpath",
   [](StackPtr& sp, VM& vm) {
auto path = pop_wo_handle(sp);
wbnd::renderpath_clear_fonts(path);
});

anfr("renderpath_font_order", "path,sprite_font", "I}:2I}:2", "I",
"Returns the order for the given font",
   [](StackPtr& sp, VM& vm) {
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
Push(sp, Value(wbnd::renderpath_font_order(path, sprite_font)));
});

anfr("renderpath_set_font_order", "path,sprite_font,order", "I}:2I}:2I", "",
"Sets the order for the given font",
   [](StackPtr& sp, VM& vm) {
auto order = (int32_t)Pop(sp).ival();
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_set_font_order(path, sprite_font, order);
});

anfr("get_renderpath_physical_dims", "path", "I}:2", "I}:2",
"Returns the physical pixel dimensions of the renderpath",
   [](StackPtr& sp, VM& vm) {
auto path = pop_wo_handle(sp);
push_xmint2(sp, wbnd::get_renderpath_physical_dims(path));
});

anfr("get_renderpath_logical_dims", "path", "I}:2", "F}:2",
"Returns the logical dims of the renderpath",
   [](StackPtr& sp, VM& vm) {
auto path = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::get_renderpath_logical_dims(path));
});

anfr("set_renderpath3d_exposure", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.exposure",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_exposure(renderpath3d, v);
});

anfr("get_renderpath3d_exposure", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.exposure",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_exposure(renderpath3d)));
});

anfr("set_renderpath3d_brightness", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.brightness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_brightness(renderpath3d, v);
});

anfr("get_renderpath3d_brightness", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.brightness",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_brightness(renderpath3d)));
});

anfr("set_renderpath3d_contrast", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.contrast",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_contrast(renderpath3d, v);
});

anfr("get_renderpath3d_contrast", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.contrast",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_contrast(renderpath3d)));
});

anfr("set_renderpath3d_saturation", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.saturation",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_saturation(renderpath3d, v);
});

anfr("get_renderpath3d_saturation", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.saturation",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_saturation(renderpath3d)));
});

anfr("set_renderpath3d_bloom_threshold", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.bloom_threshold",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_bloom_threshold(renderpath3d, v);
});

anfr("get_renderpath3d_bloom_threshold", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.bloom_threshold",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_bloom_threshold(renderpath3d)));
});

anfr("set_renderpath3d_motion_blur_strength", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.motion_blur_strength",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_motion_blur_strength(renderpath3d, v);
});

anfr("get_renderpath3d_motion_blur_strength", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.motion_blur_strength",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_motion_blur_strength(renderpath3d)));
});

anfr("set_renderpath3d_depth_of_field_strength", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.depth_of_field_strength",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_depth_of_field_strength(renderpath3d, v);
});

anfr("get_renderpath3d_depth_of_field_strength", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.depth_of_field_strength",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_depth_of_field_strength(renderpath3d)));
});

anfr("set_renderpath3d_sharpen_filter_amount", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.sharpen_filter_amount",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_sharpen_filter_amount(renderpath3d, v);
});

anfr("get_renderpath3d_sharpen_filter_amount", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.sharpen_filter_amount",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_sharpen_filter_amount(renderpath3d)));
});

anfr("set_renderpath3d_outline_threshold", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.outline_threshold",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_outline_threshold(renderpath3d, v);
});

anfr("get_renderpath3d_outline_threshold", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.outline_threshold",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_outline_threshold(renderpath3d)));
});

anfr("set_renderpath3d_outline_thickness", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.outline_thickness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_outline_thickness(renderpath3d, v);
});

anfr("get_renderpath3d_outline_thickness", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.outline_thickness",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_outline_thickness(renderpath3d)));
});

anfr("set_renderpath3d_outline_color", "renderpath3d,v", "I}:2F}:4", "",
"Sets renderpath3d.outline_color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_outline_color(renderpath3d, v);
});

anfr("get_renderpath3d_outline_color", "renderpath3d", "I}:2", "F}:4",
"Gets renderpath3d.outline_color",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_renderpath3d_outline_color(renderpath3d));
});

anfr("set_renderpath3d_ao_range", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.ao_range",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_ao_range(renderpath3d, v);
});

anfr("get_renderpath3d_ao_range", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.ao_range",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_ao_range(renderpath3d)));
});

anfr("set_renderpath3d_ao_sample_count", "renderpath3d,v", "I}:2I", "",
"Sets renderpath3d.ao_sample_count",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_ao_sample_count(renderpath3d, v);
});

anfr("get_renderpath3d_ao_sample_count", "renderpath3d", "I}:2", "I",
"Gets renderpath3d.ao_sample_count",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_ao_sample_count(renderpath3d)));
});

anfr("set_renderpath3d_ao_power", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.ao_power",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_ao_power(renderpath3d, v);
});

anfr("get_renderpath3d_ao_power", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.ao_power",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_ao_power(renderpath3d)));
});

anfr("set_renderpath3d_chromatic_aberration_amount", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.chromatic_aberration_amount",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_chromatic_aberration_amount(renderpath3d, v);
});

anfr("get_renderpath3d_chromatic_aberration_amount", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.chromatic_aberration_amount",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_chromatic_aberration_amount(renderpath3d)));
});

anfr("set_renderpath3d_screen_space_shadow_sample_count", "renderpath3d,v", "I}:2I", "",
"Sets renderpath3d.screen_space_shadow_sample_count",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_screen_space_shadow_sample_count(renderpath3d, v);
});

anfr("get_renderpath3d_screen_space_shadow_sample_count", "renderpath3d", "I}:2", "I",
"Gets renderpath3d.screen_space_shadow_sample_count",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_screen_space_shadow_sample_count(renderpath3d)));
});

anfr("set_renderpath3d_screen_space_shadow_range", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.screen_space_shadow_range",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_screen_space_shadow_range(renderpath3d, v);
});

anfr("get_renderpath3d_screen_space_shadow_range", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.screen_space_shadow_range",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_screen_space_shadow_range(renderpath3d)));
});

anfr("set_renderpath3d_eye_adaption_key", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.eye_adaption_key",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_eye_adaption_key(renderpath3d, v);
});

anfr("get_renderpath3d_eye_adaption_key", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.eye_adaption_key",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_eye_adaption_key(renderpath3d)));
});

anfr("set_renderpath3d_eye_adaption_rate", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.eye_adaption_rate",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_eye_adaption_rate(renderpath3d, v);
});

anfr("get_renderpath3d_eye_adaption_rate", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.eye_adaption_rate",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_eye_adaption_rate(renderpath3d)));
});

anfr("set_renderpath3d_fsr_sharpness", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.fsr_sharpness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_fsr_sharpness(renderpath3d, v);
});

anfr("get_renderpath3d_fsr_sharpness", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.fsr_sharpness",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_fsr_sharpness(renderpath3d)));
});

anfr("set_renderpath3d_fsr2_sharpness", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.fsr2_sharpness",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_fsr2_sharpness(renderpath3d, v);
});

anfr("get_renderpath3d_fsr2_sharpness", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.fsr2_sharpness",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_fsr2_sharpness(renderpath3d)));
});

anfr("set_renderpath3d_light_shafts_strength", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.light_shafts_strength",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_light_shafts_strength(renderpath3d, v);
});

anfr("get_renderpath3d_light_shafts_strength", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.light_shafts_strength",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_light_shafts_strength(renderpath3d)));
});

anfr("set_renderpath3d_raytraced_diffuse_range", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.raytraced_diffuse_range",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_raytraced_diffuse_range(renderpath3d, v);
});

anfr("get_renderpath3d_raytraced_diffuse_range", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.raytraced_diffuse_range",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_raytraced_diffuse_range(renderpath3d)));
});

anfr("set_renderpath3d_raytraced_reflections_range", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.raytraced_reflections_range",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_raytraced_reflections_range(renderpath3d, v);
});

anfr("get_renderpath3d_raytraced_reflections_range", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.raytraced_reflections_range",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_raytraced_reflections_range(renderpath3d)));
});

anfr("set_renderpath3d_reflection_roughness_cutoff", "renderpath3d,v", "I}:2F", "",
"Sets renderpath3d.reflection_roughness_cutoff",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_reflection_roughness_cutoff(renderpath3d, v);
});

anfr("get_renderpath3d_reflection_roughness_cutoff", "renderpath3d", "I}:2", "F",
"Gets renderpath3d.reflection_roughness_cutoff",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_reflection_roughness_cutoff(renderpath3d)));
});

anfr("set_renderpath3d_ssr_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.ssr_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_ssr_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_ssr_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.ssr_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_ssr_enabled(renderpath3d)));
});

anfr("set_renderpath3d_raytraced_diffuse_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.raytraced_diffuse_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_raytraced_diffuse_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_raytraced_diffuse_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.raytraced_diffuse_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_raytraced_diffuse_enabled(renderpath3d)));
});

anfr("set_renderpath3d_raytraced_reflection_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.raytraced_reflection_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_raytraced_reflection_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_raytraced_reflection_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.raytraced_reflection_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_raytraced_reflection_enabled(renderpath3d)));
});

anfr("set_renderpath3d_shadows_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.shadows_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_shadows_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_shadows_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.shadows_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_shadows_enabled(renderpath3d)));
});

anfr("set_renderpath3d_reflections_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.reflections_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_reflections_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_reflections_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.reflections_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_reflections_enabled(renderpath3d)));
});

anfr("set_renderpath3d_fxaa_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.fxaa_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_fxaa_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_fxaa_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.fxaa_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_fxaa_enabled(renderpath3d)));
});

anfr("set_renderpath3d_bloom_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.bloom_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_bloom_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_bloom_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.bloom_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_bloom_enabled(renderpath3d)));
});

anfr("set_renderpath3d_color_grading_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.color_grading_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_color_grading_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_color_grading_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.color_grading_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_color_grading_enabled(renderpath3d)));
});

anfr("set_renderpath3d_volume_lights_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.volume_lights_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_volume_lights_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_volume_lights_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.volume_lights_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_volume_lights_enabled(renderpath3d)));
});

anfr("set_renderpath3d_light_shafts_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.light_shafts_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_light_shafts_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_light_shafts_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.light_shafts_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_light_shafts_enabled(renderpath3d)));
});

anfr("set_renderpath3d_lens_flare_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.lens_flare_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_lens_flare_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_lens_flare_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.lens_flare_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_lens_flare_enabled(renderpath3d)));
});

anfr("set_renderpath3d_motion_blur_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.motion_blur_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_motion_blur_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_motion_blur_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.motion_blur_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_motion_blur_enabled(renderpath3d)));
});

anfr("set_renderpath3d_depth_of_field_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.depth_of_field_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_depth_of_field_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_depth_of_field_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.depth_of_field_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_depth_of_field_enabled(renderpath3d)));
});

anfr("set_renderpath3d_eye_adaptation_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.eye_adaptation_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_eye_adaptation_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_eye_adaptation_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.eye_adaptation_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_eye_adaptation_enabled(renderpath3d)));
});

anfr("set_renderpath3d_sharpen_filter_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.sharpen_filter_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_sharpen_filter_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_sharpen_filter_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.sharpen_filter_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_sharpen_filter_enabled(renderpath3d)));
});

anfr("set_renderpath3d_outline_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.outline_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_outline_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_outline_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.outline_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_outline_enabled(renderpath3d)));
});

anfr("set_renderpath3d_chromatic_aberration_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.chromatic_aberration_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_chromatic_aberration_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_chromatic_aberration_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.chromatic_aberration_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_chromatic_aberration_enabled(renderpath3d)));
});

anfr("set_renderpath3d_dither_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.dither_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_dither_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_dither_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.dither_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_dither_enabled(renderpath3d)));
});

anfr("set_renderpath3d_occlusion_culling_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.occlusion_culling_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_occlusion_culling_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_occlusion_culling_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.occlusion_culling_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_occlusion_culling_enabled(renderpath3d)));
});

anfr("set_renderpath3d_scene_update_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.scene_update_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_scene_update_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_scene_update_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.scene_update_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_scene_update_enabled(renderpath3d)));
});

anfr("set_renderpath3d_fsr_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.fsr_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_fsr_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_fsr_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.fsr_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_fsr_enabled(renderpath3d)));
});

anfr("set_renderpath3d_fsr2_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.fsr2_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_fsr2_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_fsr2_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.fsr2_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_fsr2_enabled(renderpath3d)));
});

anfr("set_renderpath3d_vxgi_resolve_full_resolution_enabled", "renderpath3d,v", "I}:2B", "",
"Sets renderpath3d.vxgi_resolve_full_resolution_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_vxgi_resolve_full_resolution_enabled(renderpath3d, v);
});

anfr("get_renderpath3d_vxgi_resolve_full_resolution_enabled", "renderpath3d", "I}:2", "B",
"Gets renderpath3d.vxgi_resolve_full_resolution_enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_vxgi_resolve_full_resolution_enabled(renderpath3d)));
});

anfr("get_renderpath3d_ao_enabled", "renderpath3d", "I}:2", "B",
"Returns true if AO is enabled",
   [](StackPtr& sp, VM& vm) {
auto renderpath3d = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_renderpath3d_ao_enabled(renderpath3d)));
});

anfr("set_renderpath3d_ao", "renderpath3d,v", "I}:2I", "",
"Set the AO mode",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto renderpath3d = pop_wo_handle(sp);
wbnd::set_renderpath3d_ao(renderpath3d, v);
});

anfr("set_collider_shape", "collider,v", "I}:2I", "",
"Sets collider.shape",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_shape(collider, v);
});

anfr("get_collider_shape", "collider", "I}:2", "I",
"Gets collider.shape",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_collider_shape(collider)));
});

anfr("set_collider_radius", "collider,v", "I}:2F", "",
"Sets collider.radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_radius(collider, v);
});

anfr("get_collider_radius", "collider", "I}:2", "F",
"Gets collider.radius",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_collider_radius(collider)));
});

anfr("set_collider_offset", "collider,v", "I}:2F}:3", "",
"Sets collider.offset",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto collider = pop_wo_handle(sp);
wbnd::set_collider_offset(collider, v);
});

anfr("get_collider_offset", "collider", "I}:2", "F}:3",
"Gets collider.offset",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_collider_offset(collider));
});

anfr("set_collider_tail", "collider,v", "I}:2F}:3", "",
"Sets collider.tail",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto collider = pop_wo_handle(sp);
wbnd::set_collider_tail(collider, v);
});

anfr("get_collider_tail", "collider", "I}:2", "F}:3",
"Gets collider.tail",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_collider_tail(collider));
});

anfr("set_collider_is_gpu_enabled", "collider,v", "I}:2B", "",
"Set collider as gpu enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_is_gpu_enabled(collider, v);
});

anfr("set_collider_is_cpu_enabled", "collider,v", "I}:2B", "",
"Set collider as cpu enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_is_cpu_enabled(collider, v);
});

anfr("create_collider_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a collider component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_collider_component(scene, entity));
});

anfr("get_collider_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the collider component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_collider_component(scene, entity));
});

anfr("entity_collider_count", "scene", "R:alien", "I",
"Returns the number of entities that have a collider component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_collider_count(scene)));
});

anfr("entity_collider_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a collider component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_collider_get(scene, n));
});

anfr("get_collider_capsule", "collider", "I}:2", "R:alien",
"Returns the primitive capsule for the collider, only valid if the shape is CAPSULE.",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
push_alien(sp, vm, wbnd::get_collider_capsule(collider));
});

anfr("create_matrix4x4", "", "", "R:alien",
"Creates a matrix",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_matrix4x4());
});

anfr("identity_matrix", "m", "R:alien", "",
"Initializes the matrix as an identity matrix",
   [](StackPtr& sp, VM& vm) {
auto m = pop_alien(sp);
wbnd::identity_matrix(m);
});

anfr("transform_vector", "matrix,v", "R:alienF}:4", "F}:4",
"Transforms a vector with the matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto matrix = pop_alien(sp);
push_xmfloat4(sp, wbnd::transform_vector(matrix, v));
});

anfr("assign_matrix", "lhs,rhs", "R:alienR:alien", "",
"Assigns matrix lhs the value from rhs",
   [](StackPtr& sp, VM& vm) {
auto rhs = pop_alien(sp);
auto lhs = pop_alien(sp);
wbnd::assign_matrix(lhs, rhs);
});

anfr("get_matrix_translation", "matrix", "R:alien", "F}:3",
"Returns the translation part of the given matrix",
   [](StackPtr& sp, VM& vm) {
auto matrix = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_matrix_translation(matrix));
});

anfr("assign_matrix_rows", "m,r1,r2,r3,r4", "R:alienF}:4F}:4F}:4F}:4", "",
"Initializes a matrix from rows",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 r4;
pop_xmfloat4(sp,r4);
XMFLOAT4 r3;
pop_xmfloat4(sp,r3);
XMFLOAT4 r2;
pop_xmfloat4(sp,r2);
XMFLOAT4 r1;
pop_xmfloat4(sp,r1);
auto m = pop_alien(sp);
wbnd::assign_matrix_rows(m, r1, r2, r3, r4);
});

anfr("return_matrix_row", "m,r", "R:alienI", "F}:4",
"Returns a row from a matrix",
   [](StackPtr& sp, VM& vm) {
auto r = (int32_t)Pop(sp).ival();
auto m = pop_alien(sp);
push_xmfloat4(sp, wbnd::return_matrix_row(m, r));
});

anfr("translation_matrix", "m,v", "R:alienF}:3", "",
"Set up as a translation matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto m = pop_alien(sp);
wbnd::translation_matrix(m, v);
});

anfr("rotation_euler_matrix", "m,angles", "R:alienF}:3", "",
"Set up as a rotation matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 angles;
pop_xmfloat3(sp,angles);
auto m = pop_alien(sp);
wbnd::rotation_euler_matrix(m, angles);
});

anfr("rotation_x_matrix", "m,a", "R:alienF", "",
"Set up as a rotation around x matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_alien(sp);
wbnd::rotation_x_matrix(m, a);
});

anfr("rotation_y_matrix", "m,a", "R:alienF", "",
"Set up as a rotation around y matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_alien(sp);
wbnd::rotation_y_matrix(m, a);
});

anfr("rotation_z_matrix", "m,a", "R:alienF", "",
"Set up as a rotation around z matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_alien(sp);
wbnd::rotation_z_matrix(m, a);
});

anfr("rotation_quat_matrix", "m,quat", "R:alienF}:4", "",
"Set matrix as quaternion rotation",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 quat;
pop_xmfloat4(sp,quat);
auto m = pop_alien(sp);
wbnd::rotation_quat_matrix(m, quat);
});

anfr("scaling_matrix", "m,scale", "R:alienF}:4", "",
"Set up matrix as a scaling matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 scale;
pop_xmfloat4(sp,scale);
auto m = pop_alien(sp);
wbnd::scaling_matrix(m, scale);
});

anfr("look_to_matrix", "m,eyepos,eyedir,up", "R:alienF}:3F}:3F}:3", "",
"Set up matrix to look to a pos",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 up;
pop_xmfloat3(sp,up);
XMFLOAT3 eyedir;
pop_xmfloat3(sp,eyedir);
XMFLOAT3 eyepos;
pop_xmfloat3(sp,eyepos);
auto m = pop_alien(sp);
wbnd::look_to_matrix(m, eyepos, eyedir, up);
});

anfr("look_at_matrix", "m,eyepos,focuspos,up", "R:alienF}:3F}:3F}:3", "",
"Set up matrix to look at a pos",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 up;
pop_xmfloat3(sp,up);
XMFLOAT3 focuspos;
pop_xmfloat3(sp,focuspos);
XMFLOAT3 eyepos;
pop_xmfloat3(sp,eyepos);
auto m = pop_alien(sp);
wbnd::look_at_matrix(m, eyepos, focuspos, up);
});

anfr("multiply_matrix", "lhs,rhs,result", "R:alienR:alienR:alien", "",
"Multiply lhs by rhs and put the reuslt into result",
   [](StackPtr& sp, VM& vm) {
auto result = pop_alien(sp);
auto rhs = pop_alien(sp);
auto lhs = pop_alien(sp);
wbnd::multiply_matrix(lhs, rhs, result);
});

anfr("add_matrix", "lhs,rhs,result", "R:alienR:alienR:alien", "",
"Add lhs and rhs, and put the result in result",
   [](StackPtr& sp, VM& vm) {
auto result = pop_alien(sp);
auto rhs = pop_alien(sp);
auto lhs = pop_alien(sp);
wbnd::add_matrix(lhs, rhs, result);
});

anfr("transpose_matrix", "m,result", "R:alienR:alien", "",
"Transpose a matrix",
   [](StackPtr& sp, VM& vm) {
auto result = pop_alien(sp);
auto m = pop_alien(sp);
wbnd::transpose_matrix(m, result);
});

anfr("invert_matrix", "m,result", "R:alienR:alien", "",
"Inverts 'm' and puts the result in 'result'",
   [](StackPtr& sp, VM& vm) {
auto result = pop_alien(sp);
auto m = pop_alien(sp);
wbnd::invert_matrix(m, result);
});

anfr("set_animation_start", "animation,v", "I}:2F", "",
"Sets animation.start",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto animation = pop_wo_handle(sp);
wbnd::set_animation_start(animation, v);
});

anfr("get_animation_start", "animation", "I}:2", "F",
"Gets animation.start",
   [](StackPtr& sp, VM& vm) {
auto animation = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_start(animation)));
});

anfr("set_animation_end", "animation,v", "I}:2F", "",
"Sets animation.end",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto animation = pop_wo_handle(sp);
wbnd::set_animation_end(animation, v);
});

anfr("get_animation_end", "animation", "I}:2", "F",
"Gets animation.end",
   [](StackPtr& sp, VM& vm) {
auto animation = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_end(animation)));
});

anfr("set_animation_timer", "animation,v", "I}:2F", "",
"Sets animation.timer",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto animation = pop_wo_handle(sp);
wbnd::set_animation_timer(animation, v);
});

anfr("get_animation_timer", "animation", "I}:2", "F",
"Gets animation.timer",
   [](StackPtr& sp, VM& vm) {
auto animation = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_timer(animation)));
});

anfr("set_animation_amount", "animation,v", "I}:2F", "",
"Sets animation.amount",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto animation = pop_wo_handle(sp);
wbnd::set_animation_amount(animation, v);
});

anfr("get_animation_amount", "animation", "I}:2", "F",
"Gets animation.amount",
   [](StackPtr& sp, VM& vm) {
auto animation = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_amount(animation)));
});

anfr("set_animation_speed", "animation,v", "I}:2F", "",
"Sets animation.speed",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto animation = pop_wo_handle(sp);
wbnd::set_animation_speed(animation, v);
});

anfr("get_animation_speed", "animation", "I}:2", "F",
"Gets animation.speed",
   [](StackPtr& sp, VM& vm) {
auto animation = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_speed(animation)));
});

anfr("is_animation_playing", "anim", "I}:2", "B",
"Returns true if animation is playing",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
Push(sp, Value(wbnd::is_animation_playing(anim)));
});

anfr("is_animation_looped", "anim", "I}:2", "B",
"Returns true if the animation is looped",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
Push(sp, Value(wbnd::is_animation_looped(anim)));
});

anfr("get_animation_length", "anim", "I}:2", "F",
"Returns the length of the animation",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_animation_length(anim)));
});

anfr("is_animation_ended", "anim", "I}:2", "F",
"Returns true if the animation has ended",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
Push(sp, Value(wbnd::is_animation_ended(anim)));
});

anfr("play_animation", "anim", "I}:2", "",
"Plays an animation",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
wbnd::play_animation(anim);
});

anfr("pause_animation", "anim", "I}:2", "",
"Pauses an animation",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
wbnd::pause_animation(anim);
});

anfr("stop_animation", "anim", "I}:2", "",
"Stops an animation",
   [](StackPtr& sp, VM& vm) {
auto anim = pop_wo_handle(sp);
wbnd::stop_animation(anim);
});

anfr("set_animation_looped", "anim,v", "I}:2B", "",
"Sets the animation as looped/not-looped",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto anim = pop_wo_handle(sp);
wbnd::set_animation_looped(anim, v);
});

anfr("create_animation_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a animation component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_animation_component(scene, entity));
});

anfr("get_animation_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the animation component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_animation_component(scene, entity));
});

anfr("entity_animation_count", "scene", "R:alien", "I",
"Returns the number of entities that have a animation component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_animation_count(scene)));
});

anfr("entity_animation_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a animation component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_animation_get(scene, n));
});

anfr("renderer_set_vxgi_enabled", "v", "B", "",
"Controls VXGI",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
wbnd::renderer_set_vxgi_enabled(v);
});

anfr("renderer_vxgi_enabled", "", "", "B",
"Returns true if VXGI is enabled",
   [](StackPtr& sp, VM& vm) {
Push(sp, Value(wbnd::renderer_vxgi_enabled()));
});

anfr("create_primitive_sphere", "", "", "R:alien",
"",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_primitive_sphere());
});

anfr("set_primitive_sphere_center", "primitive_sphere,v", "R:alienF}:3", "",
"Sets primitive_sphere.center",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_sphere = pop_alien(sp);
wbnd::set_primitive_sphere_center(primitive_sphere, v);
});

anfr("get_primitive_sphere_center", "primitive_sphere", "R:alien", "F}:3",
"Gets primitive_sphere.center",
   [](StackPtr& sp, VM& vm) {
auto primitive_sphere = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_sphere_center(primitive_sphere));
});

anfr("set_primitive_sphere_radius", "primitive_sphere,v", "R:alienF", "",
"Sets primitive_sphere.radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto primitive_sphere = pop_alien(sp);
wbnd::set_primitive_sphere_radius(primitive_sphere, v);
});

anfr("get_primitive_sphere_radius", "primitive_sphere", "R:alien", "F",
"Gets primitive_sphere.radius",
   [](StackPtr& sp, VM& vm) {
auto primitive_sphere = pop_alien(sp);
Push(sp, Value(wbnd::get_primitive_sphere_radius(primitive_sphere)));
});

anfr("sphere_sphere_intersects", "sphere0,sphere1", "R:alienR:alien", "BFF}:3",
"Primitive to primitive intersection test, returns true|false,distance,direction",
   [](StackPtr& sp, VM& vm) {
auto sphere1 = pop_alien(sp);
auto sphere0 = pop_alien(sp);
float retval2;
XMFLOAT3 retval3;
Push(sp, Value(wbnd::sphere_sphere_intersects(sphere0, sphere1, retval2, retval3)));
Push(sp, Value(retval2));
push_xmfloat3(sp, retval3);
});

anfr("create_sphere_intersection_result", "", "", "R:alien",
"",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_sphere_intersection_result());
});

anfr("set_sphere_intersection_result_entity", "sphere_intersection_result,v", "R:alienI}:2", "",
"Sets sphere_intersection_result.entity",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto sphere_intersection_result = pop_alien(sp);
wbnd::set_sphere_intersection_result_entity(sphere_intersection_result, v);
});

anfr("get_sphere_intersection_result_entity", "sphere_intersection_result", "R:alien", "I}:2",
"Gets sphere_intersection_result.entity",
   [](StackPtr& sp, VM& vm) {
auto sphere_intersection_result = pop_alien(sp);
push_wo_handle(sp, wbnd::get_sphere_intersection_result_entity(sphere_intersection_result));
});

anfr("set_sphere_intersection_result_position", "sphere_intersection_result,v", "R:alienF}:3", "",
"Sets sphere_intersection_result.position",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto sphere_intersection_result = pop_alien(sp);
wbnd::set_sphere_intersection_result_position(sphere_intersection_result, v);
});

anfr("get_sphere_intersection_result_position", "sphere_intersection_result", "R:alien", "F}:3",
"Gets sphere_intersection_result.position",
   [](StackPtr& sp, VM& vm) {
auto sphere_intersection_result = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_sphere_intersection_result_position(sphere_intersection_result));
});

anfr("set_sphere_intersection_result_normal", "sphere_intersection_result,v", "R:alienF}:3", "",
"Sets sphere_intersection_result.normal",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto sphere_intersection_result = pop_alien(sp);
wbnd::set_sphere_intersection_result_normal(sphere_intersection_result, v);
});

anfr("get_sphere_intersection_result_normal", "sphere_intersection_result", "R:alien", "F}:3",
"Gets sphere_intersection_result.normal",
   [](StackPtr& sp, VM& vm) {
auto sphere_intersection_result = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_sphere_intersection_result_normal(sphere_intersection_result));
});

anfr("set_sphere_intersection_result_velocity", "sphere_intersection_result,v", "R:alienF}:3", "",
"Sets sphere_intersection_result.velocity",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto sphere_intersection_result = pop_alien(sp);
wbnd::set_sphere_intersection_result_velocity(sphere_intersection_result, v);
});

anfr("get_sphere_intersection_result_velocity", "sphere_intersection_result", "R:alien", "F}:3",
"Gets sphere_intersection_result.velocity",
   [](StackPtr& sp, VM& vm) {
auto sphere_intersection_result = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_sphere_intersection_result_velocity(sphere_intersection_result));
});

anfr("set_sphere_intersection_result_depth", "sphere_intersection_result,v", "R:alienF", "",
"Sets sphere_intersection_result.depth",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto sphere_intersection_result = pop_alien(sp);
wbnd::set_sphere_intersection_result_depth(sphere_intersection_result, v);
});

anfr("get_sphere_intersection_result_depth", "sphere_intersection_result", "R:alien", "F",
"Gets sphere_intersection_result.depth",
   [](StackPtr& sp, VM& vm) {
auto sphere_intersection_result = pop_alien(sp);
Push(sp, Value(wbnd::get_sphere_intersection_result_depth(sphere_intersection_result)));
});

anfr("scene_sphere_intersects", "scene,sphere,filter_mask,layer_mask,lod", "R:alienR:alienIII", "R:alien",
"Tests a sphere intersection with a scene, and returns a SphereIntersectionResult",
   [](StackPtr& sp, VM& vm) {
auto lod = (int32_t)Pop(sp).ival();
auto layer_mask = (int32_t)Pop(sp).ival();
auto filter_mask = (int32_t)Pop(sp).ival();
auto sphere = pop_alien(sp);
auto scene = pop_alien(sp);
push_alien(sp, vm, wbnd::scene_sphere_intersects(scene, sphere, filter_mask, layer_mask, lod));
});

anfr("create_primitive_capsule", "", "", "R:alien",
"",
   [](StackPtr& sp, VM& vm) {
push_alien(sp, vm, wbnd::create_primitive_capsule());
});

anfr("set_primitive_capsule_base", "primitive_capsule,v", "R:alienF}:3", "",
"Sets primitive_capsule.base",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_capsule = pop_alien(sp);
wbnd::set_primitive_capsule_base(primitive_capsule, v);
});

anfr("get_primitive_capsule_base", "primitive_capsule", "R:alien", "F}:3",
"Gets primitive_capsule.base",
   [](StackPtr& sp, VM& vm) {
auto primitive_capsule = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_capsule_base(primitive_capsule));
});

anfr("set_primitive_capsule_tip", "primitive_capsule,v", "R:alienF}:3", "",
"Sets primitive_capsule.tip",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto primitive_capsule = pop_alien(sp);
wbnd::set_primitive_capsule_tip(primitive_capsule, v);
});

anfr("get_primitive_capsule_tip", "primitive_capsule", "R:alien", "F}:3",
"Gets primitive_capsule.tip",
   [](StackPtr& sp, VM& vm) {
auto primitive_capsule = pop_alien(sp);
push_xmfloat3(sp, wbnd::get_primitive_capsule_tip(primitive_capsule));
});

anfr("set_primitive_capsule_radius", "primitive_capsule,v", "R:alienF", "",
"Sets primitive_capsule.radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto primitive_capsule = pop_alien(sp);
wbnd::set_primitive_capsule_radius(primitive_capsule, v);
});

anfr("get_primitive_capsule_radius", "primitive_capsule", "R:alien", "F",
"Gets primitive_capsule.radius",
   [](StackPtr& sp, VM& vm) {
auto primitive_capsule = pop_alien(sp);
Push(sp, Value(wbnd::get_primitive_capsule_radius(primitive_capsule)));
});

anfr("capsule_capsule_intersects", "cap0,cap1", "R:alienR:alien", "BF}:3F}:3F",
"Capsule to capsule intersection test, returns true/false, position, normal, penetration_depth",
   [](StackPtr& sp, VM& vm) {
auto cap1 = pop_alien(sp);
auto cap0 = pop_alien(sp);
XMFLOAT3 retval2;
XMFLOAT3 retval3;
float retval4;
Push(sp, Value(wbnd::capsule_capsule_intersects(cap0, cap1, retval2, retval3, retval4)));
push_xmfloat3(sp, retval2);
push_xmfloat3(sp, retval3);
Push(sp, Value(retval4));
});

anfr("capsule_sphere_intersects", "cap,sphere", "R:alienR:alien", "BFF}:3",
"Capsule to sphere intersection test, returns bool, dist, direction",
   [](StackPtr& sp, VM& vm) {
auto sphere = pop_alien(sp);
auto cap = pop_alien(sp);
float retval2;
XMFLOAT3 retval3;
Push(sp, Value(wbnd::capsule_sphere_intersects(cap, sphere, retval2, retval3)));
Push(sp, Value(retval2));
push_xmfloat3(sp, retval3);
});

anfr("sphere_capsule_intersects", "sphere,cap", "R:alienR:alien", "BFF}:3",
"Sphere to capsule intersection test, returns bool, dist, direction",
   [](StackPtr& sp, VM& vm) {
auto cap = pop_alien(sp);
auto sphere = pop_alien(sp);
float retval2;
XMFLOAT3 retval3;
Push(sp, Value(wbnd::sphere_capsule_intersects(sphere, cap, retval2, retval3)));
Push(sp, Value(retval2));
push_xmfloat3(sp, retval3);
});

anfr("scene_capsule_intersects", "scene,cap,filter_mask,layer_mask,lod", "R:alienR:alienIII", "R:alien",
"Tests whether a capsule intersects anything in the scene, returning a SphereIntersectionResult (not a typo)",
   [](StackPtr& sp, VM& vm) {
auto lod = (int32_t)Pop(sp).ival();
auto layer_mask = (int32_t)Pop(sp).ival();
auto filter_mask = (int32_t)Pop(sp).ival();
auto cap = pop_alien(sp);
auto scene = pop_alien(sp);
push_alien(sp, vm, wbnd::scene_capsule_intersects(scene, cap, filter_mask, layer_mask, lod));
});

anfr("scene_ray_intersects", "scene,ray,filter_mask,layer_mask,lod", "R:alienR:alienIII", "R:alien",
"Tests whether a ray intersects anything in the scene, returning a RayIntersectionResult",
   [](StackPtr& sp, VM& vm) {
auto lod = (int32_t)Pop(sp).ival();
auto layer_mask = (int32_t)Pop(sp).ival();
auto filter_mask = (int32_t)Pop(sp).ival();
auto ray = pop_alien(sp);
auto scene = pop_alien(sp);
push_alien(sp, vm, wbnd::scene_ray_intersects(scene, ray, filter_mask, layer_mask, lod));
});

anfr("set_rigidbody_physics_shape", "rigidbody_physics,v", "I}:2I", "",
"Sets rigidbody_physics.shape",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_shape(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_shape", "rigidbody_physics", "I}:2", "I",
"Gets rigidbody_physics.shape",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_shape(rigidbody_physics)));
});

anfr("set_rigidbody_physics_mass", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.mass",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_mass(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_mass", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.mass",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_mass(rigidbody_physics)));
});

anfr("set_rigidbody_physics_friction", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.friction",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_friction(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_friction", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.friction",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_friction(rigidbody_physics)));
});

anfr("set_rigidbody_physics_restitution", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.restitution",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_restitution(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_restitution", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.restitution",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_restitution(rigidbody_physics)));
});

anfr("set_rigidbody_physics_damping_linear", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.damping_linear",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_damping_linear(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_damping_linear", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.damping_linear",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_damping_linear(rigidbody_physics)));
});

anfr("set_rigidbody_physics_damping_angular", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.damping_angular",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_damping_angular(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_damping_angular", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.damping_angular",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_damping_angular(rigidbody_physics)));
});

anfr("set_rigidbody_physics_box_halfextents", "rigidbody_physics,v", "I}:2F}:3", "",
"Sets rigidbody_physics.box_halfextents",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_box_halfextents(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_box_halfextents", "rigidbody_physics", "I}:2", "F}:3",
"Gets rigidbody_physics.box_halfextents",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_rigidbody_physics_box_halfextents(rigidbody_physics));
});

anfr("set_rigidbody_physics_sphere_radius", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.sphere_radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_sphere_radius(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_sphere_radius", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.sphere_radius",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_sphere_radius(rigidbody_physics)));
});

anfr("set_rigidbody_physics_capsule_radius", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.capsule_radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_capsule_radius(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_capsule_radius", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.capsule_radius",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_capsule_radius(rigidbody_physics)));
});

anfr("set_rigidbody_physics_capsule_height", "rigidbody_physics,v", "I}:2F", "",
"Sets rigidbody_physics.capsule_height",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_capsule_height(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_capsule_height", "rigidbody_physics", "I}:2", "F",
"Gets rigidbody_physics.capsule_height",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_capsule_height(rigidbody_physics)));
});

anfr("set_rigidbody_physics_mesh_lod", "rigidbody_physics,v", "I}:2I", "",
"Sets rigidbody_physics.mesh_lod",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_mesh_lod(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_mesh_lod", "rigidbody_physics", "I}:2", "I",
"Gets rigidbody_physics.mesh_lod",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_mesh_lod(rigidbody_physics)));
});

anfr("set_rigidbody_physics_disable_deactivation", "rigidbody_physics,v", "I}:2B", "",
"Sets rigidbody_physics.disable_deactivation",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_disable_deactivation(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_disable_deactivation", "rigidbody_physics", "I}:2", "B",
"Gets rigidbody_physics.disable_deactivation",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_disable_deactivation(rigidbody_physics)));
});

anfr("set_rigidbody_physics_kinematic", "rigidbody_physics,v", "I}:2B", "",
"Sets rigidbody_physics.kinematic",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto rigidbody_physics = pop_wo_handle(sp);
wbnd::set_rigidbody_physics_kinematic(rigidbody_physics, v);
});

anfr("get_rigidbody_physics_kinematic", "rigidbody_physics", "I}:2", "B",
"Gets rigidbody_physics.kinematic",
   [](StackPtr& sp, VM& vm) {
auto rigidbody_physics = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_rigidbody_physics_kinematic(rigidbody_physics)));
});

anfr("create_rigidbody_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a rigidbody component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_rigidbody_component(scene, entity));
});

anfr("get_rigidbody_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the rigidbody component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_rigidbody_component(scene, entity));
});

anfr("entity_rigidbody_count", "scene", "R:alien", "I",
"Returns the number of entities that have a rigidbody component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_rigidbody_count(scene)));
});

anfr("entity_rigidbody_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a rigidbody component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_rigidbody_get(scene, n));
});

anfr("set_object_mesh_id", "object,v", "I}:2I}:2", "",
"Sets object.mesh_id",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto object = pop_wo_handle(sp);
wbnd::set_object_mesh_id(object, v);
});

anfr("get_object_mesh_id", "object", "I}:2", "I}:2",
"Gets object.mesh_id",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_object_mesh_id(object));
});

anfr("set_object_cascade_mask", "object,v", "I}:2I", "",
"Sets object.cascade_mask",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_cascade_mask(object, v);
});

anfr("get_object_cascade_mask", "object", "I}:2", "I",
"Gets object.cascade_mask",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_cascade_mask(object)));
});

anfr("set_object_filter_mask", "object,v", "I}:2I", "",
"Sets object.filter_mask",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_filter_mask(object, v);
});

anfr("get_object_filter_mask", "object", "I}:2", "I",
"Gets object.filter_mask",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_filter_mask(object)));
});

anfr("set_object_color", "object,v", "I}:2F}:4", "",
"Sets object.color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto object = pop_wo_handle(sp);
wbnd::set_object_color(object, v);
});

anfr("get_object_color", "object", "I}:2", "F}:4",
"Gets object.color",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_object_color(object));
});

anfr("set_object_emissive_color", "object,v", "I}:2F}:4", "",
"Sets object.emissive_color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto object = pop_wo_handle(sp);
wbnd::set_object_emissive_color(object, v);
});

anfr("get_object_emissive_color", "object", "I}:2", "F}:4",
"Gets object.emissive_color",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_object_emissive_color(object));
});

anfr("set_object_user_stencil_ref", "object,v", "I}:2I", "",
"Sets object.user_stencil_ref",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_user_stencil_ref(object, v);
});

anfr("get_object_user_stencil_ref", "object", "I}:2", "I",
"Gets object.user_stencil_ref",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_user_stencil_ref(object)));
});

anfr("set_object_lod_distance_multiplier", "object,v", "I}:2F", "",
"Sets object.lod_distance_multiplier",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto object = pop_wo_handle(sp);
wbnd::set_object_lod_distance_multiplier(object, v);
});

anfr("get_object_lod_distance_multiplier", "object", "I}:2", "F",
"Gets object.lod_distance_multiplier",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_lod_distance_multiplier(object)));
});

anfr("set_object_draw_distance", "object,v", "I}:2F", "",
"Sets object.draw_distance",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto object = pop_wo_handle(sp);
wbnd::set_object_draw_distance(object, v);
});

anfr("get_object_draw_distance", "object", "I}:2", "F",
"Gets object.draw_distance",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_draw_distance(object)));
});

anfr("set_object_lightmap_width", "object,v", "I}:2I", "",
"Sets object.lightmap_width",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_lightmap_width(object, v);
});

anfr("get_object_lightmap_width", "object", "I}:2", "I",
"Gets object.lightmap_width",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_lightmap_width(object)));
});

anfr("set_object_lightmap_height", "object,v", "I}:2I", "",
"Sets object.lightmap_height",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_lightmap_height(object, v);
});

anfr("get_object_lightmap_height", "object", "I}:2", "I",
"Gets object.lightmap_height",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_lightmap_height(object)));
});

anfr("set_object_sort_priority", "object,v", "I}:2I", "",
"Sets object.sort_priority",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto object = pop_wo_handle(sp);
wbnd::set_object_sort_priority(object, v);
});

anfr("get_object_sort_priority", "object", "I}:2", "I",
"Gets object.sort_priority",
   [](StackPtr& sp, VM& vm) {
auto object = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_object_sort_priority(object)));
});

anfr("create_object_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a object component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_object_component(scene, entity));
});

anfr("get_object_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the object component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_object_component(scene, entity));
});

anfr("entity_object_count", "scene", "R:alien", "I",
"Returns the number of entities that have a object component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_object_count(scene)));
});

anfr("entity_object_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a object component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_object_get(scene, n));
});

anfr("set_hierarchy_parent_id", "hierarchy,v", "I}:2I}:2", "",
"Sets hierarchy.parent_id",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto hierarchy = pop_wo_handle(sp);
wbnd::set_hierarchy_parent_id(hierarchy, v);
});

anfr("get_hierarchy_parent_id", "hierarchy", "I}:2", "I}:2",
"Gets hierarchy.parent_id",
   [](StackPtr& sp, VM& vm) {
auto hierarchy = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_hierarchy_parent_id(hierarchy));
});

anfr("set_hierarchy_layermask_bind", "hierarchy,v", "I}:2I", "",
"Sets hierarchy.layermask_bind",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto hierarchy = pop_wo_handle(sp);
wbnd::set_hierarchy_layermask_bind(hierarchy, v);
});

anfr("get_hierarchy_layermask_bind", "hierarchy", "I}:2", "I",
"Gets hierarchy.layermask_bind",
   [](StackPtr& sp, VM& vm) {
auto hierarchy = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_hierarchy_layermask_bind(hierarchy)));
});

anfr("create_hierarchy_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a hierarchy component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_hierarchy_component(scene, entity));
});

anfr("get_hierarchy_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the hierarchy component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_hierarchy_component(scene, entity));
});

anfr("entity_hierarchy_count", "scene", "R:alien", "I",
"Returns the number of entities that have a hierarchy component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_hierarchy_count(scene)));
});

anfr("entity_hierarchy_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a hierarchy component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_hierarchy_get(scene, n));
});

anfr("set_light_type", "light,v", "I}:2I", "",
"Sets light.type",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto light = pop_wo_handle(sp);
wbnd::set_light_type(light, v);
});

anfr("get_light_type", "light", "I}:2", "I",
"Gets light.type",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_type(light)));
});

anfr("set_light_color", "light,v", "I}:2F}:3", "",
"Sets light.color",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto light = pop_wo_handle(sp);
wbnd::set_light_color(light, v);
});

anfr("get_light_color", "light", "I}:2", "F}:3",
"Gets light.color",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_light_color(light));
});

anfr("set_light_intensity", "light,v", "I}:2F", "",
"Sets light.intensity",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_intensity(light, v);
});

anfr("get_light_intensity", "light", "I}:2", "F",
"Gets light.intensity",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_intensity(light)));
});

anfr("set_light_range", "light,v", "I}:2F", "",
"Sets light.range",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_range(light, v);
});

anfr("get_light_range", "light", "I}:2", "F",
"Gets light.range",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_range(light)));
});

anfr("set_light_outer_cone_angle", "light,v", "I}:2F", "",
"Sets light.outer_cone_angle",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_outer_cone_angle(light, v);
});

anfr("get_light_outer_cone_angle", "light", "I}:2", "F",
"Gets light.outer_cone_angle",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_outer_cone_angle(light)));
});

anfr("set_light_inner_cone_angle", "light,v", "I}:2F", "",
"Sets light.inner_cone_angle",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_inner_cone_angle(light, v);
});

anfr("get_light_inner_cone_angle", "light", "I}:2", "F",
"Gets light.inner_cone_angle",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_inner_cone_angle(light)));
});

anfr("set_light_radius", "light,v", "I}:2F", "",
"Sets light.radius",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_radius(light, v);
});

anfr("get_light_radius", "light", "I}:2", "F",
"Gets light.radius",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_radius(light)));
});

anfr("set_light_length", "light,v", "I}:2F", "",
"Sets light.length",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto light = pop_wo_handle(sp);
wbnd::set_light_length(light, v);
});

anfr("get_light_length", "light", "I}:2", "F",
"Gets light.length",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_length(light)));
});

anfr("set_light_casts_shadow", "light,v", "I}:2B", "",
"Sets light.casts_shadow",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto light = pop_wo_handle(sp);
wbnd::set_light_casts_shadow(light, v);
});

anfr("get_light_casts_shadow", "light", "I}:2", "B",
"Gets light.casts_shadow",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_casts_shadow(light)));
});

anfr("set_light_volumetrics_enabled", "light,v", "I}:2B", "",
"Sets light.volumetrics_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto light = pop_wo_handle(sp);
wbnd::set_light_volumetrics_enabled(light, v);
});

anfr("get_light_volumetrics_enabled", "light", "I}:2", "B",
"Gets light.volumetrics_enabled",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_volumetrics_enabled(light)));
});

anfr("set_light_visualizer_enabled", "light,v", "I}:2B", "",
"Sets light.visualizer_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto light = pop_wo_handle(sp);
wbnd::set_light_visualizer_enabled(light, v);
});

anfr("get_light_visualizer_enabled", "light", "I}:2", "B",
"Gets light.visualizer_enabled",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_visualizer_enabled(light)));
});

anfr("set_light_is_static", "light,v", "I}:2B", "",
"Sets light.is_static",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto light = pop_wo_handle(sp);
wbnd::set_light_is_static(light, v);
});

anfr("get_light_is_static", "light", "I}:2", "B",
"Gets light.is_static",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_is_static(light)));
});

anfr("set_light_volumetric_clouds_enabled", "light,v", "I}:2B", "",
"Sets light.volumetric_clouds_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto light = pop_wo_handle(sp);
wbnd::set_light_volumetric_clouds_enabled(light, v);
});

anfr("get_light_volumetric_clouds_enabled", "light", "I}:2", "B",
"Gets light.volumetric_clouds_enabled",
   [](StackPtr& sp, VM& vm) {
auto light = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_light_volumetric_clouds_enabled(light)));
});

anfr("create_light_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a light component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_light_component(scene, entity));
});

anfr("get_light_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the light component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_light_component(scene, entity));
});

anfr("entity_light_count", "scene", "R:alien", "I",
"Returns the number of entities that have a light component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_light_count(scene)));
});

anfr("entity_light_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a light component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_light_get(scene, n));
});

anfr("set_resource_sound", "resource,sound", "I}:2I}:2", "",
"Populates the Resource with sound data",
   [](StackPtr& sp, VM& vm) {
auto sound = pop_wo_handle(sp);
auto resource = pop_wo_handle(sp);
wbnd::set_resource_sound(resource, sound);
});

anfr("set_resource_outdated", "resource", "I}:2", "",
"Resource marked for recreate on resourcemanager::Load()",
   [](StackPtr& sp, VM& vm) {
auto resource = pop_wo_handle(sp);
wbnd::set_resource_outdated(resource);
});

anfr("set_sound_instance_loop_begin", "sound_instance,v", "I}:2F", "",
"Sets sound_instance.loop_begin",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto sound_instance = pop_wo_handle(sp);
wbnd::set_sound_instance_loop_begin(sound_instance, v);
});

anfr("get_sound_instance_loop_begin", "sound_instance", "I}:2", "F",
"Gets sound_instance.loop_begin",
   [](StackPtr& sp, VM& vm) {
auto sound_instance = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_instance_loop_begin(sound_instance)));
});

anfr("set_sound_instance_loop_length", "sound_instance,v", "I}:2F", "",
"Sets sound_instance.loop_length",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto sound_instance = pop_wo_handle(sp);
wbnd::set_sound_instance_loop_length(sound_instance, v);
});

anfr("get_sound_instance_loop_length", "sound_instance", "I}:2", "F",
"Gets sound_instance.loop_length",
   [](StackPtr& sp, VM& vm) {
auto sound_instance = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_instance_loop_length(sound_instance)));
});

anfr("set_sound_instance_reverb_enabled", "sound_instance,v", "I}:2B", "",
"Sets sound_instance.reverb_enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto sound_instance = pop_wo_handle(sp);
wbnd::set_sound_instance_reverb_enabled(sound_instance, v);
});

anfr("get_sound_instance_reverb_enabled", "sound_instance", "I}:2", "B",
"Gets sound_instance.reverb_enabled",
   [](StackPtr& sp, VM& vm) {
auto sound_instance = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_instance_reverb_enabled(sound_instance)));
});

anfr("sound_instance_is_valid", "sound_instance", "I}:2", "B",
"Returns true if the sound instance is valid.",
   [](StackPtr& sp, VM& vm) {
auto sound_instance = pop_wo_handle(sp);
Push(sp, Value(wbnd::sound_instance_is_valid(sound_instance)));
});

anfr("set_sound_component_filename", "sound_component,v", "I}:2S", "",
"Sets sound_component.filename",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).sval()->strv();
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_filename(sound_component, v);
});

anfr("get_sound_component_filename", "sound_component", "I}:2", "S",
"Gets sound_component.filename",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
Push(sp, Value(vm.NewString(wbnd::get_sound_component_filename(sound_component))));
});

anfr("set_sound_component_resource", "sound_component,v", "I}:2I}:2", "",
"Sets sound_component.resource",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_resource(sound_component, v);
});

anfr("get_sound_component_resource", "sound_component", "I}:2", "I}:2",
"Gets sound_component.resource",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_sound_component_resource(sound_component));
});

anfr("set_sound_component_instance", "sound_component,v", "I}:2I}:2", "",
"Sets sound_component.instance",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_instance(sound_component, v);
});

anfr("get_sound_component_instance", "sound_component", "I}:2", "I}:2",
"Gets sound_component.instance",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_sound_component_instance(sound_component));
});

anfr("set_sound_component_volume", "sound_component,v", "I}:2F", "",
"Sets sound_component.volume",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_volume(sound_component, v);
});

anfr("get_sound_component_volume", "sound_component", "I}:2", "F",
"Gets sound_component.volume",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_component_volume(sound_component)));
});

anfr("set_sound_component_is_playing", "sound_component,v", "I}:2B", "",
"Sets sound_component.is_playing",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_is_playing(sound_component, v);
});

anfr("get_sound_component_is_playing", "sound_component", "I}:2", "B",
"Gets sound_component.is_playing",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_component_is_playing(sound_component)));
});

anfr("set_sound_component_is_looped", "sound_component,v", "I}:2B", "",
"Sets sound_component.is_looped",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_is_looped(sound_component, v);
});

anfr("get_sound_component_is_looped", "sound_component", "I}:2", "B",
"Gets sound_component.is_looped",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_component_is_looped(sound_component)));
});

anfr("set_sound_component_is_disable_3d", "sound_component,v", "I}:2B", "",
"Sets sound_component.is_disable_3d",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto sound_component = pop_wo_handle(sp);
wbnd::set_sound_component_is_disable_3d(sound_component, v);
});

anfr("get_sound_component_is_disable_3d", "sound_component", "I}:2", "B",
"Gets sound_component.is_disable_3d",
   [](StackPtr& sp, VM& vm) {
auto sound_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_sound_component_is_disable_3d(sound_component)));
});

anfr("create_sound_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a sound component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_sound_component(scene, entity));
});

anfr("get_sound_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the sound component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_sound_component(scene, entity));
});

anfr("entity_sound_count", "scene", "R:alien", "I",
"Returns the number of entities that have a sound component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_sound_count(scene)));
});

anfr("entity_sound_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a sound component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_sound_get(scene, n));
});

anfr("scene_create_sound_entity", "scene,name,filename,pos", "R:alienSSF}:3", "I}:2",
"Creates a entity with a sound component in the given scene, and returns it",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 pos;
pop_xmfloat3(sp,pos);
auto filename = Pop(sp).sval()->strv();
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::scene_create_sound_entity(scene, name, filename, pos));
});

anfr("set_decal_component_slope_blend_power", "decal_component,v", "I}:2F", "",
"Sets decal_component.slope_blend_power",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto decal_component = pop_wo_handle(sp);
wbnd::set_decal_component_slope_blend_power(decal_component, v);
});

anfr("get_decal_component_slope_blend_power", "decal_component", "I}:2", "F",
"Gets decal_component.slope_blend_power",
   [](StackPtr& sp, VM& vm) {
auto decal_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_decal_component_slope_blend_power(decal_component)));
});

anfr("set_decal_component_texture", "decal_component,v", "I}:2I}:2", "",
"Sets decal_component.texture",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto decal_component = pop_wo_handle(sp);
wbnd::set_decal_component_texture(decal_component, v);
});

anfr("get_decal_component_texture", "decal_component", "I}:2", "I}:2",
"Gets decal_component.texture",
   [](StackPtr& sp, VM& vm) {
auto decal_component = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_decal_component_texture(decal_component));
});

anfr("set_decal_component_normal", "decal_component,v", "I}:2I}:2", "",
"Sets decal_component.normal",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto decal_component = pop_wo_handle(sp);
wbnd::set_decal_component_normal(decal_component, v);
});

anfr("get_decal_component_normal", "decal_component", "I}:2", "I}:2",
"Gets decal_component.normal",
   [](StackPtr& sp, VM& vm) {
auto decal_component = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_decal_component_normal(decal_component));
});

anfr("set_decal_component_surfacemap", "decal_component,v", "I}:2I}:2", "",
"Sets decal_component.surfacemap",
   [](StackPtr& sp, VM& vm) {
auto v = pop_wo_handle(sp);
auto decal_component = pop_wo_handle(sp);
wbnd::set_decal_component_surfacemap(decal_component, v);
});

anfr("get_decal_component_surfacemap", "decal_component", "I}:2", "I}:2",
"Gets decal_component.surfacemap",
   [](StackPtr& sp, VM& vm) {
auto decal_component = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_decal_component_surfacemap(decal_component));
});

anfr("set_decal_component_is_base_color_only_alpha", "decal_component,v", "I}:2B", "",
"Sets decal_component.is_base_color_only_alpha",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto decal_component = pop_wo_handle(sp);
wbnd::set_decal_component_is_base_color_only_alpha(decal_component, v);
});

anfr("get_decal_component_is_base_color_only_alpha", "decal_component", "I}:2", "B",
"Gets decal_component.is_base_color_only_alpha",
   [](StackPtr& sp, VM& vm) {
auto decal_component = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_decal_component_is_base_color_only_alpha(decal_component)));
});

anfr("create_decal_component", "scene,entity", "R:alienI}:2", "I}:2",
"Creates a decal component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_decal_component(scene, entity));
});

anfr("get_decal_component", "scene,entity", "R:alienI}:2", "I}:2",
"Gets the decal component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::get_decal_component(scene, entity));
});

anfr("entity_decal_count", "scene", "R:alien", "I",
"Returns the number of entities that have a decal component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_alien(sp);
Push(sp, Value(wbnd::entity_decal_count(scene)));
});

anfr("entity_decal_get", "scene,n", "R:alienI", "I}:2",
"Returns the nth entity that has a decal component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::entity_decal_get(scene, n));
});

anfr("create_decal_entity", "scene,name,texture_name,normal_map_name", "R:alienSSS", "I}:2",
"Creates a entity with a decal in the given scene, and returns it.",
   [](StackPtr& sp, VM& vm) {
auto normal_map_name = Pop(sp).sval()->strv();
auto texture_name = Pop(sp).sval()->strv();
auto name = Pop(sp).sval()->strv();
auto scene = pop_alien(sp);
push_wo_handle(sp, wbnd::create_decal_entity(scene, name, texture_name, normal_map_name));
});

