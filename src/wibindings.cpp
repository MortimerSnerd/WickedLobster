#include "pch.h"
// wiMath is safe and doesn't cause namespace problems with Lobster.
#include "wiMath.h"
#include "DirectXMath.h"
#include "lobutil.h"
#include "wibindings.h"
#include "WickedEngine.h"
#include "GameApplication.h"
#include "wiScene.h"
#include "wiInput.h"

using namespace std;

extern void break_impl();

namespace
{
    wi::RenderPath3D *render_path_3d = nullptr;
    GameApplication *game_app = nullptr;
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
        case WK_TIMER:
        case WK_FONT_PARAMS:
        case WK_SPRITE_FONT:
        case WK_HUMANOID:
        case WK_MATRIX:
        case WK_COLLIDER:
        case WK_ANIMATION_COMP:
        case WK_SPHERE:
        case WK_RIGIDBODY:
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

    void delete_scene(wo_handle const &scene)
    {
        if (scene.name == 0) return;
        auto sp = scene_ptr(scene);
        // No deleting global scene.
        if (sp == &wi::scene::GetScene()) return;
        delete sp;
    }

    void scene_merge(wo_handle const &dest, wo_handle const &src)
    {
        auto dp = scene_ptr(dest);
        auto sp = scene_ptr(src);
        dp->Merge(*sp);
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

    wi::scene::NameComponent* name_ptr(wo_handle const &h)
    {
        handle_check(h, WK_NAME_COMP);
        return reinterpret_cast<wi::scene::NameComponent *>(h.name);
    }

    void nc_set_name(wo_handle const& name_comp, std::string_view const &name)
    {
        auto np = name_ptr(name_comp);
        np->name = name;
    }

    wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const &name, wo_handle const& ancestor)
    {
        handle_check(ancestor, WK_ENTITY);
        return {WK_ENTITY, scene_ptr(scene)->Entity_FindByName(std::string(name), 
                                                               ancestor.name)};
    }

    void backlog(int32_t level, std::string_view const &msg)
    {
        wi::backlog::post(std::string(msg), (wi::backlog::LogLevel)level);
    }

    bool is_backlog_active()
    {
        return wi::backlog::isActive();
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

    wo_handle create_transform()
    {
        return {WK_TRANSFORM_COMP, reinterpret_cast<int64_t>(new wi::scene::TransformComponent)};
    }

    wi::scene::TransformComponent* tc_ptr(wo_handle const &h)
    {
        handle_check(h, WK_TRANSFORM_COMP);
        return reinterpret_cast<wi::scene::TransformComponent *>(h.name);
    }
    
    void delete_transform(wo_handle const &trans)
    {
        delete tc_ptr(trans);
    }

    void set_3d_render_path(wi::RenderPath3D *rp)
    {
        render_path_3d = rp;
    }

    void set_game_app(GameApplication *app)
    {
        game_app = app;
    }

    wo_handle get_renderpath3d()
    {
        return {WK_RENDERPATH3, reinterpret_cast<int64_t>(render_path_3d)};
    }

    float get_fixed_update_rate()
    {
        if (game_app) {
            return game_app->getTargetFrameRate();
        } else {
            return 60.0f;
        }
    }

    wi::scene::CameraComponent* cam_ptr(wo_handle const &h)
    {
        handle_check(h, WK_CAMERA_COMP);
        return reinterpret_cast<wi::scene::CameraComponent *>(h.name);
    }

    wi::RenderPath3D* rpath_ptr(wo_handle const &h)
    {
        handle_check(h, WK_RENDERPATH3);
        return reinterpret_cast<wi::RenderPath3D *>(h.name);
    }
    void renderpath3d_set_camera(wo_handle const &rpath, wo_handle const &cam_component)
    {
        auto rp = rpath_ptr(rpath);
        auto cc = cam_ptr(cam_component);
        rp->camera = cc;
    }

    XMINT2 get_renderpath_physical_dims(wo_handle const &path)
    {
        auto pp = rpath_ptr(path);
        return {(int32_t)pp->GetPhysicalWidth(), (int32_t)pp->GetPhysicalHeight()};
    }

    XMFLOAT2 get_renderpath_logical_dims(wo_handle const &path)
    {
        auto pp = rpath_ptr(path);
        return {pp->GetLogicalWidth(), pp->GetLogicalHeight()};
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

    XMFLOAT3 decompose_transform(wo_handle const &tcomp, XMFLOAT4 &retval2, XMFLOAT3 &retval3)
    {
        XMVECTOR S, R, T;
        XMFLOAT3 rv;
        XMMatrixDecompose(&S, &R, &T, XMLoadFloat4x4(&tc_ptr(tcomp)->world));
        XMStoreFloat3(&rv, T);
        XMStoreFloat4(&retval2, R);
        XMStoreFloat3(&retval3, S);
        return rv;
    }

    XMFLOAT3 transform_scaling(wo_handle const &tcomp)
    {
        return tc_ptr(tcomp)->GetScale();
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

    bool input_down(int32_t button, int32_t playerindex)
    {
        return wi::input::Down((wi::input::BUTTON)button, playerindex);
    }

    bool input_press(int32_t button, int32_t playerindex)
    {
        return wi::input::Press((wi::input::BUTTON)button, playerindex);
    }

    bool input_hold(int32_t button, int32_t frames, bool continuous, int32_t playerindex)
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

    XMFLOAT4 input_get_analog(int32_t axis, int32_t playerindex)
    {
        return wi::input::GetAnalog((wi::input::GAMEPAD_ANALOG)axis, playerindex);
    }

    int32_t entity_names_count(wo_handle const &scene)
    {
        auto sp = scene_ptr(scene);
        return sp->names.GetCount();
    }

    wo_handle entity_names_get(wo_handle const &scene, int32_t n)
    {
        auto sp = scene_ptr(scene);
        return {WK_ENTITY,  sp->names.GetEntity(n)};
    }

    std::string_view nc_get_name(wo_handle const &name_comp)
    {
        auto np = name_ptr(name_comp);
        return np->name;
    }

    wo_handle get_name_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = scene_ptr(scene);
        return {WK_NAME_COMP,  reinterpret_cast<int64_t>(sp->names.GetComponent(entity.name))};
    }

    int32_t get_camera_count(wo_handle const &scene)
    {
        auto sp = scene_ptr(scene);
        return sp->cameras.GetCount();
    }

    wo_handle get_camera_entity(wo_handle const &scene, int32_t n)
    {
        auto sp = scene_ptr(scene);
        return {WK_CAMERA_COMP, sp->cameras.GetEntity(n)};
    }

    void draw_debug_text(std::string_view const &text, XMFLOAT3 const &pos, int32_t flags, XMFLOAT4 const &color, float scaling)
    {
        wi::renderer::DebugTextParams p;
        p.position = pos;
        p.color = color;
        p.scaling = scaling;
        p.flags = flags;
        wi::renderer::DrawDebugText(text.data(), p);
    }

    wi::Timer* timer_ptr(wo_handle const &h)
    {
        handle_check(h, WK_TIMER);
        return reinterpret_cast<wi::Timer *>(h.name);
    }

    wo_handle create_timer()
    {
        return {WK_TIMER, reinterpret_cast<int64_t>(new wi::Timer())};
    }

    void delete_timer(wo_handle const &timer)
    {
        if (timer.name == 0) return;
        auto tp = timer_ptr(timer);
        delete tp;
    }

    void timer_record(wo_handle const &timer)
    {
        timer_ptr(timer)->record();
    }

    double timer_elapsed_seconds(wo_handle const &time)
    {
        return timer_ptr(time)->elapsed_seconds();
    }

    double timer_elapsed(wo_handle const &timer)
    {
        return timer_ptr(timer)->elapsed();
    }

    wi::font::Params* fparams_ptr(wo_handle const &h)
    {
        handle_check(h, WK_FONT_PARAMS);
        return reinterpret_cast<wi::font::Params *>(h.name);
    }

    wo_handle create_font_params()
    {
        return {WK_FONT_PARAMS, reinterpret_cast<int64_t>(new wi::font::Params())};
    }

    void delete_font_params(wo_handle const &font_params)
    {
        if (font_params.name == 0) return;
        delete fparams_ptr(font_params);
    }

    //TODO questionable as to whether we should be messing with the z coordinate.
    void set_font_params_position(wo_handle const &font_params, XMFLOAT3 const &v)
    {
        fparams_ptr(font_params)->position = v;
    }

    XMFLOAT3 get_font_params_position(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->position;
    }

    void set_font_params_size(wo_handle const &font_params, int32_t v)
    {
        fparams_ptr(font_params)->size = v;
    }

    int32_t get_font_params_size(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->size;
    }

    void set_font_params_scaling(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->scaling = v;
    }

    float get_font_params_scaling(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->scaling;
    }

    void set_font_params_rotation(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->rotation = v;
    }

    float get_font_params_rotation(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->rotation;
    }

    void set_font_params_spacing_x(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->spacingX = v;
    }

    float get_font_params_spacing_x(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->spacingX;
    }

    void set_font_params_spacing_y(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->spacingY = v;
    }

    float get_font_params_spacing_y(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->spacingY;
    }

    void set_font_params_h_align(wo_handle const &font_params, int32_t v)
    {
        fparams_ptr(font_params)->h_align = (wi::font::Alignment)v;
    }

    int32_t get_font_params_h_align(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->h_align;
    }

    void set_font_params_v_align(wo_handle const &font_params, int32_t v)
    {
        fparams_ptr(font_params)->v_align = (wi::font::Alignment)v;
    }

    int32_t get_font_params_v_align(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->v_align;
    }

    void set_font_params_color(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        fparams_ptr(font_params)->color = wi::Color::fromFloat4(v);
    }

    XMFLOAT4 get_font_params_color(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->color.toFloat4();
    }

    void set_font_params_shadow_color(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        fparams_ptr(font_params)->shadowColor = wi::Color::fromFloat4(v);
    }

    XMFLOAT4 get_font_params_shadow_color(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->shadowColor.toFloat4();
    }

    void set_font_params_h_wrap(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->h_wrap = v;
    }

    float get_font_params_h_wrap(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->h_wrap;
    }

    void set_font_params_style(wo_handle const &font_params, int32_t v)
    {
        fparams_ptr(font_params)->style = v;
    }

    int32_t get_font_params_style(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->style;
    }

    void set_font_params_softness(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->softness = v;
    }

    float get_font_params_softness(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->softness;
    }

    void set_font_params_bolden(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->bolden = v;
    }

    float get_font_params_bolden(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->bolden;
    }

    void set_font_params_shadow_softness(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->shadow_softness = v;
    }

    float get_font_params_shadow_softness(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->shadow_softness;
    }

    void set_font_params_shadow_bolden(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->shadow_bolden = v;
    }

    float get_font_params_shadow_bolden(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->shadow_bolden;
    }

    void set_font_params_shadow_offset_x(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->shadow_offset_x = v;
    }

    float get_font_params_shadow_offset_x(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->shadow_offset_x;
    }

    void set_font_params_shadow_offset_y(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->shadow_offset_y = v;
    }

    float get_font_params_shadow_offset_y(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->shadow_offset_y;
    }

    void set_font_params_cursor(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        // We pack this into a float4 for lobster.
        fparams_ptr(font_params)->cursor = {XMFLOAT2{v.x, v.y}, 
                                            XMFLOAT2{v.z, v.w}};
    }

    XMFLOAT4 get_font_params_cursor(wo_handle const &font_params)
    {
        XMFLOAT4 rv;
        auto fp = fparams_ptr(font_params);

        rv.x = fp->cursor.position.x;
        rv.y = fp->cursor.position.y;
        rv.z = fp->cursor.size.x;
        rv.w = fp->cursor.size.y;
        return rv;
    }

    void set_font_params_hdr_scaling(wo_handle const &font_params, float v)
    {
        fparams_ptr(font_params)->hdr_scaling = v;
    }

    float get_font_params_hdr_scaling(wo_handle const &font_params)
    {
        return fparams_ptr(font_params)->hdr_scaling;
    }

    wi::SpriteFont* sf_ptr(wo_handle const &h)
    {
        handle_check(h, WK_SPRITE_FONT);
        return reinterpret_cast<wi::SpriteFont *>(h.name);
    }

    wo_handle create_sprite_font()
    {
        return {WK_SPRITE_FONT, reinterpret_cast<int64_t>(new wi::SpriteFont())};
    }

    void sprite_font_set_params(wo_handle const &font, wo_handle const &font_params)
    {
        sf_ptr(font)->params = *fparams_ptr(font_params);
    }

    void delete_sprite_font(wo_handle const &font)
    {
        if (font.name == 0) return;
        delete sf_ptr(font);
    }

    void sprite_font_set_hidden(wo_handle const &font, bool value)
    {
        sf_ptr(font)->SetHidden(value);
    }

    XMFLOAT2 sprite_font_text_size(wo_handle const &font)
    {
        return sf_ptr(font)->TextSize();
    }

    void sprite_font_set_text(wo_handle const &font, std::string_view const &txt)
    {
        sf_ptr(font)->SetText(std::string(txt));
    }

    std::string_view sprite_font_get_text(wo_handle const &font)
    {
        return sf_ptr(font)->GetTextA();
    }

    void renderpath_add_font(wo_handle const &path, wo_handle const &sprite_font, std::string_view const &layer)
    {
        auto rp = rpath_ptr(path);
        auto rp2 = dynamic_cast<wi::RenderPath2D *>(rp);
        if (rp2) {
            rp2->AddFont(sf_ptr(sprite_font), std::string(layer)); 
        }
    }

    void renderpath_remove_font(wo_handle const &path, wo_handle const &sprite_font)
    {
        rpath_ptr(path)->RemoveFont(sf_ptr(sprite_font));
    }

    void renderpath_clear_fonts(wo_handle const &path)
    {
        rpath_ptr(path)->ClearFonts();
    }

    int32_t renderpath_font_order(wo_handle const &path, wo_handle const &sprite_font)
    {
        return rpath_ptr(path)->GetFontOrder(sf_ptr(sprite_font));
    }

    void renderpath_set_font_order(wo_handle const &path, wo_handle const &sprite_font, int32_t order)
    {
        rpath_ptr(path)->SetFontOrder(sf_ptr(sprite_font), order);
    }

    wi::scene::HumanoidComponent* hum_ptr(wo_handle const &h)
    {
        handle_check(h, WK_HUMANOID);
        return reinterpret_cast<wi::scene::HumanoidComponent *>(h.name);
    }

    wo_handle create_humanoid_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_HUMANOID, reinterpret_cast<int64_t>(&scene_ptr(scene)->humanoids.Create(entity.name))};
    }

    wo_handle get_humanoid_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_HUMANOID, reinterpret_cast<int64_t>(scene_ptr(scene)->humanoids.GetComponent(entity.name))};
    }

    int32_t entity_humanoid_count(wo_handle const &scene)
    {
        return (int32_t)scene_ptr(scene)->humanoids.GetCount();
    }

    wo_handle entity_humanoid_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, scene_ptr(scene)->humanoids.GetEntity((size_t)n)};
    }

    void set_humanoid_default_look_direction(wo_handle const &humanoid, XMFLOAT3 const &v)
    {
        hum_ptr(humanoid)->default_look_direction = v;
    }

    XMFLOAT3 get_humanoid_default_look_direction(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->default_look_direction;
    }

    void set_humanoid_head_rotation_max(wo_handle const &humanoid, XMFLOAT2 const &v)
    {
        hum_ptr(humanoid)->head_rotation_max = v;
    }

    XMFLOAT2 get_humanoid_head_rotation_max(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->head_rotation_max;
    }

    void set_humanoid_head_rotation_speed(wo_handle const &humanoid, float v)
    {
        hum_ptr(humanoid)->head_rotation_speed = v;
    }

    float get_humanoid_head_rotation_speed(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->head_rotation_speed;
    }

    void set_humanoid_eye_rotation_max(wo_handle const &humanoid, XMFLOAT2 const &v)
    {
        hum_ptr(humanoid)->eye_rotation_max = v;
    }

    XMFLOAT2 get_humanoid_eye_rotation_max(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->eye_rotation_max;
    }

    void set_humanoid_eye_rotation_speed(wo_handle const &humanoid, float v)
    {
        hum_ptr(humanoid)->eye_rotation_speed = v;
    }

    float get_humanoid_eye_rotation_speed(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->eye_rotation_speed;
    }

    void set_humanoid_look_at(wo_handle const &humanoid, XMFLOAT3 const &v)
    {
        hum_ptr(humanoid)->lookAt = v;
    }

    XMFLOAT3 get_humanoid_look_at(wo_handle const &humanoid)
    {
        return hum_ptr(humanoid)->lookAt;
    }

    int32_t humanoid_bone_count(wo_handle const &hum)
    {
        return (int32_t)wi::scene::HumanoidComponent::HumanoidBone::Count;
    }

    wo_handle humanoid_bone(wo_handle const &hum, int32_t i)
    {
        return {WK_ENTITY, hum_ptr(hum)->bones[i]};
    }

    bool humanoid_is_lookat_enabled(wo_handle const &hum)
    {
        return hum_ptr(hum)->IsLookAtEnabled();
    }

    void humanoid_set_lookat_enabled(wo_handle const &hum, bool v)
    {
        hum_ptr(hum)->SetLookAtEnabled(v);
    }

    wi::scene::LayerComponent* layer_ptr(wo_handle const &h)
    {
        handle_check(h, WK_LAYER);
        return reinterpret_cast<wi::scene::LayerComponent *>(h.name);
    }

    wo_handle create_layer_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_LAYER, reinterpret_cast<int64_t>(&scene_ptr(scene)->layers.Create(entity.name))};
    }

    wo_handle get_layer_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_LAYER, reinterpret_cast<int64_t>(scene_ptr(scene)->layers.GetComponent(entity.name))};
    }

    int32_t entity_layer_count(wo_handle const &scene)
    {
        return (int32_t)scene_ptr(scene)->layers.GetCount();
    }

    wo_handle entity_layer_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, scene_ptr(scene)->layers.GetEntity(n)};
    }

    void set_layer_mask(wo_handle const &layer, int32_t v)
    {
        layer_ptr(layer)->layerMask = v;
    }

    int32_t get_layer_mask(wo_handle const &layer)
    {
        return layer_ptr(layer)->layerMask;
    }

    void set_layer_propagation_mask(wo_handle const &layer, int32_t v)
    {
        layer_ptr(layer)->propagationMask = v;
    }

    int32_t get_layer_propagation_mask(wo_handle const &layer)
    {
        return layer_ptr(layer)->propagationMask;
    }

    bool is_descendant_entity(wo_handle const &scene, wo_handle const &entity, wo_handle const &ancestor)
    {
        handle_check(entity, WK_ENTITY);
        handle_check(ancestor, WK_ENTITY);
        return scene_ptr(scene)->Entity_IsDescendant(entity.name, ancestor.name);
    }

    void remove_entity(wo_handle const &scene, wo_handle const &entity, bool recursive)
    {
        handle_check(entity, WK_ENTITY);
        scene_ptr(scene)->Entity_Remove(entity.name, recursive);
    }

    wo_handle duplicate_entity(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_ENTITY, scene_ptr(scene)->Entity_Duplicate(entity.name)};
    }

    wi::scene::ColliderComponent* coll_ptr(wo_handle const &collider)
    {
        handle_check(collider, WK_COLLIDER);
        return reinterpret_cast<wi::scene::ColliderComponent *>(collider.name);
    }

    void set_collider_shape(wo_handle const &collider, int32_t v)
    {
        coll_ptr(collider)->shape = (wi::scene::ColliderComponent::Shape)v;
    }

    int32_t get_collider_shape(wo_handle const &collider)
    {
        return (int32_t)coll_ptr(collider)->shape;
    }

    void set_collider_radius(wo_handle const &collider, float v)
    {
        coll_ptr(collider)->radius = v;
    }

    float get_collider_radius(wo_handle const &collider)
    {
        return coll_ptr(collider)->radius;
    }

    void set_collider_offset(wo_handle const &collider, XMFLOAT3 const &v)
    {
        coll_ptr(collider)->offset = v;
    }

    XMFLOAT3 get_collider_offset(wo_handle const &collider)
    {
        return coll_ptr(collider)->offset;
    }

    void set_collider_tail(wo_handle const &collider, XMFLOAT3 const &v)
    {
        coll_ptr(collider)->tail = v;
    }

    XMFLOAT3 get_collider_tail(wo_handle const &collider)
    {
        return coll_ptr(collider)->tail;
    }

    void set_collider_is_gpu_enabled(wo_handle const &collider, bool v)
    {
        coll_ptr(collider)->SetGPUEnabled(v);
    }

    void set_collider_is_cpu_enabled(wo_handle const &collider, bool v)
    {
        coll_ptr(collider)->SetCPUEnabled(v);
    }

    wo_handle create_collider_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_COLLIDER, reinterpret_cast<int64_t>(&scene_ptr(scene)->colliders.Create(entity.name))};
    }

    wo_handle get_collider_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_COLLIDER, reinterpret_cast<int64_t>(scene_ptr(scene)->colliders.GetComponent(entity.name))};
    }

    int32_t entity_collider_count(wo_handle const &scene)
    {
        return (int32_t)scene_ptr(scene)->colliders.GetCount();
    }

    wo_handle entity_collider_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, scene_ptr(scene)->colliders.GetEntity(n)};
    }

    XMFLOAT4X4* mx_ptr(wo_handle const &h)
    {
        handle_check(h, WK_MATRIX);
        return reinterpret_cast<XMFLOAT4X4 *>(h.name);
    }

    wo_handle create_matrix4x4()
    {
        return {WK_MATRIX, reinterpret_cast<int64_t>(new XMFLOAT4X4())};
    }

    void load_from_xmmatrix(XMFLOAT4X4 *dest, XMMATRIX &src)
    {
        XMStoreFloat4x4(dest, src); 
    }

    void delete_matrix(wo_handle const &m)
    {
        delete mx_ptr(m);
    }

    void assign_matrix(wo_handle const &lhs, wo_handle const &rhs)
    {
        auto lm = mx_ptr(lhs);
        auto rm = mx_ptr(rhs);
        *lm = *rm;
    }

    XMFLOAT3 get_matrix_translation(wo_handle const &matrix)
    {   
        auto mat = XMLoadFloat4x4(mx_ptr(matrix));
        XMVECTOR t, s, r;
        XMFLOAT3 rv;
        XMMatrixDecompose(&s, &r, &t, mat);
        XMStoreFloat3(&rv, t);
        return rv;
    }

    void assign_matrix_rows(wo_handle const &m, XMFLOAT4 const &r1,
                            XMFLOAT4 const &r2, XMFLOAT4 const &r3, XMFLOAT4 const &r4)
    {
        auto mp = mx_ptr(m);
        memcpy(mp->m[0], &r1, sizeof(XMFLOAT4));
        memcpy(mp->m[1], &r2, sizeof(XMFLOAT4)); 
        memcpy(mp->m[2], &r3, sizeof(XMFLOAT4)); 
        memcpy(mp->m[3], &r4, sizeof(XMFLOAT4)); 
    }

    XMFLOAT4 return_matrix_row(wo_handle const &m, int32_t r)
    {
        auto mp = mx_ptr(m);
        XMFLOAT4 rv;
        rv.x = mp->m[r][0];
        rv.y = mp->m[r][1]; 
        rv.z = mp->m[r][2]; 
        rv.w = mp->m[r][3]; 
        return rv;
    }

    void identity_matrix(wo_handle const &m)
    {
        auto mat = XMMatrixIdentity();
        load_from_xmmatrix(mx_ptr(m), mat);
    }
    void translation_matrix(wo_handle const &m, XMFLOAT3 const &v)
    {
        XMMATRIX mat = XMMatrixTranslationFromVector(XMLoadFloat3(&v));
        load_from_xmmatrix(mx_ptr(m), mat);
    }


    void rotation_euler_matrix(wo_handle const &m, XMFLOAT3 const &angles)
    {
        XMMATRIX mat = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&angles));
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void rotation_x_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationX(a);
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void rotation_y_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationY(a);
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void rotation_z_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationZ(a);
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void rotation_quat_matrix(wo_handle const &m, XMFLOAT4 const &quat)
    {
        auto mat = XMMatrixRotationQuaternion(XMLoadFloat4(&quat));
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void scaling_matrix(wo_handle const &m, XMFLOAT4 const &scale)
    {
        auto mat = XMMatrixScalingFromVector(XMLoadFloat4(&scale));
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    void look_to_matrix(wo_handle const &m, XMFLOAT3 const &eyepos,
                        XMFLOAT3 const &eyedir, XMFLOAT3 const &up)
    {
        auto mat = XMMatrixLookToLH(XMLoadFloat3(&eyepos), XMLoadFloat3(&eyedir),
                                    XMLoadFloat3(&up)); 
        load_from_xmmatrix(mx_ptr(m), mat); 
    }

    void look_at_matrix(wo_handle const &m, XMFLOAT3 const &eyepos, 
                        XMFLOAT3 const &focuspos, XMFLOAT3 const &up)
    {
        auto mat = XMMatrixLookAtLH(XMLoadFloat3(&eyepos), XMLoadFloat3(&focuspos),
                                    XMLoadFloat3(&up));
        load_from_xmmatrix(mx_ptr(m), mat); 
    }

    void multiply_matrix(wo_handle const &lhs, wo_handle const &rhs, wo_handle const &result)
    {
        auto mat = XMMatrixMultiply(XMLoadFloat4x4(mx_ptr(lhs)),
                                    XMLoadFloat4x4(mx_ptr(rhs)));

        load_from_xmmatrix(mx_ptr(result), mat);
    }

    XMFLOAT4 transform_vector(wo_handle const &matrix, XMFLOAT4 const &v)
    {
        auto mat = XMLoadFloat4x4(mx_ptr(matrix));
        XMFLOAT4 rv;

        XMStoreFloat4(&rv, XMVector4Transform(XMLoadFloat4(&v), mat));
        return rv;
    }


    void add_matrix(wo_handle const &lhs, wo_handle const &rhs, wo_handle const &result)
    {
        auto mat = XMLoadFloat4x4(mx_ptr(lhs)) +  XMLoadFloat4x4(mx_ptr(rhs));
        load_from_xmmatrix(mx_ptr(result), mat);
    }

    void transpose_matrix(wo_handle const &m, wo_handle const& result)
    {
        auto mat = XMMatrixTranspose(XMLoadFloat4x4(mx_ptr(m)));
        load_from_xmmatrix(mx_ptr(result), mat);
    }

    void invert_matrix(wo_handle const &m, wo_handle const &result)
    {
        XMVECTOR det;
        auto mat = XMMatrixInverse(&det, XMLoadFloat4x4(mx_ptr(m)));
        load_from_xmmatrix(mx_ptr(m), mat);
    }

    wo_handle get_transform_local_matrix(wo_handle const &tcomp)
    {
        auto mat = tc_ptr(tcomp)->GetLocalMatrix();
        auto rv = create_matrix4x4();
        load_from_xmmatrix(mx_ptr(rv), mat);
        return rv;
    }

    wo_handle get_transform_world_matrix(wo_handle const &tcomp)
    {
        auto rv = create_matrix4x4();
        *mx_ptr(rv) = tc_ptr(tcomp)->world;
        return rv;
    }

    void transform_transform_matrix(wo_handle const &tcomp, wo_handle const &matrix)
    {
        tc_ptr(tcomp)->MatrixTransform(*mx_ptr(matrix));
    }

    void transform_camera_set_matrix(wo_handle const &camera, wo_handle const &matrix)
    {
        XMMATRIX mat = XMLoadFloat4x4(mx_ptr(matrix));
        cam_ptr(camera)->TransformCamera(mat);
    }

    void transform_camera(wo_handle const &camera, wo_handle const &tcomp)
    {
        cam_ptr(camera)->TransformCamera(*tc_ptr(tcomp));
    }

    void set_camera_eye(wo_handle const &camera, XMFLOAT3 const &v)
    {
        cam_ptr(camera)->Eye = v;
    }

    XMFLOAT3 get_camera_eye(wo_handle const &camera)
    {
        return cam_ptr(camera)->Eye;
    }

    void set_camera_at(wo_handle const &camera, XMFLOAT3 const &v)
    {
        cam_ptr(camera)->At = v;
    }

    XMFLOAT3 get_camera_at(wo_handle const &camera)
    {
        return cam_ptr(camera)->At;
    }

    void set_camera_up(wo_handle const &camera, XMFLOAT3 const &v)
    {
        cam_ptr(camera)->Up = v;
    }

    XMFLOAT3 get_camera_up(wo_handle const &camera)
    {
        return cam_ptr(camera)->Up;
    }

    wi::scene::AnimationComponent* anim_ptr(wo_handle const &h)
    {
        handle_check(h, WK_ANIMATION_COMP);
        return reinterpret_cast<wi::scene::AnimationComponent *>(h.name);
    }

    void set_animation_start(wo_handle const &animation, float v)
    {
        anim_ptr(animation)->start = v;
    }

    float get_animation_start(wo_handle const &animation)
    {
        return anim_ptr(animation)->start;
    }

    void set_animation_end(wo_handle const &animation, float v)
    {
        anim_ptr(animation)->end = v;
    }

    float get_animation_end(wo_handle const &animation)
    {
        return anim_ptr(animation)->end;
    }

    void set_animation_timer(wo_handle const &animation, float v)
    {
        anim_ptr(animation)->timer = v;
    }

    float get_animation_timer(wo_handle const &animation)
    {
        return anim_ptr(animation)->timer;
    }

    void set_animation_amount(wo_handle const &animation, float v)
    {
        anim_ptr(animation)->amount = v;
    }

    float get_animation_amount(wo_handle const &animation)
    {
        return anim_ptr(animation)->amount;
    }

    void set_animation_speed(wo_handle const &animation, float v)
    {
        anim_ptr(animation)->speed = v;
    }

    float get_animation_speed(wo_handle const &animation)
    {
        return anim_ptr(animation)->speed;
    }

    bool is_animation_playing(wo_handle const &anim)
    {
        return anim_ptr(anim)->IsPlaying();
    }

    bool is_animation_looped(wo_handle const &anim)
    {
        return anim_ptr(anim)->IsLooped();
    }

    float get_animation_length(wo_handle const &anim)
    {
        return anim_ptr(anim)->GetLength();
    }

    float is_animation_ended(wo_handle const &anim)
    {
        return anim_ptr(anim)->IsEnded();
    }

    void play_animation(wo_handle const &anim)
    {
        anim_ptr(anim)->Play();
    }

    void pause_animation(wo_handle const &anim)
    {
        anim_ptr(anim)->Pause();
    }

    void stop_animation(wo_handle const &anim)
    {
        anim_ptr(anim)->Stop();
    }

    void set_animation_looped(wo_handle const &anim, bool v)
    {
        anim_ptr(anim)->SetLooped(v);
    }

    wo_handle create_animation_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_ANIMATION_COMP,
            reinterpret_cast<int64_t>(&scene_ptr(scene)->animations.Create(entity.name))};
    }

    wo_handle get_animation_component(wo_handle const &scene, wo_handle const &entity)
    {
        return {WK_ANIMATION_COMP,
            reinterpret_cast<int64_t>(scene_ptr(scene)->animations.GetComponent(entity.name))};
    }

    int32_t entity_animation_count(wo_handle const &scene)
    {
        return (int32_t)scene_ptr(scene)->animations.GetCount();
    }

    wo_handle entity_animation_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY,
            scene_ptr(scene)->animations.GetEntity(n)};
    }

    wo_handle retarget_animation(wo_handle const &scene,
                                 wo_handle const &dest_entity,
                                 wo_handle const &src_entity, bool bake_data)
    {
        handle_check(dest_entity, WK_ENTITY);
        handle_check(src_entity, WK_ENTITY);

        return {WK_ENTITY,
            scene_ptr(scene)->RetargetAnimation(dest_entity.name, src_entity.name, bake_data)};
    }

    void set_renderpath3d_exposure(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setExposure(v);
    }

    float get_renderpath3d_exposure(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getExposure();
    }

    void set_renderpath3d_brightness(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setBrightness(v);
    }

    float get_renderpath3d_brightness(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getBrightness();
    }

    void set_renderpath3d_contrast(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setContrast(v);
    }

    float get_renderpath3d_contrast(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getContrast();
    }

    void set_renderpath3d_saturation(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setSaturation(v);
    }

    float get_renderpath3d_saturation(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getSaturation();
    }

    void set_renderpath3d_bloom_threshold(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setBloomThreshold(v);
    }

    float get_renderpath3d_bloom_threshold(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getBloomThreshold();
    }

    void set_renderpath3d_motion_blur_strength(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setMotionBlurStrength(v);
    }

    float get_renderpath3d_motion_blur_strength(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getMotionBlurStrength();
    }

    void set_renderpath3d_depth_of_field_strength(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setDepthOfFieldStrength(v);
    }

    float get_renderpath3d_depth_of_field_strength(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getDepthOfFieldStrength();
    }

    void set_renderpath3d_sharpen_filter_amount(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setSharpenFilterAmount(v);
    }

    float get_renderpath3d_sharpen_filter_amount(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getSharpenFilterAmount();
    }

    void set_renderpath3d_outline_threshold(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setOutlineThreshold(v);
    }

    float get_renderpath3d_outline_threshold(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getOutlineThreshold();
    }

    void set_renderpath3d_outline_thickness(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setOutlineThickness(v);
    }

    float get_renderpath3d_outline_thickness(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getOutlineThickness();
    }

    void set_renderpath3d_outline_color(wo_handle const &renderpath3d, XMFLOAT4 const &v)
    {
        rpath_ptr(renderpath3d)->setOutlineColor(v);
    }

    XMFLOAT4 get_renderpath3d_outline_color(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getOutlineColor();
    }

    void set_renderpath3d_ao_range(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setAORange(v);
    }

    float get_renderpath3d_ao_range(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getAORange();
    }

    void set_renderpath3d_ao_sample_count(wo_handle const &renderpath3d, int32_t v)
    {
        rpath_ptr(renderpath3d)->setAOSampleCount(v);
    }

    int32_t get_renderpath3d_ao_sample_count(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getAOSampleCount();
    }

    void set_renderpath3d_ao_power(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setAOPower(v);
    }

    float get_renderpath3d_ao_power(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getAOPower();
    }

    void set_renderpath3d_chromatic_aberration_amount(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setChromaticAberrationAmount(v);
    }

    float get_renderpath3d_chromatic_aberration_amount(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getChromaticAberrationAmount();
    }

    void set_renderpath3d_screen_space_shadow_sample_count(wo_handle const &renderpath3d, int32_t v)
    {
        rpath_ptr(renderpath3d)->setScreenSpaceShadowSampleCount(v);
    }

    int32_t get_renderpath3d_screen_space_shadow_sample_count(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getScreenSpaceShadowSampleCount();
    }

    void set_renderpath3d_screen_space_shadow_range(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setScreenSpaceShadowRange(v);
    }

    float get_renderpath3d_screen_space_shadow_range(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getScreenSpaceShadowRange();
    }

    void set_renderpath3d_eye_adaption_key(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setEyeAdaptionKey(v);
    }

    float get_renderpath3d_eye_adaption_key(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getEyeAdaptionKey();
    }

    void set_renderpath3d_eye_adaption_rate(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setEyeAdaptionRate(v);
    }

    float get_renderpath3d_eye_adaption_rate(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getEyeAdaptionRate();
    }

    void set_renderpath3d_fsr_sharpness(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setFSRSharpness(v);
    }

    float get_renderpath3d_fsr_sharpness(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getFSRSharpness();
    }

    void set_renderpath3d_fsr2_sharpness(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setFSR2Sharpness(v);
    }

    float get_renderpath3d_fsr2_sharpness(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getFSR2Sharpness();
    }

    void set_renderpath3d_light_shafts_strength(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setLightShaftsStrength(v);
    }

    float get_renderpath3d_light_shafts_strength(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getLightShaftsStrength();
    }

    void set_renderpath3d_raytraced_diffuse_range(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setRaytracedDiffuseRange(v);
    }

    float get_renderpath3d_raytraced_diffuse_range(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getRaytracedDiffuseRange();
    }

    void set_renderpath3d_raytraced_reflections_range(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setRaytracedReflectionsRange(v);
    }

    float get_renderpath3d_raytraced_reflections_range(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getRaytracedReflectionsRange();
    }

    void set_renderpath3d_reflection_roughness_cutoff(wo_handle const &renderpath3d, float v)
    {
        rpath_ptr(renderpath3d)->setReflectionRoughnessCutoff(v);
    }

    float get_renderpath3d_reflection_roughness_cutoff(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getReflectionRoughnessCutoff();
    }

    void set_renderpath3d_ao(wo_handle const &renderpath3d, int32_t v)
    {
        rpath_ptr(renderpath3d)->setAO((wi::RenderPath3D::AO)v);
    }

    bool get_renderpath3d_ao_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getAOEnabled();
    }

    void set_renderpath3d_ssr_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setSSREnabled(v);
    }

    bool get_renderpath3d_ssr_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getSSREnabled();
    }

    void set_renderpath3d_raytraced_diffuse_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setRaytracedDiffuseEnabled(v);
    }

    bool get_renderpath3d_raytraced_diffuse_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getRaytracedDiffuseEnabled();
    }

    void set_renderpath3d_raytraced_reflection_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setRaytracedReflectionsEnabled(v);
    }

    bool get_renderpath3d_raytraced_reflection_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getRaytracedReflectionEnabled();
    }

    void set_renderpath3d_shadows_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setShadowsEnabled(v);
    }

    bool get_renderpath3d_shadows_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getShadowsEnabled();
    }

    void set_renderpath3d_reflections_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setReflectionsEnabled(v);
    }

    bool get_renderpath3d_reflections_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getReflectionsEnabled();
    }

    void set_renderpath3d_fxaa_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setFXAAEnabled(v);
    }

    bool get_renderpath3d_fxaa_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getFXAAEnabled();
    }

    void set_renderpath3d_bloom_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setBloomEnabled(v);
    }

    bool get_renderpath3d_bloom_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getBloomEnabled();
    }

    void set_renderpath3d_color_grading_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setColorGradingEnabled(v);
    }

    bool get_renderpath3d_color_grading_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getColorGradingEnabled();
    }

    void set_renderpath3d_volume_lights_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setVolumeLightsEnabled(v);
    }

    bool get_renderpath3d_volume_lights_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getVolumeLightsEnabled();
    }

    void set_renderpath3d_light_shafts_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setLightShaftsEnabled(v);
    }

    bool get_renderpath3d_light_shafts_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getLightShaftsEnabled();
    }

    void set_renderpath3d_lens_flare_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setLensFlareEnabled(v);
    }

    bool get_renderpath3d_lens_flare_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getLensFlareEnabled();
    }

    void set_renderpath3d_motion_blur_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setMotionBlurEnabled(v);
    }

    bool get_renderpath3d_motion_blur_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getMotionBlurEnabled();
    }

    void set_renderpath3d_depth_of_field_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setDepthOfFieldEnabled(v);
    }

    bool get_renderpath3d_depth_of_field_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getDepthOfFieldEnabled();
    }

    void set_renderpath3d_eye_adaptation_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setEyeAdaptionEnabled(v);
    }

    bool get_renderpath3d_eye_adaptation_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getEyeAdaptionEnabled();
    }

    void set_renderpath3d_sharpen_filter_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setSharpenFilterEnabled(v);
    }

    bool get_renderpath3d_sharpen_filter_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getSharpenFilterEnabled();
    }

    void set_renderpath3d_outline_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setOutlineEnabled(v);
    }

    bool get_renderpath3d_outline_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getOutlineEnabled();
    }

    void set_renderpath3d_chromatic_aberration_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setChromaticAberrationEnabled(v);
    }

    bool get_renderpath3d_chromatic_aberration_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getChromaticAberrationEnabled();
    }

    void set_renderpath3d_dither_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setDitherEnabled(v);
    }

    bool get_renderpath3d_dither_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getDitherEnabled();
    }

    void set_renderpath3d_occlusion_culling_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setOcclusionCullingEnabled(v);
    }

    bool get_renderpath3d_occlusion_culling_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getOcclusionCullingEnabled();
    }

    void set_renderpath3d_scene_update_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setSceneUpdateEnabled(v);
    }

    bool get_renderpath3d_scene_update_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getSceneUpdateEnabled();
    }

    void set_renderpath3d_fsr_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setFSREnabled(v);
    }

    bool get_renderpath3d_fsr_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getFSREnabled();
    }

    void set_renderpath3d_fsr2_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setFSR2Enabled(v);
    }

    bool get_renderpath3d_fsr2_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getFSR2Enabled();
    }

    void set_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const &renderpath3d, bool v)
    {
        rpath_ptr(renderpath3d)->setVXGIResolveFullResolutionEnabled(v);
    }

    bool get_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const &renderpath3d)
    {
        return rpath_ptr(renderpath3d)->getVXGIResolveFullResolutionEnabled();
    }

    void renderer_set_vxgi_enabled(bool v)
    {
        wi::renderer::SetVXGIEnabled(v);
    }

    bool renderer_vxgi_enabled()
    {
        return wi::renderer::GetVXGIEnabled();
    }

    wi::primitive::Sphere* sphere_ptr(wo_handle const &h)
    {
        handle_check(h, WK_SPHERE);
        return reinterpret_cast<wi::primitive::Sphere *>(h.name);
    }

    wo_handle create_primitive_sphere()
    {
        return {WK_SPHERE, reinterpret_cast<int64_t>(new wi::primitive::Sphere())};
    }

    void delete_primitive_sphere(wo_handle const &primitive_sphere)
    {
        delete sphere_ptr(primitive_sphere);
    }

    void set_primitive_sphere_center(wo_handle const &primitive_sphere, XMFLOAT3 const &v)
    {
        sphere_ptr(primitive_sphere)->center = v;
    }

    XMFLOAT3 get_primitive_sphere_center(wo_handle const &primitive_sphere)
    {
        return sphere_ptr(primitive_sphere)->center;
    }

    void set_primitive_sphere_radius(wo_handle const &primitive_sphere, float v)
    {
        sphere_ptr(primitive_sphere)->radius = v;
    }

    float get_primitive_sphere_radius(wo_handle const &primitive_sphere)
    {
        return sphere_ptr(primitive_sphere)->radius;
    }

    bool sphere_sphere_intersects(wo_handle const &sphere0, wo_handle const &sphere1, float &retval2, XMFLOAT3 &retval3)
    {
        return sphere_ptr(sphere0)->intersects(*sphere_ptr(sphere1), retval2, retval3);
    }

    wi::scene::Scene::SphereIntersectionResult* sir_ptr(wo_handle const &h)
    {
        handle_check(h, WK_SPHEREINTERSECTION);
        return reinterpret_cast<wi::scene::Scene::SphereIntersectionResult *>(h.name);
    }

    wo_handle create_sphere_intersection_result()
    {
        return {WK_SPHEREINTERSECTION, reinterpret_cast<int64_t>(new wi::scene::Scene::SphereIntersectionResult())};
    }

    void delete_sphere_intersection_result(wo_handle const &sphere_intersection_result)
    {
        delete sir_ptr(sphere_intersection_result);
    }

    void set_sphere_intersection_result_entity(wo_handle const &sphere_intersection_result, wo_handle const &v)
    {
        handle_check(v, WK_ENTITY);
        sir_ptr(sphere_intersection_result)->entity = v.name;
    }

    wo_handle get_sphere_intersection_result_entity(wo_handle const &sphere_intersection_result)
    {
        return {WK_ENTITY, sir_ptr(sphere_intersection_result)->entity};
    }

    void set_sphere_intersection_result_position(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        sir_ptr(sphere_intersection_result)->position = v;
    }

    XMFLOAT3 get_sphere_intersection_result_position(wo_handle const &sphere_intersection_result)
    {
        return sir_ptr(sphere_intersection_result)->position;
    }

    void set_sphere_intersection_result_normal(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        sir_ptr(sphere_intersection_result)->normal = v;
    }

    XMFLOAT3 get_sphere_intersection_result_normal(wo_handle const &sphere_intersection_result)
    {
        return sir_ptr(sphere_intersection_result)->normal;
    }

    void set_sphere_intersection_result_velocity(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        sir_ptr(sphere_intersection_result)->velocity = v;
    }

    XMFLOAT3 get_sphere_intersection_result_velocity(wo_handle const &sphere_intersection_result)
    {
        return sir_ptr(sphere_intersection_result)->velocity;
    }

    void set_sphere_intersection_result_depth(wo_handle const &sphere_intersection_result, float v)
    {
        sir_ptr(sphere_intersection_result)->depth = v;
    }

    float get_sphere_intersection_result_depth(wo_handle const &sphere_intersection_result)
    {
        return sir_ptr(sphere_intersection_result)->depth;
    }

    wo_handle scene_sphere_intersects(wo_handle const &scene, wo_handle const &sphere, int32_t filter_mask, int32_t layer_mask, int32_t lod)
    {
        auto rv = new wi::scene::Scene::SphereIntersectionResult();
        *rv = scene_ptr(scene)->Intersects(*sphere_ptr(sphere), filter_mask, layer_mask, lod);
        return {WK_SPHEREINTERSECTION, reinterpret_cast<int64_t>(rv)};
    }

    wi::primitive::Capsule* cap_ptr(wo_handle const &h)
    {
        handle_check(h, WK_CAPSULE);
        return reinterpret_cast<wi::primitive::Capsule *>(h.name);
    }

    wo_handle create_primitive_capsule()
    {
        return {WK_CAPSULE, reinterpret_cast<int64_t>(new wi::primitive::Capsule())};
    }

    void delete_primitive_capsule(wo_handle const &primitive_capsule)
    {
        delete cap_ptr(primitive_capsule);
    }

    void set_primitive_capsule_base(wo_handle const &primitive_capsule, XMFLOAT3 const &v)
    {
        cap_ptr(primitive_capsule)->base = v;
    }

    XMFLOAT3 get_primitive_capsule_base(wo_handle const &primitive_capsule)
    {
        return cap_ptr(primitive_capsule)->base;
    }

    void set_primitive_capsule_tip(wo_handle const &primitive_capsule, XMFLOAT3 const &v)
    {
        cap_ptr(primitive_capsule)->tip = v;
    }

    XMFLOAT3 get_primitive_capsule_tip(wo_handle const &primitive_capsule)
    {
        return cap_ptr(primitive_capsule)->tip;
    }

    void set_primitive_capsule_radius(wo_handle const &primitive_capsule, float v)
    {
        cap_ptr(primitive_capsule)->radius = v;
    }

    float get_primitive_capsule_radius(wo_handle const &primitive_capsule)
    {
        return cap_ptr(primitive_capsule)->radius;
    }

    bool capsule_capsule_intersects(wo_handle const &cap0, wo_handle const &cap1, XMFLOAT3 &retval2, XMFLOAT3 &retval3, float &retval4)
    {
        return cap_ptr(cap0)->intersects(*cap_ptr(cap1), retval2, retval3, retval4); 
    }

    bool capsule_sphere_intersects(wo_handle const &cap, wo_handle const &sphere, float &retval2, XMFLOAT3 &retval3)
    {
        return cap_ptr(cap)->intersects(*sphere_ptr(sphere), retval2, retval3);
    }

    bool sphere_capsule_intersects(wo_handle const &sphere, wo_handle const &cap, float &retval2, XMFLOAT3 &retval3)
    {
        return sphere_ptr(sphere)->intersects(*cap_ptr(cap), retval2, retval3);
    }

    wo_handle scene_capsule_intersects(wo_handle const &scene, wo_handle const &cap, int32_t filter_mask, int32_t layer_mask, int32_t lod)
    {
        auto rv = create_sphere_intersection_result();
        *sir_ptr(rv) = scene_ptr(scene)->Intersects(*cap_ptr(cap), filter_mask, layer_mask, lod);
        return rv;
    }

    wo_handle get_collider_capsule(wo_handle const &collider)
    {
        return {WK_CAPSULE, reinterpret_cast<int64_t>(&coll_ptr(collider)->capsule)};
    }

    wi::scene::RigidBodyPhysicsComponent* rigid_ptr(wo_handle const &h)
    {
        handle_check(h, WK_RIGIDBODY);
        return reinterpret_cast<wi::scene::RigidBodyPhysicsComponent *>(h.name);
    }

    void set_rigidbody_physics_shape(wo_handle const &rigidbody_physics, int32_t v)
    {
        rigid_ptr(rigidbody_physics)->shape = (wi::scene::RigidBodyPhysicsComponent::CollisionShape)v;
    }

    int32_t get_rigidbody_physics_shape(wo_handle const &rigidbody_physics)
    {
        return (int32_t)rigid_ptr(rigidbody_physics)->shape;
    }

    void set_rigidbody_physics_mass(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->mass = v;
    }

    float get_rigidbody_physics_mass(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->mass;
    }

    void set_rigidbody_physics_friction(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->friction = v;
    }

    float get_rigidbody_physics_friction(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->friction;
    }

    void set_rigidbody_physics_restitution(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->restitution = v;
    }

    float get_rigidbody_physics_restitution(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->restitution;
    }

    void set_rigidbody_physics_damping_linear(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->damping_linear = v;
    }

    float get_rigidbody_physics_damping_linear(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->damping_linear;
    }

    void set_rigidbody_physics_damping_angular(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->damping_angular = v;
    }

    float get_rigidbody_physics_damping_angular(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->damping_angular;
    }

    void set_rigidbody_physics_box_halfextents(wo_handle const &rigidbody_physics, XMFLOAT3 const &v)
    {
        rigid_ptr(rigidbody_physics)->box.halfextents = v;
    }

    XMFLOAT3 get_rigidbody_physics_box_halfextents(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->box.halfextents;
    }

    void set_rigidbody_physics_sphere_radius(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->sphere.radius = v;
    }

    float get_rigidbody_physics_sphere_radius(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->sphere.radius;
    }

    void set_rigidbody_physics_capsule_radius(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->capsule.radius = v;
    }

    float get_rigidbody_physics_capsule_radius(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->capsule.radius;
    }

    void set_rigidbody_physics_capsule_height(wo_handle const &rigidbody_physics, float v)
    {
        rigid_ptr(rigidbody_physics)->capsule.height = v;
    }

    float get_rigidbody_physics_capsule_height(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->capsule.height;
    }

    void set_rigidbody_physics_mesh_lod(wo_handle const &rigidbody_physics, int32_t v)
    {
        rigid_ptr(rigidbody_physics)->mesh_lod = v;
    }

    int32_t get_rigidbody_physics_mesh_lod(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->mesh_lod;
    }

    void set_rigidbody_physics_disable_deactivation(wo_handle const &rigidbody_physics, bool v)
    {
        rigid_ptr(rigidbody_physics)->SetDisableDeactivation(v);
    }

    bool get_rigidbody_physics_disable_deactivation(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->IsDisableDeactivation();
    }

    void set_rigidbody_physics_kinematic(wo_handle const &rigidbody_physics, bool v)
    {
        rigid_ptr(rigidbody_physics)->SetKinematic(v);
    }

    bool get_rigidbody_physics_kinematic(wo_handle const &rigidbody_physics)
    {
        return rigid_ptr(rigidbody_physics)->IsKinematic();
    }

    wo_handle create_rigidbody_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_RIGIDBODY, reinterpret_cast<int64_t>(&scene_ptr(scene)->rigidbodies.Create(entity.name))};
    }

    wo_handle get_rigidbody_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_RIGIDBODY, reinterpret_cast<int64_t>(scene_ptr(scene)->rigidbodies.GetComponent(entity.name))};
    }

    int32_t entity_rigidbody_count(wo_handle const &scene)
    {          
        return (int32_t)scene_ptr(scene)->rigidbodies.GetCount();
    }


    wo_handle entity_rigidbody_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, scene_ptr(scene)->rigidbodies.GetEntity(n)};
    }
}
