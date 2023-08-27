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
        case WK_NAME_COMP:
            if (h.name == 0) {
                printf("Null handle pointer, kind=%d\n", (int)h.kind);
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
        return {WK_ENTITY, (int64_t)ent};
    }

    wo_handle create_entity()
    {
        return {WK_ENTITY, wi::ecs::CreateEntity()};
    }

    wo_handle create_entity_name_component(wo_handle scene, wo_handle entity)
    {
        handle_check(scene, WK_SCENE);
        handle_check(entity, WK_ENTITY);
        auto sp = scene_for_ix(scene.name);
        auto &comp = sp->names.Create(entity.name);
        return {WK_NAME_COMP, reinterpret_cast<int64_t>(&comp)};
    }

    void nc_set_name(wo_handle name_comp, std::string_view const &name)
    {
        handle_check(name_comp, WK_NAME_COMP);
        auto np = reinterpret_cast<wi::scene::NameComponent *>(name_comp.name);
        np->name = name;
    }

    wo_handle entity_find_by_name(wo_handle scene, std::string_view const &name, wo_handle ancestor)
    {
        handle_check(scene, WK_SCENE);
        handle_check(ancestor, WK_ENTITY);
        return {WK_ENTITY, scene_for_ix(scene.name)->Entity_FindByName(std::string(name), 
                                                                       ancestor.name)};
    }
}

