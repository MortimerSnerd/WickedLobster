#pragma once
// Module that handles the WickedEngine details of functions exposed to Lobster
// code.

namespace wi
{
    // Fwd decls - we can't include real Wicked Engine headers here.
    class RenderPath3D;

}
class GameApplication;

namespace wbnd
{
    // Include generated boilerplate decls from tools/bindgen.lobster
    #include "wibindings.inl"

    // Needs to be called before the lobster VM is started.
    void set_3d_render_path(wi::RenderPath3D *rp);
    void set_game_app(GameApplication *app);

    // Used by AlienResource to delete a arbitrary alien pointer.
    void delete_alien(wo_handle const &h);
}

