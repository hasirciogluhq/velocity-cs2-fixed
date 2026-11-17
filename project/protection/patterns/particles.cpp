// Particle manager and resource loading.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (particle_manager,              "client.dll:488B35*????????44896C24??");
	SIGNATURE (particle_create_effect,        "client.dll:4C8BDC534881EC90000000F20F1005");
	SIGNATURE (particle_destroy_effect,       "client.dll:83FAFF0F84????????4154");
	SIGNATURE (particle_set_control_point,    "client.dll:4883EC58F3410F105104F3410F1009F3410F105908");
	SIGNATURE (particle_set_entity_binding,   "client.dll:4154415541574881EC900000004D8BF9");
	SIGNATURE (particle_set_transform,        "client.dll:48895C24??48896C24??48897424??574883EC40488BF9498BE9");
	SIGNATURE (init_particle_path_buffer,     "client.dll:48895C24??574883EC??8B41??488D79");
	SIGNATURE (init_particle_path_buffer_alt, "client.dll:48895C24??574883EC??8B41??488D79");
	SIGNATURE (resource_system_load,          "resourcesystem.dll:48895C24??48896C24??48897424??574883EC??488B01");
	SIGNATURE (resource_system_precache,      "resourcesystem.dll:405355574881EC80000000");

} // namespace patterns
