// Movement prediction, interpolation, net channel.
// Edit a signature here; only this file recompiles. Syntax: see protection/patterns/define.hpp.
#include <protection/patterns/define.hpp>

namespace patterns {

	SIGNATURE (prediction_state,            "client.dll:488B0D*????????33D28B5B38");
	SIGNATURE (prediction_seed,             "client.dll:8B3D*????????488B03488BCB");
	SIGNATURE (prediction_player,           "client.dll:488B4338488905*????????4183FC03");
	SIGNATURE (simulation_player,           "client.dll:4C3905*????????410F94C6");
	SIGNATURE (prediction_set_state,        "client.dll:8B81????????84D274??FFC08981????????C383E8018981????????75??80B9");
	SIGNATURE (prediction_set_pawn,         "client.dll:48895C24??574883EC2048C70100000000488BFA488BD94885D274??488B02");
	SIGNATURE (prediction_reset_pawn,       "client.dll:488B114885D274??806A????75??488B05????????8B4044894218");
	SIGNATURE (prediction_setup_move,       "client.dll:8021FE440809410FB6C183F001448981D8000000");
	SIGNATURE (prediction_process_movement, "client.dll:488BC453564881EC580100000F2978A8498BF048896810488978E8");
	SIGNATURE (prediction_finish_move,      "client.dll:488BC4535641554881ECE0000000440F2940A84533ED");
	SIGNATURE (get_interp_amount,           "client.dll:>E8????????418B9668030000");
	SIGNATURE (get_net_channel,             "engine2.dll:4C8B05????????4D85C07410");

} // namespace patterns
