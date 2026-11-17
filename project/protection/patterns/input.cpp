// CCSGOInput, usercmd / protobuf allocation, view angles, frame input.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (csgo_input,              "client.dll:84C0740C488D0D*????????E8????????");
	SIGNATURE (create_move,             "client.dll:FFFFFFFF488D05*????????48890D????????+28~");
	SIGNATURE (handle_view_angles,      "client.dll:FFFFFFFF488D05*????????48890D????????+40~");
	SIGNATURE (process_input_event,     "client.dll:CCCC48895C2408574883EC20C6410800488D05*????????488901488BD9+20~");
	SIGNATURE (read_frame_input,        "client.dll:>E8????????4D8BC58BD3");
	SIGNATURE (frame_input_ring_base,   "engine2.dll:488D05*????????0F1004C8");
	SIGNATURE (frame_input_ring_idx,    "engine2.dll:486315*????????83FA0A7D61");
	SIGNATURE (get_view_angles,         "client.dll:8B0D????????8BD3>E8????????F20F1000");
	SIGNATURE (set_view_angles,         "client.dll:85D275??486381");
	SIGNATURE (get_tick_view_angles,    "client.dll:48895C2408574881ECF0000000F30F100A488D8C2410010000418BD8488BFAE8????????F30F104F04");
	SIGNATURE (get_usercmd_base,        "client.dll:4883EC28>E8????????8B8010590000");
	SIGNATURE (get_usercmd,             "client.dll:40534883EC208BDAE8????????4C8BC0");
	SIGNATURE (button_state_alloc,      "client.dll:488B54CA088D4101894708EB16488B0F>E8????????488BD0488BCF-80");
	SIGNATURE (subtick_move_alloc,      "client.dll:488B54CA088D4101894708EB16488B0F>E8????????488BD0488BCF");
	SIGNATURE (history_field_alloc,     "client.dll:>E8????????488BD0488D4E28");
	SIGNATURE (utl_vector_push,         "client.dll:>E8????????4C8BD0458B4A10");
	SIGNATURE (serialize_move_crc,      "client.dll:48895C24??5556574883EC30498BC0488BFA488BF1488B09F6C103");
	SIGNATURE (string_copy,             "client.dll:>E8????????0F104588");
	SIGNATURE (weapon_get_entity_index, "client.dll:>E8????????448B4500");

} // namespace patterns
