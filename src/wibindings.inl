// GENERATED for inclusion in wibindings.h by tools/bindgen.lobster, do not edit
wo_handle get_transform_component(wo_handle const& scene, wo_handle const& entity);
wo_handle new_scene();
void delete_scene(wo_handle const& scene);
wo_handle global_scene();
void scene_merge(wo_handle const& dest, wo_handle const& src);
wo_handle load_model(wo_handle const& scene, std::string_view const& fname, bool attach);
wo_handle create_entity();
wo_handle create_name_component(wo_handle const& scene, wo_handle const& entity);
void nc_set_name(wo_handle const& name_comp, std::string_view const& name);
std::string_view nc_get_name(wo_handle const& name_comp);
wo_handle get_name_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_names_count(wo_handle const& scene);
wo_handle entity_names_get(wo_handle const& scene, int32_t n);
wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const& name, wo_handle const& ancestor_entity);
void backlog(int32_t level, std::string_view const& msg);
wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity);
wo_handle create_transform_component(wo_handle const& scene, wo_handle const& entity);
float get_fixed_update_rate();
void renderpath3d_set_camera(wo_handle const& rpath, wo_handle const& cam_component);
void transform_translate(wo_handle const& trans_component, XMFLOAT3 const& v);
void transform_rotate(wo_handle const& trans_component, XMFLOAT4 const& quat);
XMFLOAT3 transform_position(wo_handle const& tcomp);
XMFLOAT4 transform_rotation(wo_handle const& tcomp);
void transform_update_transform(wo_handle const& tcomp);
void transform_clear(wo_handle const& trans_comp);
void transform_rotate_roll_pitch_yaw(wo_handle const& tcomp, XMFLOAT3 const& angles);
void transform_scale(wo_handle const& tcomp, XMFLOAT3 const& scale);
void transform_lerp(wo_handle const& tcomp, wo_handle const& a, wo_handle const& b, float t);
float camera_fov(wo_handle const& tcomp);
void camera_set_fov(wo_handle const& tcomp, float fov);
XMFLOAT2 camera_get_dims(wo_handle const& tcomp);
void camera_set_dims(wo_handle const& tcomp, XMFLOAT2 const& dims);
float camera_znear(wo_handle const& tcomp);
void camera_set_znear(wo_handle const& tcomp, float znear);
float camera_zfar(wo_handle const& tcomp);
void camera_set_zfar(wo_handle const& tcomp, float zfar);
float camera_focal_length(wo_handle const& tcomp);
void camera_set_focal_length(wo_handle const& tcomp, float l);
void camera_update(wo_handle const& tcomp);
wo_handle get_camera_component(wo_handle const& scene, wo_handle const& ent);
int32_t get_camera_count(wo_handle const& scene);
wo_handle get_camera_entity(wo_handle const& scene, int32_t n);
bool input_down(int32_t button, int32_t playerindex);
bool input_press(int32_t button, int32_t playerindex);
bool input_hold(int32_t button, int32_t frames, bool continuous, int32_t playerindex);
XMFLOAT4 input_get_pointer();
void input_set_pointer(XMFLOAT4 const& props);
void input_hide_pointer(bool value);
XMFLOAT4 input_get_analog(int32_t axis, int32_t playerindex);
void draw_debug_text(std::string_view const& text, XMFLOAT3 const& pos, int32_t flags, XMFLOAT4 const& color, float scaling);
wo_handle create_timer();
void delete_timer(wo_handle const& timer);
void timer_record(wo_handle const& timer);
double timer_elapsed_seconds(wo_handle const& time);
double timer_elapsed(wo_handle const& timer);
wo_handle create_font_params();
void delete_font_params(wo_handle const& font_params);
void set_font_params_position(wo_handle const& font_params, XMFLOAT3 const& v);
XMFLOAT3 get_font_params_position(wo_handle const& font_params);
void set_font_params_size(wo_handle const& font_params, int32_t v);
int32_t get_font_params_size(wo_handle const& font_params);
void set_font_params_scaling(wo_handle const& font_params, float v);
float get_font_params_scaling(wo_handle const& font_params);
void set_font_params_rotation(wo_handle const& font_params, float v);
float get_font_params_rotation(wo_handle const& font_params);
void set_font_params_spacing_x(wo_handle const& font_params, float v);
float get_font_params_spacing_x(wo_handle const& font_params);
void set_font_params_spacing_y(wo_handle const& font_params, float v);
float get_font_params_spacing_y(wo_handle const& font_params);
void set_font_params_h_align(wo_handle const& font_params, int32_t v);
int32_t get_font_params_h_align(wo_handle const& font_params);
void set_font_params_v_align(wo_handle const& font_params, int32_t v);
int32_t get_font_params_v_align(wo_handle const& font_params);
void set_font_params_color(wo_handle const& font_params, XMFLOAT4 const& v);
XMFLOAT4 get_font_params_color(wo_handle const& font_params);
void set_font_params_shadow_color(wo_handle const& font_params, XMFLOAT4 const& v);
XMFLOAT4 get_font_params_shadow_color(wo_handle const& font_params);
void set_font_params_h_wrap(wo_handle const& font_params, float v);
float get_font_params_h_wrap(wo_handle const& font_params);
void set_font_params_style(wo_handle const& font_params, int32_t v);
int32_t get_font_params_style(wo_handle const& font_params);
void set_font_params_softness(wo_handle const& font_params, float v);
float get_font_params_softness(wo_handle const& font_params);
void set_font_params_bolden(wo_handle const& font_params, float v);
float get_font_params_bolden(wo_handle const& font_params);
void set_font_params_shadow_softness(wo_handle const& font_params, float v);
float get_font_params_shadow_softness(wo_handle const& font_params);
void set_font_params_shadow_bolden(wo_handle const& font_params, float v);
float get_font_params_shadow_bolden(wo_handle const& font_params);
void set_font_params_shadow_offset_x(wo_handle const& font_params, float v);
float get_font_params_shadow_offset_x(wo_handle const& font_params);
void set_font_params_shadow_offset_y(wo_handle const& font_params, float v);
float get_font_params_shadow_offset_y(wo_handle const& font_params);
void set_font_params_cursor(wo_handle const& font_params, XMFLOAT4 const& v);
XMFLOAT4 get_font_params_cursor(wo_handle const& font_params);
void set_font_params_hdr_scaling(wo_handle const& font_params, float v);
float get_font_params_hdr_scaling(wo_handle const& font_params);
wo_handle create_sprite_font();
void sprite_font_set_params(wo_handle const& font, wo_handle const& font_params);
void delete_sprite_font(wo_handle const& font);
void sprite_font_set_hidden(wo_handle const& font, bool value);
XMFLOAT2 sprite_font_text_size(wo_handle const& font);
void sprite_font_set_text(wo_handle const& font, std::string_view const& txt);
std::string_view sprite_font_get_text(wo_handle const& font);
wo_handle get_renderpath3d();
void renderpath_add_font(wo_handle const& path, wo_handle const& sprite_font, std::string_view const& layer);
