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


namespace
{
    const int64_t GLOBAL_SCENE_IX = -1;
    // Array of scenes created by Lobster code.  Indexed by wo_handle.name.
    vector<wi::scene::Scene*> g_scenes;
}

namespace wbnd
{
    template<typename T>
    bool handle_array_check(vector<T> arr, int64_t ix)
    {
        return ix >= 0 && ix < (int64_t)arr.size();
    }
    void handle_check(wo_handle h, WOKIND kind)
    {
        if (h.kind != kind) {
            printf("BAD HANDLE: expecting %d, but got %d\n",
                   (int)kind, (int)h.kind);
            dump_lobster_stack();
            fflush(stdout);
            abort();
        }
        switch (kind) {
        case WK_SCENE:
            if (h.name != GLOBAL_SCENE_IX && !handle_array_check(g_scenes, h.name)) {
                printf("Bad scene handle: %d\n", (int)h.name);
                dump_lobster_stack(); 
                fflush(stdout);
                abort();
            }
        }
    }

    wi::scene::Scene& scene_for_ix(int64_t i)
    {
        if (i == GLOBAL_SCENE_IX) {
            return wi::scene::GetScene();
        } else {
            return *g_scenes[i];
        }
    }

    wo_handle new_scene()
    {
        auto ix = g_scenes.size();
        g_scenes.push_back(new wi::scene::Scene());
        return wo_handle{WK_SCENE, (int64_t)ix};
    }

    wo_handle global_scene()
    {
        return wo_handle{WK_SCENE, GLOBAL_SCENE_IX};
    }

    wo_handle load_model(wo_handle dest_scene, std::string const& filename, bool attach_to_entity)
    {
        handle_check(dest_scene, WK_SCENE);
        auto ent = wi::scene::LoadModel(scene_for_ix(dest_scene.name), filename,
                                        XMMatrixIdentity(), attach_to_entity);
        if (ent == wi::ecs::INVALID_ENTITY) {
            return {-WK_ENTITY, 0};
        }
        return {WK_ENTITY, (int64_t)ent};
    }
}

