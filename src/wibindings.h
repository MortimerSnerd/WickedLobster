#pragma once
// Module that handles the WickedEngine details of functions exposed to Lobster
// code.

namespace wi
{
    // Fwd decls - we can't include real Wicked Engine headers here.
    class RenderPath3D;

}

namespace wbnd
{
    wo_handle new_scene();
    wo_handle global_scene();
    wo_handle load_model(wo_handle const& dest_scene, std::string const &filename, bool attach_to_entity);
    wo_handle create_entity();
    wo_handle create_entity_name_component(wo_handle const& scene, wo_handle const& entity);
    void nc_set_name(wo_handle const& name_comp, std::string_view const &name);
    wo_handle entity_find_by_name(wo_handle const& scene, std::string_view const &name, wo_handle ancestor);
    void backlog(int level, std::string_view const &msg);
    wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity);
    wo_handle create_transform_component(wo_handle const &scene, wo_handle const &entity);
    wo_handle get_3d_renderpath();
    void renderpath3d_set_camera(wo_handle const &rpath, wo_handle const &cam_component);
    void transform_translate(wo_handle const &trans, const XMFLOAT3 &value);
    wo_handle get_transform_component(wo_handle const &scene, wo_handle const &entity);
    void transform_clear(wo_handle const &trans);

    // Needs to be called before the lobster VM is started.
    void set_3d_render_path(wi::RenderPath3D *rp);
}

