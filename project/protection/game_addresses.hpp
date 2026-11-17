#ifndef GAME_ADDRESSES_HPP
#define GAME_ADDRESSES_HPP

#include <cstdint>
#include <cstddef>

/*
* @info
* PATTERN ( patterns::name )              -> signature names: protection/patterns.hpp
*                                            signature bytes: protection/patterns/<group>.cpp
* MODULE_BASE ( "MODULE" )
* MODULE_EXPORT ( "MODULE:EXPORT" )
* INTERFACE_ ( "MODULE:INTERFACE_NAME" )
* CONVAR ( "CONVAR_NAME" )
*
* Patterns are resolved once and cached inside patterns::name (), so call it
* where you need the address instead of copying it into your own globals.
*
* bad:
* detail::address_1 = PATTERN (patterns::name); then in another function call detail::address_1
* good:
* call (PATTERN (patterns::name))
*/

namespace protection::addresses {
	constexpr std::uint32_t hash_const (const char* str, std::uint32_t value = 0x811C9DC5u) {
		return *str ? hash_const (str + 1, (value ^ std::uint32_t (*str)) * 0x01000193u) : value;
	}

	template <std::size_t N>
	consteval std::uint32_t hash (const char (&str) [N]) {
		return hash_const (str);
	}
}

#ifndef PATTERN
#define PATTERN(entry) ((entry) ())
#endif

#ifndef INTERFACE_
#define INTERFACE_(str) \
    []() -> std::uintptr_t { \
        static const auto val = memory::get_module_interface(str); \
        return val; \
    }()
#endif

#ifndef CONVAR
#define CONVAR(str) \
    []() -> c_convar* { \
        static const auto val = addresses::globals::cvar->find(::protection::addresses::hash(str)); \
        return val; \
    }()
#endif

#ifndef MODULE_BASE
#define MODULE_BASE(str) \
    []() -> std::uintptr_t { \
        static const auto val = memory::get_module_base(str); \
        return val; \
    }()
#endif

#ifndef MODULE_EXPORT
#define MODULE_EXPORT(str) \
    ([]() -> std::uintptr_t { \
        static std::uintptr_t val{}; \
        if ( !val ) { \
            val = memory::get_module_export( str ); \
        } \
        return val; \
    }())
#endif

#include <protection/patterns.hpp>

#endif // !GAME_ADDRESSES_HPP
