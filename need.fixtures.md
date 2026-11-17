# need.fixtures

The project last worked about 1–1.5 months ago. This file lists everything that may have broken after CS2 updates since then.
No current `client.dll` / `engine2.dll` was available, so nothing here is confirmed broken. Risk was ranked by reading the code.

## 0. Run this first: which ones are actually broken?

A DEV build (`xmake f -m debug`) now scans every signature once at startup:

```
[error] pattern not found | 488D058AE04A01...      <- resolve_pattern, bytes of the broken signature
[error] signature broken | parse_report_hit        <- patterns::verify, name of the signature
signatures resolved: 139/144
```

- Every name logged as `signature broken` is broken. Fix it in `protection/patterns/<group>.cpp`.
- A signature that is **not found** returns 0. The dangerous case is one that **matches the wrong place**: the log stays clean but the game crashes. See §1.4 and §1.5.
- `INIT_FAIL("failed to initialize global addresses.")` in release means one of the required globals in §2 broke.

How to fix one: find the function in the old DLL (previous build, or a dump where the signature still matches). Locate the same function in the new DLL via string xrefs or vtables, then re-extract the signature. Wildcard (`??`) displacements, struct offsets and stack sizes. Most entries below are fragile precisely because they are not wildcarded.

---

## 1. Signatures (`protection/patterns/*.cpp`)

### 1.1 Almost certainly broken

| Name | File | Reason |
|---|---|---|
| `parse_report_hit` | game.cpp | `488D058AE04A01` = `lea rax,[rip+0x14AE08A]`. This RIP displacement is hardcoded and changes on every `client.dll` rebuild. Use `488D05????????` or re-extract. |
| `button_state_alloc` | input.cpp | Byte-identical to `subtick_move_alloc` plus `-80`. It assumes the button allocator sits 0x80 bytes before the subtick allocator. Once the linker reorders functions, it calls the wrong function and crashes instead of returning 0. Give it its own signature. |

### 1.2 Intra-function jump distance embedded (shifts when code changes)

| Name | Embedded value |
|---|---|
| `base_fire_guns_get_inaccuracy` | `0F84C6FEFFFF` (jz rel32 -0x13A) |
| `render_crosshair` | `0F849B000000` (jz rel32 +0x9B) |

Fix: wildcard the rel32 (`????????`).

### 1.3 Struct offset / stack size / vtable slot embedded (breaks when class layouts change)

| Name | Embedded value | Note |
|---|---|---|
| `get_usercmd_base` | `8B8010590000` → +0x5910 | `systems/impl/input.cpp:121` also hardcodes `0x5910`; update both together |
| `get_interp_amount` | `418B9668030000` → +0x368 | |
| `set_voice_data` | `4C39B5C8140000` → +0x14C8 | |
| `game_scene_node_set_mesh_group` | `8B852C850100` → +0x1852C | |
| `econ_item_view_set_attribute` | `4881C108020000` → +0x208 | |
| `weapon_get_viewmodel` | `4883BB8803000000` → +0x388 | |
| `prediction_finish_move` | `488B8398010000` → +0x198 | |
| `weapon_calculate_spread` | `488D85B0000000` → +0xB0 | |
| `get_world_group_id` | `F3410F10B674FFFFFF` → -0x8C | |
| `material_manager` | `80A5E7000000EF` → +0xE7 | |
| `service_read` | `488987E0000000` → +0xE0 | |
| `filesystem_close` | `4C8BA42498000000` → stack +0x98 | `hooks/impl/utility.cpp:116` also uses `a1 - 224` |
| `trace_ray` | `B8E8240000` → stack probe 0x24E8 | |
| `post_network_data_received` | stack 0x450 / -0x350, `FF90B8000000` vfunc 0xB8 | very long signature, very likely to change |
| `engine_client_cmd` | stack 0x170, very long signature | |
| `get_tick_view_angles` | stack 0xF0 / 0x110 | |
| `render_view` | stack 0xD8 | |
| `weapon_update_skin` | stack 0x300 / -0x200 | |
| `particle_create_effect`, `particle_set_entity_binding` | stack 0x90 | |
| `global_vars` | `448B4044` → +0x44 tick_count | see also the `global_vars + 0x30/0x44` reads in §3 |
| `dynamic_light_time` | `F30F104830` → curtime +0x30 | |
| `item_system` | `0F8581` (first byte of jnz rel32 embedded) | |
| `weapon_update_mesh`, `viewmodel_update_mesh` | +0x608 | both **unused** |

### 1.4 Vtable-index based (`+N~`). If Valve adds or removes a virtual, these silently hook the wrong function

| Name | Slot |
|---|---|
| `create_move` | +0x28 (5) |
| `handle_view_angles` | +0x40 (8) |
| `process_input_event` | +0x20 (4) |
| `add_entity` / `remove_entity` | +0x78 / +0x80 (15 / 16) |
| `override_view` | +0x78 (15) |
| `level_initialization` | +0xB8 (23) |
| `game_event_get_controller` / `game_event_get_pawn` | +0x80 / +0x88 |
| `draw_scene_object` / `generate_primitives` | +0x8 / +0x20 |

These never return 0; they return a **wrong address**. Open each vtable in IDA and check the slots. `create_move` and `handle_view_angles` share the same base signature and vtable: if one shifted, both did.

### 1.5 Too short / generic: risk of matching the wrong function (crash, clean log)

`play_sound` (`4C8BDC55415541564157`, a plain prologue), `get_bone_index` (8 bytes), `get_spread` (`4883EC??486391`), `set_view_angles` (`85D275??486381`), `draw_overhead`, `resource_system_precache` (`405355574881EC80000000`), `render_scope`, `frame_stage_notify`, `prepare_scene_material`, `set_bodygroup` / `draw_flash_effect` (both start with `85D20F88????????`).

Fix: lengthen them. Suggested improvement: `memory::resolve_pattern` stops at the first match. A uniqueness counter would let `verify()` log multi-match signatures too.

### 1.6 Inconsistencies

- `init_particle_path_buffer` and `init_particle_path_buffer_alt` have the **same signature**. `_alt` (used by weather.cpp) was probably a different function once and got broken by copy-paste.
- The name `game_event_get_string` is wrong. `features/misc/impl/other.cpp:175-207` calls it as `(pawn, alpha)`, so it is a different function. Check whether the name and the signature belong to each other.
- Unused signatures: `hud_weapon_selection_update`, `kv3_load`, `viewmodel_update_mesh`, `weapon_update_mesh`.

---

## 2. Required at startup (one broken = DLL init stops)

`utilities/addresses/impl/globals.cpp`: `csgo_input, entity_list, local_player_controller, global_vars, view_matrix, game_rules, light_data_queue, particle_manager, game_event_manager, game_trace_manager, render_game_system_storage, material_manager, game_entity_system, weapon_recoil_data, hud, prediction_seed, simulation_player, prediction_player, planted_c4, item_system, frame_input_ring_idx, frame_input_ring_base, prediction_state` + `tier0.dll:g_pMemAlloc`.

Interface versions are in the same file: `Source2Client002, PanoramaUIEngine001, Source2EngineToClient001, SceneSystem_002, VMaterialSystem2_001, SchemaSystem_001, InputSystemVersion001, ParticleSystemMgr003, VEngineCvar007, Source2ClientPrediction001, NetworkClientService_001, ResourceSystem013, Localize_001, MeshSystem001, VFileSystem017`. A version bump logs `interface not found`.

Broken hooks (`hooks/impl/cheat.cpp`) do not stop init. They only log `skipping unavailable hook: X`.

---

## 3. Hardcoded offsets (not schema, not signatures): what shifts most often

Move whatever you can to `SCHEMA(...)` (pawn/controller fields). Verify the rest with IDA / cs2-dumper.

| Location | Offset |
|---|---|
| `systems/impl/input.cpp:121` | `usercmd_base + 0x5910` (sequence) |
| `features/misc/impl/camera.cpp:109`, `removals.cpp:56` | `view_setup + 0x4A0` (origin), `+ 0x4B8` (angles) |
| `hooks/impl/cheat.cpp:468`, `systems/impl/view.cpp:17` | `render_view thisptr + 0x10`, `view + 0x18` (fov) |
| `cheat.cpp:515,541` | `glow_property + 0x18` (owner) |
| `cheat.cpp:579`, `player.chams.cpp:533` | `scene_object + 0xC0` (owner handle) |
| `player.chams.cpp:211,532,539,570,571`, `item.chams.cpp:53` | scene_object `+0x78` flags, `+0x110` scene node, `+0x9A` lod, `+0xD0/+0xD8` bones |
| `cheat.cpp:743-744`, `hitboxes.cpp:15,18` | `+0x1C0` bone cache, `+0x1E0 / +0x210` model handle |
| `cheat.cpp:774`, `bones.cpp:88,96` | `m_modelState + 0x80` (bone cache), `+ 0x8C` (count) |
| `hitboxes.cpp:32-123` | CModel chain `0x78, 0x150, 0x164, 0x168, 0x174, 0x220, 0x228, 0x240, 0x2F0`, hitbox stride `0x70`, fields `0x18/0x24/0x30/0x3C/0x3D/0x48` |
| `cheat.cpp:962,964,989` (set_info) | `a2 + 0x440`, `arg_list + 0x8 / + 0x10` |
| `global_vars + 0x30` (curtime), `+ 0x44` (tickcount) | `shared.cpp`, `impacts.cpp` (×12), `player.chams.cpp`, `local.cpp`, `widgets.cpp`, `other.overlay.cpp`, `other.cpp:271`. Keep these as one shared constant |
| `changer/impl/econ_item_system.cpp:29-32,193-308` | item schema `0x128/0x130/0x2F0/0x2F8`; item def `0x10, 0x42, 0x70, 0xA8, 0x148, 0x260, 0x338, 0x368`; paint kit `0x08, 0x10, 0x18, 0x44, 0x6C, 0x70, 0xAE` |
| `guns.cpp:145`, `knives.cpp:286` | `weapon + 0x608` (composite material) |
| `movement/impl/edgestop.cpp:60,62` | `pawn + 0xD48`, `pawn + 0x3F8`. Should be schema |
| `esp/projectile/projectile.overlay.cpp:359-400` | `+0x8570` count, `+0x1970` base, stride `432`, `+0x1A8/+0x1AC/+0x38` |
| `misc/impl/other.cpp:315,323` | `hud_element + 0x58`, `hud_element - 0x20` |
| `misc/impl/dlight.cpp:66-220` | light entry `0x04/0x10/0x14/0x18/0x1C/0x24/0x48`, scene object `0xE4` |
| `world/impl/scene.cpp:233-393` | skybox stride `0x70` / `-0x58`, `0xD0`, `0xE8`, scene object `0xE4..0xEC`, `light_data_queue + 0x18`, `+ 0x30`, mesh `0x20 / 0x50` |
| `misc/impl/removals.cpp:17-28`, `systems/impl/materials.cpp:554-838` | material param array `0x18 / 0x20`, entry `0x28` name, `0x10` |
| `systems/impl/entities.cpp:123,136,172,194` | identity `+0x10`, `CEntityClass + 0x58`, entity list stride `112`, `0x1FF` chunk |
| `systems/impl/schemas.cpp:25-45` | SchemaClassInfo `0x24/0x30`, field stride `0x20`, offset `+0x10`. If this breaks, **every SCHEMA** breaks |
| `systems/impl/tracing.cpp:141` | `movement_services + 1592` |
| `systems/systems.hpp:450-454` | `trace_data` static_asserts (`0x1D60` size etc.). If the game struct changed this still compiles but breaks at runtime |
| `combat/impl/shared.cpp:210,766-805` | `trace_holder + 0x2C`, input history slot `0x0C/0x10`, entry `0x00..0x10` |

## 4. Vtable indices (`call_vfunc` / `get_vfunc`)

| Location | Object → index |
|---|---|
| `systems/impl/prediction.cpp:322-363` | movement_services → 38, 39, 43, 46, 47, 48 (highest-risk group) |
| `systems/impl/events.cpp:41,68,91` | game_event_manager → 3, 5 |
| `systems/impl/schemas.cpp:11,18` | schema_system → 13, type_scope → 2 |
| `combat/impl/shared.cpp:459,752,1121`, `extrapolation.cpp:115`, `widgets.cpp:76` | net_channel → 10, net_client → 23, weapon_services → 29 |
| `cheat.cpp:171`, `menu.core.cpp:1250,1263,1382` | input_system → 76 (mouse capture) |
| `changer/impl/guns.cpp:146`, `knives.cpp:287` | weapon → 10 |
| `econ_item_system.cpp:244,360` | localize → 17 |
| `player.chams.cpp:526,559` | mesh_system → 20, scene_system → 16 |
| `world/impl/scene.cpp:61,554` | material → 0, resource_system → 79 |
| `hooks/impl/utility.cpp:108` | async filesystem → 22 |
| `logging/impl/popup.cpp:24` | game_ui → 28 |
| `cheat.cpp:922,927` | smoke render ctx → 32/33 (map/unmap) |

The D3D11 indices (`present 8`, `resize_buffers 13`, `OMSetRenderTargets 33`) are stable; leave them.

## 5. Code bugs (independent of game updates)

- `hooks::cheat::get_inaccuracy` is defined but never created in `initialize()`, so `impacts.on_base_fire_guns_get_inaccuracy` never runs.
- `m_level_shutdown` is hooked but not `reset()` in `cheat::shutdown()`.

---

## Signature system: what changed

- Names: one list in `protection/patterns.hpp` (`VELOCITY_PATTERN_LIST`). Each name is declared as `std::uintptr_t patterns::name()`.
- Bytes: `SIGNATURE (name, "module.dll:...")` in `protection/patterns/{entities,input,prediction,weapons,changer,trace,scene,visuals,particles,game}.cpp`. Changing a signature recompiles only that file.
- A missing or duplicate definition is a link error, so a signature cannot silently disappear.
- `PATTERN (patterns::x)` still works; no call sites changed.
- Each signature is scanned **once** and cached; before, every call site scanned on its own. If the module is not loaded yet, the miss is not cached and the next call retries.
- `patterns::verify()` (runs at startup in DEV) logs every broken signature by name in one pass.
- Removed the dead `_addr` section / `address_t` / `ADDRESS_IMPL` code; nothing read it.
- Adding a signature: `X (name)` in the `patterns.hpp` list, then `SIGNATURE (name, "...")` in the matching group `.cpp`.
