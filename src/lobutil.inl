// GENERATED for inclusion into lobutils.cpp, do not edit.
anfr("wi_transform_clear", "trans_comp", "I}:2", "",
     "Clears the transform component's transform.",
    [](StackPtr &sp, VM &) {
        auto trans_comp = pop_wo_handle(sp);
        wbnd::transform_clear(trans_comp);
});

anfr("wi_get_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Returns the transform component for 'entity' if it exists, or int2{?, 0} if there is none.",
    [](StackPtr &sp, VM &) {
        auto entity = pop_wo_handle(sp);
        auto scene  = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::get_transform_component(scene, entity));
});

anfr("wi_new_scene", "", "", "I}:2",
     "Creates a new empty scene.",
    [](StackPtr &sp, VM &) {
        push_wo_handle(sp, wbnd::new_scene());
});

anfr("wi_global_scene", "", "", "I}:2",
     "Returns the global scene",
    [](StackPtr &sp, VM &) {
        push_wo_handle(sp, wbnd::global_scene());
});

anfr("wi_load_model", "scene,fname,attach", "I}:2SB", "I}:2",
     "Loads the model from the file into the given scene. Returns valid entity handle if attached==true",
    [](StackPtr &sp, VM &) {
        auto attach = Pop(sp).True();
        auto fname  = Pop(sp).sval()->strv();
        auto scene  = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::load_model(scene, fname, attach));
});

anfr("wi_create_entity", "", "", "I}:2",
     "Creates a new empty entity",
    [](StackPtr &sp, VM &) {
        push_wo_handle(sp, wbnd::create_entity());
});

anfr("wi_create_name_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a name component for the given entity, and returns a the handle",
    [](StackPtr &sp, VM &) {
        auto entity = pop_wo_handle(sp);
        auto scene  = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::create_name_component(scene, entity));
});

anfr("wi_nc_set_name", "name_comp,name", "I}:2S", "",
     "Sets the name for a name component.",
    [](StackPtr &sp, VM &) {
        auto name      = Pop(sp).sval()->strv();
        auto name_comp = pop_wo_handle(sp);
        wbnd::nc_set_name(name_comp, name);
});

anfr("wi_find_entity_by_name", "scene,name,ancestor_entity", "I}:2SI}:2", "I}:2",
     "Searches scene for an entity by name. Returns INVALID_ENTITY if not found.",
    [](StackPtr &sp, VM &) {
        auto ancestor_entity = pop_wo_handle(sp);
        auto name            = Pop(sp).sval()->strv();
        auto scene           = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::find_entity_by_name(scene, name, ancestor_entity));
});

anfr("wi_backlog", "level,msg", "IS", "",
     "Logs to Wicked Engine backlog with given log level",
    [](StackPtr &sp, VM &) {
        auto msg   = Pop(sp).sval()->strv();
        auto level = Pop(sp).ival();
        wbnd::backlog(level, msg);
});

anfr("wi_create_camera_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a camera component on an entity.",
    [](StackPtr &sp, VM &) {
        auto entity = pop_wo_handle(sp);
        auto scene  = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::create_camera_component(scene, entity));
});

anfr("wi_create_transform_component", "scene,entity", "I}:2I}:2", "I}:2",
     "Creates a transform component on an entity",
    [](StackPtr &sp, VM &) {
        auto entity = pop_wo_handle(sp);
        auto scene  = pop_wo_handle(sp);
        push_wo_handle(sp, wbnd::create_transform_component(scene, entity));
});

anfr("wi_get_renderpath3d", "", "", "I}:2",
     "Returns the games RenderPath3d",
    [](StackPtr &sp, VM &) {
        push_wo_handle(sp, wbnd::get_renderpath3d());
});

anfr("wi_renderpath3d_set_camera", "rpath,cam_component", "I}:2I}:2", "",
     "Sets the camera component used by the 3d renderpath",
    [](StackPtr &sp, VM &) {
        auto cam_component = pop_wo_handle(sp);
        auto rpath         = pop_wo_handle(sp);
        wbnd::renderpath3d_set_camera(rpath, cam_component);
});

anfr("wi_transform_translate", "trans_component,v", "I}:2F}:3", "",
     "Tranlates transform by 'vec'",
    [](StackPtr &sp, VM &) {
        XMFLOAT3 v;
        pop_xmfloat3(sp, v);
        auto trans_component = pop_wo_handle(sp);
        wbnd::transform_translate(trans_component, v);
}); 


