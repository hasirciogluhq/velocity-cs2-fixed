// Entity system, game rules, global state, model/skeleton helpers.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (entity_list,                     "client.dll:488B0D*????????8BFBC1EB0E");
	SIGNATURE (game_entity_system,              "client.dll:488B0D*????????EB028BC6");
	SIGNATURE (add_entity,                      "client.dll:48897424??574883EC??41B9????????418BC04123C1488BF24183F8??488BF9440F45C84181F9????????73??FF81");
	SIGNATURE (remove_entity,                   "client.dll:48897424??574883EC??41B9????????418BC04123C1488BF24183F8??488BF9440F45C84181F9????????73??FF89");
	SIGNATURE (local_player_controller,         "client.dll:48391D*????????7504B001");
	SIGNATURE (global_vars,                     "client.dll:488B05*????????448B4044");
	SIGNATURE (game_rules,                      "client.dll:488B0D*????????4C897010");
	SIGNATURE (planted_c4,                      "client.dll:488B1D*????????488BD34C8B81");
	SIGNATURE (set_player_model,                "client.dll:488D15????????488BCB>E8????????488BD7488BCB");
	SIGNATURE (set_bodygroup,                   "client.dll:85D20F88????????555657");
	SIGNATURE (get_bone_index,                  "client.dll:448B42??488B12E9");
	SIGNATURE (game_scene_node_set_mesh_group,  "client.dll:>E8????????8B852C850100");
	SIGNATURE (game_scene_node_set_skeleton,    "client.dll:>E8????????4084ED7417");
	SIGNATURE (get_transforms_for_hitbox_list,  "client.dll:48895C24??555657415441554881EC????????4963304D8BE0488BEA488BD985F6");
	SIGNATURE (get_interpolated_shoot_position, "client.dll:40555641564881EC20010000");

} // namespace patterns
