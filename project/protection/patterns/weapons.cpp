// Weapon accuracy, spread, recoil.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (get_inaccuracy,                "client.dll:48895C24??5556574881EC????????440F298424");
	SIGNATURE (base_fire_guns_get_inaccuracy, "client.dll:>E8????????84C00F84C6FEFFFF");
	SIGNATURE (get_spread,                    "client.dll:4883EC??486391");
	SIGNATURE (get_aim_punch,                 "client.dll:140000488D542420>E8????????F30F1015????????");
	SIGNATURE (weapon_calculate_spread,       "client.dll:28F3440F11442420>E8????????488D85B0000000");
	SIGNATURE (weapon_update_accuracy,        "client.dll:405741564883EC68488BF9E8????????4C8BF04885C0");
	SIGNATURE (weapon_recoil_data,            "client.dll:488D0D*????????488D8424????????41B801000000");
	SIGNATURE (weapon_get_recoil_offset,      "client.dll:>E8????????488D44243C");

} // namespace patterns
