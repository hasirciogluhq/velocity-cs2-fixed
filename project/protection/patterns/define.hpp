#pragma once

// Included only by protection/patterns/*.cpp. Keeps those files light: no pch, no Windows headers.

#include <atomic>
#include <cstdint>
#include <string_view>

#include <protection/patterns.hpp>

/*
* SIGNATURE (name, "module.dll:BYTES")
*
* BYTES is hex, spaces optional:
*   ?? or ?    wildcard byte
*   >          before E8/E9: resolve the rel32 call/jmp target at that byte
*   *          before a rel32 operand: resolve RIP-relative address (operand + 4 + rel)
*   ^          read an absolute pointer at that byte
*   +N / -N    add/subtract hex N after resolving (e.g. a vtable slot: +28 = index 5)
*   ~          dereference the final address once
*
* The address is resolved on first use and cached. While the module is not loaded
* yet nothing is cached, so the next call retries.
*/

namespace patterns::detail {

	struct slot_t {
		std::atomic<std::uintptr_t> address {};
		std::atomic<bool>           resolved {};
	};

	[[nodiscard]] std::uintptr_t resolve (slot_t& slot, std::string_view signature);

} // namespace patterns::detail

#define SIGNATURE(name, signature)                                  \
	std::uintptr_t name () {                                        \
		static ::patterns::detail::slot_t slot {};                  \
		return ::patterns::detail::resolve (slot, signature);       \
	}                                                               \
	static_assert (true)
