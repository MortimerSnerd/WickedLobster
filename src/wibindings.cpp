#include "pch.h"
// wiMath is safe and doesn't cause namespace problems with Lobster.
#include "wiMath.h"
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
}

