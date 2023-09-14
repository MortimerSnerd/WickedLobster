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
        case WK_ANIMATION_COMP:
        case WK_CAMERA_COMP:
        case WK_CAPSULE:
        case WK_COLLIDER:
        case WK_FONT_PARAMS:
        case WK_HIER_COMP:
        case WK_HUMANOID:
        case WK_LIGHT_COMP:
        case WK_MATRIX:
        case WK_NAME_COMP:
        case WK_OBJECT_COMP:
        case WK_RESOURCE:
        case WK_RIGIDBODY:
        case WK_SCENE:
        case WK_SOUND:
        case WK_SOUND_COMP:
        case WK_SOUND_INSTANCE:
        case WK_SPHERE:
        case WK_SPRITE_FONT:
        case WK_TIMER:
        case WK_TRANSFORM_COMP:
            if (h.name == 0) {
                printf("Null handle pointer, kind=%d\n", (int)h.kind);
                dump_lobster_stack();
                fflush(stdout);
                abort();
            }
        }
    }

    // Helper class that converts between wi:: types and our tagged handles.
    template<typename T, WOKIND W>
    struct AlienPtr
    {
        static wo_handle handle(T *alien)
        {
            return {W, reinterpret_cast<int64_t>(alien)};
        }

        static T* ptr(wo_handle const &h)
        {
            handle_check(h, W);
            return reinterpret_cast<T *>(h.name);
        }

    };

    AlienPtr<wi::scene::Scene, WK_SCENE> SCENE;
    AlienPtr<wi::scene::NameComponent, WK_NAME_COMP> NAME;
    AlienPtr<wi::scene::TransformComponent, WK_TRANSFORM_COMP> TRANSFORM;
    AlienPtr<wi::scene::CameraComponent, WK_CAMERA_COMP> CAMERA;
    AlienPtr<wi::RenderPath3D, WK_RENDERPATH3> RENDERPATH;
    AlienPtr<wi::Timer, WK_TIMER> TIMER;
    AlienPtr<wi::font::Params, WK_FONT_PARAMS> FONT_PARAMS;
    AlienPtr<wi::SpriteFont, WK_SPRITE_FONT> SPRITE_FONT;
    AlienPtr<wi::scene::HumanoidComponent, WK_HUMANOID> HUMANOID;
    AlienPtr<wi::scene::LayerComponent, WK_LAYER> LAYER;
    AlienPtr<wi::scene::ColliderComponent, WK_COLLIDER> COLLIDER;
    AlienPtr<XMFLOAT4X4, WK_MATRIX> MATRIX;
    AlienPtr<wi::scene::AnimationComponent, WK_ANIMATION_COMP> ANIMATION;
    AlienPtr<wi::primitive::Sphere, WK_SPHERE> SPHERE;
    AlienPtr<wi::scene::Scene::SphereIntersectionResult, WK_SPHEREINTERSECTION> SPHERE_INTERSECTION;
    AlienPtr<wi::primitive::Capsule, WK_CAPSULE> CAPSULE;
    AlienPtr<wi::scene::RigidBodyPhysicsComponent, WK_RIGIDBODY> RIGIDBODY;
    AlienPtr<wi::scene::ObjectComponent, WK_OBJECT_COMP> OBJECT;
    AlienPtr<wi::scene::HierarchyComponent, WK_HIER_COMP> HIERARCHY;
    AlienPtr<wi::scene::LightComponent, WK_LIGHT_COMP> LIGHT;
    AlienPtr<wi::Resource, WK_RESOURCE> RESOURCE;
    AlienPtr<wi::audio::Sound, WK_SOUND> SOUND;
    AlienPtr<wi::scene::SoundComponent, WK_SOUND_COMP> SOUND_COMP;
    AlienPtr<wi::audio::SoundInstance, WK_SOUND_INSTANCE> SOUND_INSTANCE;


    void valid_entity(wo_handle const &h)
    {
        if (h.name == wi::ecs::INVALID_ENTITY) {
            wi::backlog::post("invalid entity", wi::backlog::LogLevel::Error);
            dump_lobster_stack();
            abort();
        }
    }

    wo_handle new_scene()
    {
        // We create scenes, or return pointers to a global scene, neither
        // which will move.  So it's safe to use the address as the key.
        return SCENE.handle(new wi::scene::Scene());
    }

    void delete_scene(wo_handle const &scene)
    {
        if (scene.name == 0) return;
        auto sp = SCENE.ptr(scene);
        // No deleting global scene.
        if (sp == &wi::scene::GetScene()) return;
        delete sp;
    }

    void scene_merge(wo_handle const &dest, wo_handle const &src)
    {
        auto dp = SCENE.ptr(dest);
        auto sp = SCENE.ptr(src);
        dp->Merge(*sp);
    }

    wo_handle global_scene()
    {
        return wo_handle{WK_SCENE, reinterpret_cast<int64_t>(&wi::scene::GetScene())};
    }

    wo_handle load_model(wo_handle const& dest_scene, std::string_view const& filename, bool attach_to_entity)
    {
        auto ent = wi::scene::LoadModel(*SCENE.ptr(dest_scene), std::string(filename),
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
        auto sp = SCENE.ptr(scene);
        return NAME.handle(&sp->names.Create(entity.name));
    }

    void nc_set_name(wo_handle const& name_comp, std::string_view const &name)
    {
        auto np = NAME.ptr(name_comp);
        np->name = name;
    }

    wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const &name, wo_handle const& ancestor)
    {
        handle_check(ancestor, WK_ENTITY);
        return {WK_ENTITY, SCENE.ptr(scene)->Entity_FindByName(std::string(name), 
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
        return SCENE.ptr(scene);
    }

    wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity)
    {
        auto sp = create_component_common(scene, entity);
        return CAMERA.handle(&sp->cameras.Create(entity.name));
    }

    wo_handle create_transform_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = create_component_common(scene, entity);
        return TRANSFORM.handle(&sp->transforms.Create(entity.name));
    }

    wo_handle create_transform()
    {
        return TRANSFORM.handle(new wi::scene::TransformComponent);
    }

    void delete_transform(wo_handle const &trans)
    {
        delete TRANSFORM.ptr(trans);
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
        return RENDERPATH.handle(render_path_3d);
    }

    float get_fixed_update_rate()
    {
        if (game_app) {
            return game_app->getTargetFrameRate();
        } else {
            return 60.0f;
        }
    }

    void renderpath3d_set_camera(wo_handle const &rpath, wo_handle const &cam_component)
    {
        auto rp = RENDERPATH.ptr(rpath);
        auto cc = CAMERA.ptr(cam_component);
        rp->camera = cc;
    }

    XMINT2 get_renderpath_physical_dims(wo_handle const &path)
    {
        auto pp = RENDERPATH.ptr(path);
        return {(int32_t)pp->GetPhysicalWidth(), (int32_t)pp->GetPhysicalHeight()};
    }

    XMFLOAT2 get_renderpath_logical_dims(wo_handle const &path)
    {
        auto pp = RENDERPATH.ptr(path);
        return {pp->GetLogicalWidth(), pp->GetLogicalHeight()};
    }

    void transform_translate(wo_handle const &trans, const XMFLOAT3 &value)
    {
        TRANSFORM.ptr(trans)->Translate(value);
    }

    wo_handle get_transform_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = create_component_common(scene, entity);
        return TRANSFORM.handle(sp->transforms.GetComponent(entity.name));
    }

    void transform_clear(wo_handle const &trans)
    {
        auto tp = TRANSFORM.ptr(trans);
        tp->ClearTransform();
    }

    void transform_rotate(wo_handle const &trans_component, XMFLOAT4 const &quat)
    {
        auto tp = TRANSFORM.ptr(trans_component);
        tp->Rotate(quat);
    }

    XMFLOAT3 transform_position(wo_handle const &tcomp)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        return tp->GetPosition();
    }

    XMFLOAT4 transform_rotation(wo_handle const &tcomp)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        return tp->GetRotation();
    }

    XMFLOAT3 decompose_transform(wo_handle const &tcomp, XMFLOAT4 &retval2, XMFLOAT3 &retval3)
    {
        XMVECTOR S, R, T;
        XMFLOAT3 rv;
        XMMatrixDecompose(&S, &R, &T, XMLoadFloat4x4(&TRANSFORM.ptr(tcomp)->world));
        XMStoreFloat3(&rv, T);
        XMStoreFloat4(&retval2, R);
        XMStoreFloat3(&retval3, S);
        return rv;
    }

    void set_transform_scale_local(wo_handle const &transform, XMFLOAT3 const &v)
    {
        TRANSFORM.ptr(transform)->scale_local = v;
    }

    XMFLOAT3 get_transform_scale_local(wo_handle const &transform)
    {
        return TRANSFORM.ptr(transform)->scale_local;
    }

    void set_transform_rotation_local(wo_handle const &transform, XMFLOAT4 const &v)
    {
        TRANSFORM.ptr(transform)->rotation_local = v;
    }

    XMFLOAT4 get_transform_rotation_local(wo_handle const &transform)
    {
        return TRANSFORM.ptr(transform)->rotation_local;
    }

    void set_transform_translation_local(wo_handle const &transform, XMFLOAT3 const &v)
    {
        TRANSFORM.ptr(transform)->translation_local = v;
    }

    XMFLOAT3 get_transform_translation_local(wo_handle const &transform)
    {
        return TRANSFORM.ptr(transform)->translation_local;
    }

    void set_transform_dirty(wo_handle const &transform, bool v)
    {
        TRANSFORM.ptr(transform)->SetDirty(v);
    }

    bool get_transform_dirty(wo_handle const &transform)
    {
        return TRANSFORM.ptr(transform)->IsDirty();
    }

    XMFLOAT3 transform_scaling(wo_handle const &tcomp)
    {
        return TRANSFORM.ptr(tcomp)->GetScale();
    }

    void transform_update_transform(wo_handle const &tcomp)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        tp->UpdateTransform();
    }

    void transform_rotate_roll_pitch_yaw(wo_handle const &tcomp, XMFLOAT3 const &angles)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        tp->RotateRollPitchYaw(angles);
    }

    void transform_scale(wo_handle const &tcomp, XMFLOAT3 const &scale)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        tp->Scale(scale);
    }

    void transform_lerp(wo_handle const &tcomp, wo_handle const &a, wo_handle const &b, float t)
    {
        auto tp = TRANSFORM.ptr(tcomp);
        auto ap = TRANSFORM.ptr(a);
        auto bp = TRANSFORM.ptr(b);
        tp->Lerp(*ap, *bp, t);
    }

    float camera_fov(wo_handle const &tcomp)
    {
        return CAMERA.ptr(tcomp)->fov;
    }

    void camera_set_fov(wo_handle const &tcomp, float fov)
    {
        CAMERA.ptr(tcomp)->fov = fov;
    }

    XMFLOAT2 camera_get_dims(wo_handle const &tcomp)
    {
        auto cp = CAMERA.ptr(tcomp);
        return {cp->width, cp->height};
    }

    void camera_set_dims(wo_handle const &tcomp, XMFLOAT2 const &dims)
    {
        auto cp = CAMERA.ptr(tcomp);
        cp->width = dims.x;
        cp->height = dims.y;
    }

    float camera_znear(wo_handle const &tcomp)
    {
        return CAMERA.ptr(tcomp)->zNearP;
    }

    void camera_set_znear(wo_handle const &tcomp, float znear)
    {
        CAMERA.ptr(tcomp)->zNearP = znear;
    }

    float camera_zfar(wo_handle const &tcomp)
    {
        return CAMERA.ptr(tcomp)->zFarP;
    }

    void camera_set_zfar(wo_handle const &tcomp, float zfar)
    {
        CAMERA.ptr(tcomp)->zFarP = zfar;
    }

    float camera_focal_length(wo_handle const &tcomp)
    {
        return CAMERA.ptr(tcomp)->focal_length;
    }

    void camera_set_focal_length(wo_handle const &tcomp, float l)
    {
        CAMERA.ptr(tcomp)->focal_length = l;
    }

    void camera_update(wo_handle const &tcomp)
    {
        CAMERA.ptr(tcomp)->UpdateCamera();
    }

    wo_handle get_camera_component(wo_handle const &scene, wo_handle const &ent)
    {
        auto sp = SCENE.ptr(scene);
        return CAMERA.handle(sp->cameras.GetComponent(ent.name));
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
        auto sp = SCENE.ptr(scene);
        return sp->names.GetCount();
    }

    wo_handle entity_names_get(wo_handle const &scene, int32_t n)
    {
        auto sp = SCENE.ptr(scene);
        return {WK_ENTITY,  sp->names.GetEntity(n)};
    }

    std::string_view nc_get_name(wo_handle const &name_comp)
    {
        auto np = NAME.ptr(name_comp);
        return np->name;
    }

    wo_handle get_name_component(wo_handle const &scene, wo_handle const &entity)
    {
        auto sp = SCENE.ptr(scene);
        return NAME.handle(sp->names.GetComponent(entity.name));
    }

    int32_t get_camera_count(wo_handle const &scene)
    {
        auto sp = SCENE.ptr(scene);
        return sp->cameras.GetCount();
    }

    wo_handle get_camera_entity(wo_handle const &scene, int32_t n)
    {
        auto sp = SCENE.ptr(scene);
        return {WK_ENTITY, sp->cameras.GetEntity(n)};
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

    wo_handle create_timer()
    {
        return TIMER.handle(new wi::Timer());
    }

    void delete_timer(wo_handle const &timer)
    {
        if (timer.name == 0) return;
        auto tp = TIMER.ptr(timer);
        delete tp;
    }

    void timer_record(wo_handle const &timer)
    {
        TIMER.ptr(timer)->record();
    }

    double timer_elapsed_seconds(wo_handle const &time)
    {
        return TIMER.ptr(time)->elapsed_seconds();
    }

    double timer_elapsed(wo_handle const &timer)
    {
        return TIMER.ptr(timer)->elapsed();
    }

    wo_handle create_font_params()
    {
        return FONT_PARAMS.handle(new wi::font::Params());
    }

    void delete_font_params(wo_handle const &font_params)
    {
        if (font_params.name == 0) return;
        delete FONT_PARAMS.ptr(font_params);
    }

    //TODO questionable as to whether we should be messing with the z coordinate.
    void set_font_params_position(wo_handle const &font_params, XMFLOAT3 const &v)
    {
        FONT_PARAMS.ptr(font_params)->position = v;
    }

    XMFLOAT3 get_font_params_position(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->position;
    }

    void set_font_params_size(wo_handle const &font_params, int32_t v)
    {
        FONT_PARAMS.ptr(font_params)->size = v;
    }

    int32_t get_font_params_size(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->size;
    }

    void set_font_params_scaling(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->scaling = v;
    }

    float get_font_params_scaling(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->scaling;
    }

    void set_font_params_rotation(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->rotation = v;
    }

    float get_font_params_rotation(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->rotation;
    }

    void set_font_params_spacing_x(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->spacingX = v;
    }

    float get_font_params_spacing_x(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->spacingX;
    }

    void set_font_params_spacing_y(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->spacingY = v;
    }

    float get_font_params_spacing_y(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->spacingY;
    }

    void set_font_params_h_align(wo_handle const &font_params, int32_t v)
    {
        FONT_PARAMS.ptr(font_params)->h_align = (wi::font::Alignment)v;
    }

    int32_t get_font_params_h_align(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->h_align;
    }

    void set_font_params_v_align(wo_handle const &font_params, int32_t v)
    {
        FONT_PARAMS.ptr(font_params)->v_align = (wi::font::Alignment)v;
    }

    int32_t get_font_params_v_align(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->v_align;
    }

    void set_font_params_color(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        FONT_PARAMS.ptr(font_params)->color = wi::Color::fromFloat4(v);
    }

    XMFLOAT4 get_font_params_color(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->color.toFloat4();
    }

    void set_font_params_shadow_color(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        FONT_PARAMS.ptr(font_params)->shadowColor = wi::Color::fromFloat4(v);
    }

    XMFLOAT4 get_font_params_shadow_color(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->shadowColor.toFloat4();
    }

    void set_font_params_h_wrap(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->h_wrap = v;
    }

    float get_font_params_h_wrap(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->h_wrap;
    }

    void set_font_params_style(wo_handle const &font_params, int32_t v)
    {
        FONT_PARAMS.ptr(font_params)->style = v;
    }

    int32_t get_font_params_style(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->style;
    }

    void set_font_params_softness(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->softness = v;
    }

    float get_font_params_softness(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->softness;
    }

    void set_font_params_bolden(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->bolden = v;
    }

    float get_font_params_bolden(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->bolden;
    }

    void set_font_params_shadow_softness(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->shadow_softness = v;
    }

    float get_font_params_shadow_softness(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->shadow_softness;
    }

    void set_font_params_shadow_bolden(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->shadow_bolden = v;
    }

    float get_font_params_shadow_bolden(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->shadow_bolden;
    }

    void set_font_params_shadow_offset_x(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->shadow_offset_x = v;
    }

    float get_font_params_shadow_offset_x(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->shadow_offset_x;
    }

    void set_font_params_shadow_offset_y(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->shadow_offset_y = v;
    }

    float get_font_params_shadow_offset_y(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->shadow_offset_y;
    }

    void set_font_params_cursor(wo_handle const &font_params, XMFLOAT4 const &v)
    {
        // We pack this into a float4 for lobster.
        FONT_PARAMS.ptr(font_params)->cursor = {XMFLOAT2{v.x, v.y}, 
                                            XMFLOAT2{v.z, v.w}};
    }

    XMFLOAT4 get_font_params_cursor(wo_handle const &font_params)
    {
        XMFLOAT4 rv;
        auto fp = FONT_PARAMS.ptr(font_params);

        rv.x = fp->cursor.position.x;
        rv.y = fp->cursor.position.y;
        rv.z = fp->cursor.size.x;
        rv.w = fp->cursor.size.y;
        return rv;
    }

    void set_font_params_hdr_scaling(wo_handle const &font_params, float v)
    {
        FONT_PARAMS.ptr(font_params)->hdr_scaling = v;
    }

    float get_font_params_hdr_scaling(wo_handle const &font_params)
    {
        return FONT_PARAMS.ptr(font_params)->hdr_scaling;
    }

    wo_handle create_sprite_font()
    {
        return SPRITE_FONT.handle(new wi::SpriteFont());
    }

    void sprite_font_set_params(wo_handle const &font, wo_handle const &font_params)
    {
        SPRITE_FONT.ptr(font)->params = *FONT_PARAMS.ptr(font_params);
    }

    void delete_sprite_font(wo_handle const &font)
    {
        if (font.name == 0) return;
        delete SPRITE_FONT.ptr(font);
    }

    void sprite_font_set_hidden(wo_handle const &font, bool value)
    {
        SPRITE_FONT.ptr(font)->SetHidden(value);
    }

    XMFLOAT2 sprite_font_text_size(wo_handle const &font)
    {
        return SPRITE_FONT.ptr(font)->TextSize();
    }

    void sprite_font_set_text(wo_handle const &font, std::string_view const &txt)
    {
        SPRITE_FONT.ptr(font)->SetText(std::string(txt));
    }

    std::string_view sprite_font_get_text(wo_handle const &font)
    {
        return SPRITE_FONT.ptr(font)->GetTextA();
    }

    void renderpath_add_font(wo_handle const &path, wo_handle const &sprite_font, std::string_view const &layer)
    {
        auto rp = RENDERPATH.ptr(path);
        auto rp2 = dynamic_cast<wi::RenderPath2D *>(rp);
        if (rp2) {
            rp2->AddFont(SPRITE_FONT.ptr(sprite_font), std::string(layer)); 
        }
    }

    void renderpath_remove_font(wo_handle const &path, wo_handle const &sprite_font)
    {
        RENDERPATH.ptr(path)->RemoveFont(SPRITE_FONT.ptr(sprite_font));
    }

    void renderpath_clear_fonts(wo_handle const &path)
    {
        RENDERPATH.ptr(path)->ClearFonts();
    }

    int32_t renderpath_font_order(wo_handle const &path, wo_handle const &sprite_font)
    {
        return RENDERPATH.ptr(path)->GetFontOrder(SPRITE_FONT.ptr(sprite_font));
    }

    void renderpath_set_font_order(wo_handle const &path, wo_handle const &sprite_font, int32_t order)
    {
        RENDERPATH.ptr(path)->SetFontOrder(SPRITE_FONT.ptr(sprite_font), order);
    }

    wo_handle create_humanoid_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return HUMANOID.handle(&SCENE.ptr(scene)->humanoids.Create(entity.name));
    }

    wo_handle get_humanoid_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return HUMANOID.handle(SCENE.ptr(scene)->humanoids.GetComponent(entity.name));
    }

    int32_t entity_humanoid_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->humanoids.GetCount();
    }

    wo_handle entity_humanoid_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->humanoids.GetEntity((size_t)n)};
    }

    void set_humanoid_default_look_direction(wo_handle const &humanoid, XMFLOAT3 const &v)
    {
        HUMANOID.ptr(humanoid)->default_look_direction = v;
    }

    XMFLOAT3 get_humanoid_default_look_direction(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->default_look_direction;
    }

    void set_humanoid_head_rotation_max(wo_handle const &humanoid, XMFLOAT2 const &v)
    {
        HUMANOID.ptr(humanoid)->head_rotation_max = v;
    }

    XMFLOAT2 get_humanoid_head_rotation_max(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->head_rotation_max;
    }

    void set_humanoid_head_rotation_speed(wo_handle const &humanoid, float v)
    {
        HUMANOID.ptr(humanoid)->head_rotation_speed = v;
    }

    float get_humanoid_head_rotation_speed(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->head_rotation_speed;
    }

    void set_humanoid_eye_rotation_max(wo_handle const &humanoid, XMFLOAT2 const &v)
    {
        HUMANOID.ptr(humanoid)->eye_rotation_max = v;
    }

    XMFLOAT2 get_humanoid_eye_rotation_max(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->eye_rotation_max;
    }

    void set_humanoid_eye_rotation_speed(wo_handle const &humanoid, float v)
    {
        HUMANOID.ptr(humanoid)->eye_rotation_speed = v;
    }

    float get_humanoid_eye_rotation_speed(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->eye_rotation_speed;
    }

    void set_humanoid_look_at(wo_handle const &humanoid, XMFLOAT3 const &v)
    {
        HUMANOID.ptr(humanoid)->lookAt = v;
    }

    XMFLOAT3 get_humanoid_look_at(wo_handle const &humanoid)
    {
        return HUMANOID.ptr(humanoid)->lookAt;
    }

    int32_t humanoid_bone_count(wo_handle const &hum)
    {
        return (int32_t)wi::scene::HumanoidComponent::HumanoidBone::Count;
    }

    wo_handle humanoid_bone(wo_handle const &hum, int32_t i)
    {
        return {WK_ENTITY, HUMANOID.ptr(hum)->bones[i]};
    }

    bool humanoid_is_lookat_enabled(wo_handle const &hum)
    {
        return HUMANOID.ptr(hum)->IsLookAtEnabled();
    }

    void humanoid_set_lookat_enabled(wo_handle const &hum, bool v)
    {
        HUMANOID.ptr(hum)->SetLookAtEnabled(v);
    }

    wo_handle create_layer_component(wo_handle const &scene, wo_handle const &entity)
    {
        return LAYER.handle(&SCENE.ptr(scene)->layers.Create(entity.name));
    }

    wo_handle get_layer_component(wo_handle const &scene, wo_handle const &entity)
    {
        return LAYER.handle(SCENE.ptr(scene)->layers.GetComponent(entity.name));
    }

    int32_t entity_layer_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->layers.GetCount();
    }

    wo_handle entity_layer_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->layers.GetEntity(n)};
    }

    void set_layer_mask(wo_handle const &layer, int32_t v)
    {
        LAYER.ptr(layer)->layerMask = v;
    }

    int32_t get_layer_mask(wo_handle const &layer)
    {
        return LAYER.ptr(layer)->layerMask;
    }

    void set_layer_propagation_mask(wo_handle const &layer, int32_t v)
    {
        LAYER.ptr(layer)->propagationMask = v;
    }

    int32_t get_layer_propagation_mask(wo_handle const &layer)
    {
        return LAYER.ptr(layer)->propagationMask;
    }

    bool is_descendant_entity(wo_handle const &scene, wo_handle const &entity, wo_handle const &ancestor)
    {
        handle_check(entity, WK_ENTITY);
        handle_check(ancestor, WK_ENTITY);
        return SCENE.ptr(scene)->Entity_IsDescendant(entity.name, ancestor.name);
    }

    void remove_entity(wo_handle const &scene, wo_handle const &entity, bool recursive)
    {
        handle_check(entity, WK_ENTITY);
        SCENE.ptr(scene)->Entity_Remove(entity.name, recursive);
    }

    wo_handle duplicate_entity(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return {WK_ENTITY, SCENE.ptr(scene)->Entity_Duplicate(entity.name)};
    }

    void set_collider_shape(wo_handle const &collider, int32_t v)
    {
        COLLIDER.ptr(collider)->shape = (wi::scene::ColliderComponent::Shape)v;
    }

    int32_t get_collider_shape(wo_handle const &collider)
    {
        return (int32_t)COLLIDER.ptr(collider)->shape;
    }

    void set_collider_radius(wo_handle const &collider, float v)
    {
        COLLIDER.ptr(collider)->radius = v;
    }

    float get_collider_radius(wo_handle const &collider)
    {
        return COLLIDER.ptr(collider)->radius;
    }

    void set_collider_offset(wo_handle const &collider, XMFLOAT3 const &v)
    {
        COLLIDER.ptr(collider)->offset = v;
    }

    XMFLOAT3 get_collider_offset(wo_handle const &collider)
    {
        return COLLIDER.ptr(collider)->offset;
    }

    void set_collider_tail(wo_handle const &collider, XMFLOAT3 const &v)
    {
        COLLIDER.ptr(collider)->tail = v;
    }

    XMFLOAT3 get_collider_tail(wo_handle const &collider)
    {
        return COLLIDER.ptr(collider)->tail;
    }

    void set_collider_is_gpu_enabled(wo_handle const &collider, bool v)
    {
        COLLIDER.ptr(collider)->SetGPUEnabled(v);
    }

    void set_collider_is_cpu_enabled(wo_handle const &collider, bool v)
    {
        COLLIDER.ptr(collider)->SetCPUEnabled(v);
    }

    wo_handle create_collider_component(wo_handle const &scene, wo_handle const &entity)
    {
        return COLLIDER.handle(&SCENE.ptr(scene)->colliders.Create(entity.name));
    }

    wo_handle get_collider_component(wo_handle const &scene, wo_handle const &entity)
    {
        return COLLIDER.handle(SCENE.ptr(scene)->colliders.GetComponent(entity.name));
    }

    int32_t entity_collider_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->colliders.GetCount();
    }

    wo_handle entity_collider_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->colliders.GetEntity(n)};
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
        delete MATRIX.ptr(m);
    }

    void assign_matrix(wo_handle const &lhs, wo_handle const &rhs)
    {
        auto lm = MATRIX.ptr(lhs);
        auto rm = MATRIX.ptr(rhs);
        *lm = *rm;
    }

    XMFLOAT3 get_matrix_translation(wo_handle const &matrix)
    {   
        auto mat = XMLoadFloat4x4(MATRIX.ptr(matrix));
        XMVECTOR t, s, r;
        XMFLOAT3 rv;
        XMMatrixDecompose(&s, &r, &t, mat);
        XMStoreFloat3(&rv, t);
        return rv;
    }

    void assign_matrix_rows(wo_handle const &m, XMFLOAT4 const &r1,
                            XMFLOAT4 const &r2, XMFLOAT4 const &r3, XMFLOAT4 const &r4)
    {
        auto mp = MATRIX.ptr(m);
        memcpy(mp->m[0], &r1, sizeof(XMFLOAT4));
        memcpy(mp->m[1], &r2, sizeof(XMFLOAT4)); 
        memcpy(mp->m[2], &r3, sizeof(XMFLOAT4)); 
        memcpy(mp->m[3], &r4, sizeof(XMFLOAT4)); 
    }

    XMFLOAT4 return_matrix_row(wo_handle const &m, int32_t r)
    {
        auto mp = MATRIX.ptr(m);
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
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }
    void translation_matrix(wo_handle const &m, XMFLOAT3 const &v)
    {
        XMMATRIX mat = XMMatrixTranslationFromVector(XMLoadFloat3(&v));
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }


    void rotation_euler_matrix(wo_handle const &m, XMFLOAT3 const &angles)
    {
        XMMATRIX mat = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&angles));
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void rotation_x_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationX(a);
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void rotation_y_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationY(a);
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void rotation_z_matrix(wo_handle const &m, float a)
    {
        auto mat = XMMatrixRotationZ(a);
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void rotation_quat_matrix(wo_handle const &m, XMFLOAT4 const &quat)
    {
        auto mat = XMMatrixRotationQuaternion(XMLoadFloat4(&quat));
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void scaling_matrix(wo_handle const &m, XMFLOAT4 const &scale)
    {
        auto mat = XMMatrixScalingFromVector(XMLoadFloat4(&scale));
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    void look_to_matrix(wo_handle const &m, XMFLOAT3 const &eyepos,
                        XMFLOAT3 const &eyedir, XMFLOAT3 const &up)
    {
        auto mat = XMMatrixLookToLH(XMLoadFloat3(&eyepos), XMLoadFloat3(&eyedir),
                                    XMLoadFloat3(&up)); 
        load_from_xmmatrix(MATRIX.ptr(m), mat); 
    }

    void look_at_matrix(wo_handle const &m, XMFLOAT3 const &eyepos, 
                        XMFLOAT3 const &focuspos, XMFLOAT3 const &up)
    {
        auto mat = XMMatrixLookAtLH(XMLoadFloat3(&eyepos), XMLoadFloat3(&focuspos),
                                    XMLoadFloat3(&up));
        load_from_xmmatrix(MATRIX.ptr(m), mat); 
    }

    void multiply_matrix(wo_handle const &lhs, wo_handle const &rhs, wo_handle const &result)
    {
        auto mat = XMMatrixMultiply(XMLoadFloat4x4(MATRIX.ptr(lhs)),
                                    XMLoadFloat4x4(MATRIX.ptr(rhs)));

        load_from_xmmatrix(MATRIX.ptr(result), mat);
    }

    XMFLOAT4 transform_vector(wo_handle const &matrix, XMFLOAT4 const &v)
    {
        auto mat = XMLoadFloat4x4(MATRIX.ptr(matrix));
        XMFLOAT4 rv;

        XMStoreFloat4(&rv, XMVector4Transform(XMLoadFloat4(&v), mat));
        return rv;
    }


    void add_matrix(wo_handle const &lhs, wo_handle const &rhs, wo_handle const &result)
    {
        auto mat = XMLoadFloat4x4(MATRIX.ptr(lhs)) +  XMLoadFloat4x4(MATRIX.ptr(rhs));
        load_from_xmmatrix(MATRIX.ptr(result), mat);
    }

    void transpose_matrix(wo_handle const &m, wo_handle const& result)
    {
        auto mat = XMMatrixTranspose(XMLoadFloat4x4(MATRIX.ptr(m)));
        load_from_xmmatrix(MATRIX.ptr(result), mat);
    }

    void invert_matrix(wo_handle const &m, wo_handle const &result)
    {
        XMVECTOR det;
        auto mat = XMMatrixInverse(&det, XMLoadFloat4x4(MATRIX.ptr(m)));
        load_from_xmmatrix(MATRIX.ptr(m), mat);
    }

    wo_handle get_transform_local_matrix(wo_handle const &tcomp)
    {
        auto mat = TRANSFORM.ptr(tcomp)->GetLocalMatrix();
        auto rv = create_matrix4x4();
        load_from_xmmatrix(MATRIX.ptr(rv), mat);
        return rv;
    }

    wo_handle get_transform_world_matrix(wo_handle const &tcomp)
    {
        auto rv = create_matrix4x4();
        *MATRIX.ptr(rv) = TRANSFORM.ptr(tcomp)->world;
        return rv;
    }

    void transform_transform_matrix(wo_handle const &tcomp, wo_handle const &matrix)
    {
        TRANSFORM.ptr(tcomp)->MatrixTransform(*MATRIX.ptr(matrix));
    }

    void transform_camera_set_matrix(wo_handle const &camera, wo_handle const &matrix)
    {
        XMMATRIX mat = XMLoadFloat4x4(MATRIX.ptr(matrix));
        CAMERA.ptr(camera)->TransformCamera(mat);
    }

    void transform_camera(wo_handle const &camera, wo_handle const &tcomp)
    {
        CAMERA.ptr(camera)->TransformCamera(*TRANSFORM.ptr(tcomp));
    }

    void set_camera_eye(wo_handle const &camera, XMFLOAT3 const &v)
    {
        CAMERA.ptr(camera)->Eye = v;
    }

    XMFLOAT3 get_camera_eye(wo_handle const &camera)
    {
        return CAMERA.ptr(camera)->Eye;
    }

    void set_camera_at(wo_handle const &camera, XMFLOAT3 const &v)
    {
        CAMERA.ptr(camera)->At = v;
    }

    XMFLOAT3 get_camera_at(wo_handle const &camera)
    {
        return CAMERA.ptr(camera)->At;
    }

    void set_camera_up(wo_handle const &camera, XMFLOAT3 const &v)
    {
        CAMERA.ptr(camera)->Up = v;
    }

    XMFLOAT3 get_camera_up(wo_handle const &camera)
    {
        return CAMERA.ptr(camera)->Up;
    }

    wo_handle get_camera_projection(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->Projection);
    }

    wo_handle get_camera_view(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->View);
    }

    wo_handle get_camera_VP(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->VP);
    }

    wo_handle get_camera_inverse_projection(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->InvProjection);
    }

    wo_handle get_camera_inverse_view(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->InvView);
    }

    wo_handle get_camera_inverse_VP(wo_handle const &tcomp)
    {
        return MATRIX.handle(&CAMERA.ptr(tcomp)->InvVP);
    }

    void set_animation_start(wo_handle const &animation, float v)
    {
        ANIMATION.ptr(animation)->start = v;
    }

    float get_animation_start(wo_handle const &animation)
    {
        return ANIMATION.ptr(animation)->start;
    }

    void set_animation_end(wo_handle const &animation, float v)
    {
        ANIMATION.ptr(animation)->end = v;
    }

    float get_animation_end(wo_handle const &animation)
    {
        return ANIMATION.ptr(animation)->end;
    }

    void set_animation_timer(wo_handle const &animation, float v)
    {
        ANIMATION.ptr(animation)->timer = v;
    }

    float get_animation_timer(wo_handle const &animation)
    {
        return ANIMATION.ptr(animation)->timer;
    }

    void set_animation_amount(wo_handle const &animation, float v)
    {
        ANIMATION.ptr(animation)->amount = v;
    }

    float get_animation_amount(wo_handle const &animation)
    {
        return ANIMATION.ptr(animation)->amount;
    }

    void set_animation_speed(wo_handle const &animation, float v)
    {
        ANIMATION.ptr(animation)->speed = v;
    }

    float get_animation_speed(wo_handle const &animation)
    {
        return ANIMATION.ptr(animation)->speed;
    }

    bool is_animation_playing(wo_handle const &anim)
    {
        return ANIMATION.ptr(anim)->IsPlaying();
    }

    bool is_animation_looped(wo_handle const &anim)
    {
        return ANIMATION.ptr(anim)->IsLooped();
    }

    float get_animation_length(wo_handle const &anim)
    {
        return ANIMATION.ptr(anim)->GetLength();
    }

    float is_animation_ended(wo_handle const &anim)
    {
        return ANIMATION.ptr(anim)->IsEnded();
    }

    void play_animation(wo_handle const &anim)
    {
        ANIMATION.ptr(anim)->Play();
    }

    void pause_animation(wo_handle const &anim)
    {
        ANIMATION.ptr(anim)->Pause();
    }

    void stop_animation(wo_handle const &anim)
    {
        ANIMATION.ptr(anim)->Stop();
    }

    void set_animation_looped(wo_handle const &anim, bool v)
    {
        ANIMATION.ptr(anim)->SetLooped(v);
    }

    wo_handle create_animation_component(wo_handle const &scene, wo_handle const &entity)
    {
        return ANIMATION.handle(&SCENE.ptr(scene)->animations.Create(entity.name));
    }

    wo_handle get_animation_component(wo_handle const &scene, wo_handle const &entity)
    {
        return ANIMATION.handle(SCENE.ptr(scene)->animations.GetComponent(entity.name));
    }

    int32_t entity_animation_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->animations.GetCount();
    }

    wo_handle entity_animation_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY,
            SCENE.ptr(scene)->animations.GetEntity(n)};
    }

    wo_handle retarget_animation(wo_handle const &scene,
                                 wo_handle const &dest_entity,
                                 wo_handle const &src_entity, bool bake_data)
    {
        handle_check(dest_entity, WK_ENTITY);
        handle_check(src_entity, WK_ENTITY);

        return {WK_ENTITY,
            SCENE.ptr(scene)->RetargetAnimation(dest_entity.name, src_entity.name, bake_data)};
    }

    void set_renderpath3d_exposure(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setExposure(v);
    }

    float get_renderpath3d_exposure(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getExposure();
    }

    void set_renderpath3d_brightness(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setBrightness(v);
    }

    float get_renderpath3d_brightness(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getBrightness();
    }

    void set_renderpath3d_contrast(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setContrast(v);
    }

    float get_renderpath3d_contrast(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getContrast();
    }

    void set_renderpath3d_saturation(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setSaturation(v);
    }

    float get_renderpath3d_saturation(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getSaturation();
    }

    void set_renderpath3d_bloom_threshold(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setBloomThreshold(v);
    }

    float get_renderpath3d_bloom_threshold(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getBloomThreshold();
    }

    void set_renderpath3d_motion_blur_strength(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setMotionBlurStrength(v);
    }

    float get_renderpath3d_motion_blur_strength(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getMotionBlurStrength();
    }

    void set_renderpath3d_depth_of_field_strength(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setDepthOfFieldStrength(v);
    }

    float get_renderpath3d_depth_of_field_strength(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getDepthOfFieldStrength();
    }

    void set_renderpath3d_sharpen_filter_amount(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setSharpenFilterAmount(v);
    }

    float get_renderpath3d_sharpen_filter_amount(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getSharpenFilterAmount();
    }

    void set_renderpath3d_outline_threshold(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setOutlineThreshold(v);
    }

    float get_renderpath3d_outline_threshold(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getOutlineThreshold();
    }

    void set_renderpath3d_outline_thickness(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setOutlineThickness(v);
    }

    float get_renderpath3d_outline_thickness(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getOutlineThickness();
    }

    void set_renderpath3d_outline_color(wo_handle const &renderpath3d, XMFLOAT4 const &v)
    {
        RENDERPATH.ptr(renderpath3d)->setOutlineColor(v);
    }

    XMFLOAT4 get_renderpath3d_outline_color(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getOutlineColor();
    }

    void set_renderpath3d_ao_range(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setAORange(v);
    }

    float get_renderpath3d_ao_range(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getAORange();
    }

    void set_renderpath3d_ao_sample_count(wo_handle const &renderpath3d, int32_t v)
    {
        RENDERPATH.ptr(renderpath3d)->setAOSampleCount(v);
    }

    int32_t get_renderpath3d_ao_sample_count(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getAOSampleCount();
    }

    void set_renderpath3d_ao_power(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setAOPower(v);
    }

    float get_renderpath3d_ao_power(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getAOPower();
    }

    void set_renderpath3d_chromatic_aberration_amount(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setChromaticAberrationAmount(v);
    }

    float get_renderpath3d_chromatic_aberration_amount(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getChromaticAberrationAmount();
    }

    void set_renderpath3d_screen_space_shadow_sample_count(wo_handle const &renderpath3d, int32_t v)
    {
        RENDERPATH.ptr(renderpath3d)->setScreenSpaceShadowSampleCount(v);
    }

    int32_t get_renderpath3d_screen_space_shadow_sample_count(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getScreenSpaceShadowSampleCount();
    }

    void set_renderpath3d_screen_space_shadow_range(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setScreenSpaceShadowRange(v);
    }

    float get_renderpath3d_screen_space_shadow_range(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getScreenSpaceShadowRange();
    }

    void set_renderpath3d_eye_adaption_key(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setEyeAdaptionKey(v);
    }

    float get_renderpath3d_eye_adaption_key(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getEyeAdaptionKey();
    }

    void set_renderpath3d_eye_adaption_rate(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setEyeAdaptionRate(v);
    }

    float get_renderpath3d_eye_adaption_rate(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getEyeAdaptionRate();
    }

    void set_renderpath3d_fsr_sharpness(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setFSRSharpness(v);
    }

    float get_renderpath3d_fsr_sharpness(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getFSRSharpness();
    }

    void set_renderpath3d_fsr2_sharpness(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setFSR2Sharpness(v);
    }

    float get_renderpath3d_fsr2_sharpness(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getFSR2Sharpness();
    }

    void set_renderpath3d_light_shafts_strength(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setLightShaftsStrength(v);
    }

    float get_renderpath3d_light_shafts_strength(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getLightShaftsStrength();
    }

    void set_renderpath3d_raytraced_diffuse_range(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setRaytracedDiffuseRange(v);
    }

    float get_renderpath3d_raytraced_diffuse_range(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getRaytracedDiffuseRange();
    }

    void set_renderpath3d_raytraced_reflections_range(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setRaytracedReflectionsRange(v);
    }

    float get_renderpath3d_raytraced_reflections_range(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getRaytracedReflectionsRange();
    }

    void set_renderpath3d_reflection_roughness_cutoff(wo_handle const &renderpath3d, float v)
    {
        RENDERPATH.ptr(renderpath3d)->setReflectionRoughnessCutoff(v);
    }

    float get_renderpath3d_reflection_roughness_cutoff(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getReflectionRoughnessCutoff();
    }

    void set_renderpath3d_ao(wo_handle const &renderpath3d, int32_t v)
    {
        RENDERPATH.ptr(renderpath3d)->setAO((wi::RenderPath3D::AO)v);
    }

    bool get_renderpath3d_ao_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getAOEnabled();
    }

    void set_renderpath3d_ssr_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setSSREnabled(v);
    }

    bool get_renderpath3d_ssr_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getSSREnabled();
    }

    void set_renderpath3d_raytraced_diffuse_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setRaytracedDiffuseEnabled(v);
    }

    bool get_renderpath3d_raytraced_diffuse_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getRaytracedDiffuseEnabled();
    }

    void set_renderpath3d_raytraced_reflection_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setRaytracedReflectionsEnabled(v);
    }

    bool get_renderpath3d_raytraced_reflection_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getRaytracedReflectionEnabled();
    }

    void set_renderpath3d_shadows_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setShadowsEnabled(v);
    }

    bool get_renderpath3d_shadows_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getShadowsEnabled();
    }

    void set_renderpath3d_reflections_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setReflectionsEnabled(v);
    }

    bool get_renderpath3d_reflections_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getReflectionsEnabled();
    }

    void set_renderpath3d_fxaa_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setFXAAEnabled(v);
    }

    bool get_renderpath3d_fxaa_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getFXAAEnabled();
    }

    void set_renderpath3d_bloom_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setBloomEnabled(v);
    }

    bool get_renderpath3d_bloom_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getBloomEnabled();
    }

    void set_renderpath3d_color_grading_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setColorGradingEnabled(v);
    }

    bool get_renderpath3d_color_grading_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getColorGradingEnabled();
    }

    void set_renderpath3d_volume_lights_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setVolumeLightsEnabled(v);
    }

    bool get_renderpath3d_volume_lights_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getVolumeLightsEnabled();
    }

    void set_renderpath3d_light_shafts_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setLightShaftsEnabled(v);
    }

    bool get_renderpath3d_light_shafts_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getLightShaftsEnabled();
    }

    void set_renderpath3d_lens_flare_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setLensFlareEnabled(v);
    }

    bool get_renderpath3d_lens_flare_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getLensFlareEnabled();
    }

    void set_renderpath3d_motion_blur_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setMotionBlurEnabled(v);
    }

    bool get_renderpath3d_motion_blur_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getMotionBlurEnabled();
    }

    void set_renderpath3d_depth_of_field_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setDepthOfFieldEnabled(v);
    }

    bool get_renderpath3d_depth_of_field_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getDepthOfFieldEnabled();
    }

    void set_renderpath3d_eye_adaptation_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setEyeAdaptionEnabled(v);
    }

    bool get_renderpath3d_eye_adaptation_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getEyeAdaptionEnabled();
    }

    void set_renderpath3d_sharpen_filter_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setSharpenFilterEnabled(v);
    }

    bool get_renderpath3d_sharpen_filter_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getSharpenFilterEnabled();
    }

    void set_renderpath3d_outline_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setOutlineEnabled(v);
    }

    bool get_renderpath3d_outline_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getOutlineEnabled();
    }

    void set_renderpath3d_chromatic_aberration_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setChromaticAberrationEnabled(v);
    }

    bool get_renderpath3d_chromatic_aberration_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getChromaticAberrationEnabled();
    }

    void set_renderpath3d_dither_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setDitherEnabled(v);
    }

    bool get_renderpath3d_dither_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getDitherEnabled();
    }

    void set_renderpath3d_occlusion_culling_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setOcclusionCullingEnabled(v);
    }

    bool get_renderpath3d_occlusion_culling_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getOcclusionCullingEnabled();
    }

    void set_renderpath3d_scene_update_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setSceneUpdateEnabled(v);
    }

    bool get_renderpath3d_scene_update_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getSceneUpdateEnabled();
    }

    void set_renderpath3d_fsr_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setFSREnabled(v);
    }

    bool get_renderpath3d_fsr_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getFSREnabled();
    }

    void set_renderpath3d_fsr2_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setFSR2Enabled(v);
    }

    bool get_renderpath3d_fsr2_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getFSR2Enabled();
    }

    void set_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const &renderpath3d, bool v)
    {
        RENDERPATH.ptr(renderpath3d)->setVXGIResolveFullResolutionEnabled(v);
    }

    bool get_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const &renderpath3d)
    {
        return RENDERPATH.ptr(renderpath3d)->getVXGIResolveFullResolutionEnabled();
    }

    void renderer_set_vxgi_enabled(bool v)
    {
        wi::renderer::SetVXGIEnabled(v);
    }

    bool renderer_vxgi_enabled()
    {
        return wi::renderer::GetVXGIEnabled();
    }

    wo_handle create_primitive_sphere()
    {
        return SPHERE.handle(new wi::primitive::Sphere());
    }

    void delete_primitive_sphere(wo_handle const &primitive_sphere)
    {
        delete SPHERE.ptr(primitive_sphere);
    }

    void set_primitive_sphere_center(wo_handle const &primitive_sphere, XMFLOAT3 const &v)
    {
        SPHERE.ptr(primitive_sphere)->center = v;
    }

    XMFLOAT3 get_primitive_sphere_center(wo_handle const &primitive_sphere)
    {
        return SPHERE.ptr(primitive_sphere)->center;
    }

    void set_primitive_sphere_radius(wo_handle const &primitive_sphere, float v)
    {
        SPHERE.ptr(primitive_sphere)->radius = v;
    }

    float get_primitive_sphere_radius(wo_handle const &primitive_sphere)
    {
        return SPHERE.ptr(primitive_sphere)->radius;
    }

    bool sphere_sphere_intersects(wo_handle const &sphere0, wo_handle const &sphere1, float &retval2, XMFLOAT3 &retval3)
    {
        return SPHERE.ptr(sphere0)->intersects(*SPHERE.ptr(sphere1), retval2, retval3);
    }

    wo_handle create_sphere_intersection_result()
    {
        return SPHERE_INTERSECTION.handle(new wi::scene::Scene::SphereIntersectionResult());
    }

    void delete_sphere_intersection_result(wo_handle const &sphere_intersection_result)
    {
        delete SPHERE_INTERSECTION.ptr(sphere_intersection_result);
    }

    void set_sphere_intersection_result_entity(wo_handle const &sphere_intersection_result, wo_handle const &v)
    {
        handle_check(v, WK_ENTITY);
        SPHERE_INTERSECTION.ptr(sphere_intersection_result)->entity = v.name;
    }

    wo_handle get_sphere_intersection_result_entity(wo_handle const &sphere_intersection_result)
    {
        return {WK_ENTITY, SPHERE_INTERSECTION.ptr(sphere_intersection_result)->entity};
    }

    void set_sphere_intersection_result_position(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        SPHERE_INTERSECTION.ptr(sphere_intersection_result)->position = v;
    }

    XMFLOAT3 get_sphere_intersection_result_position(wo_handle const &sphere_intersection_result)
    {
        return SPHERE_INTERSECTION.ptr(sphere_intersection_result)->position;
    }

    void set_sphere_intersection_result_normal(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        SPHERE_INTERSECTION.ptr(sphere_intersection_result)->normal = v;
    }

    XMFLOAT3 get_sphere_intersection_result_normal(wo_handle const &sphere_intersection_result)
    {
        return SPHERE_INTERSECTION.ptr(sphere_intersection_result)->normal;
    }

    void set_sphere_intersection_result_velocity(wo_handle const &sphere_intersection_result, XMFLOAT3 const &v)
    {
        SPHERE_INTERSECTION.ptr(sphere_intersection_result)->velocity = v;
    }

    XMFLOAT3 get_sphere_intersection_result_velocity(wo_handle const &sphere_intersection_result)
    {
        return SPHERE_INTERSECTION.ptr(sphere_intersection_result)->velocity;
    }

    void set_sphere_intersection_result_depth(wo_handle const &sphere_intersection_result, float v)
    {
        SPHERE_INTERSECTION.ptr(sphere_intersection_result)->depth = v;
    }

    float get_sphere_intersection_result_depth(wo_handle const &sphere_intersection_result)
    {
        return SPHERE_INTERSECTION.ptr(sphere_intersection_result)->depth;
    }

    wo_handle scene_sphere_intersects(wo_handle const &scene, wo_handle const &sphere, int32_t filter_mask, int32_t layer_mask, int32_t lod)
    {
        auto rv = new wi::scene::Scene::SphereIntersectionResult();
        *rv = SCENE.ptr(scene)->Intersects(*SPHERE.ptr(sphere), filter_mask, layer_mask, lod);
        return SPHERE_INTERSECTION.handle(rv);
    }

    wo_handle create_primitive_capsule()
    {
        return CAPSULE.handle(new wi::primitive::Capsule());
    }

    void delete_primitive_capsule(wo_handle const &primitive_capsule)
    {
        delete CAPSULE.ptr(primitive_capsule);
    }

    void set_primitive_capsule_base(wo_handle const &primitive_capsule, XMFLOAT3 const &v)
    {
        CAPSULE.ptr(primitive_capsule)->base = v;
    }

    XMFLOAT3 get_primitive_capsule_base(wo_handle const &primitive_capsule)
    {
        return CAPSULE.ptr(primitive_capsule)->base;
    }

    void set_primitive_capsule_tip(wo_handle const &primitive_capsule, XMFLOAT3 const &v)
    {
        CAPSULE.ptr(primitive_capsule)->tip = v;
    }

    XMFLOAT3 get_primitive_capsule_tip(wo_handle const &primitive_capsule)
    {
        return CAPSULE.ptr(primitive_capsule)->tip;
    }

    void set_primitive_capsule_radius(wo_handle const &primitive_capsule, float v)
    {
        CAPSULE.ptr(primitive_capsule)->radius = v;
    }

    float get_primitive_capsule_radius(wo_handle const &primitive_capsule)
    {
        return CAPSULE.ptr(primitive_capsule)->radius;
    }

    bool capsule_capsule_intersects(wo_handle const &cap0, wo_handle const &cap1, XMFLOAT3 &retval2, XMFLOAT3 &retval3, float &retval4)
    {
        return CAPSULE.ptr(cap0)->intersects(*CAPSULE.ptr(cap1), retval2, retval3, retval4); 
    }

    bool capsule_sphere_intersects(wo_handle const &cap, wo_handle const &sphere, float &retval2, XMFLOAT3 &retval3)
    {
        return CAPSULE.ptr(cap)->intersects(*SPHERE.ptr(sphere), retval2, retval3);
    }

    bool sphere_capsule_intersects(wo_handle const &sphere, wo_handle const &cap, float &retval2, XMFLOAT3 &retval3)
    {
        return SPHERE.ptr(sphere)->intersects(*CAPSULE.ptr(cap), retval2, retval3);
    }

    wo_handle scene_capsule_intersects(wo_handle const &scene, wo_handle const &cap, int32_t filter_mask, int32_t layer_mask, int32_t lod)
    {
        auto rv = create_sphere_intersection_result();
        *SPHERE_INTERSECTION.ptr(rv) = SCENE.ptr(scene)->Intersects(*CAPSULE.ptr(cap), filter_mask, layer_mask, lod);
        return rv;
    }

    wo_handle get_collider_capsule(wo_handle const &collider)
    {
        return CAPSULE.handle(&COLLIDER.ptr(collider)->capsule);
    }

    void set_rigidbody_physics_shape(wo_handle const &rigidbody_physics, int32_t v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->shape = (wi::scene::RigidBodyPhysicsComponent::CollisionShape)v;
    }

    int32_t get_rigidbody_physics_shape(wo_handle const &rigidbody_physics)
    {
        return (int32_t)RIGIDBODY.ptr(rigidbody_physics)->shape;
    }

    void set_rigidbody_physics_mass(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->mass = v;
    }

    float get_rigidbody_physics_mass(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->mass;
    }

    void set_rigidbody_physics_friction(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->friction = v;
    }

    float get_rigidbody_physics_friction(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->friction;
    }

    void set_rigidbody_physics_restitution(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->restitution = v;
    }

    float get_rigidbody_physics_restitution(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->restitution;
    }

    void set_rigidbody_physics_damping_linear(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->damping_linear = v;
    }

    float get_rigidbody_physics_damping_linear(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->damping_linear;
    }

    void set_rigidbody_physics_damping_angular(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->damping_angular = v;
    }

    float get_rigidbody_physics_damping_angular(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->damping_angular;
    }

    void set_rigidbody_physics_box_halfextents(wo_handle const &rigidbody_physics, XMFLOAT3 const &v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->box.halfextents = v;
    }

    XMFLOAT3 get_rigidbody_physics_box_halfextents(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->box.halfextents;
    }

    void set_rigidbody_physics_sphere_radius(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->sphere.radius = v;
    }

    float get_rigidbody_physics_sphere_radius(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->sphere.radius;
    }

    void set_rigidbody_physics_capsule_radius(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->capsule.radius = v;
    }

    float get_rigidbody_physics_capsule_radius(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->capsule.radius;
    }

    void set_rigidbody_physics_capsule_height(wo_handle const &rigidbody_physics, float v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->capsule.height = v;
    }

    float get_rigidbody_physics_capsule_height(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->capsule.height;
    }

    void set_rigidbody_physics_mesh_lod(wo_handle const &rigidbody_physics, int32_t v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->mesh_lod = v;
    }

    int32_t get_rigidbody_physics_mesh_lod(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->mesh_lod;
    }

    void set_rigidbody_physics_disable_deactivation(wo_handle const &rigidbody_physics, bool v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->SetDisableDeactivation(v);
    }

    bool get_rigidbody_physics_disable_deactivation(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->IsDisableDeactivation();
    }

    void set_rigidbody_physics_kinematic(wo_handle const &rigidbody_physics, bool v)
    {
        RIGIDBODY.ptr(rigidbody_physics)->SetKinematic(v);
    }

    bool get_rigidbody_physics_kinematic(wo_handle const &rigidbody_physics)
    {
        return RIGIDBODY.ptr(rigidbody_physics)->IsKinematic();
    }

    wo_handle create_rigidbody_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return RIGIDBODY.handle(&SCENE.ptr(scene)->rigidbodies.Create(entity.name));
    }

    wo_handle get_rigidbody_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return RIGIDBODY.handle(SCENE.ptr(scene)->rigidbodies.GetComponent(entity.name));
    }

    int32_t entity_rigidbody_count(wo_handle const &scene)
    {          
        return (int32_t)SCENE.ptr(scene)->rigidbodies.GetCount();
    }


    wo_handle entity_rigidbody_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->rigidbodies.GetEntity(n)};
    }

    void set_object_mesh_id(wo_handle const &object, wo_handle const &v)
    {
        handle_check(v, WK_ENTITY);
        OBJECT.ptr(object)->meshID = v.name;
    }

    wo_handle get_object_mesh_id(wo_handle const &object)
    {
        return {WK_ENTITY, OBJECT.ptr(object)->meshID};
    }

    void set_object_cascade_mask(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->cascadeMask = v;
    }

    int32_t get_object_cascade_mask(wo_handle const &object)
    {
        return OBJECT.ptr(object)->cascadeMask;
    }

    void set_object_filter_mask(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->filterMask = v;
    }

    int32_t get_object_filter_mask(wo_handle const &object)
    {
        return OBJECT.ptr(object)->filterMask;
    }

    void set_object_color(wo_handle const &object, XMFLOAT4 const &v)
    {
        OBJECT.ptr(object)->color = v;
    }

    XMFLOAT4 get_object_color(wo_handle const &object)
    {
        return OBJECT.ptr(object)->color;
    }

    void set_object_emissive_color(wo_handle const &object, XMFLOAT4 const &v)
    {
        OBJECT.ptr(object)->emissiveColor = v;
    }

    XMFLOAT4 get_object_emissive_color(wo_handle const &object)
    {
        return OBJECT.ptr(object)->emissiveColor;
    }

    void set_object_user_stencil_ref(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->userStencilRef = (uint8_t)v;
    }

    int32_t get_object_user_stencil_ref(wo_handle const &object)
    {
        return OBJECT.ptr(object)->userStencilRef;
    }

    void set_object_lod_distance_multiplier(wo_handle const &object, float v)
    {
        OBJECT.ptr(object)->lod_distance_multiplier = v;
    }

    float get_object_lod_distance_multiplier(wo_handle const &object)
    {
        return OBJECT.ptr(object)->lod_distance_multiplier;
    }

    void set_object_draw_distance(wo_handle const &object, float v)
    {
        OBJECT.ptr(object)->draw_distance = v;
    }

    float get_object_draw_distance(wo_handle const &object)
    {
        return OBJECT.ptr(object)->draw_distance;
    }

    void set_object_lightmap_width(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->lightmapWidth = v;
    }

    int32_t get_object_lightmap_width(wo_handle const &object)
    {
        return OBJECT.ptr(object)->lightmapWidth;
    }

    void set_object_lightmap_height(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->lightmapHeight = v;
    }

    int32_t get_object_lightmap_height(wo_handle const &object)
    {
        return OBJECT.ptr(object)->lightmapHeight;
    }

    void set_object_sort_priority(wo_handle const &object, int32_t v)
    {
        OBJECT.ptr(object)->sort_priority = v;
    }

    int32_t get_object_sort_priority(wo_handle const &object)
    {
        return OBJECT.ptr(object)->sort_priority;
    }

    wo_handle create_object_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return OBJECT.handle(&SCENE.ptr(scene)->objects.Create(entity.name));
    }

    wo_handle get_object_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return OBJECT.handle(SCENE.ptr(scene)->objects.GetComponent(entity.name));
    }

    int32_t entity_object_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->objects.GetCount();
    }

    wo_handle entity_object_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->objects.GetEntity(n)};
    }

    void set_hierarchy_parent_id(wo_handle const &hierarchy, wo_handle const &v)
    {
        handle_check(v, WK_ENTITY);
        HIERARCHY.ptr(hierarchy)->parentID = v.name;
    }

    wo_handle get_hierarchy_parent_id(wo_handle const &hierarchy)
    {
        return {WK_ENTITY, HIERARCHY.ptr(hierarchy)->parentID};
    }

    void set_hierarchy_layermask_bind(wo_handle const &hierarchy, int32_t v)
    {
        HIERARCHY.ptr(hierarchy)->layerMask_bind = v;
    }

    int32_t get_hierarchy_layermask_bind(wo_handle const &hierarchy)
    {
        return HIERARCHY.ptr(hierarchy)->layerMask_bind;
    }

    wo_handle create_hierarchy_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return HIERARCHY.handle(&SCENE.ptr(scene)->hierarchy.Create(entity.name));
    }

    wo_handle get_hierarchy_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return HIERARCHY.handle(SCENE.ptr(scene)->hierarchy.GetComponent(entity.name));
    }

    int32_t entity_hierarchy_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->hierarchy.GetCount();
    }

    wo_handle entity_hierarchy_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->hierarchy.GetEntity(n)};
    }

    void set_light_type(wo_handle const &light, int32_t v)
    {
        LIGHT.ptr(light)->type = (wi::scene::LightComponent::LightType)v;
    }

    int32_t get_light_type(wo_handle const &light)
    {
        return LIGHT.ptr(light)->type;
    }

    void set_light_color(wo_handle const &light, XMFLOAT3 const &v)
    {
        LIGHT.ptr(light)->color = v;
    }

    XMFLOAT3 get_light_color(wo_handle const &light)
    {
        return LIGHT.ptr(light)->color;
    }

    void set_light_intensity(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->intensity = v;
    }

    float get_light_intensity(wo_handle const &light)
    {
        return LIGHT.ptr(light)->intensity;
    }

    void set_light_range(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->range = v;
    }

    float get_light_range(wo_handle const &light)
    {
        return LIGHT.ptr(light)->range;
    }

    void set_light_outer_cone_angle(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->outerConeAngle = v;
    }

    float get_light_outer_cone_angle(wo_handle const &light)
    {
        return LIGHT.ptr(light)->outerConeAngle;
    }

    void set_light_inner_cone_angle(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->innerConeAngle = v;
    }

    float get_light_inner_cone_angle(wo_handle const &light)
    {
        return LIGHT.ptr(light)->innerConeAngle;
    }

    void set_light_radius(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->radius = v;
    }

    float get_light_radius(wo_handle const &light)
    {
        return LIGHT.ptr(light)->radius;
    }

    void set_light_length(wo_handle const &light, float v)
    {
        LIGHT.ptr(light)->length = v;
    }

    float get_light_length(wo_handle const &light)
    {
        return LIGHT.ptr(light)->length;
    }

    void set_light_casts_shadow(wo_handle const &light, bool v)
    {
        LIGHT.ptr(light)->SetCastShadow(v);
    }

    bool get_light_casts_shadow(wo_handle const &light)
    {
        return LIGHT.ptr(light)->IsCastingShadow();
    }

    void set_light_volumetrics_enabled(wo_handle const &light, bool v)
    {
        LIGHT.ptr(light)->SetVolumetricsEnabled(v);
    }

    bool get_light_volumetrics_enabled(wo_handle const &light)
    {
        return LIGHT.ptr(light)->IsVolumetricsEnabled();
    }

    void set_light_visualizer_enabled(wo_handle const &light, bool v)
    {
        LIGHT.ptr(light)->SetVisualizerEnabled(v);
    }

    bool get_light_visualizer_enabled(wo_handle const &light)
    {
        return LIGHT.ptr(light)->IsVisualizerEnabled();
    }

    void set_light_is_static(wo_handle const &light, bool v)
    {
        LIGHT.ptr(light)->SetStatic(v);
    }

    bool get_light_is_static(wo_handle const &light)
    {
        return LIGHT.ptr(light)->IsStatic();
    }

    void set_light_volumetric_clouds_enabled(wo_handle const &light, bool v)
    {
        LIGHT.ptr(light)->SetVolumetricCloudsEnabled(v);
    }

    bool get_light_volumetric_clouds_enabled(wo_handle const &light)
    {
        return LIGHT.ptr(light)->IsVolumetricCloudsEnabled();
    }

    wo_handle create_light_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return LIGHT.handle(&SCENE.ptr(scene)->lights.Create(entity.name));
    }

    wo_handle get_light_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return LIGHT.handle(SCENE.ptr(scene)->lights.GetComponent(entity.name));
    }

    int32_t entity_light_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->lights.GetCount();
    }

    wo_handle entity_light_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->lights.GetEntity(n)};
    }

    void set_resource_sound(wo_handle const &resource, wo_handle const &sound)
    {
        RESOURCE.ptr(resource)->SetSound(*SOUND.ptr(sound));
    }

    void set_resource_outdated(wo_handle const &resource)
    {
        RESOURCE.ptr(resource)->SetOutdated();
    }

    void set_sound_instance_loop_begin(wo_handle const &sound_instance, float v)
    {
        SOUND_INSTANCE.ptr(sound_instance)->loop_begin = v;
    }

    float get_sound_instance_loop_begin(wo_handle const &sound_instance)
    {
        return SOUND_INSTANCE.ptr(sound_instance)->loop_begin;
    }

    void set_sound_instance_loop_length(wo_handle const &sound_instance, float v)
    {
        SOUND_INSTANCE.ptr(sound_instance)->loop_length = v;
    }

    float get_sound_instance_loop_length(wo_handle const &sound_instance)
    {
        return SOUND_INSTANCE.ptr(sound_instance)->loop_length;
    }

    void set_sound_instance_reverb_enabled(wo_handle const &sound_instance, bool v)
    {
        SOUND_INSTANCE.ptr(sound_instance)->SetEnableReverb(v);
    }

    bool get_sound_instance_reverb_enabled(wo_handle const &sound_instance)
    {
        return SOUND_INSTANCE.ptr(sound_instance)->IsEnableReverb();
    }

    bool sound_instance_is_valid(wo_handle const &sound_instance)
    {
        return SOUND_INSTANCE.ptr(sound_instance)->IsValid();
    }

    void set_sound_component_filename(wo_handle const &sound_component, std::string_view const &v)
    {
        SOUND_COMP.ptr(sound_component)->filename = string(v);
    }

    std::string_view get_sound_component_filename(wo_handle const &sound_component)
    {
        return SOUND_COMP.ptr(sound_component)->filename;
    }

    void set_sound_component_resource(wo_handle const &sound_component, wo_handle const &v)
    {
        SOUND_COMP.ptr(sound_component)->soundResource = *RESOURCE.ptr(v);
    }

    wo_handle get_sound_component_resource(wo_handle const &sound_component)
    {
        return RESOURCE.handle(&SOUND_COMP.ptr(sound_component)->soundResource);
    }

    void set_sound_component_instance(wo_handle const &sound_component, wo_handle const &v)
    {
        SOUND_COMP.ptr(sound_component)->soundinstance = *SOUND_INSTANCE.ptr(v);
    }

    wo_handle get_sound_component_instance(wo_handle const &sound_component)
    {
        return SOUND_INSTANCE.handle(&SOUND_COMP.ptr(sound_component)->soundinstance);
    }

    void set_sound_component_volume(wo_handle const &sound_component, float v)
    {
        SOUND_COMP.ptr(sound_component)->volume = v;
    }

    float get_sound_component_volume(wo_handle const &sound_component)
    {
        return SOUND_COMP.ptr(sound_component)->volume;
    }

    void set_sound_component_is_playing(wo_handle const &sound_component, bool v)
    {
        if (v) {
            SOUND_COMP.ptr(sound_component)->Play();
        } else {
            SOUND_COMP.ptr(sound_component)->Stop();
        }
    }

    bool get_sound_component_is_playing(wo_handle const &sound_component)
    {
        return SOUND_COMP.ptr(sound_component)->IsPlaying();
    }

    void set_sound_component_is_looped(wo_handle const &sound_component, bool v)
    {
        SOUND_COMP.ptr(sound_component)->SetLooped(v);
    }

    bool get_sound_component_is_looped(wo_handle const &sound_component)
    {
        return SOUND_COMP.ptr(sound_component)->IsLooped();
    }

    void set_sound_component_is_disable_3d(wo_handle const &sound_component, bool v)
    {
        SOUND_COMP.ptr(sound_component)->SetDisable3D(v);
    }

    bool get_sound_component_is_disable_3d(wo_handle const &sound_component)
    {
        return SOUND_COMP.ptr(sound_component)->IsDisable3D();
    }

    wo_handle create_sound_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return SOUND_COMP.handle(&SCENE.ptr(scene)->sounds.Create(entity.name));
    }

    wo_handle get_sound_component(wo_handle const &scene, wo_handle const &entity)
    {
        handle_check(entity, WK_ENTITY);
        return SOUND_COMP.handle(SCENE.ptr(scene)->sounds.GetComponent(entity.name));
    }

    int32_t entity_sound_count(wo_handle const &scene)
    {
        return (int32_t)SCENE.ptr(scene)->sounds.GetCount();
    }

    wo_handle entity_sound_get(wo_handle const &scene, int32_t n)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->sounds.GetEntity(n)};
    }

    wo_handle scene_create_sound_entity(wo_handle const &scene, std::string_view const &name, std::string_view const &filename, XMFLOAT3 const &pos)
    {
        return {WK_ENTITY, SCENE.ptr(scene)->Entity_CreateSound(string(name), string(filename), pos)};
    }
}
