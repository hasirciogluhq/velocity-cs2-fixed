# Contributing

Read [DISCLAIMER.md](DISCLAIMER.md) first. Contributions must stay within the project's educational scope.
Changes meant to evade anti-cheat or to support use in online play will not be accepted.

## Workflow

- `main` is the only branch. Open a pull request against `main`.
- CI must pass: it builds `debug` and `release` with MSVC on Windows (see [.github/ci.md](.github/ci.md)).
- The project builds with MSVC only. Do not add MinGW/Clang-specific workarounds.
- Keep commit messages short and describe what changed.
- Write code, comments and docs in English.

## Fixing a broken signature

1. Run a debug build. The log lists each one as `signature broken | <name>`.
2. Find the function in the current game DLL and extract a new signature. Wildcard (`??`) relative
   displacements, struct offsets and stack sizes so the signature survives the next update.
3. Replace the bytes in `project/protection/patterns/<group>.cpp`:

   ```cpp
   SIGNATURE (view_matrix, "client.dll:488D0D*????????48C1E006");
   ```

   Syntax: `??` wildcard, `>` resolve E8/E9 call target, `*` resolve RIP-relative operand,
   `^` read absolute pointer, `+N` / `-N` hex offset, `~` dereference.
   Full reference: `project/protection/patterns/define.hpp`.
4. Update [need.fixtures.md](need.fixtures.md) if the entry was listed there.

## Adding a signature

1. Add `X (name)` to the matching group in `VELOCITY_PATTERN_LIST` in `project/protection/patterns.hpp`.
2. Add `SIGNATURE (name, "module.dll:...")` to the matching `project/protection/patterns/<group>.cpp`.
3. Use it as `patterns::name ()` or `PATTERN (patterns::name)`.

A missing or duplicate definition fails at link time.

## Offsets

Prefer `SCHEMA ("Class", "m_field"_hash)` over hardcoded offsets wherever the schema system exposes the field.
