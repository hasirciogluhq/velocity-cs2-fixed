// Glow, overlays, removals (scope, crosshair, legs, smoke, flash, decals).
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (is_glowing,        "client.dll:0000488BEA488BF9>E8????????4533F684C0");
	SIGNATURE (get_glow_color,    "client.dll:>E8????????F30F10BE????????488BCF");
	SIGNATURE (draw_overhead,     "client.dll:40534883EC??488BD983FA??75??");
	SIGNATURE (draw_legs,         "client.dll:4055535641564157488DAC24????????4881EC????????F20F1042??");
	SIGNATURE (render_scope,      "client.dll:488BC453574883EC68488BFA");
	SIGNATURE (render_crosshair,  "client.dll:488BC844887C2430>E8????????84C00F849B000000");
	SIGNATURE (render_decals,     "client.dll:B001488BD7498BCD>E8????????BAFFFFFFFF");
	SIGNATURE (render_smoke,      "client.dll:5C24284889442420>E8????????488B5C2460");
	SIGNATURE (draw_flash_effect, "client.dll:85D20F88????????48894C24??5556");

} // namespace patterns
