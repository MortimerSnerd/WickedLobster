#include "pch.h"
// wiMath is safe and doesn't cause namespace problems with Lobster.
#include "wiMath.h"
#include "lobutil.h"
#include "wibindings.h"
#include "WickedEngine.h"
#include "wiScene.h"
#include "wiInput.h"

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

    wi::scene::Scene* scene_ptr(wo_handle const &h)
    {
        handle_check(h, WK_SCENE);
        return reinterpret_cast<wi::scene::Scene *>(h.name);
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
        auto ent = wi::scene::LoadModel(*scene_ptr(dest_scene), std::string(filename),
                                        XMMatrixIdentity(), attach_to_entity);
        return {WK_ENTITY, (int64_t)ent};
    }

    wo_handle create_entity()
    {
        return {WK_ENTITY, wi::ecs::CreateEntity()};
    }

    wo_handle create_name_component(wo_handle const& scene, wo_handle const& entity)
    {
        handle_check(entity, WK_ENTITY);
        auto sp = scene_ptr(scene);
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
        handle_check(ancestor, WK_ENTITY);
        return {WK_ENTITY, scene_ptr(scene)->Entity_FindByName(std::string(name), 
                                                               ancestor.name)};
    }

    void backlog(int64_t level, std::string_view const &msg)
    {
        wi::backlog::post(std::string(msg), (wi::backlog::LogLevel)level);
    }

    wi::scene::Scene* create_component_common(wo_handle const &scene, 
                                              wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        valid_entity(entity);
        return scene_ptr(scene);
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

    wi::scene::CameraComponent* cam_ptr(wo_handle const &h)
    {
        handle_check(h, WK_CAMERA_COMP);
        return reinterpret_cast<wi::scene::CameraComponent *>(h.name);
    }

    void renderpath3d_set_camera(wo_handle const &rpath, wo_handle const &cam_component)
    {
        handle_check(rpath, WK_RENDERPATH3);
        auto rp = reinterpret_cast<wi::RenderPath3D *>(rpath.name);
        auto cc = cam_ptr(cam_component);
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

    wi::scene::TransformComponent* tc_ptr(wo_handle const &h)
    {
        handle_check(h, WK_TRANSFORM_COMP);
        return reinterpret_cast<wi::scene::TransformComponent *>(h.name);
    }

    void transform_clear(wo_handle const &trans)
    {
        auto tp = tc_ptr(trans);
        tp->ClearTransform();
    }

    void transform_rotate(wo_handle const &trans_component, XMFLOAT4 const &quat)
    {
        auto tp = tc_ptr(trans_component);
        tp->Rotate(quat);
    }

    XMFLOAT3 transform_position(wo_handle const &tcomp)
    {
        auto tp = tc_ptr(tcomp);
        return tp->GetPosition();
    }

    XMFLOAT4 transform_rotation(wo_handle const &tcomp)
    {
        auto tp = tc_ptr(tcomp);
        return tp->GetRotation();
    }

    void transform_update_transform(wo_handle const &tcomp)
    {
        auto tp = tc_ptr(tcomp);
        tp->UpdateTransform();
    }

    void transform_rotate_roll_pitch_yaw(wo_handle const &tcomp, XMFLOAT3 const &angles)
    {
        auto tp = tc_ptr(tcomp);
        tp->RotateRollPitchYaw(angles);
    }

    void transform_scale(wo_handle const &tcomp, XMFLOAT3 const &scale)
    {
        auto tp = tc_ptr(tcomp);
        tp->Scale(scale);
    }

    void transform_lerp(wo_handle const &tcomp, wo_handle const &a, wo_handle const &b, float t)
    {
        auto tp = tc_ptr(tcomp);
        auto ap = tc_ptr(a);
        auto bp = tc_ptr(b);
        tp->Lerp(*ap, *bp, t);
    }

    float camera_fov(wo_handle const &tcomp)
    {
        return cam_ptr(tcomp)->fov;
    }

    void camera_set_fov(wo_handle const &tcomp, float fov)
    {
        cam_ptr(tcomp)->fov = fov;
    }

    XMFLOAT2 camera_get_dims(wo_handle const &tcomp)
    {
        auto cp = cam_ptr(tcomp);
        return {cp->width, cp->height};
    }

    void camera_set_dims(wo_handle const &tcomp, XMFLOAT2 const &dims)
    {
        auto cp = cam_ptr(tcomp);
        cp->width = dims.x;
        cp->height = dims.y;
    }

    float camera_znear(wo_handle const &tcomp)
    {
        return cam_ptr(tcomp)->zNearP;
    }

    void camera_set_znear(wo_handle const &tcomp, float znear)
    {
        cam_ptr(tcomp)->zNearP = znear;
    }

    float camera_zfar(wo_handle const &tcomp)
    {
        return cam_ptr(tcomp)->zFarP;
    }

    void camera_set_zfar(wo_handle const &tcomp, float zfar)
    {
        cam_ptr(tcomp)->zFarP = zfar;
    }

    float camera_focal_length(wo_handle const &tcomp)
    {
        return cam_ptr(tcomp)->focal_length;
    }

    void camera_set_focal_length(wo_handle const &tcomp, float l)
    {
        cam_ptr(tcomp)->focal_length = l;
    }

    void camera_update(wo_handle const &tcomp)
    {
        cam_ptr(tcomp)->UpdateCamera();
    }

    wo_handle get_camera_component(wo_handle const &scene, wo_handle const &ent)
    {
        auto sp = scene_ptr(scene);
        return {WK_CAMERA_COMP,  reinterpret_cast<int64_t>(sp->cameras.GetComponent(ent.name))};
    }

    bool input_down(int64_t button, int64_t playerindex)
    {
        return wi::input::Down((wi::input::BUTTON)button, playerindex);
    }

    bool input_press(int64_t button, int64_t playerindex)
    {
        return wi::input::Press((wi::input::BUTTON)button, playerindex);
    }

    bool input_hold(int64_t button, int64_t frames, bool continuous, int64_t playerindex)
    {
        return wi::input::Hold((wi::input::BUTTON)button, frames, continuous, playerindex);
    }

    XMFLOAT4 input_get_pointer()
    {
        return wi::input::GetPointer();
    }

    void input_set_pointer(XMFLOAT4 const &props)
    {
        wi::input::SetPointer(props);
    }

    void input_hide_pointer(bool value)
    {
        wi::input::HidePointer(value);
    }

    XMFLOAT4 input_get_analog(int64_t axis, int64_t playerindex)
    {
        return wi::input::GetAnalog((wi::input::GAMEPAD_ANALOG)axis, playerindex);
    }
}

