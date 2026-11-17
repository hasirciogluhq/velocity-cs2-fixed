// Scene system, materials, lighting, view and post-processing.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (render_view,                "client.dll:4C8BDC53555741554881EC????????488D05");
	SIGNATURE (view_matrix,                "client.dll:488D0D*????????48C1E006");
	SIGNATURE (override_view,              "client.dll:A8000000488D05*????????4C89742420+78~");
	SIGNATURE (update_fov_sensitivity,     "client.dll:48895C24??48896C24??48897424??574883EC20488BB9????????488BF1");
	SIGNATURE (render_game_system_storage, "client.dll:488B0D*????????418BD6E8????????418B5F");
	SIGNATURE (get_world_group_id,         "client.dll:>E8????????F3410F10B674FFFFFF");
	SIGNATURE (get_world_group_handle,     "client.dll:>E8????????418B5F10");
	SIGNATURE (draw_scene_object,          "scenesystem.dll:488D05*????????488907488B7C2448+8~");
	SIGNATURE (draw_scene_object_array,    "scenesystem.dll:488BC4488950??488948??555356574154415541564157488DA8????????4881EC????????0F2970??");
	SIGNATURE (draw_skybox_array,          "scenesystem.dll:4585C90F8E????????4C8BDC");
	SIGNATURE (generate_primitives,        "scenesystem.dll:488D05*????????488907488B7C2448+20~");
	SIGNATURE (sort_primitives,            "scenesystem.dll:4585C90F84????????5556574883EC30");
	SIGNATURE (light_scene_object,         "scenesystem.dll:>E8????????440F285C2460");
	SIGNATURE (light_data_queue,           "scenesystem.dll:488B05*????????48C1E104+8");
	SIGNATURE (dynamic_light_manager,      "client.dll:488B0D*????????4885C97408488BD7E8????????E8????????BAFFFFFFFF");
	SIGNATURE (dynamic_light_alloc,        "client.dll:488BD94533C0488B0D????????BA01000000>E8????????8B0B");
	SIGNATURE (dynamic_light_time,         "client.dll:40534883EC20488BD985D2741A488B05????????F30F104830");
	SIGNATURE (material_manager,           "client.dll:488B0D*????????80A5E7000000EF");
	SIGNATURE (material_create,            "materialsystem2.dll:48895C24??48896C24??48897424??48897C24??41564881EC????????488B05????????488BF2");
	SIGNATURE (prepare_scene_material,     "materialsystem2.dll:48895C24084889742410574883EC30488B5920");
	SIGNATURE (kv3_alloc,                  "tier0.dll:40534883EC3080FA060FB6C241B916");
	SIGNATURE (kv3_destroy,                "tier0.dll:405741574883EC384C8B01448BFA498BC0488BF948C1E802");
	SIGNATURE (kv3_load,                   "tier0.dll:44242848897C2420>E8????????0FB6D88B4C2444");
	SIGNATURE (set_shader_param,           "client.dll:4C8D442430BAEB293D2E488BCB0F10000F29442430>E8????????");
	SIGNATURE (set_shader_param_i,         "client.dll:48896C24??48897424??574883EC20660F6ECA418BF0");
	SIGNATURE (set_postprocess_vec,        "engine2.dll:>E8????????440F289424");
	SIGNATURE (setup_fog,                  "client.dll:48895C24??48896C24??48897424??48894C24??5741544155415641574883EC20486302");
	SIGNATURE (cmd_interpreter,            "rendersystemdx11.dll:>E8????????4183BDC000000000");

} // namespace patterns
