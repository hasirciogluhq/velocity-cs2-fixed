# CI

Builds run on GitHub-hosted `windows-2025-vs2026` (Visual Studio 2026, MSVC v145) through xmake.

## Workflows

| Workflow | Trigger | What it does |
|---|---|---|
| `workflows/ci.yml` | push / PR to `main`, manual | Builds `debug` and `release`, uploads each zip as a run artifact |
| `workflows/release.yml` | push of a `v*` tag | Checks the tag is on `main`, builds `release`, creates a GitHub Release with the zip (tags with `-`, e.g. `v1.0.0-rc.1`, become pre-releases) |

`main` is the only branch. To release:

```sh
git tag v1.0.0
git push origin v1.0.0
```

## Shared actions

| Action | Inputs | Purpose |
|---|---|---|
| `actions/setup` | `mode` | Installs xmake (cached in `.xmake-cache`) and restores `build/.build_cache` |
| `actions/build` | `mode`, `name` | `xmake f` + `xmake`, then zips `*.dll` + `*.pdb` into `dist/<name>.zip` (output: `archive`) |

Use them in any new workflow after `actions/checkout`:

```yaml
- uses: ./.github/actions/setup
  with: { mode: release }
- id: build
  uses: ./.github/actions/build
  with: { mode: release, name: my-archive }
```

## Caching

- **xmake itself**: `setup-xmake`'s `actions-cache-folder`, so there is no download on warm runs.
- **Objects**: xmake's content-hashed build cache (`--policies=build.ccache:y`, stored in `build/.build_cache`).
  The cache key includes a hash of `xmake.lua` and `project/**`. `restore-keys` fall back to the newest older cache,
  so a commit recompiles only the translation units whose preprocessed input changed.
- **Packages / toolchain**: the project uses no xmake packages or apt; MSVC is preinstalled on the image, so there is nothing else to cache.

## Local builds

```sh
xmake                    # Windows: MSVC. macOS/Linux: MinGW cross (default plat = mingw)
xmake f -m release       # switch mode (debug -> velocity-debug.dll, release -> velocity.dll)
xmake f -p mingw         # MinGW on Windows
```

MinGW is configured but does not compile yet: the code still relies on MSVC-only headers/extensions.
