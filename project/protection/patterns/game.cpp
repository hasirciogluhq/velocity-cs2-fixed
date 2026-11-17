// Frame/level lifecycle, game events, HUD, sound, engine commands, filesystem, logging.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (frame_stage_notify,          "client.dll:48895C241848896C2420574883EC40488BF9");
	SIGNATURE (post_network_data_received,  "client.dll:48895C241048894C24085556574154415541564157488DAC24B0FCFFFF4881EC500400004C8BE9488B0D????????488B01FF90B8000000488BC8488B10FF5238498BCD8945848BF0E8????????498BCDE8????????");
	SIGNATURE (level_initialization,        "client.dll:488D05*????????C6411000+B8~");
	SIGNATURE (level_shutdown,              "client.dll:4883EC??488B0D????????488D15????????4533C94533C0488B01FF50304885C074??488B0D????????488BD04C8B0141FF50404883C4??");
	SIGNATURE (game_event_manager,          "client.dll:488B0D*????????488B01FF50??FFC3~");
	SIGNATURE (game_event_get_controller,   "client.dll:488D05*????????4D8BF8488901+80~");
	SIGNATURE (game_event_get_pawn,         "client.dll:488D05*????????4D8BF8488901+88~");
	SIGNATURE (game_event_get_int,          "client.dll:>E8????????3D00800000");
	SIGNATURE (game_event_get_float,        "client.dll:>E8????????0F28D8895C2420");
	SIGNATURE (game_event_get_string,       "client.dll:>E8????????85DB0F9FC3");
	SIGNATURE (parse_report_hit,            "client.dll:48895C24184889742420574883EC20488D058AE04A01");
	SIGNATURE (hud,                         "client.dll:488B05*????????4885C07471");
	SIGNATURE (find_hud_element,            "client.dll:40534883EC20488B05????????488BD94885C074??48895C24");
	SIGNATURE (hud_death_notice_clear,      "client.dll:85C07509488D4EE0>E8????????488B5C2440");
	SIGNATURE (hud_weapon_selection_update, "client.dll:498BE35FC3488BCB>E8????????488BCBE8????????");
	SIGNATURE (set_voice_data,              "client.dll:>E8????????4C39B5C8140000");
	SIGNATURE (play_sound,                  "soundsystem.dll:4C8BDC55415541564157");
	SIGNATURE (engine_client_cmd,           "engine2.dll:488BC448895808488968104889701857415641574881EC700100000F2970D8410FB6E98D42FC4D8BF88BFA4C8BF183F801763EBAFFFFFFFF488D0D????????E8????????4885C0750B");
	SIGNATURE (set_info,                    "engine2.dll:40554157488D6C24??4881EC????????4533FF");
	SIGNATURE (service_read,                "filesystem_stdio.dll:00488907488D05*????????488987E0000000~");
	SIGNATURE (filesystem_close,            "filesystem_stdio.dll:>E8????????FFD34C8BA42498000000");
	SIGNATURE (log_internal,                "tier0.dll:>E8????????448B55B3");

} // namespace patterns
