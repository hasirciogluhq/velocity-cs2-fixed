set_project("velocity")

-- Windows host: MSVC (`xmake`). Other hosts: MinGW cross (`xmake`, or `xmake f -p mingw` on Windows).
if not is_host("windows") then
    set_defaultplat("mingw")
end
set_defaultarchs("windows|x64", "mingw|x86_64")

add_rules("mode.debug", "mode.release")

target("velocity")
    set_kind("shared")
    set_prefixname("")
    set_languages("clatest", "cxxlatest")
    set_exceptions("cxx")

    add_files("project/**.cpp|pch/pch.cpp", "project/**.c")
    add_includedirs("project", "project/external/phnt", "project/external/xdraw/dependencies/freetype")
    add_defines("VELOCITYCS2_EXPORTS", "_WINDOWS", "_USRDLL", "UNICODE", "_UNICODE")
    add_vectorexts("avx2")
    add_syslinks("synchronization", "d3d11", "dxgi", "version")

    if is_mode("debug") then
        set_basename("velocity-debug")
        add_defines("DEV")
    else
        add_defines("NDEBUG")
        set_symbols("debug")
        set_policy("build.optimization.lto", true)
    end

    if is_plat("windows") then
        -- MSVC has no x64 inline asm; GCC/Clang use the inline stubs in inline_syscall.inl instead.
        add_files("project/external/inline-syscall/syscall_impl.asm")
        set_runtimes("MT")
        add_cxflags("/GS-", "/Gy")
        add_shflags("/ENTRY:entry", "/SUBSYSTEM:WINDOWS")
        if is_mode("release") then
            add_shflags("/OPT:REF", "/OPT:ICF")
        end
    elseif is_plat("mingw") then
        add_shflags("-Wl,--entry=entry", "-static", {force = true})
    end
