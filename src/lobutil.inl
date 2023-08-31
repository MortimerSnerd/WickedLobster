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

