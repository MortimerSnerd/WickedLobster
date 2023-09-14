// GENERATED for inclusion into lobutils.cpp, do not edit.
anfr("wi_get_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Returns the transform component for 'entity' if it exists, or int2{?, 0} if there is none.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_transform_component(scene, entity));
     });

anfr("wi_new_scene", "", "", "I}:2",
     "Creates a new empty scene.",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::new_scene());
     });

anfr("wi_delete_scene", "scene", "I}:2", "",
     "Deletes a scene.",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         wbnd::delete_scene(scene);
     });

anfr("wi_global_scene", "", "", "I}:2",
     "Returns the global scene",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::global_scene());
     });

anfr("wi_is_descendant_entity", "scene,entity,ancestor", "I}:2I}:2I}:2", "B",
     "Returns true if 'entity' is descendant of 'ancestor'",
     [](StackPtr &sp, VM &vm) {
         auto ancestor = pop_wo_handle(sp);
         auto entity   = pop_wo_handle(sp);
         auto scene    = pop_wo_handle(sp);
         Push(sp, Value(wbnd::is_descendant_entity(scene, entity, ancestor)));
     });

anfr("wi_retarget_animation", "scene,dest_entity,src_entity,bake_data", "I}:2I}:2I}:2B", "I}:2",
     "Retargets an animation from one humanoid to another and returns resulting entity",
     [](StackPtr &sp, VM &vm) {
         auto bake_data   = Pop(sp).True();
         auto src_entity  = pop_wo_handle(sp);
         auto dest_entity = pop_wo_handle(sp);
         auto scene       = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::retarget_animation(scene, dest_entity, src_entity, bake_data));
     });

anfr("wi_remove_entity", "scene,entity,recursive", "I}:2I}:2B", "",
     "Deletes an entity from the scene",
     [](StackPtr &sp, VM &vm) {
         auto recursive = Pop(sp).True();
         auto entity    = pop_wo_handle(sp);
         auto scene     = pop_wo_handle(sp);
         wbnd::remove_entity(scene, entity, recursive);
     });

anfr("wi_duplicate_entity", "scene,entity", "I}:2I}:2", "I}:2",
     "Duplicates an entity",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::duplicate_entity(scene, entity));
     });

anfr("wi_scene_merge", "dest,src", "I}:2I}:2", "",
     "Merges src scene into dest scene.",
     [](StackPtr &sp, VM &vm) {
         auto src  = pop_wo_handle(sp);
         auto dest = pop_wo_handle(sp);
         wbnd::scene_merge(dest, src);
     });

anfr("wi_load_model", "scene,fname,attach", "I}:2SB", "I}:2",
     "Loads the model from the file into the given scene. Returns valid entity handle if attached==true",
     [](StackPtr &sp, VM &vm) {
         auto attach = Pop(sp).True();
         auto fname  = Pop(sp).sval()->strv();
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::load_model(scene, fname, attach));
     });

anfr("wi_create_entity", "", "", "I}:2",
     "Creates a new empty entity",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_entity());
     });

anfr("wi_create_layer_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a layer component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_layer_component(scene, entity));
     });

anfr("wi_get_layer_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the layer component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_layer_component(scene, entity));
     });

anfr("wi_entity_layer_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a layer component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_layer_count(scene)));
     });

anfr("wi_entity_layer_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a layer component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_layer_get(scene, n));
     });

anfr("wi_create_humanoid_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a humanoid component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_humanoid_component(scene, entity));
     });

anfr("wi_get_humanoid_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the humanoid component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_humanoid_component(scene, entity));
     });

anfr("wi_entity_humanoid_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a humanoid component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_humanoid_count(scene)));
     });

anfr("wi_entity_humanoid_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a humanoid component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_humanoid_get(scene, n));
     });

anfr("wi_create_name_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a name component for the given entity, and returns a the handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_name_component(scene, entity));
     });

anfr("wi_nc_set_name", "name_comp,name", "I}:2S", "",
     "Sets the name for a name component.",
     [](StackPtr &sp, VM &vm) {
         auto name      = Pop(sp).sval()->strv();
         auto name_comp = pop_wo_handle(sp);
         wbnd::nc_set_name(name_comp, name);
     });

anfr("wi_nc_get_name", "name_comp", "I}:2", "S",
     "Gets the name of a name component",
     [](StackPtr &sp, VM &vm) {
         auto name_comp = pop_wo_handle(sp);
         Push(sp, Value(vm.NewString(wbnd::nc_get_name(name_comp))));
     });

anfr("wi_get_name_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the name component for the given entity",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_name_component(scene, entity));
     });

anfr("wi_entity_names_count", "scene", "I}:2", "I",
     "Returns number of entities that have name components.",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_names_count(scene)));
     });

anfr("wi_entity_names_get", "scene,n", "I}:2I", "I}:2",
     "Returns entity #n that has a name component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_names_get(scene, n));
     });

anfr("wi_find_entity_by_name", "scene,name,ancestor_entity", "I}:2SI}:2", "I}:2",
     "Searches scene for an entity by name. Returns INVALID_ENTITY if not found.",
     [](StackPtr &sp, VM &vm) {
         auto ancestor_entity = pop_wo_handle(sp);
         auto name            = Pop(sp).sval()->strv();
         auto scene           = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::find_entity_by_name(scene, name, ancestor_entity));
     });

anfr("wi_backlog", "level,msg", "IS", "",
     "Logs to Wicked Engine backlog with given log level",
     [](StackPtr &sp, VM &vm) {
         auto msg   = Pop(sp).sval()->strv();
         auto level = (int32_t)Pop(sp).ival();
         wbnd::backlog(level, msg);
     });

anfr("wi_is_backlog_active", "", "", "B",
     "Returns true if the backlog is active",
     [](StackPtr &sp, VM &vm) {
         Push(sp, Value(wbnd::is_backlog_active()));
     });

anfr("wi_create_camera_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a camera component on an entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_camera_component(scene, entity));
     });

anfr("wi_set_transform_scale_local", "transform,v", "I}:2F}:3", "",
     "Sets transform.scale_local",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto transform = pop_wo_handle(sp);
         wbnd::set_transform_scale_local(transform, v);
     });

anfr("wi_get_transform_scale_local", "transform", "I}:2", "F}:3",
     "Gets transform.scale_local",
     [](StackPtr &sp, VM &vm) {
         auto transform = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_transform_scale_local(transform));
     });

anfr("wi_set_transform_rotation_local", "transform,v", "I}:2F}:4", "",
     "Sets transform.rotation_local",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto transform = pop_wo_handle(sp);
         wbnd::set_transform_rotation_local(transform, v);
     });

anfr("wi_get_transform_rotation_local", "transform", "I}:2", "F}:4",
     "Gets transform.rotation_local",
     [](StackPtr &sp, VM &vm) {
         auto transform = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_transform_rotation_local(transform));
     });

anfr("wi_set_transform_translation_local", "transform,v", "I}:2F}:3", "",
     "Sets transform.translation_local",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto transform = pop_wo_handle(sp);
         wbnd::set_transform_translation_local(transform, v);
     });

anfr("wi_get_transform_translation_local", "transform", "I}:2", "F}:3",
     "Gets transform.translation_local",
     [](StackPtr &sp, VM &vm) {
         auto transform = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_transform_translation_local(transform));
     });

anfr("wi_set_transform_dirty", "transform,v", "I}:2B", "",
     "Sets transform.dirty",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).True();
         auto transform = pop_wo_handle(sp);
         wbnd::set_transform_dirty(transform, v);
     });

anfr("wi_get_transform_dirty", "transform", "I}:2", "B",
     "Gets transform.dirty",
     [](StackPtr &sp, VM &vm) {
         auto transform = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_transform_dirty(transform)));
     });

anfr("wi_create_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a transform component on an entity",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_transform_component(scene, entity));
     });

anfr("wi_create_transform", "", "", "I}:2",
     "Creates a transform component attached to no scene or entity.  Seems to be used primarly for calculations from scripts",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_transform());
     });

anfr("wi_delete_transform", "trans", "I}:2", "",
     "Deletes a transform created by create_transform()",
     [](StackPtr &sp, VM &vm) {
         auto trans = pop_wo_handle(sp);
         wbnd::delete_transform(trans);
     });

anfr("wi_get_fixed_update_rate", "", "", "F",
     "Returns the application fixed frame update rate",
     [](StackPtr &sp, VM &vm) {
         Push(sp, Value(wbnd::get_fixed_update_rate()));
     });

anfr("wi_renderpath3d_set_camera", "rpath,cam_component", "I}:2I}:2", "",
     "Sets the camera component used by the 3d renderpath",
     [](StackPtr &sp, VM &vm) {
         auto cam_component = pop_wo_handle(sp);
         auto rpath         = pop_wo_handle(sp);
         wbnd::renderpath3d_set_camera(rpath, cam_component);
     });

anfr("wi_transform_translate", "trans_component,v", "I}:2F}:3", "",
     "Tranlates transform by 'vec'",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto trans_component = pop_wo_handle(sp);
         wbnd::transform_translate(trans_component, v);
     });

anfr("wi_transform_rotate", "trans_component,quat", "I}:2F}:4", "",
     "Rotates transform around given quaternion",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 quat;
         pop_xmfloat4(sp, quat);
         auto trans_component = pop_wo_handle(sp);
         wbnd::transform_rotate(trans_component, quat);
     });

anfr("wi_transform_position", "tcomp", "I}:2", "F}:3",
     "Gets transform position",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::transform_position(tcomp));
     });

anfr("wi_transform_rotation", "tcomp", "I}:2", "F}:4",
     "Gets transform rotation",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::transform_rotation(tcomp));
     });

anfr("wi_transform_scaling", "tcomp", "I}:2", "F}:3",
     "Gets the transform's scaling",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::transform_scaling(tcomp));
     });

anfr("wi_decompose_transform", "tcomp", "I}:2", "F}:3F}:4F}:3",
     "Decomposes transform pieces into position, rotation, scale",
     [](StackPtr &sp, VM &vm) {
         auto     tcomp   = pop_wo_handle(sp);
         XMFLOAT4 retval2;
         XMFLOAT3 retval3;
         push_xmfloat3(sp, wbnd::decompose_transform(tcomp, retval2, retval3));
         push_xmfloat4(sp, retval2);
         push_xmfloat3(sp, retval3);
     });

anfr("wi_transform_update_transform", "tcomp", "I}:2", "",
     "Applies local space to world space matrix for transform",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         wbnd::transform_update_transform(tcomp);
     });

anfr("wi_transform_clear", "trans_comp", "I}:2", "",
     "Clears the transform component's transform.",
     [](StackPtr &sp, VM &vm) {
         auto trans_comp = pop_wo_handle(sp);
         wbnd::transform_clear(trans_comp);
     });

anfr("wi_transform_rotate_roll_pitch_yaw", "tcomp,angles", "I}:2F}:3", "",
     "Apply euler rotation to transform",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 angles;
         pop_xmfloat3(sp, angles);
         auto tcomp = pop_wo_handle(sp);
         wbnd::transform_rotate_roll_pitch_yaw(tcomp, angles);
     });

anfr("wi_transform_scale", "tcomp,scale", "I}:2F}:3", "",
     "Apply scale to transform",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 scale;
         pop_xmfloat3(sp, scale);
         auto tcomp = pop_wo_handle(sp);
         wbnd::transform_scale(tcomp, scale);
     });

anfr("wi_transform_lerp", "tcomp,a,b,t", "I}:2I}:2I}:2F", "",
     "Set this transform to be the linear interpolation of transforms 'a' and 'b'",
     [](StackPtr &sp, VM &vm) {
         auto t     = Pop(sp).fltval();
         auto b     = pop_wo_handle(sp);
         auto a     = pop_wo_handle(sp);
         auto tcomp = pop_wo_handle(sp);
         wbnd::transform_lerp(tcomp, a, b, t);
     });

anfr("wi_get_transform_local_matrix", "tcomp", "I}:2", "I}:2",
     "gets the local matrix for the transform",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_transform_local_matrix(tcomp));
     });

anfr("wi_get_transform_world_matrix", "tcomp", "I}:2", "I}:2",
     "gets the world matrix for the transform",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_transform_world_matrix(tcomp));
     });

anfr("wi_transform_transform_matrix", "tcomp,matrix", "I}:2I}:2", "",
     "Trasforms the transform by the given matrix",
     [](StackPtr &sp, VM &vm) {
         auto matrix = pop_wo_handle(sp);
         auto tcomp  = pop_wo_handle(sp);
         wbnd::transform_transform_matrix(tcomp, matrix);
     });

anfr("wi_camera_fov", "tcomp", "I}:2", "F",
     "Gets camera component fov",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         Push(sp, Value(wbnd::camera_fov(tcomp)));
     });

anfr("wi_camera_set_fov", "tcomp,fov", "I}:2F", "",
     "Sets camera component fov, in radians.",
     [](StackPtr &sp, VM &vm) {
         auto fov   = Pop(sp).fltval();
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_set_fov(tcomp, fov);
     });

anfr("wi_camera_get_dims", "tcomp", "I}:2", "F}:2",
     "Gets camera plane dims",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_xmfloat2(sp, wbnd::camera_get_dims(tcomp));
     });

anfr("wi_camera_set_dims", "tcomp,dims", "I}:2F}:2", "",
     "Sets camera plane dims",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT2 dims;
         pop_xmfloat2(sp, dims);
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_set_dims(tcomp, dims);
     });

anfr("wi_camera_znear", "tcomp", "I}:2", "F",
     "Gets the camera zNear",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         Push(sp, Value(wbnd::camera_znear(tcomp)));
     });

anfr("wi_camera_set_znear", "tcomp,znear", "I}:2F", "",
     "Sets the camera zNear",
     [](StackPtr &sp, VM &vm) {
         auto znear = Pop(sp).fltval();
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_set_znear(tcomp, znear);
     });

anfr("wi_camera_zfar", "tcomp", "I}:2", "F",
     "Gets the camera zFar",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         Push(sp, Value(wbnd::camera_zfar(tcomp)));
     });

anfr("wi_camera_set_zfar", "tcomp,zfar", "I}:2F", "",
     "Sets the camera zFar",
     [](StackPtr &sp, VM &vm) {
         auto zfar  = Pop(sp).fltval();
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_set_zfar(tcomp, zfar);
     });

anfr("wi_camera_focal_length", "tcomp", "I}:2", "F",
     "Gets the camera focal length",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         Push(sp, Value(wbnd::camera_focal_length(tcomp)));
     });

anfr("wi_camera_set_focal_length", "tcomp,l", "I}:2F", "",
     "Sets the camera focal length",
     [](StackPtr &sp, VM &vm) {
         auto l     = Pop(sp).fltval();
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_set_focal_length(tcomp, l);
     });

anfr("wi_camera_update", "tcomp", "I}:2", "",
     "Updates the camera transforms",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         wbnd::camera_update(tcomp);
     });

anfr("wi_transform_camera", "camera,tcomp", "I}:2I}:2", "",
     "Sets the camera transform from another transform component",
     [](StackPtr &sp, VM &vm) {
         auto tcomp  = pop_wo_handle(sp);
         auto camera = pop_wo_handle(sp);
         wbnd::transform_camera(camera, tcomp);
     });

anfr("wi_transform_camera_set_matrix", "camera,matrix", "I}:2I}:2", "",
     "Sets the camera's transform from the matris",
     [](StackPtr &sp, VM &vm) {
         auto matrix = pop_wo_handle(sp);
         auto camera = pop_wo_handle(sp);
         wbnd::transform_camera_set_matrix(camera, matrix);
     });

anfr("wi_get_camera_component", "scene,ent", "I}:2I}:2", "I}:2",
     "Gets the camera component of an entity",
     [](StackPtr &sp, VM &vm) {
         auto ent   = pop_wo_handle(sp);
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_component(scene, ent));
     });

anfr("wi_get_camera_count", "scene", "I}:2", "I",
     "Returns the number of cameras in the scene",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_camera_count(scene)));
     });

anfr("wi_get_camera_entity", "scene,n", "I}:2I", "I}:2",
     "returns entity holding the nth camera in the scene",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_entity(scene, n));
     });

anfr("wi_set_camera_eye", "camera,v", "I}:2F}:3", "",
     "Sets camera.eye",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto camera = pop_wo_handle(sp);
         wbnd::set_camera_eye(camera, v);
     });

anfr("wi_get_camera_eye", "camera", "I}:2", "F}:3",
     "Gets camera.eye",
     [](StackPtr &sp, VM &vm) {
         auto camera = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_camera_eye(camera));
     });

anfr("wi_set_camera_at", "camera,v", "I}:2F}:3", "",
     "Sets camera.at",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto camera = pop_wo_handle(sp);
         wbnd::set_camera_at(camera, v);
     });

anfr("wi_get_camera_at", "camera", "I}:2", "F}:3",
     "Gets camera.at",
     [](StackPtr &sp, VM &vm) {
         auto camera = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_camera_at(camera));
     });

anfr("wi_set_camera_up", "camera,v", "I}:2F}:3", "",
     "Sets camera.up",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto camera = pop_wo_handle(sp);
         wbnd::set_camera_up(camera, v);
     });

anfr("wi_get_camera_up", "camera", "I}:2", "F}:3",
     "Gets camera.up",
     [](StackPtr &sp, VM &vm) {
         auto camera = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_camera_up(camera));
     });

anfr("wi_get_camera_projection", "tcomp", "I}:2", "I}:2",
     "Gets the camera projection matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_projection(tcomp));
     });

anfr("wi_get_camera_view", "tcomp", "I}:2", "I}:2",
     "Gets the camera view matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_view(tcomp));
     });

anfr("wi_get_camera_VP", "tcomp", "I}:2", "I}:2",
     "Gets the camera VP matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_VP(tcomp));
     });

anfr("wi_get_camera_inverse_projection", "tcomp", "I}:2", "I}:2",
     "Gets the camera inverse projection matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_inverse_projection(tcomp));
     });

anfr("wi_get_camera_inverse_view", "tcomp", "I}:2", "I}:2",
     "Gets the camera inverse view matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_inverse_view(tcomp));
     });

anfr("wi_get_camera_inverse_VP", "tcomp", "I}:2", "I}:2",
     "Gets the camera inverse VP matrix.  Matrix valid as long as camera component exists.",
     [](StackPtr &sp, VM &vm) {
         auto tcomp = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_camera_inverse_VP(tcomp));
     });

anfr("wi_input_down", "button,playerindex", "II", "B",
     "Check if a button is down",
     [](StackPtr &sp, VM &vm) {
         auto playerindex = (int32_t)Pop(sp).ival();
         auto button      = (int32_t)Pop(sp).ival();
         Push(sp, Value(wbnd::input_down(button, playerindex)));
     });

anfr("wi_input_press", "button,playerindex", "II", "B",
     "Check if a button is pressed once",
     [](StackPtr &sp, VM &vm) {
         auto playerindex = (int32_t)Pop(sp).ival();
         auto button      = (int32_t)Pop(sp).ival();
         Push(sp, Value(wbnd::input_press(button, playerindex)));
     });

anfr("wi_input_hold", "button,frames,continuous,playerindex", "IIBI", "B",
     "Check if a button is held down",
     [](StackPtr &sp, VM &vm) {
         auto playerindex = (int32_t)Pop(sp).ival();
         auto continuous  = Pop(sp).True();
         auto frames      = (int32_t)Pop(sp).ival();
         auto button      = (int32_t)Pop(sp).ival();
         Push(sp, Value(wbnd::input_hold(button, frames, continuous, playerindex)));
     });

anfr("wi_input_get_pointer", "", "", "F}:4",
     "get pointer position (eg. mouse pointer) (.xy) + scroll delta (.z) + pressure (.w)",
     [](StackPtr &sp, VM &vm) {
         push_xmfloat4(sp, wbnd::input_get_pointer());
     });

anfr("wi_input_set_pointer", "props", "F}:4", "",
     "sets pointer position",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 props;
         pop_xmfloat4(sp, props);
         wbnd::input_set_pointer(props);
     });

anfr("wi_input_hide_pointer", "value", "B", "",
     "Hides/shows pointer",
     [](StackPtr &sp, VM &vm) {
         auto value = Pop(sp).True();
         wbnd::input_hide_pointer(value);
     });

anfr("wi_input_get_analog", "axis,playerindex", "II", "F}:4",
     "Reads input from analog controller axis",
     [](StackPtr &sp, VM &vm) {
         auto playerindex = (int32_t)Pop(sp).ival();
         auto axis        = (int32_t)Pop(sp).ival();
         push_xmfloat4(sp, wbnd::input_get_analog(axis, playerindex));
     });

anfr("wi_draw_debug_text", "text,pos,flags,color,scaling", "SF}:3IF}:4F", "",
     "Renders debug text in the next frame",
     [](StackPtr &sp, VM &vm) {
         auto     scaling = Pop(sp).fltval();
         XMFLOAT4 color;
         pop_xmfloat4(sp, color);
         auto     flags = (int32_t)Pop(sp).ival();
         XMFLOAT3 pos;
         pop_xmfloat3(sp, pos);
         auto text = Pop(sp).sval()->strv();
         wbnd::draw_debug_text(text, pos, flags, color, scaling);
     });

anfr("wi_create_timer", "", "", "I}:2",
     "Creates a wi::Timer",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_timer());
     });

anfr("wi_delete_timer", "timer", "I}:2", "",
     "Deletes a timer created with create_timer",
     [](StackPtr &sp, VM &vm) {
         auto timer = pop_wo_handle(sp);
         wbnd::delete_timer(timer);
     });

anfr("wi_timer_record", "timer", "I}:2", "",
     "Records a reference timestamp",
     [](StackPtr &sp, VM &vm) {
         auto timer = pop_wo_handle(sp);
         wbnd::timer_record(timer);
     });

anfr("wi_timer_elapsed_seconds", "time", "I}:2", "F",
     "Elapsed time since creation or last record call.",
     [](StackPtr &sp, VM &vm) {
         auto time = pop_wo_handle(sp);
         Push(sp, Value(wbnd::timer_elapsed_seconds(time)));
     });

anfr("wi_timer_elapsed", "timer", "I}:2", "F",
     "Elapsed time in milliseconds since creation or later record() call",
     [](StackPtr &sp, VM &vm) {
         auto timer = pop_wo_handle(sp);
         Push(sp, Value(wbnd::timer_elapsed(timer)));
     });

anfr("wi_create_font_params", "", "", "I}:2",
     "",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_font_params());
     });

anfr("wi_delete_font_params", "font_params", "I}:2", "",
     "",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         wbnd::delete_font_params(font_params);
     });

anfr("wi_set_font_params_position", "font_params,v", "I}:2F}:3", "",
     "Sets font_params.position",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_position(font_params, v);
     });

anfr("wi_get_font_params_position", "font_params", "I}:2", "F}:3",
     "Gets font_params.position",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_font_params_position(font_params));
     });

anfr("wi_set_font_params_size", "font_params,v", "I}:2I", "",
     "Sets font_params.size",
     [](StackPtr &sp, VM &vm) {
         auto v           = (int32_t)Pop(sp).ival();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_size(font_params, v);
     });

anfr("wi_get_font_params_size", "font_params", "I}:2", "I",
     "Gets font_params.size",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_size(font_params)));
     });

anfr("wi_set_font_params_scaling", "font_params,v", "I}:2F", "",
     "Sets font_params.scaling",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_scaling(font_params, v);
     });

anfr("wi_get_font_params_scaling", "font_params", "I}:2", "F",
     "Gets font_params.scaling",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_scaling(font_params)));
     });

anfr("wi_set_font_params_rotation", "font_params,v", "I}:2F", "",
     "Sets font_params.rotation",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_rotation(font_params, v);
     });

anfr("wi_get_font_params_rotation", "font_params", "I}:2", "F",
     "Gets font_params.rotation",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_rotation(font_params)));
     });

anfr("wi_set_font_params_spacing_x", "font_params,v", "I}:2F", "",
     "Sets font_params.spacing_x",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_spacing_x(font_params, v);
     });

anfr("wi_get_font_params_spacing_x", "font_params", "I}:2", "F",
     "Gets font_params.spacing_x",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_spacing_x(font_params)));
     });

anfr("wi_set_font_params_spacing_y", "font_params,v", "I}:2F", "",
     "Sets font_params.spacing_y",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_spacing_y(font_params, v);
     });

anfr("wi_get_font_params_spacing_y", "font_params", "I}:2", "F",
     "Gets font_params.spacing_y",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_spacing_y(font_params)));
     });

anfr("wi_set_font_params_h_align", "font_params,v", "I}:2I", "",
     "Sets font_params.h_align",
     [](StackPtr &sp, VM &vm) {
         auto v           = (int32_t)Pop(sp).ival();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_h_align(font_params, v);
     });

anfr("wi_get_font_params_h_align", "font_params", "I}:2", "I",
     "Gets font_params.h_align",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_h_align(font_params)));
     });

anfr("wi_set_font_params_v_align", "font_params,v", "I}:2I", "",
     "Sets font_params.v_align",
     [](StackPtr &sp, VM &vm) {
         auto v           = (int32_t)Pop(sp).ival();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_v_align(font_params, v);
     });

anfr("wi_get_font_params_v_align", "font_params", "I}:2", "I",
     "Gets font_params.v_align",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_v_align(font_params)));
     });

anfr("wi_set_font_params_color", "font_params,v", "I}:2F}:4", "",
     "Sets font_params.color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_color(font_params, v);
     });

anfr("wi_get_font_params_color", "font_params", "I}:2", "F}:4",
     "Gets font_params.color",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_font_params_color(font_params));
     });

anfr("wi_set_font_params_shadow_color", "font_params,v", "I}:2F}:4", "",
     "Sets font_params.shadow_color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_shadow_color(font_params, v);
     });

anfr("wi_get_font_params_shadow_color", "font_params", "I}:2", "F}:4",
     "Gets font_params.shadow_color",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_font_params_shadow_color(font_params));
     });

anfr("wi_set_font_params_h_wrap", "font_params,v", "I}:2F", "",
     "Sets font_params.h_wrap",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_h_wrap(font_params, v);
     });

anfr("wi_get_font_params_h_wrap", "font_params", "I}:2", "F",
     "Gets font_params.h_wrap",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_h_wrap(font_params)));
     });

anfr("wi_set_font_params_style", "font_params,v", "I}:2I", "",
     "Sets font_params.style",
     [](StackPtr &sp, VM &vm) {
         auto v           = (int32_t)Pop(sp).ival();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_style(font_params, v);
     });

anfr("wi_get_font_params_style", "font_params", "I}:2", "I",
     "Gets font_params.style",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_style(font_params)));
     });

anfr("wi_set_font_params_softness", "font_params,v", "I}:2F", "",
     "Sets font_params.softness",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_softness(font_params, v);
     });

anfr("wi_get_font_params_softness", "font_params", "I}:2", "F",
     "Gets font_params.softness",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_softness(font_params)));
     });

anfr("wi_set_font_params_bolden", "font_params,v", "I}:2F", "",
     "Sets font_params.bolden",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_bolden(font_params, v);
     });

anfr("wi_get_font_params_bolden", "font_params", "I}:2", "F",
     "Gets font_params.bolden",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_bolden(font_params)));
     });

anfr("wi_set_font_params_shadow_softness", "font_params,v", "I}:2F", "",
     "Sets font_params.shadow_softness",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_shadow_softness(font_params, v);
     });

anfr("wi_get_font_params_shadow_softness", "font_params", "I}:2", "F",
     "Gets font_params.shadow_softness",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_shadow_softness(font_params)));
     });

anfr("wi_set_font_params_shadow_bolden", "font_params,v", "I}:2F", "",
     "Sets font_params.shadow_bolden",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_shadow_bolden(font_params, v);
     });

anfr("wi_get_font_params_shadow_bolden", "font_params", "I}:2", "F",
     "Gets font_params.shadow_bolden",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_shadow_bolden(font_params)));
     });

anfr("wi_set_font_params_shadow_offset_x", "font_params,v", "I}:2F", "",
     "Sets font_params.shadow_offset_x",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_shadow_offset_x(font_params, v);
     });

anfr("wi_get_font_params_shadow_offset_x", "font_params", "I}:2", "F",
     "Gets font_params.shadow_offset_x",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_shadow_offset_x(font_params)));
     });

anfr("wi_set_font_params_shadow_offset_y", "font_params,v", "I}:2F", "",
     "Sets font_params.shadow_offset_y",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_shadow_offset_y(font_params, v);
     });

anfr("wi_get_font_params_shadow_offset_y", "font_params", "I}:2", "F",
     "Gets font_params.shadow_offset_y",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_shadow_offset_y(font_params)));
     });

anfr("wi_set_font_params_cursor", "font_params,v", "I}:2F}:4", "",
     "Sets font_params.cursor",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_cursor(font_params, v);
     });

anfr("wi_get_font_params_cursor", "font_params", "I}:2", "F}:4",
     "Gets font_params.cursor",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_font_params_cursor(font_params));
     });

anfr("wi_set_font_params_hdr_scaling", "font_params,v", "I}:2F", "",
     "Sets font_params.hdr_scaling",
     [](StackPtr &sp, VM &vm) {
         auto v           = Pop(sp).fltval();
         auto font_params = pop_wo_handle(sp);
         wbnd::set_font_params_hdr_scaling(font_params, v);
     });

anfr("wi_get_font_params_hdr_scaling", "font_params", "I}:2", "F",
     "Gets font_params.hdr_scaling",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_font_params_hdr_scaling(font_params)));
     });

anfr("wi_create_sprite_font", "", "", "I}:2",
     "Creates a SpriteFont",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_sprite_font());
     });

anfr("wi_sprite_font_set_params", "font,font_params", "I}:2I}:2", "",
     "Sets the font_params for a sprite font",
     [](StackPtr &sp, VM &vm) {
         auto font_params = pop_wo_handle(sp);
         auto font        = pop_wo_handle(sp);
         wbnd::sprite_font_set_params(font, font_params);
     });

anfr("wi_delete_sprite_font", "font", "I}:2", "",
     "Deletes a SpriteFont",
     [](StackPtr &sp, VM &vm) {
         auto font = pop_wo_handle(sp);
         wbnd::delete_sprite_font(font);
     });

anfr("wi_sprite_font_set_hidden", "font,value", "I}:2B", "",
     "Changes fonts hidden state",
     [](StackPtr &sp, VM &vm) {
         auto value = Pop(sp).True();
         auto font  = pop_wo_handle(sp);
         wbnd::sprite_font_set_hidden(font, value);
     });

anfr("wi_sprite_font_text_size", "font", "I}:2", "F}:2",
     "Returns dimensions of the text",
     [](StackPtr &sp, VM &vm) {
         auto font = pop_wo_handle(sp);
         push_xmfloat2(sp, wbnd::sprite_font_text_size(font));
     });

anfr("wi_sprite_font_set_text", "font,txt", "I}:2S", "",
     "Sets the text TODO is non-wstring version of this utf8 friendly?",
     [](StackPtr &sp, VM &vm) {
         auto txt  = Pop(sp).sval()->strv();
         auto font = pop_wo_handle(sp);
         wbnd::sprite_font_set_text(font, txt);
     });

anfr("wi_sprite_font_get_text", "font", "I}:2", "S",
     "Gets the text",
     [](StackPtr &sp, VM &vm) {
         auto font = pop_wo_handle(sp);
         Push(sp, Value(vm.NewString(wbnd::sprite_font_get_text(font))));
     });

anfr("wi_set_humanoid_default_look_direction", "humanoid,v", "I}:2F}:3", "",
     "Sets humanoid.default_look_direction",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_default_look_direction(humanoid, v);
     });

anfr("wi_get_humanoid_default_look_direction", "humanoid", "I}:2", "F}:3",
     "Gets humanoid.default_look_direction",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_humanoid_default_look_direction(humanoid));
     });

anfr("wi_set_humanoid_head_rotation_max", "humanoid,v", "I}:2F}:2", "",
     "Sets humanoid.head_rotation_max",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT2 v;
         pop_xmfloat2(sp, v);
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_head_rotation_max(humanoid, v);
     });

anfr("wi_get_humanoid_head_rotation_max", "humanoid", "I}:2", "F}:2",
     "Gets humanoid.head_rotation_max",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         push_xmfloat2(sp, wbnd::get_humanoid_head_rotation_max(humanoid));
     });

anfr("wi_set_humanoid_head_rotation_speed", "humanoid,v", "I}:2F", "",
     "Sets humanoid.head_rotation_speed",
     [](StackPtr &sp, VM &vm) {
         auto v        = Pop(sp).fltval();
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_head_rotation_speed(humanoid, v);
     });

anfr("wi_get_humanoid_head_rotation_speed", "humanoid", "I}:2", "F",
     "Gets humanoid.head_rotation_speed",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_humanoid_head_rotation_speed(humanoid)));
     });

anfr("wi_set_humanoid_eye_rotation_max", "humanoid,v", "I}:2F}:2", "",
     "Sets humanoid.eye_rotation_max",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT2 v;
         pop_xmfloat2(sp, v);
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_eye_rotation_max(humanoid, v);
     });

anfr("wi_get_humanoid_eye_rotation_max", "humanoid", "I}:2", "F}:2",
     "Gets humanoid.eye_rotation_max",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         push_xmfloat2(sp, wbnd::get_humanoid_eye_rotation_max(humanoid));
     });

anfr("wi_set_humanoid_eye_rotation_speed", "humanoid,v", "I}:2F", "",
     "Sets humanoid.eye_rotation_speed",
     [](StackPtr &sp, VM &vm) {
         auto v        = Pop(sp).fltval();
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_eye_rotation_speed(humanoid, v);
     });

anfr("wi_get_humanoid_eye_rotation_speed", "humanoid", "I}:2", "F",
     "Gets humanoid.eye_rotation_speed",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_humanoid_eye_rotation_speed(humanoid)));
     });

anfr("wi_set_humanoid_look_at", "humanoid,v", "I}:2F}:3", "",
     "Sets humanoid.look_at",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto humanoid = pop_wo_handle(sp);
         wbnd::set_humanoid_look_at(humanoid, v);
     });

anfr("wi_get_humanoid_look_at", "humanoid", "I}:2", "F}:3",
     "Gets humanoid.look_at",
     [](StackPtr &sp, VM &vm) {
         auto humanoid = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_humanoid_look_at(humanoid));
     });

anfr("wi_humanoid_bone_count", "hum", "I}:2", "I",
     "Returns number of bones in humanoid component",
     [](StackPtr &sp, VM &vm) {
         auto hum = pop_wo_handle(sp);
         Push(sp, Value(wbnd::humanoid_bone_count(hum)));
     });

anfr("wi_humanoid_bone", "hum,i", "I}:2I", "I}:2",
     "Returns entity for bone with the given HumanoidBone name",
     [](StackPtr &sp, VM &vm) {
         auto i   = (int32_t)Pop(sp).ival();
         auto hum = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::humanoid_bone(hum, i));
     });

anfr("wi_humanoid_is_lookat_enabled", "hum", "I}:2", "B",
     "Is lookat enabled?",
     [](StackPtr &sp, VM &vm) {
         auto hum = pop_wo_handle(sp);
         Push(sp, Value(wbnd::humanoid_is_lookat_enabled(hum)));
     });

anfr("wi_humanoid_set_lookat_enabled", "hum,v", "I}:2B", "",
     "Sets lookat for humanoid component",
     [](StackPtr &sp, VM &vm) {
         auto v   = Pop(sp).True();
         auto hum = pop_wo_handle(sp);
         wbnd::humanoid_set_lookat_enabled(hum, v);
     });

anfr("wi_set_layer_mask", "layer,v", "I}:2I", "",
     "Sets layer.mask",
     [](StackPtr &sp, VM &vm) {
         auto v     = (int32_t)Pop(sp).ival();
         auto layer = pop_wo_handle(sp);
         wbnd::set_layer_mask(layer, v);
     });

anfr("wi_get_layer_mask", "layer", "I}:2", "I",
     "Gets layer.mask",
     [](StackPtr &sp, VM &vm) {
         auto layer = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_layer_mask(layer)));
     });

anfr("wi_set_layer_propagation_mask", "layer,v", "I}:2I", "",
     "Sets layer.propagation_mask",
     [](StackPtr &sp, VM &vm) {
         auto v     = (int32_t)Pop(sp).ival();
         auto layer = pop_wo_handle(sp);
         wbnd::set_layer_propagation_mask(layer, v);
     });

anfr("wi_get_layer_propagation_mask", "layer", "I}:2", "I",
     "Gets layer.propagation_mask",
     [](StackPtr &sp, VM &vm) {
         auto layer = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_layer_propagation_mask(layer)));
     });

anfr("wi_get_renderpath3d", "", "", "I}:2",
     "Returns the games RenderPath3d",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::get_renderpath3d());
     });

anfr("wi_renderpath_add_font", "path,sprite_font,layer", "I}:2I}:2S", "",
     "Adds a sprite font to the renderpath",
     [](StackPtr &sp, VM &vm) {
         auto layer       = Pop(sp).sval()->strv();
         auto sprite_font = pop_wo_handle(sp);
         auto path        = pop_wo_handle(sp);
         wbnd::renderpath_add_font(path, sprite_font, layer);
     });

anfr("wi_renderpath_remove_font", "path,sprite_font", "I}:2I}:2", "",
     "Removes a sprite font from the renderpath",
     [](StackPtr &sp, VM &vm) {
         auto sprite_font = pop_wo_handle(sp);
         auto path        = pop_wo_handle(sp);
         wbnd::renderpath_remove_font(path, sprite_font);
     });

anfr("wi_renderpath_clear_fonts", "path", "I}:2", "",
     "Clears all fonts from renderpath",
     [](StackPtr &sp, VM &vm) {
         auto path = pop_wo_handle(sp);
         wbnd::renderpath_clear_fonts(path);
     });

anfr("wi_renderpath_font_order", "path,sprite_font", "I}:2I}:2", "I",
     "Returns the order for the given font",
     [](StackPtr &sp, VM &vm) {
         auto sprite_font = pop_wo_handle(sp);
         auto path        = pop_wo_handle(sp);
         Push(sp, Value(wbnd::renderpath_font_order(path, sprite_font)));
     });

anfr("wi_renderpath_set_font_order", "path,sprite_font,order", "I}:2I}:2I", "",
     "Sets the order for the given font",
     [](StackPtr &sp, VM &vm) {
         auto order       = (int32_t)Pop(sp).ival();
         auto sprite_font = pop_wo_handle(sp);
         auto path        = pop_wo_handle(sp);
         wbnd::renderpath_set_font_order(path, sprite_font, order);
     });

anfr("wi_get_renderpath_physical_dims", "path", "I}:2", "I}:2",
     "Returns the physical pixel dimensions of the renderpath",
     [](StackPtr &sp, VM &vm) {
         auto path = pop_wo_handle(sp);
         push_xmint2(sp, wbnd::get_renderpath_physical_dims(path));
     });

anfr("wi_get_renderpath_logical_dims", "path", "I}:2", "F}:2",
     "Returns the logical dims of the renderpath",
     [](StackPtr &sp, VM &vm) {
         auto path = pop_wo_handle(sp);
         push_xmfloat2(sp, wbnd::get_renderpath_logical_dims(path));
     });

anfr("wi_set_renderpath3d_exposure", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.exposure",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_exposure(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_exposure", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.exposure",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_exposure(renderpath3d)));
     });

anfr("wi_set_renderpath3d_brightness", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.brightness",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_brightness(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_brightness", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.brightness",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_brightness(renderpath3d)));
     });

anfr("wi_set_renderpath3d_contrast", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.contrast",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_contrast(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_contrast", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.contrast",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_contrast(renderpath3d)));
     });

anfr("wi_set_renderpath3d_saturation", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.saturation",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_saturation(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_saturation", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.saturation",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_saturation(renderpath3d)));
     });

anfr("wi_set_renderpath3d_bloom_threshold", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.bloom_threshold",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_bloom_threshold(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_bloom_threshold", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.bloom_threshold",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_bloom_threshold(renderpath3d)));
     });

anfr("wi_set_renderpath3d_motion_blur_strength", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.motion_blur_strength",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_motion_blur_strength(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_motion_blur_strength", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.motion_blur_strength",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_motion_blur_strength(renderpath3d)));
     });

anfr("wi_set_renderpath3d_depth_of_field_strength", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.depth_of_field_strength",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_depth_of_field_strength(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_depth_of_field_strength", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.depth_of_field_strength",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_depth_of_field_strength(renderpath3d)));
     });

anfr("wi_set_renderpath3d_sharpen_filter_amount", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.sharpen_filter_amount",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_sharpen_filter_amount(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_sharpen_filter_amount", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.sharpen_filter_amount",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_sharpen_filter_amount(renderpath3d)));
     });

anfr("wi_set_renderpath3d_outline_threshold", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.outline_threshold",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_outline_threshold(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_outline_threshold", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.outline_threshold",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_outline_threshold(renderpath3d)));
     });

anfr("wi_set_renderpath3d_outline_thickness", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.outline_thickness",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_outline_thickness(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_outline_thickness", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.outline_thickness",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_outline_thickness(renderpath3d)));
     });

anfr("wi_set_renderpath3d_outline_color", "renderpath3d,v", "I}:2F}:4", "",
     "Sets renderpath3d.outline_color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_outline_color(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_outline_color", "renderpath3d", "I}:2", "F}:4",
     "Gets renderpath3d.outline_color",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_renderpath3d_outline_color(renderpath3d));
     });

anfr("wi_set_renderpath3d_ao_range", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.ao_range",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_ao_range(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_ao_range", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.ao_range",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_ao_range(renderpath3d)));
     });

anfr("wi_set_renderpath3d_ao_sample_count", "renderpath3d,v", "I}:2I", "",
     "Sets renderpath3d.ao_sample_count",
     [](StackPtr &sp, VM &vm) {
         auto v            = (int32_t)Pop(sp).ival();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_ao_sample_count(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_ao_sample_count", "renderpath3d", "I}:2", "I",
     "Gets renderpath3d.ao_sample_count",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_ao_sample_count(renderpath3d)));
     });

anfr("wi_set_renderpath3d_ao_power", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.ao_power",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_ao_power(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_ao_power", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.ao_power",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_ao_power(renderpath3d)));
     });

anfr("wi_set_renderpath3d_chromatic_aberration_amount", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.chromatic_aberration_amount",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_chromatic_aberration_amount(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_chromatic_aberration_amount", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.chromatic_aberration_amount",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_chromatic_aberration_amount(renderpath3d)));
     });

anfr("wi_set_renderpath3d_screen_space_shadow_sample_count", "renderpath3d,v", "I}:2I", "",
     "Sets renderpath3d.screen_space_shadow_sample_count",
     [](StackPtr &sp, VM &vm) {
         auto v            = (int32_t)Pop(sp).ival();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_screen_space_shadow_sample_count(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_screen_space_shadow_sample_count", "renderpath3d", "I}:2", "I",
     "Gets renderpath3d.screen_space_shadow_sample_count",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_screen_space_shadow_sample_count(renderpath3d)));
     });

anfr("wi_set_renderpath3d_screen_space_shadow_range", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.screen_space_shadow_range",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_screen_space_shadow_range(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_screen_space_shadow_range", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.screen_space_shadow_range",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_screen_space_shadow_range(renderpath3d)));
     });

anfr("wi_set_renderpath3d_eye_adaption_key", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.eye_adaption_key",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_eye_adaption_key(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_eye_adaption_key", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.eye_adaption_key",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_eye_adaption_key(renderpath3d)));
     });

anfr("wi_set_renderpath3d_eye_adaption_rate", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.eye_adaption_rate",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_eye_adaption_rate(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_eye_adaption_rate", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.eye_adaption_rate",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_eye_adaption_rate(renderpath3d)));
     });

anfr("wi_set_renderpath3d_fsr_sharpness", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.fsr_sharpness",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_fsr_sharpness(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_fsr_sharpness", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.fsr_sharpness",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_fsr_sharpness(renderpath3d)));
     });

anfr("wi_set_renderpath3d_fsr2_sharpness", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.fsr2_sharpness",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_fsr2_sharpness(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_fsr2_sharpness", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.fsr2_sharpness",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_fsr2_sharpness(renderpath3d)));
     });

anfr("wi_set_renderpath3d_light_shafts_strength", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.light_shafts_strength",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_light_shafts_strength(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_light_shafts_strength", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.light_shafts_strength",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_light_shafts_strength(renderpath3d)));
     });

anfr("wi_set_renderpath3d_raytraced_diffuse_range", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.raytraced_diffuse_range",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_raytraced_diffuse_range(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_raytraced_diffuse_range", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.raytraced_diffuse_range",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_raytraced_diffuse_range(renderpath3d)));
     });

anfr("wi_set_renderpath3d_raytraced_reflections_range", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.raytraced_reflections_range",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_raytraced_reflections_range(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_raytraced_reflections_range", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.raytraced_reflections_range",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_raytraced_reflections_range(renderpath3d)));
     });

anfr("wi_set_renderpath3d_reflection_roughness_cutoff", "renderpath3d,v", "I}:2F", "",
     "Sets renderpath3d.reflection_roughness_cutoff",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).fltval();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_reflection_roughness_cutoff(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_reflection_roughness_cutoff", "renderpath3d", "I}:2", "F",
     "Gets renderpath3d.reflection_roughness_cutoff",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_reflection_roughness_cutoff(renderpath3d)));
     });

anfr("wi_set_renderpath3d_ssr_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.ssr_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_ssr_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_ssr_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.ssr_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_ssr_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_raytraced_diffuse_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.raytraced_diffuse_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_raytraced_diffuse_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_raytraced_diffuse_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.raytraced_diffuse_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_raytraced_diffuse_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_raytraced_reflection_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.raytraced_reflection_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_raytraced_reflection_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_raytraced_reflection_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.raytraced_reflection_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_raytraced_reflection_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_shadows_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.shadows_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_shadows_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_shadows_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.shadows_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_shadows_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_reflections_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.reflections_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_reflections_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_reflections_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.reflections_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_reflections_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_fxaa_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.fxaa_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_fxaa_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_fxaa_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.fxaa_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_fxaa_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_bloom_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.bloom_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_bloom_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_bloom_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.bloom_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_bloom_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_color_grading_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.color_grading_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_color_grading_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_color_grading_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.color_grading_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_color_grading_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_volume_lights_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.volume_lights_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_volume_lights_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_volume_lights_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.volume_lights_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_volume_lights_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_light_shafts_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.light_shafts_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_light_shafts_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_light_shafts_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.light_shafts_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_light_shafts_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_lens_flare_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.lens_flare_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_lens_flare_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_lens_flare_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.lens_flare_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_lens_flare_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_motion_blur_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.motion_blur_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_motion_blur_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_motion_blur_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.motion_blur_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_motion_blur_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_depth_of_field_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.depth_of_field_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_depth_of_field_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_depth_of_field_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.depth_of_field_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_depth_of_field_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_eye_adaptation_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.eye_adaptation_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_eye_adaptation_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_eye_adaptation_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.eye_adaptation_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_eye_adaptation_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_sharpen_filter_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.sharpen_filter_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_sharpen_filter_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_sharpen_filter_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.sharpen_filter_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_sharpen_filter_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_outline_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.outline_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_outline_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_outline_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.outline_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_outline_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_chromatic_aberration_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.chromatic_aberration_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_chromatic_aberration_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_chromatic_aberration_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.chromatic_aberration_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_chromatic_aberration_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_dither_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.dither_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_dither_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_dither_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.dither_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_dither_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_occlusion_culling_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.occlusion_culling_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_occlusion_culling_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_occlusion_culling_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.occlusion_culling_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_occlusion_culling_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_scene_update_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.scene_update_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_scene_update_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_scene_update_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.scene_update_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_scene_update_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_fsr_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.fsr_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_fsr_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_fsr_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.fsr_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_fsr_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_fsr2_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.fsr2_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_fsr2_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_fsr2_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.fsr2_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_fsr2_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_vxgi_resolve_full_resolution_enabled", "renderpath3d,v", "I}:2B", "",
     "Sets renderpath3d.vxgi_resolve_full_resolution_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v            = Pop(sp).True();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_vxgi_resolve_full_resolution_enabled(renderpath3d, v);
     });

anfr("wi_get_renderpath3d_vxgi_resolve_full_resolution_enabled", "renderpath3d", "I}:2", "B",
     "Gets renderpath3d.vxgi_resolve_full_resolution_enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_vxgi_resolve_full_resolution_enabled(renderpath3d)));
     });

anfr("wi_get_renderpath3d_ao_enabled", "renderpath3d", "I}:2", "B",
     "Returns true if AO is enabled",
     [](StackPtr &sp, VM &vm) {
         auto renderpath3d = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_renderpath3d_ao_enabled(renderpath3d)));
     });

anfr("wi_set_renderpath3d_ao", "renderpath3d,v", "I}:2I", "",
     "Set the AO mode",
     [](StackPtr &sp, VM &vm) {
         auto v            = (int32_t)Pop(sp).ival();
         auto renderpath3d = pop_wo_handle(sp);
         wbnd::set_renderpath3d_ao(renderpath3d, v);
     });

anfr("wi_set_collider_shape", "collider,v", "I}:2I", "",
     "Sets collider.shape",
     [](StackPtr &sp, VM &vm) {
         auto v        = (int32_t)Pop(sp).ival();
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_shape(collider, v);
     });

anfr("wi_get_collider_shape", "collider", "I}:2", "I",
     "Gets collider.shape",
     [](StackPtr &sp, VM &vm) {
         auto collider = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_collider_shape(collider)));
     });

anfr("wi_set_collider_radius", "collider,v", "I}:2F", "",
     "Sets collider.radius",
     [](StackPtr &sp, VM &vm) {
         auto v        = Pop(sp).fltval();
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_radius(collider, v);
     });

anfr("wi_get_collider_radius", "collider", "I}:2", "F",
     "Gets collider.radius",
     [](StackPtr &sp, VM &vm) {
         auto collider = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_collider_radius(collider)));
     });

anfr("wi_set_collider_offset", "collider,v", "I}:2F}:3", "",
     "Sets collider.offset",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_offset(collider, v);
     });

anfr("wi_get_collider_offset", "collider", "I}:2", "F}:3",
     "Gets collider.offset",
     [](StackPtr &sp, VM &vm) {
         auto collider = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_collider_offset(collider));
     });

anfr("wi_set_collider_tail", "collider,v", "I}:2F}:3", "",
     "Sets collider.tail",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_tail(collider, v);
     });

anfr("wi_get_collider_tail", "collider", "I}:2", "F}:3",
     "Gets collider.tail",
     [](StackPtr &sp, VM &vm) {
         auto collider = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_collider_tail(collider));
     });

anfr("wi_set_collider_is_gpu_enabled", "collider,v", "I}:2B", "",
     "Set collider as gpu enabled",
     [](StackPtr &sp, VM &vm) {
         auto v        = Pop(sp).True();
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_is_gpu_enabled(collider, v);
     });

anfr("wi_set_collider_is_cpu_enabled", "collider,v", "I}:2B", "",
     "Set collider as cpu enabled",
     [](StackPtr &sp, VM &vm) {
         auto v        = Pop(sp).True();
         auto collider = pop_wo_handle(sp);
         wbnd::set_collider_is_cpu_enabled(collider, v);
     });

anfr("wi_create_collider_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a collider component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_collider_component(scene, entity));
     });

anfr("wi_get_collider_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the collider component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_collider_component(scene, entity));
     });

anfr("wi_entity_collider_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a collider component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_collider_count(scene)));
     });

anfr("wi_entity_collider_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a collider component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_collider_get(scene, n));
     });

anfr("wi_get_collider_capsule", "collider", "I}:2", "I}:2",
     "Returns the primitive capsule for the collider, only valid if the shape is CAPSULE.  Returns value does not need to be deleted, valid until there is an ecs change in the scene",
     [](StackPtr &sp, VM &vm) {
         auto collider = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_collider_capsule(collider));
     });

anfr("wi_create_matrix4x4", "", "", "I}:2",
     "Creates a matrix",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_matrix4x4());
     });

anfr("wi_delete_matrix", "m", "I}:2", "",
     "Deletes a matrix",
     [](StackPtr &sp, VM &vm) {
         auto m = pop_wo_handle(sp);
         wbnd::delete_matrix(m);
     });

anfr("wi_identity_matrix", "m", "I}:2", "",
     "Initializes the matrix as an identity matrix",
     [](StackPtr &sp, VM &vm) {
         auto m = pop_wo_handle(sp);
         wbnd::identity_matrix(m);
     });

anfr("wi_transform_vector", "matrix,v", "I}:2F}:4", "F}:4",
     "Transforms a vector with the matrix",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto matrix = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::transform_vector(matrix, v));
     });

anfr("wi_assign_matrix", "lhs,rhs", "I}:2I}:2", "",
     "Assigns matrix lhs the value from rhs",
     [](StackPtr &sp, VM &vm) {
         auto rhs = pop_wo_handle(sp);
         auto lhs = pop_wo_handle(sp);
         wbnd::assign_matrix(lhs, rhs);
     });

anfr("wi_get_matrix_translation", "matrix", "I}:2", "F}:3",
     "Returns the translation part of the given matrix",
     [](StackPtr &sp, VM &vm) {
         auto matrix = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_matrix_translation(matrix));
     });

anfr("wi_assign_matrix_rows", "m,r1,r2,r3,r4", "I}:2F}:4F}:4F}:4F}:4", "",
     "Initializes a matrix from rows",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 r4;
         pop_xmfloat4(sp, r4);
         XMFLOAT4 r3;
         pop_xmfloat4(sp, r3);
         XMFLOAT4 r2;
         pop_xmfloat4(sp, r2);
         XMFLOAT4 r1;
         pop_xmfloat4(sp, r1);
         auto m = pop_wo_handle(sp);
         wbnd::assign_matrix_rows(m, r1, r2, r3, r4);
     });

anfr("wi_return_matrix_row", "m,r", "I}:2I", "F}:4",
     "Returns a row from a matrix",
     [](StackPtr &sp, VM &vm) {
         auto r = (int32_t)Pop(sp).ival();
         auto m = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::return_matrix_row(m, r));
     });

anfr("wi_translation_matrix", "m,v", "I}:2F}:3", "",
     "Set up as a translation matrix",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto m = pop_wo_handle(sp);
         wbnd::translation_matrix(m, v);
     });

anfr("wi_rotation_euler_matrix", "m,angles", "I}:2F}:3", "",
     "Set up as a rotation matrix",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 angles;
         pop_xmfloat3(sp, angles);
         auto m = pop_wo_handle(sp);
         wbnd::rotation_euler_matrix(m, angles);
     });

anfr("wi_rotation_x_matrix", "m,a", "I}:2F", "",
     "Set up as a rotation around x matrix",
     [](StackPtr &sp, VM &vm) {
         auto a = Pop(sp).fltval();
         auto m = pop_wo_handle(sp);
         wbnd::rotation_x_matrix(m, a);
     });

anfr("wi_rotation_y_matrix", "m,a", "I}:2F", "",
     "Set up as a rotation around y matrix",
     [](StackPtr &sp, VM &vm) {
         auto a = Pop(sp).fltval();
         auto m = pop_wo_handle(sp);
         wbnd::rotation_y_matrix(m, a);
     });

anfr("wi_rotation_z_matrix", "m,a", "I}:2F", "",
     "Set up as a rotation around z matrix",
     [](StackPtr &sp, VM &vm) {
         auto a = Pop(sp).fltval();
         auto m = pop_wo_handle(sp);
         wbnd::rotation_z_matrix(m, a);
     });

anfr("wi_rotation_quat_matrix", "m,quat", "I}:2F}:4", "",
     "Set matrix as quaternion rotation",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 quat;
         pop_xmfloat4(sp, quat);
         auto m = pop_wo_handle(sp);
         wbnd::rotation_quat_matrix(m, quat);
     });

anfr("wi_scaling_matrix", "m,scale", "I}:2F}:4", "",
     "Set up matrix as a scaling matrix",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 scale;
         pop_xmfloat4(sp, scale);
         auto m = pop_wo_handle(sp);
         wbnd::scaling_matrix(m, scale);
     });

anfr("wi_look_to_matrix", "m,eyepos,eyedir,up", "I}:2F}:3F}:3F}:3", "",
     "Set up matrix to look to a pos",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 up;
         pop_xmfloat3(sp, up);
         XMFLOAT3 eyedir;
         pop_xmfloat3(sp, eyedir);
         XMFLOAT3 eyepos;
         pop_xmfloat3(sp, eyepos);
         auto m = pop_wo_handle(sp);
         wbnd::look_to_matrix(m, eyepos, eyedir, up);
     });

anfr("wi_look_at_matrix", "m,eyepos,focuspos,up", "I}:2F}:3F}:3F}:3", "",
     "Set up matrix to look at a pos",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 up;
         pop_xmfloat3(sp, up);
         XMFLOAT3 focuspos;
         pop_xmfloat3(sp, focuspos);
         XMFLOAT3 eyepos;
         pop_xmfloat3(sp, eyepos);
         auto m = pop_wo_handle(sp);
         wbnd::look_at_matrix(m, eyepos, focuspos, up);
     });

anfr("wi_multiply_matrix", "lhs,rhs,result", "I}:2I}:2I}:2", "",
     "Multiply lhs by rhs and put the reuslt into result",
     [](StackPtr &sp, VM &vm) {
         auto result = pop_wo_handle(sp);
         auto rhs    = pop_wo_handle(sp);
         auto lhs    = pop_wo_handle(sp);
         wbnd::multiply_matrix(lhs, rhs, result);
     });

anfr("wi_add_matrix", "lhs,rhs,result", "I}:2I}:2I}:2", "",
     "Add lhs and rhs, and put the result in result",
     [](StackPtr &sp, VM &vm) {
         auto result = pop_wo_handle(sp);
         auto rhs    = pop_wo_handle(sp);
         auto lhs    = pop_wo_handle(sp);
         wbnd::add_matrix(lhs, rhs, result);
     });

anfr("wi_transpose_matrix", "m,result", "I}:2I}:2", "",
     "Transpose a matrix",
     [](StackPtr &sp, VM &vm) {
         auto result = pop_wo_handle(sp);
         auto m      = pop_wo_handle(sp);
         wbnd::transpose_matrix(m, result);
     });

anfr("wi_invert_matrix", "m,result", "I}:2I}:2", "",
     "Inverts 'm' and puts the result in 'result'",
     [](StackPtr &sp, VM &vm) {
         auto result = pop_wo_handle(sp);
         auto m      = pop_wo_handle(sp);
         wbnd::invert_matrix(m, result);
     });

anfr("wi_set_animation_start", "animation,v", "I}:2F", "",
     "Sets animation.start",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).fltval();
         auto animation = pop_wo_handle(sp);
         wbnd::set_animation_start(animation, v);
     });

anfr("wi_get_animation_start", "animation", "I}:2", "F",
     "Gets animation.start",
     [](StackPtr &sp, VM &vm) {
         auto animation = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_start(animation)));
     });

anfr("wi_set_animation_end", "animation,v", "I}:2F", "",
     "Sets animation.end",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).fltval();
         auto animation = pop_wo_handle(sp);
         wbnd::set_animation_end(animation, v);
     });

anfr("wi_get_animation_end", "animation", "I}:2", "F",
     "Gets animation.end",
     [](StackPtr &sp, VM &vm) {
         auto animation = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_end(animation)));
     });

anfr("wi_set_animation_timer", "animation,v", "I}:2F", "",
     "Sets animation.timer",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).fltval();
         auto animation = pop_wo_handle(sp);
         wbnd::set_animation_timer(animation, v);
     });

anfr("wi_get_animation_timer", "animation", "I}:2", "F",
     "Gets animation.timer",
     [](StackPtr &sp, VM &vm) {
         auto animation = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_timer(animation)));
     });

anfr("wi_set_animation_amount", "animation,v", "I}:2F", "",
     "Sets animation.amount",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).fltval();
         auto animation = pop_wo_handle(sp);
         wbnd::set_animation_amount(animation, v);
     });

anfr("wi_get_animation_amount", "animation", "I}:2", "F",
     "Gets animation.amount",
     [](StackPtr &sp, VM &vm) {
         auto animation = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_amount(animation)));
     });

anfr("wi_set_animation_speed", "animation,v", "I}:2F", "",
     "Sets animation.speed",
     [](StackPtr &sp, VM &vm) {
         auto v         = Pop(sp).fltval();
         auto animation = pop_wo_handle(sp);
         wbnd::set_animation_speed(animation, v);
     });

anfr("wi_get_animation_speed", "animation", "I}:2", "F",
     "Gets animation.speed",
     [](StackPtr &sp, VM &vm) {
         auto animation = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_speed(animation)));
     });

anfr("wi_is_animation_playing", "anim", "I}:2", "B",
     "Returns true if animation is playing",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         Push(sp, Value(wbnd::is_animation_playing(anim)));
     });

anfr("wi_is_animation_looped", "anim", "I}:2", "B",
     "Returns true if the animation is looped",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         Push(sp, Value(wbnd::is_animation_looped(anim)));
     });

anfr("wi_get_animation_length", "anim", "I}:2", "F",
     "Returns the length of the animation",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_animation_length(anim)));
     });

anfr("wi_is_animation_ended", "anim", "I}:2", "F",
     "Returns true if the animation has ended",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         Push(sp, Value(wbnd::is_animation_ended(anim)));
     });

anfr("wi_play_animation", "anim", "I}:2", "",
     "Plays an animation",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         wbnd::play_animation(anim);
     });

anfr("wi_pause_animation", "anim", "I}:2", "",
     "Pauses an animation",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         wbnd::pause_animation(anim);
     });

anfr("wi_stop_animation", "anim", "I}:2", "",
     "Stops an animation",
     [](StackPtr &sp, VM &vm) {
         auto anim = pop_wo_handle(sp);
         wbnd::stop_animation(anim);
     });

anfr("wi_set_animation_looped", "anim,v", "I}:2B", "",
     "Sets the animation as looped/not-looped",
     [](StackPtr &sp, VM &vm) {
         auto v    = Pop(sp).True();
         auto anim = pop_wo_handle(sp);
         wbnd::set_animation_looped(anim, v);
     });

anfr("wi_create_animation_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a animation component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_animation_component(scene, entity));
     });

anfr("wi_get_animation_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the animation component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_animation_component(scene, entity));
     });

anfr("wi_entity_animation_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a animation component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_animation_count(scene)));
     });

anfr("wi_entity_animation_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a animation component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_animation_get(scene, n));
     });

anfr("wi_renderer_set_vxgi_enabled", "v", "B", "",
     "Controls VXGI",
     [](StackPtr &sp, VM &vm) {
         auto v = Pop(sp).True();
         wbnd::renderer_set_vxgi_enabled(v);
     });

anfr("wi_renderer_vxgi_enabled", "", "", "B",
     "Returns true if VXGI is enabled",
     [](StackPtr &sp, VM &vm) {
         Push(sp, Value(wbnd::renderer_vxgi_enabled()));
     });

anfr("wi_create_primitive_sphere", "", "", "I}:2",
     "",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_primitive_sphere());
     });

anfr("wi_delete_primitive_sphere", "primitive_sphere", "I}:2", "",
     "",
     [](StackPtr &sp, VM &vm) {
         auto primitive_sphere = pop_wo_handle(sp);
         wbnd::delete_primitive_sphere(primitive_sphere);
     });

anfr("wi_set_primitive_sphere_center", "primitive_sphere,v", "I}:2F}:3", "",
     "Sets primitive_sphere.center",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto primitive_sphere = pop_wo_handle(sp);
         wbnd::set_primitive_sphere_center(primitive_sphere, v);
     });

anfr("wi_get_primitive_sphere_center", "primitive_sphere", "I}:2", "F}:3",
     "Gets primitive_sphere.center",
     [](StackPtr &sp, VM &vm) {
         auto primitive_sphere = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_primitive_sphere_center(primitive_sphere));
     });

anfr("wi_set_primitive_sphere_radius", "primitive_sphere,v", "I}:2F", "",
     "Sets primitive_sphere.radius",
     [](StackPtr &sp, VM &vm) {
         auto v                = Pop(sp).fltval();
         auto primitive_sphere = pop_wo_handle(sp);
         wbnd::set_primitive_sphere_radius(primitive_sphere, v);
     });

anfr("wi_get_primitive_sphere_radius", "primitive_sphere", "I}:2", "F",
     "Gets primitive_sphere.radius",
     [](StackPtr &sp, VM &vm) {
         auto primitive_sphere = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_primitive_sphere_radius(primitive_sphere)));
     });

anfr("wi_sphere_sphere_intersects", "sphere0,sphere1", "I}:2I}:2", "BFF}:3",
     "Primitive to primitive intersection test, returns true|false,distance,direction",
     [](StackPtr &sp, VM &vm) {
         auto     sphere1 = pop_wo_handle(sp);
         auto     sphere0 = pop_wo_handle(sp);
         float    retval2;
         XMFLOAT3 retval3;
         Push(sp, Value(wbnd::sphere_sphere_intersects(sphere0, sphere1, retval2, retval3)));
         Push(sp, Value(retval2));
         push_xmfloat3(sp, retval3);
     });

anfr("wi_create_sphere_intersection_result", "", "", "I}:2",
     "",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_sphere_intersection_result());
     });

anfr("wi_delete_sphere_intersection_result", "sphere_intersection_result", "I}:2", "",
     "",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::delete_sphere_intersection_result(sphere_intersection_result);
     });

anfr("wi_set_sphere_intersection_result_entity", "sphere_intersection_result,v", "I}:2I}:2", "",
     "Sets sphere_intersection_result.entity",
     [](StackPtr &sp, VM &vm) {
         auto v                          = pop_wo_handle(sp);
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::set_sphere_intersection_result_entity(sphere_intersection_result, v);
     });

anfr("wi_get_sphere_intersection_result_entity", "sphere_intersection_result", "I}:2", "I}:2",
     "Gets sphere_intersection_result.entity",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_sphere_intersection_result_entity(sphere_intersection_result));
     });

anfr("wi_set_sphere_intersection_result_position", "sphere_intersection_result,v", "I}:2F}:3", "",
     "Sets sphere_intersection_result.position",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::set_sphere_intersection_result_position(sphere_intersection_result, v);
     });

anfr("wi_get_sphere_intersection_result_position", "sphere_intersection_result", "I}:2", "F}:3",
     "Gets sphere_intersection_result.position",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_sphere_intersection_result_position(sphere_intersection_result));
     });

anfr("wi_set_sphere_intersection_result_normal", "sphere_intersection_result,v", "I}:2F}:3", "",
     "Sets sphere_intersection_result.normal",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::set_sphere_intersection_result_normal(sphere_intersection_result, v);
     });

anfr("wi_get_sphere_intersection_result_normal", "sphere_intersection_result", "I}:2", "F}:3",
     "Gets sphere_intersection_result.normal",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_sphere_intersection_result_normal(sphere_intersection_result));
     });

anfr("wi_set_sphere_intersection_result_velocity", "sphere_intersection_result,v", "I}:2F}:3", "",
     "Sets sphere_intersection_result.velocity",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::set_sphere_intersection_result_velocity(sphere_intersection_result, v);
     });

anfr("wi_get_sphere_intersection_result_velocity", "sphere_intersection_result", "I}:2", "F}:3",
     "Gets sphere_intersection_result.velocity",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_sphere_intersection_result_velocity(sphere_intersection_result));
     });

anfr("wi_set_sphere_intersection_result_depth", "sphere_intersection_result,v", "I}:2F", "",
     "Sets sphere_intersection_result.depth",
     [](StackPtr &sp, VM &vm) {
         auto v                          = Pop(sp).fltval();
         auto sphere_intersection_result = pop_wo_handle(sp);
         wbnd::set_sphere_intersection_result_depth(sphere_intersection_result, v);
     });

anfr("wi_get_sphere_intersection_result_depth", "sphere_intersection_result", "I}:2", "F",
     "Gets sphere_intersection_result.depth",
     [](StackPtr &sp, VM &vm) {
         auto sphere_intersection_result = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_sphere_intersection_result_depth(sphere_intersection_result)));
     });

anfr("wi_scene_sphere_intersects", "scene,sphere,filter_mask,layer_mask,lod", "I}:2I}:2III", "I}:2",
     "Tests a sphere intersection with a scene, and returns a SphereIntersectionResult",
     [](StackPtr &sp, VM &vm) {
         auto lod         = (int32_t)Pop(sp).ival();
         auto layer_mask  = (int32_t)Pop(sp).ival();
         auto filter_mask = (int32_t)Pop(sp).ival();
         auto sphere      = pop_wo_handle(sp);
         auto scene       = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::scene_sphere_intersects(scene, sphere, filter_mask, layer_mask, lod));
     });

anfr("wi_create_primitive_capsule", "", "", "I}:2",
     "",
     [](StackPtr &sp, VM &vm) {
         push_wo_handle(sp, wbnd::create_primitive_capsule());
     });

anfr("wi_delete_primitive_capsule", "primitive_capsule", "I}:2", "",
     "",
     [](StackPtr &sp, VM &vm) {
         auto primitive_capsule = pop_wo_handle(sp);
         wbnd::delete_primitive_capsule(primitive_capsule);
     });

anfr("wi_set_primitive_capsule_base", "primitive_capsule,v", "I}:2F}:3", "",
     "Sets primitive_capsule.base",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto primitive_capsule = pop_wo_handle(sp);
         wbnd::set_primitive_capsule_base(primitive_capsule, v);
     });

anfr("wi_get_primitive_capsule_base", "primitive_capsule", "I}:2", "F}:3",
     "Gets primitive_capsule.base",
     [](StackPtr &sp, VM &vm) {
         auto primitive_capsule = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_primitive_capsule_base(primitive_capsule));
     });

anfr("wi_set_primitive_capsule_tip", "primitive_capsule,v", "I}:2F}:3", "",
     "Sets primitive_capsule.tip",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto primitive_capsule = pop_wo_handle(sp);
         wbnd::set_primitive_capsule_tip(primitive_capsule, v);
     });

anfr("wi_get_primitive_capsule_tip", "primitive_capsule", "I}:2", "F}:3",
     "Gets primitive_capsule.tip",
     [](StackPtr &sp, VM &vm) {
         auto primitive_capsule = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_primitive_capsule_tip(primitive_capsule));
     });

anfr("wi_set_primitive_capsule_radius", "primitive_capsule,v", "I}:2F", "",
     "Sets primitive_capsule.radius",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto primitive_capsule = pop_wo_handle(sp);
         wbnd::set_primitive_capsule_radius(primitive_capsule, v);
     });

anfr("wi_get_primitive_capsule_radius", "primitive_capsule", "I}:2", "F",
     "Gets primitive_capsule.radius",
     [](StackPtr &sp, VM &vm) {
         auto primitive_capsule = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_primitive_capsule_radius(primitive_capsule)));
     });

anfr("wi_capsule_capsule_intersects", "cap0,cap1", "I}:2I}:2", "BF}:3F}:3F",
     "Capsule to capsule intersection test, returns true/false, position, normal, penetration_depth",
     [](StackPtr &sp, VM &vm) {
         auto     cap1    = pop_wo_handle(sp);
         auto     cap0    = pop_wo_handle(sp);
         XMFLOAT3 retval2;
         XMFLOAT3 retval3;
         float    retval4;
         Push(sp, Value(wbnd::capsule_capsule_intersects(cap0, cap1, retval2, retval3, retval4)));
         push_xmfloat3(sp, retval2);
         push_xmfloat3(sp, retval3);
         Push(sp, Value(retval4));
     });

anfr("wi_capsule_sphere_intersects", "cap,sphere", "I}:2I}:2", "BFF}:3",
     "Capsule to sphere intersection test, returns bool, dist, direction",
     [](StackPtr &sp, VM &vm) {
         auto     sphere  = pop_wo_handle(sp);
         auto     cap     = pop_wo_handle(sp);
         float    retval2;
         XMFLOAT3 retval3;
         Push(sp, Value(wbnd::capsule_sphere_intersects(cap, sphere, retval2, retval3)));
         Push(sp, Value(retval2));
         push_xmfloat3(sp, retval3);
     });

anfr("wi_sphere_capsule_intersects", "sphere,cap", "I}:2I}:2", "BFF}:3",
     "Sphere to capsule intersection test, returns bool, dist, direction",
     [](StackPtr &sp, VM &vm) {
         auto     cap     = pop_wo_handle(sp);
         auto     sphere  = pop_wo_handle(sp);
         float    retval2;
         XMFLOAT3 retval3;
         Push(sp, Value(wbnd::sphere_capsule_intersects(sphere, cap, retval2, retval3)));
         Push(sp, Value(retval2));
         push_xmfloat3(sp, retval3);
     });

anfr("wi_scene_capsule_intersects", "scene,cap,filter_mask,layer_mask,lod", "I}:2I}:2III", "I}:2",
     "Tests whether a capsule intersects anything in the scene, returning a SphereIntersectionResult (not a typo)",
     [](StackPtr &sp, VM &vm) {
         auto lod         = (int32_t)Pop(sp).ival();
         auto layer_mask  = (int32_t)Pop(sp).ival();
         auto filter_mask = (int32_t)Pop(sp).ival();
         auto cap         = pop_wo_handle(sp);
         auto scene       = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::scene_capsule_intersects(scene, cap, filter_mask, layer_mask, lod));
     });

anfr("wi_set_rigidbody_physics_shape", "rigidbody_physics,v", "I}:2I", "",
     "Sets rigidbody_physics.shape",
     [](StackPtr &sp, VM &vm) {
         auto v                 = (int32_t)Pop(sp).ival();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_shape(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_shape", "rigidbody_physics", "I}:2", "I",
     "Gets rigidbody_physics.shape",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_shape(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_mass", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.mass",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_mass(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_mass", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.mass",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_mass(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_friction", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.friction",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_friction(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_friction", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.friction",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_friction(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_restitution", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.restitution",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_restitution(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_restitution", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.restitution",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_restitution(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_damping_linear", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.damping_linear",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_damping_linear(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_damping_linear", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.damping_linear",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_damping_linear(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_damping_angular", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.damping_angular",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_damping_angular(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_damping_angular", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.damping_angular",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_damping_angular(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_box_halfextents", "rigidbody_physics,v", "I}:2F}:3", "",
     "Sets rigidbody_physics.box_halfextents",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_box_halfextents(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_box_halfextents", "rigidbody_physics", "I}:2", "F}:3",
     "Gets rigidbody_physics.box_halfextents",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_rigidbody_physics_box_halfextents(rigidbody_physics));
     });

anfr("wi_set_rigidbody_physics_sphere_radius", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.sphere_radius",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_sphere_radius(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_sphere_radius", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.sphere_radius",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_sphere_radius(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_capsule_radius", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.capsule_radius",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_capsule_radius(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_capsule_radius", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.capsule_radius",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_capsule_radius(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_capsule_height", "rigidbody_physics,v", "I}:2F", "",
     "Sets rigidbody_physics.capsule_height",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).fltval();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_capsule_height(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_capsule_height", "rigidbody_physics", "I}:2", "F",
     "Gets rigidbody_physics.capsule_height",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_capsule_height(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_mesh_lod", "rigidbody_physics,v", "I}:2I", "",
     "Sets rigidbody_physics.mesh_lod",
     [](StackPtr &sp, VM &vm) {
         auto v                 = (int32_t)Pop(sp).ival();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_mesh_lod(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_mesh_lod", "rigidbody_physics", "I}:2", "I",
     "Gets rigidbody_physics.mesh_lod",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_mesh_lod(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_disable_deactivation", "rigidbody_physics,v", "I}:2B", "",
     "Sets rigidbody_physics.disable_deactivation",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).True();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_disable_deactivation(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_disable_deactivation", "rigidbody_physics", "I}:2", "B",
     "Gets rigidbody_physics.disable_deactivation",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_disable_deactivation(rigidbody_physics)));
     });

anfr("wi_set_rigidbody_physics_kinematic", "rigidbody_physics,v", "I}:2B", "",
     "Sets rigidbody_physics.kinematic",
     [](StackPtr &sp, VM &vm) {
         auto v                 = Pop(sp).True();
         auto rigidbody_physics = pop_wo_handle(sp);
         wbnd::set_rigidbody_physics_kinematic(rigidbody_physics, v);
     });

anfr("wi_get_rigidbody_physics_kinematic", "rigidbody_physics", "I}:2", "B",
     "Gets rigidbody_physics.kinematic",
     [](StackPtr &sp, VM &vm) {
         auto rigidbody_physics = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_rigidbody_physics_kinematic(rigidbody_physics)));
     });

anfr("wi_create_rigidbody_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a rigidbody component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_rigidbody_component(scene, entity));
     });

anfr("wi_get_rigidbody_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the rigidbody component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_rigidbody_component(scene, entity));
     });

anfr("wi_entity_rigidbody_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a rigidbody component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_rigidbody_count(scene)));
     });

anfr("wi_entity_rigidbody_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a rigidbody component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_rigidbody_get(scene, n));
     });

anfr("wi_set_object_mesh_id", "object,v", "I}:2I}:2", "",
     "Sets object.mesh_id",
     [](StackPtr &sp, VM &vm) {
         auto v      = pop_wo_handle(sp);
         auto object = pop_wo_handle(sp);
         wbnd::set_object_mesh_id(object, v);
     });

anfr("wi_get_object_mesh_id", "object", "I}:2", "I}:2",
     "Gets object.mesh_id",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_object_mesh_id(object));
     });

anfr("wi_set_object_cascade_mask", "object,v", "I}:2I", "",
     "Sets object.cascade_mask",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_cascade_mask(object, v);
     });

anfr("wi_get_object_cascade_mask", "object", "I}:2", "I",
     "Gets object.cascade_mask",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_cascade_mask(object)));
     });

anfr("wi_set_object_filter_mask", "object,v", "I}:2I", "",
     "Sets object.filter_mask",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_filter_mask(object, v);
     });

anfr("wi_get_object_filter_mask", "object", "I}:2", "I",
     "Gets object.filter_mask",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_filter_mask(object)));
     });

anfr("wi_set_object_color", "object,v", "I}:2F}:4", "",
     "Sets object.color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto object = pop_wo_handle(sp);
         wbnd::set_object_color(object, v);
     });

anfr("wi_get_object_color", "object", "I}:2", "F}:4",
     "Gets object.color",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_object_color(object));
     });

anfr("wi_set_object_emissive_color", "object,v", "I}:2F}:4", "",
     "Sets object.emissive_color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT4 v;
         pop_xmfloat4(sp, v);
         auto object = pop_wo_handle(sp);
         wbnd::set_object_emissive_color(object, v);
     });

anfr("wi_get_object_emissive_color", "object", "I}:2", "F}:4",
     "Gets object.emissive_color",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         push_xmfloat4(sp, wbnd::get_object_emissive_color(object));
     });

anfr("wi_set_object_user_stencil_ref", "object,v", "I}:2I", "",
     "Sets object.user_stencil_ref",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_user_stencil_ref(object, v);
     });

anfr("wi_get_object_user_stencil_ref", "object", "I}:2", "I",
     "Gets object.user_stencil_ref",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_user_stencil_ref(object)));
     });

anfr("wi_set_object_lod_distance_multiplier", "object,v", "I}:2F", "",
     "Sets object.lod_distance_multiplier",
     [](StackPtr &sp, VM &vm) {
         auto v      = Pop(sp).fltval();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_lod_distance_multiplier(object, v);
     });

anfr("wi_get_object_lod_distance_multiplier", "object", "I}:2", "F",
     "Gets object.lod_distance_multiplier",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_lod_distance_multiplier(object)));
     });

anfr("wi_set_object_draw_distance", "object,v", "I}:2F", "",
     "Sets object.draw_distance",
     [](StackPtr &sp, VM &vm) {
         auto v      = Pop(sp).fltval();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_draw_distance(object, v);
     });

anfr("wi_get_object_draw_distance", "object", "I}:2", "F",
     "Gets object.draw_distance",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_draw_distance(object)));
     });

anfr("wi_set_object_lightmap_width", "object,v", "I}:2I", "",
     "Sets object.lightmap_width",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_lightmap_width(object, v);
     });

anfr("wi_get_object_lightmap_width", "object", "I}:2", "I",
     "Gets object.lightmap_width",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_lightmap_width(object)));
     });

anfr("wi_set_object_lightmap_height", "object,v", "I}:2I", "",
     "Sets object.lightmap_height",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_lightmap_height(object, v);
     });

anfr("wi_get_object_lightmap_height", "object", "I}:2", "I",
     "Gets object.lightmap_height",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_lightmap_height(object)));
     });

anfr("wi_set_object_sort_priority", "object,v", "I}:2I", "",
     "Sets object.sort_priority",
     [](StackPtr &sp, VM &vm) {
         auto v      = (int32_t)Pop(sp).ival();
         auto object = pop_wo_handle(sp);
         wbnd::set_object_sort_priority(object, v);
     });

anfr("wi_get_object_sort_priority", "object", "I}:2", "I",
     "Gets object.sort_priority",
     [](StackPtr &sp, VM &vm) {
         auto object = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_object_sort_priority(object)));
     });

anfr("wi_create_object_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a object component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_object_component(scene, entity));
     });

anfr("wi_get_object_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the object component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_object_component(scene, entity));
     });

anfr("wi_entity_object_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a object component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_object_count(scene)));
     });

anfr("wi_entity_object_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a object component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_object_get(scene, n));
     });

anfr("wi_set_hierarchy_parent_id", "hierarchy,v", "I}:2I}:2", "",
     "Sets hierarchy.parent_id",
     [](StackPtr &sp, VM &vm) {
         auto v         = pop_wo_handle(sp);
         auto hierarchy = pop_wo_handle(sp);
         wbnd::set_hierarchy_parent_id(hierarchy, v);
     });

anfr("wi_get_hierarchy_parent_id", "hierarchy", "I}:2", "I}:2",
     "Gets hierarchy.parent_id",
     [](StackPtr &sp, VM &vm) {
         auto hierarchy = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_hierarchy_parent_id(hierarchy));
     });

anfr("wi_set_hierarchy_layermask_bind", "hierarchy,v", "I}:2I", "",
     "Sets hierarchy.layermask_bind",
     [](StackPtr &sp, VM &vm) {
         auto v         = (int32_t)Pop(sp).ival();
         auto hierarchy = pop_wo_handle(sp);
         wbnd::set_hierarchy_layermask_bind(hierarchy, v);
     });

anfr("wi_get_hierarchy_layermask_bind", "hierarchy", "I}:2", "I",
     "Gets hierarchy.layermask_bind",
     [](StackPtr &sp, VM &vm) {
         auto hierarchy = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_hierarchy_layermask_bind(hierarchy)));
     });

anfr("wi_create_hierarchy_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a hierarchy component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_hierarchy_component(scene, entity));
     });

anfr("wi_get_hierarchy_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the hierarchy component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_hierarchy_component(scene, entity));
     });

anfr("wi_entity_hierarchy_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a hierarchy component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_hierarchy_count(scene)));
     });

anfr("wi_entity_hierarchy_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a hierarchy component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_hierarchy_get(scene, n));
     });

anfr("wi_set_light_type", "light,v", "I}:2I", "",
     "Sets light.type",
     [](StackPtr &sp, VM &vm) {
         auto v     = (int32_t)Pop(sp).ival();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_type(light, v);
     });

anfr("wi_get_light_type", "light", "I}:2", "I",
     "Gets light.type",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_type(light)));
     });

anfr("wi_set_light_color", "light,v", "I}:2F}:3", "",
     "Sets light.color",
     [](StackPtr &sp, VM &vm) {
         XMFLOAT3 v;
         pop_xmfloat3(sp, v);
         auto light = pop_wo_handle(sp);
         wbnd::set_light_color(light, v);
     });

anfr("wi_get_light_color", "light", "I}:2", "F}:3",
     "Gets light.color",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         push_xmfloat3(sp, wbnd::get_light_color(light));
     });

anfr("wi_set_light_intensity", "light,v", "I}:2F", "",
     "Sets light.intensity",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_intensity(light, v);
     });

anfr("wi_get_light_intensity", "light", "I}:2", "F",
     "Gets light.intensity",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_intensity(light)));
     });

anfr("wi_set_light_range", "light,v", "I}:2F", "",
     "Sets light.range",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_range(light, v);
     });

anfr("wi_get_light_range", "light", "I}:2", "F",
     "Gets light.range",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_range(light)));
     });

anfr("wi_set_light_outer_cone_angle", "light,v", "I}:2F", "",
     "Sets light.outer_cone_angle",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_outer_cone_angle(light, v);
     });

anfr("wi_get_light_outer_cone_angle", "light", "I}:2", "F",
     "Gets light.outer_cone_angle",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_outer_cone_angle(light)));
     });

anfr("wi_set_light_inner_cone_angle", "light,v", "I}:2F", "",
     "Sets light.inner_cone_angle",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_inner_cone_angle(light, v);
     });

anfr("wi_get_light_inner_cone_angle", "light", "I}:2", "F",
     "Gets light.inner_cone_angle",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_inner_cone_angle(light)));
     });

anfr("wi_set_light_radius", "light,v", "I}:2F", "",
     "Sets light.radius",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_radius(light, v);
     });

anfr("wi_get_light_radius", "light", "I}:2", "F",
     "Gets light.radius",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_radius(light)));
     });

anfr("wi_set_light_length", "light,v", "I}:2F", "",
     "Sets light.length",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).fltval();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_length(light, v);
     });

anfr("wi_get_light_length", "light", "I}:2", "F",
     "Gets light.length",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_length(light)));
     });

anfr("wi_set_light_casts_shadow", "light,v", "I}:2B", "",
     "Sets light.casts_shadow",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).True();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_casts_shadow(light, v);
     });

anfr("wi_get_light_casts_shadow", "light", "I}:2", "B",
     "Gets light.casts_shadow",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_casts_shadow(light)));
     });

anfr("wi_set_light_volumetrics_enabled", "light,v", "I}:2B", "",
     "Sets light.volumetrics_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).True();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_volumetrics_enabled(light, v);
     });

anfr("wi_get_light_volumetrics_enabled", "light", "I}:2", "B",
     "Gets light.volumetrics_enabled",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_volumetrics_enabled(light)));
     });

anfr("wi_set_light_visualizer_enabled", "light,v", "I}:2B", "",
     "Sets light.visualizer_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).True();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_visualizer_enabled(light, v);
     });

anfr("wi_get_light_visualizer_enabled", "light", "I}:2", "B",
     "Gets light.visualizer_enabled",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_visualizer_enabled(light)));
     });

anfr("wi_set_light_is_static", "light,v", "I}:2B", "",
     "Sets light.is_static",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).True();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_is_static(light, v);
     });

anfr("wi_get_light_is_static", "light", "I}:2", "B",
     "Gets light.is_static",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_is_static(light)));
     });

anfr("wi_set_light_volumetric_clouds_enabled", "light,v", "I}:2B", "",
     "Sets light.volumetric_clouds_enabled",
     [](StackPtr &sp, VM &vm) {
         auto v     = Pop(sp).True();
         auto light = pop_wo_handle(sp);
         wbnd::set_light_volumetric_clouds_enabled(light, v);
     });

anfr("wi_get_light_volumetric_clouds_enabled", "light", "I}:2", "B",
     "Gets light.volumetric_clouds_enabled",
     [](StackPtr &sp, VM &vm) {
         auto light = pop_wo_handle(sp);
         Push(sp, Value(wbnd::get_light_volumetric_clouds_enabled(light)));
     });

anfr("wi_create_light_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a light component for the given entity and returns a handle",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::create_light_component(scene, entity));
     });

anfr("wi_get_light_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Gets the light component for the given entity.",
     [](StackPtr &sp, VM &vm) {
         auto entity = pop_wo_handle(sp);
         auto scene  = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::get_light_component(scene, entity));
     });

anfr("wi_entity_light_count", "scene", "I}:2", "I",
     "Returns the number of entities that have a light component",
     [](StackPtr &sp, VM &vm) {
         auto scene = pop_wo_handle(sp);
         Push(sp, Value(wbnd::entity_light_count(scene)));
     });

anfr("wi_entity_light_get", "scene,n", "I}:2I", "I}:2",
     "Returns the nth entity that has a light component",
     [](StackPtr &sp, VM &vm) {
         auto n     = (int32_t)Pop(sp).ival();
         auto scene = pop_wo_handle(sp);
         push_wo_handle(sp, wbnd::entity_light_get(scene, n));
     }); 


