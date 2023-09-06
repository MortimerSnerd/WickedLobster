// GENERATED for inclusion in wibindings.h by tools/bindgen.lobster, do not edit
wo_handle get_transform_component(wo_handle const& scene, wo_handle const& entity);
wo_handle new_scene();
void delete_scene(wo_handle const& scene);
wo_handle global_scene();
bool is_descendant_entity(wo_handle const& scene, wo_handle const& entity, wo_handle const& ancestor);
wo_handle retarget_animation(wo_handle const& scene, wo_handle const& dest_entity, wo_handle const& src_entity, bool bake_data);
void remove_entity(wo_handle const& scene, wo_handle const& entity, bool recursive);
wo_handle duplicate_entity(wo_handle const& scene, wo_handle const& entity);
void scene_merge(wo_handle const& dest, wo_handle const& src);
wo_handle load_model(wo_handle const& scene, std::string_view const& fname, bool attach);
wo_handle create_entity();
wo_handle create_layer_component(wo_handle const& scene, wo_handle const& entity);
wo_handle get_layer_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_layer_count(wo_handle const& scene);
wo_handle entity_layer_get(wo_handle const& scene, int32_t n);
wo_handle create_humanoid_component(wo_handle const& scene, wo_handle const& entity);
wo_handle get_humanoid_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_humanoid_count(wo_handle const& scene);
wo_handle entity_humanoid_get(wo_handle const& scene, int32_t n);
wo_handle create_name_component(wo_handle const& scene, wo_handle const& entity);
void nc_set_name(wo_handle const& name_comp, std::string_view const& name);
std::string_view nc_get_name(wo_handle const& name_comp);
wo_handle get_name_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_names_count(wo_handle const& scene);
wo_handle entity_names_get(wo_handle const& scene, int32_t n);
wo_handle find_entity_by_name(wo_handle const& scene, std::string_view const& name, wo_handle const& ancestor_entity);
void backlog(int32_t level, std::string_view const& msg);
bool is_backlog_active();
wo_handle create_camera_component(wo_handle const& scene, wo_handle const& entity);
wo_handle create_transform_component(wo_handle const& scene, wo_handle const& entity);
wo_handle create_transform();
void delete_transform(wo_handle const& trans);
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
wo_handle get_transform_local_matrix(wo_handle const& tcomp);
wo_handle get_transform_world_matrix(wo_handle const& tcomp);
void transform_transform_matrix(wo_handle const& tcomp, wo_handle const& matrix);
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
void transform_camera(wo_handle const& camera, wo_handle const& tcomp);
void transform_camera_set_matrix(wo_handle const& camera, wo_handle const& matrix);
wo_handle get_camera_component(wo_handle const& scene, wo_handle const& ent);
int32_t get_camera_count(wo_handle const& scene);
wo_handle get_camera_entity(wo_handle const& scene, int32_t n);
void set_camera_eye(wo_handle const& camera, XMFLOAT3 const& v);
XMFLOAT3 get_camera_eye(wo_handle const& camera);
void set_camera_at(wo_handle const& camera, XMFLOAT3 const& v);
XMFLOAT3 get_camera_at(wo_handle const& camera);
void set_camera_up(wo_handle const& camera, XMFLOAT3 const& v);
XMFLOAT3 get_camera_up(wo_handle const& camera);
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
void set_humanoid_default_look_direction(wo_handle const& humanoid, XMFLOAT3 const& v);
XMFLOAT3 get_humanoid_default_look_direction(wo_handle const& humanoid);
void set_humanoid_head_rotation_max(wo_handle const& humanoid, XMFLOAT2 const& v);
XMFLOAT2 get_humanoid_head_rotation_max(wo_handle const& humanoid);
void set_humanoid_head_rotation_speed(wo_handle const& humanoid, float v);
float get_humanoid_head_rotation_speed(wo_handle const& humanoid);
void set_humanoid_eye_rotation_max(wo_handle const& humanoid, XMFLOAT2 const& v);
XMFLOAT2 get_humanoid_eye_rotation_max(wo_handle const& humanoid);
void set_humanoid_eye_rotation_speed(wo_handle const& humanoid, float v);
float get_humanoid_eye_rotation_speed(wo_handle const& humanoid);
void set_humanoid_look_at(wo_handle const& humanoid, XMFLOAT3 const& v);
XMFLOAT3 get_humanoid_look_at(wo_handle const& humanoid);
int32_t humanoid_bone_count(wo_handle const& hum);
wo_handle humanoid_bone(wo_handle const& hum, int32_t i);
bool humanoid_is_lookat_enabled(wo_handle const& hum);
void humanoid_set_lookat_enabled(wo_handle const& hum, bool v);
void set_layer_mask(wo_handle const& layer, int32_t v);
int32_t get_layer_mask(wo_handle const& layer);
void set_layer_propagation_mask(wo_handle const& layer, int32_t v);
int32_t get_layer_propagation_mask(wo_handle const& layer);
wo_handle get_renderpath3d();
void renderpath_add_font(wo_handle const& path, wo_handle const& sprite_font, std::string_view const& layer);
void renderpath_remove_font(wo_handle const& path, wo_handle const& sprite_font);
void renderpath_clear_fonts(wo_handle const& path);
int32_t renderpath_font_order(wo_handle const& path, wo_handle const& sprite_font);
void renderpath_set_font_order(wo_handle const& path, wo_handle const& sprite_font, int32_t order);
XMINT2 get_renderpath_physical_dims(wo_handle const& path);
XMFLOAT2 get_renderpath_logical_dims(wo_handle const& path);
void set_renderpath3d_exposure(wo_handle const& renderpath3d, float v);
float get_renderpath3d_exposure(wo_handle const& renderpath3d);
void set_renderpath3d_brightness(wo_handle const& renderpath3d, float v);
float get_renderpath3d_brightness(wo_handle const& renderpath3d);
void set_renderpath3d_contrast(wo_handle const& renderpath3d, float v);
float get_renderpath3d_contrast(wo_handle const& renderpath3d);
void set_renderpath3d_saturation(wo_handle const& renderpath3d, float v);
float get_renderpath3d_saturation(wo_handle const& renderpath3d);
void set_renderpath3d_bloom_threshold(wo_handle const& renderpath3d, float v);
float get_renderpath3d_bloom_threshold(wo_handle const& renderpath3d);
void set_renderpath3d_motion_blur_strength(wo_handle const& renderpath3d, float v);
float get_renderpath3d_motion_blur_strength(wo_handle const& renderpath3d);
void set_renderpath3d_depth_of_field_strength(wo_handle const& renderpath3d, float v);
float get_renderpath3d_depth_of_field_strength(wo_handle const& renderpath3d);
void set_renderpath3d_sharpen_filter_amount(wo_handle const& renderpath3d, float v);
float get_renderpath3d_sharpen_filter_amount(wo_handle const& renderpath3d);
void set_renderpath3d_outline_threshold(wo_handle const& renderpath3d, float v);
float get_renderpath3d_outline_threshold(wo_handle const& renderpath3d);
void set_renderpath3d_outline_thickness(wo_handle const& renderpath3d, float v);
float get_renderpath3d_outline_thickness(wo_handle const& renderpath3d);
void set_renderpath3d_outline_color(wo_handle const& renderpath3d, XMFLOAT4 const& v);
XMFLOAT4 get_renderpath3d_outline_color(wo_handle const& renderpath3d);
void set_renderpath3d_ao_range(wo_handle const& renderpath3d, float v);
float get_renderpath3d_ao_range(wo_handle const& renderpath3d);
void set_renderpath3d_ao_sample_count(wo_handle const& renderpath3d, int32_t v);
int32_t get_renderpath3d_ao_sample_count(wo_handle const& renderpath3d);
void set_renderpath3d_ao_power(wo_handle const& renderpath3d, float v);
float get_renderpath3d_ao_power(wo_handle const& renderpath3d);
void set_renderpath3d_chromatic_aberration_amount(wo_handle const& renderpath3d, float v);
float get_renderpath3d_chromatic_aberration_amount(wo_handle const& renderpath3d);
void set_renderpath3d_screen_space_shadow_sample_count(wo_handle const& renderpath3d, int32_t v);
int32_t get_renderpath3d_screen_space_shadow_sample_count(wo_handle const& renderpath3d);
void set_renderpath3d_screen_space_shadow_range(wo_handle const& renderpath3d, float v);
float get_renderpath3d_screen_space_shadow_range(wo_handle const& renderpath3d);
void set_renderpath3d_eye_adaption_key(wo_handle const& renderpath3d, float v);
float get_renderpath3d_eye_adaption_key(wo_handle const& renderpath3d);
void set_renderpath3d_eye_adaption_rate(wo_handle const& renderpath3d, float v);
float get_renderpath3d_eye_adaption_rate(wo_handle const& renderpath3d);
void set_renderpath3d_fsr_sharpness(wo_handle const& renderpath3d, float v);
float get_renderpath3d_fsr_sharpness(wo_handle const& renderpath3d);
void set_renderpath3d_fsr2_sharpness(wo_handle const& renderpath3d, float v);
float get_renderpath3d_fsr2_sharpness(wo_handle const& renderpath3d);
void set_renderpath3d_light_shafts_strength(wo_handle const& renderpath3d, float v);
float get_renderpath3d_light_shafts_strength(wo_handle const& renderpath3d);
void set_renderpath3d_raytraced_diffuse_range(wo_handle const& renderpath3d, float v);
float get_renderpath3d_raytraced_diffuse_range(wo_handle const& renderpath3d);
void set_renderpath3d_raytraced_reflections_range(wo_handle const& renderpath3d, float v);
float get_renderpath3d_raytraced_reflections_range(wo_handle const& renderpath3d);
void set_renderpath3d_reflection_roughness_cutoff(wo_handle const& renderpath3d, float v);
float get_renderpath3d_reflection_roughness_cutoff(wo_handle const& renderpath3d);
void set_renderpath3d_ssr_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_ssr_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_raytraced_diffuse_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_raytraced_diffuse_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_raytraced_reflection_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_raytraced_reflection_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_shadows_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_shadows_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_reflections_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_reflections_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_fxaa_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_fxaa_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_bloom_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_bloom_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_color_grading_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_color_grading_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_volume_lights_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_volume_lights_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_light_shafts_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_light_shafts_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_lens_flare_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_lens_flare_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_motion_blur_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_motion_blur_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_depth_of_field_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_depth_of_field_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_eye_adaptation_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_eye_adaptation_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_sharpen_filter_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_sharpen_filter_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_outline_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_outline_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_chromatic_aberration_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_chromatic_aberration_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_dither_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_dither_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_occlusion_culling_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_occlusion_culling_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_scene_update_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_scene_update_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_fsr_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_fsr_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_fsr2_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_fsr2_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const& renderpath3d, bool v);
bool get_renderpath3d_vxgi_resolve_full_resolution_enabled(wo_handle const& renderpath3d);
bool get_renderpath3d_ao_enabled(wo_handle const& renderpath3d);
void set_renderpath3d_ao(wo_handle const& renderpath3d, int32_t v);
void set_collider_shape(wo_handle const& collider, int32_t v);
int32_t get_collider_shape(wo_handle const& collider);
void set_collider_radius(wo_handle const& collider, float v);
float get_collider_radius(wo_handle const& collider);
void set_collider_offset(wo_handle const& collider, XMFLOAT3 const& v);
XMFLOAT3 get_collider_offset(wo_handle const& collider);
void set_collider_tail(wo_handle const& collider, XMFLOAT3 const& v);
XMFLOAT3 get_collider_tail(wo_handle const& collider);
void set_collider_is_gpu_enabled(wo_handle const& collider, bool v);
void set_collider_is_cpu_enabled(wo_handle const& collider, bool v);
wo_handle create_collider_component(wo_handle const& scene, wo_handle const& entity);
wo_handle get_collider_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_collider_count(wo_handle const& scene);
wo_handle entity_collider_get(wo_handle const& scene, int32_t n);
wo_handle create_matrix4x4();
void delete_matrix(wo_handle const& m);
void identity_matrix(wo_handle const& m);
XMFLOAT4 transform_vector(wo_handle const& matrix, XMFLOAT4 const& v);
void assign_matrix(wo_handle const& lhs, wo_handle const& rhs);
XMFLOAT3 get_matrix_translation(wo_handle const& matrix);
void assign_matrix_rows(wo_handle const& m, XMFLOAT4 const& r1, XMFLOAT4 const& r2, XMFLOAT4 const& r3, XMFLOAT4 const& r4);
XMFLOAT4 return_matrix_row(wo_handle const& m, int32_t r);
void translation_matrix(wo_handle const& m, XMFLOAT3 const& v);
void rotation_euler_matrix(wo_handle const& m, XMFLOAT3 const& angles);
void rotation_x_matrix(wo_handle const& m, float a);
void rotation_y_matrix(wo_handle const& m, float a);
void rotation_z_matrix(wo_handle const& m, float a);
void rotation_quat_matrix(wo_handle const& m, XMFLOAT4 const& quat);
void scaling_matrix(wo_handle const& m, XMFLOAT4 const& scale);
void look_to_matrix(wo_handle const& m, XMFLOAT3 const& eyepos, XMFLOAT3 const& eyedir, XMFLOAT3 const& up);
void look_at_matrix(wo_handle const& m, XMFLOAT3 const& eyepos, XMFLOAT3 const& focuspos, XMFLOAT3 const& up);
void multiply_matrix(wo_handle const& lhs, wo_handle const& rhs, wo_handle const& result);
void add_matrix(wo_handle const& lhs, wo_handle const& rhs, wo_handle const& result);
void transpose_matrix(wo_handle const& m, wo_handle const& result);
void invert_matrix(wo_handle const& m, wo_handle const& result);
void set_animation_start(wo_handle const& animation, float v);
float get_animation_start(wo_handle const& animation);
void set_animation_end(wo_handle const& animation, float v);
float get_animation_end(wo_handle const& animation);
void set_animation_timer(wo_handle const& animation, float v);
float get_animation_timer(wo_handle const& animation);
void set_animation_amount(wo_handle const& animation, float v);
float get_animation_amount(wo_handle const& animation);
void set_animation_speed(wo_handle const& animation, float v);
float get_animation_speed(wo_handle const& animation);
bool is_animation_playing(wo_handle const& anim);
bool is_animation_looped(wo_handle const& anim);
float get_animation_length(wo_handle const& anim);
float is_animation_ended(wo_handle const& anim);
void play_animation(wo_handle const& anim);
void pause_animation(wo_handle const& anim);
void stop_animation(wo_handle const& anim);
void set_animation_looped(wo_handle const& anim, bool v);
wo_handle create_animation_component(wo_handle const& scene, wo_handle const& entity);
wo_handle get_animation_component(wo_handle const& scene, wo_handle const& entity);
int32_t entity_animation_count(wo_handle const& scene);
wo_handle entity_animation_get(wo_handle const& scene, int32_t n);
void renderer_set_vxgi_enabled(bool v);
bool renderer_vxgi_enabled();
wo_handle create_primitive_sphere();
void delete_primitive_sphere(wo_handle const& primitive_sphere);
void set_primitive_sphere_center(wo_handle const& primitive_sphere, XMFLOAT3 const& v);
XMFLOAT3 get_primitive_sphere_center(wo_handle const& primitive_sphere);
void set_primitive_sphere_radius(wo_handle const& primitive_sphere, float v);
float get_primitive_sphere_radius(wo_handle const& primitive_sphere);
bool sphere_sphere_intersects(wo_handle const& sphere0, wo_handle const& sphere1, float& retval2, XMFLOAT3& retval3);
wo_handle create_sphere_intersection_result();
void delete_sphere_intersection_result(wo_handle const& sphere_intersection_result);
void set_sphere_intersection_result_entity(wo_handle const& sphere_intersection_result, wo_handle const& v);
wo_handle get_sphere_intersection_result_entity(wo_handle const& sphere_intersection_result);
void set_sphere_intersection_result_position(wo_handle const& sphere_intersection_result, XMFLOAT3 const& v);
XMFLOAT3 get_sphere_intersection_result_position(wo_handle const& sphere_intersection_result);
void set_sphere_intersection_result_normal(wo_handle const& sphere_intersection_result, XMFLOAT3 const& v);
XMFLOAT3 get_sphere_intersection_result_normal(wo_handle const& sphere_intersection_result);
void set_sphere_intersection_result_velocity(wo_handle const& sphere_intersection_result, XMFLOAT3 const& v);
XMFLOAT3 get_sphere_intersection_result_velocity(wo_handle const& sphere_intersection_result);
void set_sphere_intersection_result_depth(wo_handle const& sphere_intersection_result, float v);
float get_sphere_intersection_result_depth(wo_handle const& sphere_intersection_result);
wo_handle scene_sphere_intersects(wo_handle const& scene, wo_handle const& sphere, int32_t filter_mask, int32_t layer_mask, int32_t lod);
