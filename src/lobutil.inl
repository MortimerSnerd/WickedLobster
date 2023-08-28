// GENERATED for inclusion into lobutils.cpp, do not edit.
anfr("wi_get_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
"Returns the transform component for 'entity' if it exists, or int2{?, 0} if there is none.",
   [](StackPtr& sp, VM&) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_transform_component(scene, entity));
});

anfr("wi_new_scene", "", "", "I}:2",
"Creates a new empty scene.",
   [](StackPtr& sp, VM&) {
push_wo_handle(sp, wbnd::new_scene());
});

anfr("wi_global_scene", "", "", "I}:2",
"Returns the global scene",
   [](StackPtr& sp, VM&) {
push_wo_handle(sp, wbnd::global_scene());
});

anfr("wi_load_model", "scene,fname,attach", "I}:2SB", "I}:2",
"Loads the model from the file into the given scene. Returns valid entity handle if attached==true",
   [](StackPtr& sp, VM&) {
auto attach = Pop(sp).True();
auto fname = Pop(sp).sval()->strv();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::load_model(scene, fname, attach));
});

anfr("wi_create_entity", "", "", "I}:2",
"Creates a new empty entity",
   [](StackPtr& sp, VM&) {
push_wo_handle(sp, wbnd::create_entity());
});

anfr("wi_create_name_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a name component for the given entity, and returns a the handle",
   [](StackPtr& sp, VM&) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_name_component(scene, entity));
});

anfr("wi_nc_set_name", "name_comp,name", "I}:2S", "",
"Sets the name for a name component.",
   [](StackPtr& sp, VM&) {
auto name = Pop(sp).sval()->strv();
auto name_comp = pop_wo_handle(sp);
wbnd::nc_set_name(name_comp, name);
});

anfr("wi_find_entity_by_name", "scene,name,ancestor_entity", "I}:2SI}:2", "I}:2",
"Searches scene for an entity by name. Returns INVALID_ENTITY if not found.",
   [](StackPtr& sp, VM&) {
auto ancestor_entity = pop_wo_handle(sp);
auto name = Pop(sp).sval()->strv();
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::find_entity_by_name(scene, name, ancestor_entity));
});

anfr("wi_backlog", "level,msg", "IS", "",
"Logs to Wicked Engine backlog with given log level",
   [](StackPtr& sp, VM&) {
auto msg = Pop(sp).sval()->strv();
auto level = Pop(sp).ival();
wbnd::backlog(level, msg);
});

anfr("wi_create_camera_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a camera component on an entity.",
   [](StackPtr& sp, VM&) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_camera_component(scene, entity));
});

anfr("wi_create_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
"Creates a transform component on an entity",
   [](StackPtr& sp, VM&) {
auto entity = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::create_transform_component(scene, entity));
});

anfr("wi_get_renderpath3d", "", "", "I}:2",
"Returns the games RenderPath3d",
   [](StackPtr& sp, VM&) {
push_wo_handle(sp, wbnd::get_renderpath3d());
});

anfr("wi_renderpath3d_set_camera", "rpath,cam_component", "I}:2I}:2", "",
"Sets the camera component used by the 3d renderpath",
   [](StackPtr& sp, VM&) {
auto cam_component = pop_wo_handle(sp);
auto rpath = pop_wo_handle(sp);
wbnd::renderpath3d_set_camera(rpath, cam_component);
});

anfr("wi_transform_translate", "trans_component,v", "I}:2F}:3", "",
"Tranlates transform by 'vec'",
   [](StackPtr& sp, VM&) {
XMFLOAT3 v;
pop_xmfloat3(sp,v);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_translate(trans_component, v);
});

anfr("wi_transform_rotate", "trans_component,quat", "I}:2F}:4", "",
"Rotates transform around given quaternion",
   [](StackPtr& sp, VM&) {
XMFLOAT4 quat;
pop_xmfloat4(sp,quat);
auto trans_component = pop_wo_handle(sp);
wbnd::transform_rotate(trans_component, quat);
});

anfr("wi_transform_position", "tcomp", "I}:2", "F}:3",
"Gets transform position",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat3(sp, wbnd::transform_position(tcomp));
});

anfr("wi_transform_rotation", "tcomp", "I}:2", "F}:4",
"Gets transform rotation",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat4(sp, wbnd::transform_rotation(tcomp));
});

anfr("wi_transform_update_transform", "tcomp", "I}:2", "",
"Applies local space to world space matrix for transform",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
wbnd::transform_update_transform(tcomp);
});

anfr("wi_transform_clear", "trans_comp", "I}:2", "",
"Clears the transform component's transform.",
   [](StackPtr& sp, VM&) {
auto trans_comp = pop_wo_handle(sp);
wbnd::transform_clear(trans_comp);
});

anfr("wi_transform_rotate_roll_pitch_yaw", "tcomp,angles", "I}:2F}:3", "",
"Apply euler rotation to transform",
   [](StackPtr& sp, VM&) {
XMFLOAT3 angles;
pop_xmfloat3(sp,angles);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_rotate_roll_pitch_yaw(tcomp, angles);
});

anfr("wi_transform_scale", "tcomp,scale", "I}:2F}:3", "",
"Apply scale to transform",
   [](StackPtr& sp, VM&) {
XMFLOAT3 scale;
pop_xmfloat3(sp,scale);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_scale(tcomp, scale);
});

anfr("wi_transform_lerp", "tcomp,a,b,t", "I}:2I}:2I}:2F", "",
"Set this transform to be the linear interpolation of transforms 'a' and 'b'",
   [](StackPtr& sp, VM&) {
auto t = Pop(sp).fltval();
auto b = pop_wo_handle(sp);
auto a = pop_wo_handle(sp);
auto tcomp = pop_wo_handle(sp);
wbnd::transform_lerp(tcomp, a, b, t);
});

anfr("wi_camera_fov", "tcomp", "I}:2", "F",
"Gets camera component fov",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_fov(tcomp)));
});

anfr("wi_camera_set_fov", "tcomp,fov", "I}:2F", "",
"Sets camera component fov, in radians.",
   [](StackPtr& sp, VM&) {
auto fov = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_fov(tcomp, fov);
});

anfr("wi_camera_get_dims", "tcomp", "I}:2", "F}:2",
"Gets camera plane dims",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
push_xmfloat2(sp, wbnd::camera_get_dims(tcomp));
});

anfr("wi_camera_set_dims", "tcomp,dims", "I}:2F}:2", "",
"Sets camera plane dims",
   [](StackPtr& sp, VM&) {
XMFLOAT2 dims;
pop_xmfloat2(sp,dims);
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_dims(tcomp, dims);
});

anfr("wi_camera_znear", "tcomp", "I}:2", "F",
"Gets the camera zNear",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_znear(tcomp)));
});

anfr("wi_camera_set_znear", "tcomp,znear", "I}:2F", "",
"Sets the camera zNear",
   [](StackPtr& sp, VM&) {
auto znear = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_znear(tcomp, znear);
});

anfr("wi_camera_zfar", "tcomp", "I}:2", "F",
"Gets the camera zFar",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_zfar(tcomp)));
});

anfr("wi_camera_set_zfar", "tcomp,zfar", "I}:2F", "",
"Sets the camera zFar",
   [](StackPtr& sp, VM&) {
auto zfar = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_zfar(tcomp, zfar);
});

anfr("wi_camera_focal_length", "tcomp", "I}:2", "F",
"Gets the camera focal length",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
Push(sp, Value(wbnd::camera_focal_length(tcomp)));
});

anfr("wi_camera_set_focal_length", "tcomp,l", "I}:2F", "",
"Sets the camera focal length",
   [](StackPtr& sp, VM&) {
auto l = Pop(sp).fltval();
auto tcomp = pop_wo_handle(sp);
wbnd::camera_set_focal_length(tcomp, l);
});

anfr("wi_camera_update", "tcomp", "I}:2", "",
"Updates the camera transforms",
   [](StackPtr& sp, VM&) {
auto tcomp = pop_wo_handle(sp);
wbnd::camera_update(tcomp);
});

anfr("wi_get_camera_component", "scene,ent", "I}:2I}:2", "I}:2",
"Gets the camera component of an entity",
   [](StackPtr& sp, VM&) {
auto ent = pop_wo_handle(sp);
auto scene = pop_wo_handle(sp);
push_wo_handle(sp, wbnd::get_camera_component(scene, ent));
});

