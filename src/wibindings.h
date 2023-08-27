#pragma once
// Module that handles the WickedEngine details of functions exposed to Lobster
// code.

namespace wbnd
{
    wo_handle new_scene();
    wo_handle global_scene();
    wo_handle load_model(wo_handle dest_scene, std::string const &filename, bool attach_to_entity);
    wo_handle create_entity();
}

