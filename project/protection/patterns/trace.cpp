// Trace manager, rays, filters, bullet penetration.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (game_trace_manager,         "client.dll:488B0D*????????488D3452~");
	SIGNATURE (trace_ray,                  "client.dll:48895424??48894C24??5553565741564157488DAC24????????B8E8240000");
	SIGNATURE (trace_ray_entity,           "client.dll:44246848897C2420>E8????????488B3D????????");
	SIGNATURE (trace_hull,                 "client.dll:>E8????????0F2F754C");
	SIGNATURE (trace_filter_init,          "client.dll:48895C24??48897424??574883EC??0FB641??33FF24");
	SIGNATURE (trace_filter_set_collision, "client.dll:000041B800010000>E8????????4C397F38");
	SIGNATURE (trace_bullet,               "client.dll:40535741564883EC508B8424");
	SIGNATURE (trace_bullet_data_init,     "client.dll:48895C24??48896C24??48897424??57415641574883EC??F20F1002");
	SIGNATURE (trace_bullet_update,        "client.dll:>E8????????F3440F106574");
	SIGNATURE (trace_bullet_free,          "client.dll:>E8????????3BDE744E");

} // namespace patterns
