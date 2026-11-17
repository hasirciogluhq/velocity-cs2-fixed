#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include <cstddef>
#include <cstdint>
#include <span>

/*
* Signature names only. The byte patterns live in protection/patterns/<group>.cpp,
* so changing a signature recompiles one small file instead of the project.
*
*   use:     patterns::view_matrix ()            -> resolved address, 0 if not found
*            PATTERN (patterns::view_matrix)     -> same thing (legacy macro)
*   add:     1) add X (name) to the list below under the matching group
*            2) add SIGNATURE (name, "module.dll:...") to protection/patterns/<group>.cpp
*   check:   patterns::verify () scans every signature and logs the broken ones
*
* Each name is defined exactly once: a missing or duplicate SIGNATURE is a link error.
*/
#define VELOCITY_PATTERN_LIST(X) \
	/* entities.cpp: Entity system, game rules, global state, model/skeleton helpers */ \
	X (entity_list) \
	X (game_entity_system) \
	X (add_entity) \
	X (remove_entity) \
	X (local_player_controller) \
	X (global_vars) \
	X (game_rules) \
	X (planted_c4) \
	X (set_player_model) \
	X (set_bodygroup) \
	X (get_bone_index) \
	X (game_scene_node_set_mesh_group) \
	X (game_scene_node_set_skeleton) \
	X (get_transforms_for_hitbox_list) \
	X (get_interpolated_shoot_position) \
	/* input.cpp: CCSGOInput, usercmd / protobuf allocation, view angles, frame input */ \
	X (csgo_input) \
	X (create_move) \
	X (handle_view_angles) \
	X (process_input_event) \
	X (read_frame_input) \
	X (frame_input_ring_base) \
	X (frame_input_ring_idx) \
	X (get_view_angles) \
	X (set_view_angles) \
	X (get_tick_view_angles) \
	X (get_usercmd_base) \
	X (get_usercmd) \
	X (button_state_alloc) \
	X (subtick_move_alloc) \
	X (history_field_alloc) \
	X (utl_vector_push) \
	X (serialize_move_crc) \
	X (string_copy) \
	X (weapon_get_entity_index) \
	/* prediction.cpp: Movement prediction, interpolation, net channel */ \
	X (prediction_state) \
	X (prediction_seed) \
	X (prediction_player) \
	X (simulation_player) \
	X (prediction_set_state) \
	X (prediction_set_pawn) \
	X (prediction_reset_pawn) \
	X (prediction_setup_move) \
	X (prediction_process_movement) \
	X (prediction_finish_move) \
	X (get_interp_amount) \
	X (get_net_channel) \
	/* weapons.cpp: Weapon accuracy, spread, recoil */ \
	X (get_inaccuracy) \
	X (base_fire_guns_get_inaccuracy) \
	X (get_spread) \
	X (get_aim_punch) \
	X (weapon_calculate_spread) \
	X (weapon_update_accuracy) \
	X (weapon_recoil_data) \
	X (weapon_get_recoil_offset) \
	/* changer.cpp: Econ items, skins, knives, gloves, agents */ \
	X (item_system) \
	X (weapon_get_viewmodel) \
	X (weapon_get_model_path) \
	X (weapon_set_mesh_group_mask) \
	X (weapon_update_composite_material) \
	X (weapon_update_skin) \
	X (weapon_update_mesh) \
	X (viewmodel_update_mesh) \
	X (econ_item_view_set_attribute) \
	X (econ_item_view_remove_attribute) \
	X (econ_item_view_invalidate_description) \
	/* trace.cpp: Trace manager, rays, filters, bullet penetration */ \
	X (game_trace_manager) \
	X (trace_ray) \
	X (trace_ray_entity) \
	X (trace_hull) \
	X (trace_filter_init) \
	X (trace_filter_set_collision) \
	X (trace_bullet) \
	X (trace_bullet_data_init) \
	X (trace_bullet_update) \
	X (trace_bullet_free) \
	/* scene.cpp: Scene system, materials, lighting, view and post-processing */ \
	X (render_view) \
	X (view_matrix) \
	X (override_view) \
	X (update_fov_sensitivity) \
	X (render_game_system_storage) \
	X (get_world_group_id) \
	X (get_world_group_handle) \
	X (draw_scene_object) \
	X (draw_scene_object_array) \
	X (draw_skybox_array) \
	X (generate_primitives) \
	X (sort_primitives) \
	X (light_scene_object) \
	X (light_data_queue) \
	X (dynamic_light_manager) \
	X (dynamic_light_alloc) \
	X (dynamic_light_time) \
	X (material_manager) \
	X (material_create) \
	X (prepare_scene_material) \
	X (kv3_alloc) \
	X (kv3_destroy) \
	X (kv3_load) \
	X (set_shader_param) \
	X (set_shader_param_i) \
	X (set_postprocess_vec) \
	X (setup_fog) \
	X (cmd_interpreter) \
	/* visuals.cpp: Glow, overlays, removals (scope, crosshair, legs, smoke, flash, decals) */ \
	X (is_glowing) \
	X (get_glow_color) \
	X (draw_overhead) \
	X (draw_legs) \
	X (render_scope) \
	X (render_crosshair) \
	X (render_decals) \
	X (render_smoke) \
	X (draw_flash_effect) \
	/* particles.cpp: Particle manager and resource loading */ \
	X (particle_manager) \
	X (particle_create_effect) \
	X (particle_destroy_effect) \
	X (particle_set_control_point) \
	X (particle_set_entity_binding) \
	X (particle_set_transform) \
	X (init_particle_path_buffer) \
	X (init_particle_path_buffer_alt) \
	X (resource_system_load) \
	X (resource_system_precache) \
	/* game.cpp: Frame/level lifecycle, game events, HUD, sound, engine commands, filesystem, logging */ \
	X (frame_stage_notify) \
	X (post_network_data_received) \
	X (level_initialization) \
	X (level_shutdown) \
	X (game_event_manager) \
	X (game_event_get_controller) \
	X (game_event_get_pawn) \
	X (game_event_get_int) \
	X (game_event_get_float) \
	X (game_event_get_string) \
	X (parse_report_hit) \
	X (hud) \
	X (find_hud_element) \
	X (hud_death_notice_clear) \
	X (hud_weapon_selection_update) \
	X (set_voice_data) \
	X (play_sound) \
	X (engine_client_cmd) \
	X (set_info) \
	X (service_read) \
	X (filesystem_close) \
	X (log_internal)

namespace patterns {

#define VELOCITY_DECLARE_PATTERN(name) [[nodiscard]] std::uintptr_t name ();
	VELOCITY_PATTERN_LIST (VELOCITY_DECLARE_PATTERN)
#undef VELOCITY_DECLARE_PATTERN

	struct entry_t {
		const char* name;
		std::uintptr_t (*resolve) ();
	};

	// Every signature, in list order.
	[[nodiscard]] std::span<const entry_t> all ();

	// Resolves every signature and logs each one that fails. Returns the failure count.
	std::size_t verify ();

} // namespace patterns

#endif // !PATTERNS_HPP
