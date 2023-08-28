#include "pch.h"
// wiMath is safe and doesn't cause namespace problems with Lobster.
#include "wiMath.h"
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
    wi::RenderPath3D *render_path_3d = nullptr;
}

namespace wbnd
{
    void handle_check(wo_handle const& h, WOKIND kind)
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
        case WK_CAMERA_COMP:
        case WK_TRANSFORM_COMP:
            if (h.name == 0) {
                printf("Null handle pointer, kind=%d\n", (int)h.kind);
                dump_lobster_stack();
                fflush(stdout);
                abort();
            }
        }
    }

    void valid_entity(wo_handle const &h)
    {
        if (h.name == wi::ecs::INVALID_ENTITY) {
            wi::backlog::post("invalid entity", wi::backlog::LogLevel::Error);
            dump_lobster_stack();
            abort();
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

    wo_handle load_model(wo_handle const& dest_scene, std::string_view const& filename, bool attach_to_entity)
    {
        handle_check(dest_scene, WK_SCENE);
        auto ent = wi::scene::LoadModel(*scene_for_ix(dest_scene.name), std::string(filename),
                                        XMMatrixIdentity(), attach_to_entity);
        return {WK_ENTITY, (int64_t)ent};
    }

    wo_handle create_entity()
    {
        return {WK_ENTITY, wi::ecs::CreateEntity()};
    }

    wo_handle create_name_component(wo_handle const& scene, wo_handle const& entity)
    {
        handle_check(scene, WK_SCENE);
        handle_check(entity, WK_ENTITY);
        auto sp = scene_for_ix(scene.name);
        auto &comp = sp->names.Create(entity.name);
        return {WK_NAME_COMP, reinterpret_cast<int64_t>(&comp)};
    }

    void nc_set_name(wo_handle const& name_comp, std::string_view const &name)
    {
        handle_check(name_comp, WK_NAME_COMP);
        auto np = reinterpret_cast<wi::scene::NameComponent *>(name_comp.name);
        np->name = name;
    }

    wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const &name, wo_handle const& ancestor)
    {
        handle_check(scene, WK_SCENE);
        handle_check(ancestor, WK_ENTITY);
        return {WK_ENTITY, scene_for_ix(scene.name)->Entity_FindByName(std::string(name), 
                                                                       ancestor.name)};
    }

    void backlog(int64_t level, std::string_view const &msg)
    {
        wi::backlog::post(std::string(msg), (wi::backlog::LogLevel)level);
    }

    wi::scene::Scene* create_component_common(wo_handle const &scene, 
                                              wo_handle const &entity)
    {
        handle_check(scene, WK_SCENE);
        handle_check(entity, WK_ENTITY);
        valid_entity(entity);
        return scene_for_ix(scene.name);
    }

    wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity)
    {
        auto sp = create_component_common(scene, entity);
        auto &comp = sp->cameras.Create(entity.name);
        return {WK_CAMERA_COMP, reinterpret_cast<int64_t>(&comp)};
    }

    wo_handle create_transform_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = create_component_common(scene, entity);
        auto &comp = sp->transforms.Create(entity.name);
        return {WK_TRANSFORM_COMP, reinterpret_cast<int64_t>(&comp)};
    }

    void set_3d_render_path(wi::RenderPath3D *rp)
    {
        render_path_3d = rp;
    }

    wo_handle get_renderpath3d()
    {
        return {WK_RENDERPATH3, reinterpret_cast<int64_t>(render_path_3d)};
    }

    void renderpath3d_set_camera(wo_handle const &rpath, wo_handle const &cam_component)
    {
        handle_check(rpath, WK_RENDERPATH3);
        handle_check(cam_component, WK_CAMERA_COMP);
        auto rp = reinterpret_cast<wi::RenderPath3D *>(rpath.name);
        auto cc = reinterpret_cast<wi::scene::CameraComponent *>(cam_component.name);
        rp->camera = cc;
    }

    void transform_translate(wo_handle const &trans, const XMFLOAT3 &value)
    {
        handle_check(trans, WK_TRANSFORM_COMP);
        auto tp = reinterpret_cast<wi::scene::TransformComponent *>(trans.name);
        tp->Translate(value);
    }

    wo_handle get_transform_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = create_component_common(scene, entity);
        return {WK_TRANSFORM_COMP, reinterpret_cast<int64_t>(sp->transforms.GetComponent(entity.name))};
    }

    void transform_clear(wo_handle const &trans)
    {
        handle_check(trans, WK_TRANSFORM_COMP);
        auto tp = reinterpret_cast<wi::scene::TransformComponent *>(trans.name);
        tp->ClearTransform();
    }
}

