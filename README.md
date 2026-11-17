# velocity

An educational research project that studies the internals of the Source 2 engine as used by Counter-Strike 2:
how the client is structured in memory, how its systems can be located at runtime, and how they behave.

> [!WARNING]
> **Unofficial and not affiliated with Valve Corporation.** This software modifies the game client.
> Using it on VAC-secured servers or in official matchmaking violates the Steam Subscriber Agreement and
> the Counter-Strike 2 rules, and will get your account permanently banned.
> It is published for **educational and research purposes only**. Read [DISCLAIMER.md](DISCLAIMER.md) before doing anything with it.

## What this project explores

| Area | Where | Topics |
|---|---|---|
| Address resolution | `project/protection/`, `project/utilities/memory/` | Byte-signature scanning with RIP-relative / call-target / vtable resolution, interface registries, module exports |
| Runtime type info | `project/core/systems/impl/schemas.cpp` | Reading Source 2's schema system to resolve class field offsets at runtime instead of hardcoding them |
| Hooking | `project/utilities/hooking/` | Inline (JMP) detours, trampoline allocation, a hook manager |
| Engine systems | `project/core/systems/` | Entity list, input / usercmd protobufs, movement prediction, ray tracing, materials, bones and hitboxes |
| Rendering | `project/core/rendering/`, `project/external/xdraw/` | D3D11 present hook, an immediate-mode UI and drawing layer |
| Features | `project/core/features/` | Visual overlays, scene and world modification, movement and combat experiments |
| Diagnostics | `project/utilities/diag.hpp`, `project/entry.cpp` | Crash capture, minidumps, staged initialization logging |

## Project layout

```
project/
  entry.cpp              DLL entry point and staged initialization
  core/                  features, hooks, rendering, engine systems, settings
  protection/            signature names (patterns.hpp) and signature bytes (patterns/<group>.cpp)
  utilities/             memory, hooking, logging, math, addresses, steam helpers
  external/              third-party code (see "Third-party code")
xmake.lua                build definition
need.fixtures.md         signatures and offsets that are likely broken by recent game updates
```

## Building

The code depends on MSVC-only headers and extensions, so it builds on **Windows with Visual Studio (MSVC)** only.

```sh
xmake f -m debug         # velocity-debug.dll, extra diagnostics (DEV)
xmake f -m release       # velocity.dll
xmake
```

CI builds both modes on every push to `main`. See [.github/ci.md](.github/ci.md).

## State of the project

Game updates regularly move the functions and data this project depends on.
[need.fixtures.md](need.fixtures.md) lists what is most likely broken and how to repair it.
A debug build logs every signature that no longer resolves.

Signatures are kept in one place:

- names: `project/protection/patterns.hpp`
- bytes: `project/protection/patterns/<group>.cpp`, written as `SIGNATURE (name, "module.dll:...")`

## Third-party code

`project/external/` contains third-party code under its own licenses, including
[phnt](https://github.com/winsiderss/phnt), [Zydis](https://github.com/zyantific/zydis),
[LZ4](https://github.com/lz4/lz4), [nlohmann/json](https://github.com/nlohmann/json),
[xorstr](https://github.com/JustasMasiulis/xorstr), [nanosvg](https://github.com/memononen/nanosvg),
[stb_truetype](https://github.com/nothings/stb), StackWalker, inline-syscall and FreeType headers.

## Disclaimer

Counter-Strike 2, Source 2, Steam and VAC are trademarks of Valve Corporation. This project is not endorsed by,
sponsored by or affiliated with Valve. The authors accept no responsibility for bans, data loss or any other
consequence of using this code. See [DISCLAIMER.md](DISCLAIMER.md).
