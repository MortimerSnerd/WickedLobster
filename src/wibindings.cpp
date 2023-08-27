#include "pch.h"
#include "lobutil.h"
#include "wibindings.h"
#include "WickedEngine.h"
#include "wiScene.h"

// NB for arrays of WI objects that are indexed by wo_handle, when the object
// is deleted, a nullptr is put in that array slot.  Which will catch any 
// references after delete from the Lobster side.  Cleaning out nulls is 
// deferred to large events where it makes sense to clear everything out, 
// like when loading a new level.

using namespace std;


namespace wbnd
{
    void handle_check(wo_handle h, WOKIND kind)
    {
        if (h.kind != kind) {
            printf("BAD HANDLE: expecting %d, but got %d\n",
                   (int)kind, (int)h.kind);
            dump_lobster_stack();
            fflush(stdout);
            abort();
        }
        switch (h.kind) {
        case WK_SCENE:
            if (h.name == 0) {
                printf("Null scene pointer.");
                dump_lobster_stack();
                fflush(stdout);
                abort();
            }
        }
    }

    wi::scene::Scene* scene_for_ix(int64_t i)
    {
        return reinterpret_cast<wi::scene::Scene *>(i);
    }

    wo_handle new_scene()
    {
        // We create scenes, or return pointers to a global scene, neither
        // which will move.  So it's safe to use the address as the key.
        auto sc = new wi::scene::Scene();
        return {WK_SCENE, reinterpret_cast<int64_t>(sc)};
    }

    wo_handle global_scene()
    {
        return wo_handle{WK_SCENE, reinterpret_cast<int64_t>(&wi::scene::GetScene())};
    }

    wo_handle load_model(wo_handle dest_scene, std::string const& filename, bool attach_to_entity)
    {
        handle_check(dest_scene, WK_SCENE);
        auto ent = wi::scene::LoadModel(*scene_for_ix(dest_scene.name), filename,
                                        XMMatrixIdentity(), attach_to_entity);
        if (ent == wi::ecs::INVALID_ENTITY) {
            return {-WK_ENTITY, 0};
        }
        return {WK_ENTITY, (int64_t)ent};
    }

    wo_handle create_entity()
    {
        return {WK_ENTITY, wi::ecs::CreateEntity()};
    }
}

