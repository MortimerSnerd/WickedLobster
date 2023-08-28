// GENERATED for inclusion in wibindings.h by tools/bindgen.lobster, do not edit
void transform_clear(wo_handle const& trans_comp);
wo_handle get_transform_component(wo_handle const& scene, wo_handle const& entity);
wo_handle new_scene();
wo_handle global_scene();
wo_handle load_model(wo_handle const& scene, std::string_view const& fname, bool attach);
wo_handle create_entity();
wo_handle create_name_component(wo_handle const& scene, wo_handle const& entity);
void nc_set_name(wo_handle const& name_comp, std::string_view const& name);
wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const& name, wo_handle const& ancestor_entity);
void backlog(int64_t level, std::string_view const& msg);
wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity);
wo_handle create_transform_component(wo_handle const& scene, wo_handle const& entity);
wo_handle get_renderpath3d();
void renderpath3d_set_camera(wo_handle const& rpath, wo_handle const& cam_component);
void transform_translate(wo_handle const& trans_component, XMFLOAT3 const& v);
