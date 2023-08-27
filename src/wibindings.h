#pragma once
// Module that handles the WickedEngine details of functions exposed to Lobster
// code.

namespace wbnd
{
    wo_handle new_scene();
    wo_handle global_scene();
    wo_handle load_model(wo_handle dest_scene, std::string const &filename, bool attach_to_entity);
    wo_handle create_entity();
    wo_handle create_entity_name_component(wo_handle scene, wo_handle entity);
    void nc_set_name(wo_handle name_comp, std::string_view const &name);
    wo_handle entity_find_by_name(wo_handle scene, std::string_view const &name, wo_handle ancestor);
    void backlog(int level, std::string_view const &msg);
}

