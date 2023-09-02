// GENERATED for inclusion into lobutils.cpp, do not edit.
anfr("wi_get_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
"Returns the transform component for 'entity' if it exists, or int2{?, 0} if there is none.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_transform_component(scene, entity));
});

anfr("wi_new_scene", "", "", "I}:2",
"Creates a new empty scene.",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::new_scene());
});

anfr("wi_delete_scene", "scene", "I}:2", "",
"Deletes a scene.",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
wbnd::delete_scene(scene);
});

anfr("wi_global_scene", "", "", "I}:2",
"Returns the global scene",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::global_scene());
});

anfr("wi_is_descendant_entity", "scene,entity,ancestor", "I}:2I}:2I}:2", "B",
"Returns true if 'entity' is descendant of 'ancestor'",
   [](StackPtr& sp, VM& vm) {
auto ancestor = pop_wo_handle(sp);
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::is_descendant_entity(scene, entity, ancestor)));
});

anfr("wi_remove_entity", "scene,entity,recursive", "I}:2I}:2B", "",
"Deletes an entity from the scene",
   [](StackPtr& sp, VM& vm) {
auto recursive = Pop(sp).True();
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
wbnd::remove_entity(scene, entity, recursive);
});

anfr("wi_duplicate_entity", "scene,entity", "I}:2I}:2", "I}:2",
"Duplicates an entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::duplicate_entity(scene, entity));
});

anfr("wi_scene_merge", "dest,src", "I}:2I}:2", "",
"Merges src scene into dest scene.",
   [](StackPtr& sp, VM& vm) {
auto src = pop_wo_handle(sp);
auto dest = pop_wo_handle(sp);
wbnd::scene_merge(dest, src);
});

anfr("wi_load_model", "scene,fname,attach", "I}:2SB", "I}:2",
"Loads the model from the file into the given scene. Returns valid entity handle if attached==true",
   [](StackPtr& sp, VM& vm) {
auto attach = Pop(sp).True();
auto fname = Pop(sp).sval()->strv();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::load_model(scene, fname, attach));
});

anfr("wi_create_entity", "", "", "I}:2",
"Creates a new empty entity",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_entity());
});

anfr("wi_create_layer_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a layer component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_layer_component(scene, entity));
});

anfr("wi_get_layer_component", "scene,entity", "I}:2I}:2", "I}:2",
"Gets the layer component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_layer_component(scene, entity));
});

anfr("wi_entity_layer_count", "scene", "I}:2", "I",
"Returns the number of entities that have a layer component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::entity_layer_count(scene)));
});

anfr("wi_entity_layer_get", "scene,n", "I}:2I", "I}:2",
"Returns the nth entity that has a layer component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::entity_layer_get(scene, n));
});

anfr("wi_create_humanoid_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a humanoid component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_humanoid_component(scene, entity));
});

anfr("wi_get_humanoid_component", "scene,entity", "I}:2I}:2", "I}:2",
"Gets the humanoid component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_humanoid_component(scene, entity));
});

anfr("wi_entity_humanoid_count", "scene", "I}:2", "I",
"Returns the number of entities that have a humanoid component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::entity_humanoid_count(scene)));
});

anfr("wi_entity_humanoid_get", "scene,n", "I}:2I", "I}:2",
"Returns the nth entity that has a humanoid component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::entity_humanoid_get(scene, n));
});

anfr("wi_create_name_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a name component for the given entity, and returns a the handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_name_component(scene, entity));
});

anfr("wi_nc_set_name", "name_comp,name", "I}:2S", "",
"Sets the name for a name component.",
   [](StackPtr& sp, VM& vm) {
auto name = Pop(sp).sval()->strv();
auto name_comp = pop_wo_handle(sp);
wbnd::nc_set_name(name_comp, name);
});

anfr("wi_nc_get_name", "name_comp", "I}:2", "S",
"Gets the name of a name component",
   [](StackPtr& sp, VM& vm) {
auto name_comp = pop_wo_handle(sp);
Push(sp, Value(vm.NewString(wbnd::nc_get_name(name_comp))));
});

anfr("wi_get_name_component", "scene,entity", "I}:2I}:2", "I}:2",
"Gets the name component for the given entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_name_component(scene, entity));
});

anfr("wi_entity_names_count", "scene", "I}:2", "I",
"Returns number of entities that have name components.",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::entity_names_count(scene)));
});

anfr("wi_entity_names_get", "scene,n", "I}:2I", "I}:2",
"Returns entity #n that has a name component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::entity_names_get(scene, n));
});

anfr("wi_find_entity_by_name", "scene,name,ancestor_entity", "I}:2SI}:2", "I}:2",
"Searches scene for an entity by name. Returns INVALID_ENTITY if not found.",
   [](StackPtr& sp, VM& vm) {
auto ancestor_entity = pop_wo_handle(sp);
auto name = Pop(sp).sval()->strv();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::find_entity_by_name(scene, name, ancestor_entity));
});

anfr("wi_backlog", "level,msg", "IS", "",
"Logs to Wicked Engine backlog with given log level",
   [](StackPtr& sp, VM& vm) {
auto msg = Pop(sp).sval()->strv();
auto level = (int32_t)Pop(sp).ival();
wbnd::backlog(level, msg);
});

anfr("wi_create_camera_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a camera component on an entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_camera_component(scene, entity));
});

anfr("wi_create_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a transform component on an entity",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_transform_component(scene, entity));
});

anfr("wi_create_transform", "", "", "I}:2",
"Creates a transform component attached to no scene or entity.  Seems to be used primarly for calculations from scripts",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_transform());
});

anfr("wi_delete_transform", "trans", "I}:2", "",
"Deletes a transform created by create_transform()",
   [](StackPtr& sp, VM& vm) {
auto trans = pop_wo_handle(sp);
wbnd::delete_transform(trans);
});

anfr("wi_get_fixed_update_rate", "", "", "F",
"Returns the application fixed frame update rate",
   [](StackPtr& sp, VM& vm) {
Push(sp, Value(wbnd::get_fixed_update_rate()));
});

anfr("wi_renderpath3d_set_camera", "rpath,cam_component", "I}:2I}:2", "",
"Sets the camera component used by the 3d renderpath",
   [](StackPtr& sp, VM& vm) {
auto cam_component = pop_wo_handle(sp);
auto rpath = pop_wo_handle(sp);
wbnd::renderpath3d_set_camera(rpath, cam_component);
});

anfr("wi_transform_translate", "trans_component,v", "I}:2F}:3", "",
"Tranlates transform by 'vec'",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_translate(trans_component, v);
});

anfr("wi_transform_rotate", "trans_component,quat", "I}:2F}:4", "",
"Rotates transform around given quaternion",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 quat;
pop_xmfloat4(sp,quat);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_rotate(trans_component, quat);
});

anfr("wi_transform_position", "tcomp", "I}:2", "F}:3",
"Gets transform position",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::transform_position(tcomp));
});

anfr("wi_transform_rotation", "tcomp", "I}:2", "F}:4",
"Gets transform rotation",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::transform_rotation(tcomp));
});

anfr("wi_transform_update_transform", "tcomp", "I}:2", "",
"Applies local space to world space matrix for transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
wbnd::transform_update_transform(tcomp);
});

anfr("wi_transform_clear", "trans_comp", "I}:2", "",
"Clears the transform component's transform.",
   [](StackPtr& sp, VM& vm) {
auto trans_comp = pop_wo_handle(sp);
wbnd::transform_clear(trans_comp);
});

anfr("wi_transform_rotate_roll_pitch_yaw", "tcomp,angles", "I}:2F}:3", "",
"Apply euler rotation to transform",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 angles;
pop_xmfloat3(sp,angles);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_rotate_roll_pitch_yaw(tcomp, angles);
});

anfr("wi_transform_scale", "tcomp,scale", "I}:2F}:3", "",
"Apply scale to transform",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 scale;
pop_xmfloat3(sp,scale);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_scale(tcomp, scale);
});

anfr("wi_transform_lerp", "tcomp,a,b,t", "I}:2I}:2I}:2F", "",
"Set this transform to be the linear interpolation of transforms 'a' and 'b'",
   [](StackPtr& sp, VM& vm) {
auto t = Pop(sp).fltval();
auto b = pop_wo_handle(sp);
auto a = pop_wo_handle(sp);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_lerp(tcomp, a, b, t);
});

anfr("wi_get_transform_local_matrix", "tcomp", "I}:2", "I}:2",
"gets the local matrix for the transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_transform_local_matrix(tcomp));
});

anfr("wi_get_transform_world_matrix", "tcomp", "I}:2", "I}:2",
"gets the world matrix for the transform",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_transform_world_matrix(tcomp));
});

anfr("wi_transform_transform_matrix", "tcomp,matrix", "I}:2I}:2", "",
"Trasforms the transform by the given matrix",
   [](StackPtr& sp, VM& vm) {
auto matrix = pop_wo_handle(sp);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_transform_matrix(tcomp, matrix);
});

anfr("wi_camera_fov", "tcomp", "I}:2", "F",
"Gets camera component fov",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_fov(tcomp)));
});

anfr("wi_camera_set_fov", "tcomp,fov", "I}:2F", "",
"Sets camera component fov, in radians.",
   [](StackPtr& sp, VM& vm) {
auto fov = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_fov(tcomp, fov);
});

anfr("wi_camera_get_dims", "tcomp", "I}:2", "F}:2",
"Gets camera plane dims",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::camera_get_dims(tcomp));
});

anfr("wi_camera_set_dims", "tcomp,dims", "I}:2F}:2", "",
"Sets camera plane dims",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 dims;
pop_xmfloat2(sp,dims);
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_dims(tcomp, dims);
});

anfr("wi_camera_znear", "tcomp", "I}:2", "F",
"Gets the camera zNear",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_znear(tcomp)));
});

anfr("wi_camera_set_znear", "tcomp,znear", "I}:2F", "",
"Sets the camera zNear",
   [](StackPtr& sp, VM& vm) {
auto znear = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_znear(tcomp, znear);
});

anfr("wi_camera_zfar", "tcomp", "I}:2", "F",
"Gets the camera zFar",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_zfar(tcomp)));
});

anfr("wi_camera_set_zfar", "tcomp,zfar", "I}:2F", "",
"Sets the camera zFar",
   [](StackPtr& sp, VM& vm) {
auto zfar = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_zfar(tcomp, zfar);
});

anfr("wi_camera_focal_length", "tcomp", "I}:2", "F",
"Gets the camera focal length",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_focal_length(tcomp)));
});

anfr("wi_camera_set_focal_length", "tcomp,l", "I}:2F", "",
"Sets the camera focal length",
   [](StackPtr& sp, VM& vm) {
auto l = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_focal_length(tcomp, l);
});

anfr("wi_camera_update", "tcomp", "I}:2", "",
"Updates the camera transforms",
   [](StackPtr& sp, VM& vm) {
auto tcomp = pop_wo_handle(sp);
wbnd::camera_update(tcomp);
});

anfr("wi_transform_camera_set_matrix", "camera,matrix", "I}:2I}:2", "",
"Sets the camera's transform from the matris",
   [](StackPtr& sp, VM& vm) {
auto matrix = pop_wo_handle(sp);
auto camera = pop_wo_handle(sp);
wbnd::transform_camera_set_matrix(camera, matrix);
});

anfr("wi_get_camera_component", "scene,ent", "I}:2I}:2", "I}:2",
"Gets the camera component of an entity",
   [](StackPtr& sp, VM& vm) {
auto ent = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_camera_component(scene, ent));
});

anfr("wi_get_camera_count", "scene", "I}:2", "I",
"Returns the number of cameras in the scene",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_camera_count(scene)));
});

anfr("wi_get_camera_entity", "scene,n", "I}:2I", "I}:2",
"returns entity holding the nth camera in the scene",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_camera_entity(scene, n));
});

anfr("wi_set_camera_eye", "camera,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_eye(camera, v);
});

anfr("wi_get_camera_eye", "camera", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_eye(camera));
});

anfr("wi_set_camera_at", "camera,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_at(camera, v);
});

anfr("wi_get_camera_at", "camera", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_at(camera));
});

anfr("wi_set_camera_up", "camera,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto camera = pop_wo_handle(sp);
wbnd::set_camera_up(camera, v);
});

anfr("wi_get_camera_up", "camera", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto camera = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_camera_up(camera));
});

anfr("wi_input_down", "button,playerindex", "II", "B",
"Check if a button is down",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::input_down(button, playerindex)));
});

anfr("wi_input_press", "button,playerindex", "II", "B",
"Check if a button is pressed once",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::input_press(button, playerindex)));
});

anfr("wi_input_hold", "button,frames,continuous,playerindex", "IIBI", "B",
"Check if a button is held down",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto continuous = Pop(sp).True();
auto frames = (int32_t)Pop(sp).ival();
auto button = (int32_t)Pop(sp).ival();
Push(sp, Value(wbnd::input_hold(button, frames, continuous, playerindex)));
});

anfr("wi_input_get_pointer", "", "", "F}:4",
"get pointer position (eg. mouse pointer) (.xy) + scroll delta (.z) + pressure (.w)",
   [](StackPtr& sp, VM& vm) {
push_xmfloat4(sp, wbnd::input_get_pointer());
});

anfr("wi_input_set_pointer", "props", "F}:4", "",
"sets pointer position",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 props;
pop_xmfloat4(sp,props);
wbnd::input_set_pointer(props);
});

anfr("wi_input_hide_pointer", "value", "B", "",
"Hides/shows pointer",
   [](StackPtr& sp, VM& vm) {
auto value = Pop(sp).True();
wbnd::input_hide_pointer(value);
});

anfr("wi_input_get_analog", "axis,playerindex", "II", "F}:4",
"Reads input from analog controller axis",
   [](StackPtr& sp, VM& vm) {
auto playerindex = (int32_t)Pop(sp).ival();
auto axis = (int32_t)Pop(sp).ival();
push_xmfloat4(sp, wbnd::input_get_analog(axis, playerindex));
});

anfr("wi_draw_debug_text", "text,pos,flags,color,scaling", "SF}:3IF}:4F", "",
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

anfr("wi_create_timer", "", "", "I}:2",
"Creates a wi::Timer",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_timer());
});

anfr("wi_delete_timer", "timer", "I}:2", "",
"Deletes a timer created with create_timer",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
wbnd::delete_timer(timer);
});

anfr("wi_timer_record", "timer", "I}:2", "",
"Records a reference timestamp",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
wbnd::timer_record(timer);
});

anfr("wi_timer_elapsed_seconds", "time", "I}:2", "F",
"Elapsed time since creation or last record call.",
   [](StackPtr& sp, VM& vm) {
auto time = pop_wo_handle(sp);
Push(sp, Value(wbnd::timer_elapsed_seconds(time)));
});

anfr("wi_timer_elapsed", "timer", "I}:2", "F",
"Elapsed time in milliseconds since creation or later record() call",
   [](StackPtr& sp, VM& vm) {
auto timer = pop_wo_handle(sp);
Push(sp, Value(wbnd::timer_elapsed(timer)));
});

anfr("wi_create_font_params", "", "", "I}:2",
"",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_font_params());
});

anfr("wi_delete_font_params", "font_params", "I}:2", "",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
wbnd::delete_font_params(font_params);
});

anfr("wi_set_font_params_position", "font_params,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_position(font_params, v);
});

anfr("wi_get_font_params_position", "font_params", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_font_params_position(font_params));
});

anfr("wi_set_font_params_size", "font_params,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_size(font_params, v);
});

anfr("wi_get_font_params_size", "font_params", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_size(font_params)));
});

anfr("wi_set_font_params_scaling", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_scaling(font_params, v);
});

anfr("wi_get_font_params_scaling", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_scaling(font_params)));
});

anfr("wi_set_font_params_rotation", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_rotation(font_params, v);
});

anfr("wi_get_font_params_rotation", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_rotation(font_params)));
});

anfr("wi_set_font_params_spacing_x", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_spacing_x(font_params, v);
});

anfr("wi_get_font_params_spacing_x", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_spacing_x(font_params)));
});

anfr("wi_set_font_params_spacing_y", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_spacing_y(font_params, v);
});

anfr("wi_get_font_params_spacing_y", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_spacing_y(font_params)));
});

anfr("wi_set_font_params_h_align", "font_params,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_h_align(font_params, v);
});

anfr("wi_get_font_params_h_align", "font_params", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_h_align(font_params)));
});

anfr("wi_set_font_params_v_align", "font_params,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_v_align(font_params, v);
});

anfr("wi_get_font_params_v_align", "font_params", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_v_align(font_params)));
});

anfr("wi_set_font_params_color", "font_params,v", "I}:2F}:4", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_color(font_params, v);
});

anfr("wi_get_font_params_color", "font_params", "I}:2", "F}:4",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_color(font_params));
});

anfr("wi_set_font_params_shadow_color", "font_params,v", "I}:2F}:4", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_color(font_params, v);
});

anfr("wi_get_font_params_shadow_color", "font_params", "I}:2", "F}:4",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_shadow_color(font_params));
});

anfr("wi_set_font_params_h_wrap", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_h_wrap(font_params, v);
});

anfr("wi_get_font_params_h_wrap", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_h_wrap(font_params)));
});

anfr("wi_set_font_params_style", "font_params,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_style(font_params, v);
});

anfr("wi_get_font_params_style", "font_params", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_style(font_params)));
});

anfr("wi_set_font_params_softness", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_softness(font_params, v);
});

anfr("wi_get_font_params_softness", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_softness(font_params)));
});

anfr("wi_set_font_params_bolden", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_bolden(font_params, v);
});

anfr("wi_get_font_params_bolden", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_bolden(font_params)));
});

anfr("wi_set_font_params_shadow_softness", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_softness(font_params, v);
});

anfr("wi_get_font_params_shadow_softness", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_softness(font_params)));
});

anfr("wi_set_font_params_shadow_bolden", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_bolden(font_params, v);
});

anfr("wi_get_font_params_shadow_bolden", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_bolden(font_params)));
});

anfr("wi_set_font_params_shadow_offset_x", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_offset_x(font_params, v);
});

anfr("wi_get_font_params_shadow_offset_x", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_offset_x(font_params)));
});

anfr("wi_set_font_params_shadow_offset_y", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_shadow_offset_y(font_params, v);
});

anfr("wi_get_font_params_shadow_offset_y", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_shadow_offset_y(font_params)));
});

anfr("wi_set_font_params_cursor", "font_params,v", "I}:2F}:4", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 v;
pop_xmfloat4(sp,v);
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_cursor(font_params, v);
});

anfr("wi_get_font_params_cursor", "font_params", "I}:2", "F}:4",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::get_font_params_cursor(font_params));
});

anfr("wi_set_font_params_hdr_scaling", "font_params,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto font_params = pop_wo_handle(sp);
wbnd::set_font_params_hdr_scaling(font_params, v);
});

anfr("wi_get_font_params_hdr_scaling", "font_params", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_font_params_hdr_scaling(font_params)));
});

anfr("wi_create_sprite_font", "", "", "I}:2",
"Creates a SpriteFont",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_sprite_font());
});

anfr("wi_sprite_font_set_params", "font,font_params", "I}:2I}:2", "",
"Sets the font_params for a sprite font",
   [](StackPtr& sp, VM& vm) {
auto font_params = pop_wo_handle(sp);
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_params(font, font_params);
});

anfr("wi_delete_sprite_font", "font", "I}:2", "",
"Deletes a SpriteFont",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
wbnd::delete_sprite_font(font);
});

anfr("wi_sprite_font_set_hidden", "font,value", "I}:2B", "",
"Changes fonts hidden state",
   [](StackPtr& sp, VM& vm) {
auto value = Pop(sp).True();
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_hidden(font, value);
});

anfr("wi_sprite_font_text_size", "font", "I}:2", "F}:2",
"Returns dimensions of the text",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::sprite_font_text_size(font));
});

anfr("wi_sprite_font_set_text", "font,txt", "I}:2S", "",
"Sets the text TODO is non-wstring version of this utf8 friendly?",
   [](StackPtr& sp, VM& vm) {
auto txt = Pop(sp).sval()->strv();
auto font = pop_wo_handle(sp);
wbnd::sprite_font_set_text(font, txt);
});

anfr("wi_sprite_font_get_text", "font", "I}:2", "S",
"Gets the text",
   [](StackPtr& sp, VM& vm) {
auto font = pop_wo_handle(sp);
Push(sp, Value(vm.NewString(wbnd::sprite_font_get_text(font))));
});

anfr("wi_set_humanoid_default_look_direction", "humanoid,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_default_look_direction(humanoid, v);
});

anfr("wi_get_humanoid_default_look_direction", "humanoid", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_humanoid_default_look_direction(humanoid));
});

anfr("wi_set_humanoid_head_rotation_max", "humanoid,v", "I}:2F}:2", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 v;
pop_xmfloat2(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_head_rotation_max(humanoid, v);
});

anfr("wi_get_humanoid_head_rotation_max", "humanoid", "I}:2", "F}:2",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::get_humanoid_head_rotation_max(humanoid));
});

anfr("wi_set_humanoid_head_rotation_speed", "humanoid,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_head_rotation_speed(humanoid, v);
});

anfr("wi_get_humanoid_head_rotation_speed", "humanoid", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_humanoid_head_rotation_speed(humanoid)));
});

anfr("wi_set_humanoid_eye_rotation_max", "humanoid,v", "I}:2F}:2", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT2 v;
pop_xmfloat2(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_eye_rotation_max(humanoid, v);
});

anfr("wi_get_humanoid_eye_rotation_max", "humanoid", "I}:2", "F}:2",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::get_humanoid_eye_rotation_max(humanoid));
});

anfr("wi_set_humanoid_eye_rotation_speed", "humanoid,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_eye_rotation_speed(humanoid, v);
});

anfr("wi_get_humanoid_eye_rotation_speed", "humanoid", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_humanoid_eye_rotation_speed(humanoid)));
});

anfr("wi_set_humanoid_look_at", "humanoid,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto humanoid = pop_wo_handle(sp);
wbnd::set_humanoid_look_at(humanoid, v);
});

anfr("wi_get_humanoid_look_at", "humanoid", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto humanoid = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_humanoid_look_at(humanoid));
});

anfr("wi_humanoid_bone_count", "hum", "I}:2", "I",
"Returns number of bones in humanoid component",
   [](StackPtr& sp, VM& vm) {
auto hum = pop_wo_handle(sp);
Push(sp, Value(wbnd::humanoid_bone_count(hum)));
});

anfr("wi_humanoid_bone", "hum,i", "I}:2I", "I}:2",
"Returns entity for bone with the given HumanoidBone name",
   [](StackPtr& sp, VM& vm) {
auto i = (int32_t)Pop(sp).ival();
auto hum = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::humanoid_bone(hum, i));
});

anfr("wi_humanoid_is_lookat_enabled", "hum", "I}:2", "B",
"Is lookat enabled?",
   [](StackPtr& sp, VM& vm) {
auto hum = pop_wo_handle(sp);
Push(sp, Value(wbnd::humanoid_is_lookat_enabled(hum)));
});

anfr("wi_humanoid_set_lookat_enabled", "hum,v", "I}:2B", "",
"Sets lookat for humanoid component",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto hum = pop_wo_handle(sp);
wbnd::humanoid_set_lookat_enabled(hum, v);
});

anfr("wi_set_layer_mask", "layer,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto layer = pop_wo_handle(sp);
wbnd::set_layer_mask(layer, v);
});

anfr("wi_get_layer_mask", "layer", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto layer = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_layer_mask(layer)));
});

anfr("wi_set_layer_propagation_mask", "layer,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto layer = pop_wo_handle(sp);
wbnd::set_layer_propagation_mask(layer, v);
});

anfr("wi_get_layer_propagation_mask", "layer", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto layer = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_layer_propagation_mask(layer)));
});

anfr("wi_get_renderpath3d", "", "", "I}:2",
"Returns the games RenderPath3d",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::get_renderpath3d());
});

anfr("wi_renderpath_add_font", "path,sprite_font,layer", "I}:2I}:2S", "",
"Adds a sprite font to the renderpath",
   [](StackPtr& sp, VM& vm) {
auto layer = Pop(sp).sval()->strv();
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_add_font(path, sprite_font, layer);
});

anfr("wi_renderpath_remove_font", "path,sprite_font", "I}:2I}:2", "",
"Removes a sprite font from the renderpath",
   [](StackPtr& sp, VM& vm) {
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_remove_font(path, sprite_font);
});

anfr("wi_renderpath_clear_fonts", "path", "I}:2", "",
"Clears all fonts from renderpath",
   [](StackPtr& sp, VM& vm) {
auto path = pop_wo_handle(sp);
wbnd::renderpath_clear_fonts(path);
});

anfr("wi_renderpath_font_order", "path,sprite_font", "I}:2I}:2", "I",
"Returns the order for the given font",
   [](StackPtr& sp, VM& vm) {
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
Push(sp, Value(wbnd::renderpath_font_order(path, sprite_font)));
});

anfr("wi_renderpath_set_font_order", "path,sprite_font,order", "I}:2I}:2I", "",
"Sets the order for the given font",
   [](StackPtr& sp, VM& vm) {
auto order = (int32_t)Pop(sp).ival();
auto sprite_font = pop_wo_handle(sp);
auto path = pop_wo_handle(sp);
wbnd::renderpath_set_font_order(path, sprite_font, order);
});

anfr("wi_set_collider_shape", "collider,v", "I}:2I", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = (int32_t)Pop(sp).ival();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_shape(collider, v);
});

anfr("wi_get_collider_shape", "collider", "I}:2", "I",
"",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_collider_shape(collider)));
});

anfr("wi_set_collider_radius", "collider,v", "I}:2F", "",
"",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).fltval();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_radius(collider, v);
});

anfr("wi_get_collider_radius", "collider", "I}:2", "F",
"",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
Push(sp, Value(wbnd::get_collider_radius(collider)));
});

anfr("wi_set_collider_offset", "collider,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto collider = pop_wo_handle(sp);
wbnd::set_collider_offset(collider, v);
});

anfr("wi_get_collider_offset", "collider", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_collider_offset(collider));
});

anfr("wi_set_collider_tail", "collider,v", "I}:2F}:3", "",
"",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto collider = pop_wo_handle(sp);
wbnd::set_collider_tail(collider, v);
});

anfr("wi_get_collider_tail", "collider", "I}:2", "F}:3",
"",
   [](StackPtr& sp, VM& vm) {
auto collider = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::get_collider_tail(collider));
});

anfr("wi_set_collider_is_gpu_enabled", "collider,v", "I}:2B", "",
"Set collider as gpu enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_is_gpu_enabled(collider, v);
});

anfr("wi_set_collider_is_cpu_enabled", "collider,v", "I}:2B", "",
"Set collider as cpu enabled",
   [](StackPtr& sp, VM& vm) {
auto v = Pop(sp).True();
auto collider = pop_wo_handle(sp);
wbnd::set_collider_is_cpu_enabled(collider, v);
});

anfr("wi_create_collider_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a collider component for the given entity and returns a handle",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_collider_component(scene, entity));
});

anfr("wi_get_collider_component", "scene,entity", "I}:2I}:2", "I}:2",
"Gets the collider component for the given entity.",
   [](StackPtr& sp, VM& vm) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_collider_component(scene, entity));
});

anfr("wi_entity_collider_count", "scene", "I}:2", "I",
"Returns the number of entities that have a collider component",
   [](StackPtr& sp, VM& vm) {
auto scene = pop_wo_handle(sp);
Push(sp, Value(wbnd::entity_collider_count(scene)));
});

anfr("wi_entity_collider_get", "scene,n", "I}:2I", "I}:2",
"Returns the nth entity that has a collider component",
   [](StackPtr& sp, VM& vm) {
auto n = (int32_t)Pop(sp).ival();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::entity_collider_get(scene, n));
});

anfr("wi_create_matrix4x4", "", "", "I}:2",
"Creates a matrix",
   [](StackPtr& sp, VM& vm) {
push_wo_handle(sp, wbnd::create_matrix4x4());
});

anfr("wi_delete_matrix", "m", "I}:2", "",
"Deletes a matrix",
   [](StackPtr& sp, VM& vm) {
auto m = pop_wo_handle(sp);
wbnd::delete_matrix(m);
});

anfr("wi_identity_matrix", "m", "I}:2", "",
"Initializes the matrix as an identity matrix",
   [](StackPtr& sp, VM& vm) {
auto m = pop_wo_handle(sp);
wbnd::identity_matrix(m);
});

anfr("wi_assign_matrix", "lhs,rhs", "I}:2I}:2", "",
"Assigns matrix lhs the value from rhs",
   [](StackPtr& sp, VM& vm) {
auto rhs = pop_wo_handle(sp);
auto lhs = pop_wo_handle(sp);
wbnd::assign_matrix(lhs, rhs);
});

anfr("wi_assign_matrix_rows", "m,r1,r2,r3,r4", "I}:2F}:4F}:4F}:4F}:4", "",
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
auto m = pop_wo_handle(sp);
wbnd::assign_matrix_rows(m, r1, r2, r3, r4);
});

anfr("wi_return_matrix_row", "m,r", "I}:2I", "F}:4",
"Returns a row from a matrix",
   [](StackPtr& sp, VM& vm) {
auto r = (int32_t)Pop(sp).ival();
auto m = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::return_matrix_row(m, r));
});

anfr("wi_translation_matrix", "m,v", "I}:2F}:3", "",
"Set up as a translation matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto m = pop_wo_handle(sp);
wbnd::translation_matrix(m, v);
});

anfr("wi_rotation_euler_matrix", "m,angles", "I}:2F}:3", "",
"Set up as a rotation matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 angles;
pop_xmfloat3(sp,angles);
auto m = pop_wo_handle(sp);
wbnd::rotation_euler_matrix(m, angles);
});

anfr("wi_rotation_x_matrix", "m,a", "I}:2F", "",
"Set up as a rotation around x matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_wo_handle(sp);
wbnd::rotation_x_matrix(m, a);
});

anfr("wi_rotation_y_matrix", "m,a", "I}:2F", "",
"Set up as a rotation around y matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_wo_handle(sp);
wbnd::rotation_y_matrix(m, a);
});

anfr("wi_rotation_z_matrix", "m,a", "I}:2F", "",
"Set up as a rotation around z matrix",
   [](StackPtr& sp, VM& vm) {
auto a = Pop(sp).fltval();
auto m = pop_wo_handle(sp);
wbnd::rotation_z_matrix(m, a);
});

anfr("wi_rotation_quat_matrix", "m,quat", "I}:2F}:4", "",
"Set matrix as quaternion rotation",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 quat;
pop_xmfloat4(sp,quat);
auto m = pop_wo_handle(sp);
wbnd::rotation_quat_matrix(m, quat);
});

anfr("wi_scaling_matrix", "m,scale", "I}:2F}:4", "",
"Set up matrix as a scaling matrix",
   [](StackPtr& sp, VM& vm) {
XMFLOAT4 scale;
pop_xmfloat4(sp,scale);
auto m = pop_wo_handle(sp);
wbnd::scaling_matrix(m, scale);
});

anfr("wi_look_to_matrix", "m,eyepos,eyedir,up", "I}:2F}:3F}:3F}:3", "",
"Set up matrix to look to a pos",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 up;
pop_xmfloat3(sp,up);
XMFLOAT3 eyedir;
pop_xmfloat3(sp,eyedir);
XMFLOAT3 eyepos;
pop_xmfloat3(sp,eyepos);
auto m = pop_wo_handle(sp);
wbnd::look_to_matrix(m, eyepos, eyedir, up);
});

anfr("wi_look_at_matrix", "m,eyepos,focuspos,up", "I}:2F}:3F}:3F}:3", "",
"Set up matrix to look at a pos",
   [](StackPtr& sp, VM& vm) {
XMFLOAT3 up;
pop_xmfloat3(sp,up);
XMFLOAT3 focuspos;
pop_xmfloat3(sp,focuspos);
XMFLOAT3 eyepos;
pop_xmfloat3(sp,eyepos);
auto m = pop_wo_handle(sp);
wbnd::look_at_matrix(m, eyepos, focuspos, up);
});

anfr("wi_multiply_matrix", "lhs,rhs,result", "I}:2I}:2I}:2", "",
"Multiply lhs by rhs and put the reuslt into result",
   [](StackPtr& sp, VM& vm) {
auto result = pop_wo_handle(sp);
auto rhs = pop_wo_handle(sp);
auto lhs = pop_wo_handle(sp);
wbnd::multiply_matrix(lhs, rhs, result);
});

anfr("wi_add_matrix", "lhs,rhs,result", "I}:2I}:2I}:2", "",
"Add lhs and rhs, and put the result in result",
   [](StackPtr& sp, VM& vm) {
auto result = pop_wo_handle(sp);
auto rhs = pop_wo_handle(sp);
auto lhs = pop_wo_handle(sp);
wbnd::add_matrix(lhs, rhs, result);
});

anfr("wi_transpose_matrix", "m,result", "I}:2I}:2", "",
"Transpose a matrix",
   [](StackPtr& sp, VM& vm) {
auto result = pop_wo_handle(sp);
auto m = pop_wo_handle(sp);
wbnd::transpose_matrix(m, result);
});

anfr("wi_invert_matrix", "m,result", "I}:2I}:2", "",
"Inverts 'm' and puts the result in 'result'",
   [](StackPtr& sp, VM& vm) {
auto result = pop_wo_handle(sp);
auto m = pop_wo_handle(sp);
wbnd::invert_matrix(m, result);
});

