// Econ items, skins, knives, gloves, agents.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (item_system,                           "client.dll:4883EC28488B05????????4885C00F8581");
	SIGNATURE (weapon_get_viewmodel,                  "client.dll:40534883EC20488BD9E8????????4883BB8803000000");
	SIGNATURE (weapon_get_model_path,                 "client.dll:48895C2410564883EC20488B1D????????");
	SIGNATURE (weapon_set_mesh_group_mask,            "client.dll:48895C24??48897424??574883EC??488D99????????488B71");
	SIGNATURE (weapon_update_composite_material,      "client.dll:48895C241048896C2418488974242057415641574883EC20440FB6F2488BF9");
	SIGNATURE (weapon_update_skin,                    "client.dll:4055534157488DAC2400FEFFFF4881EC00030000440FB6FA488BD9");
	SIGNATURE (weapon_update_mesh,                    "client.dll:>E8????????498D8C2408060000");
	SIGNATURE (viewmodel_update_mesh,                 "client.dll:>E8????????498D8D??????????????488D5424");
	SIGNATURE (econ_item_view_set_attribute,          "client.dll:40534883EC20488BD94881C108020000");
	SIGNATURE (econ_item_view_remove_attribute,       "client.dll:40534883EC20486381????????440FB7CA");
	SIGNATURE (econ_item_view_invalidate_description, "client.dll:48895C24??48897424??574883EC20488DB9????????488BF1");

} // namespace patterns
