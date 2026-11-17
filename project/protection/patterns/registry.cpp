#include <pch/pch.hpp>
#include <utilities/memory/memory.hpp>
#include <utilities/logging/logging.hpp>
#include <protection/patterns/define.hpp>

namespace patterns {

	namespace detail {

		std::uintptr_t resolve (slot_t& slot, std::string_view signature) {
			if (slot.resolved.load (std::memory_order_acquire))
				return slot.address.load (std::memory_order_relaxed);

			// Module not mapped yet: do not cache the miss, retry on the next call.
			if (const auto colon = signature.find (':'); colon != std::string_view::npos)
				if (!memory::get_module_base (signature.substr (0, colon)))
					return 0;

			// Two threads may scan the same signature at once; both get the same result.
			const auto address = memory::resolve_pattern (signature);
			slot.address.store (address, std::memory_order_relaxed);
			slot.resolved.store (true, std::memory_order_release);
			return address;
		}

	} // namespace detail

	std::span<const entry_t> all () {
		static constexpr entry_t entries [] = {
#define VELOCITY_PATTERN_ENTRY(name) { #name, &name },
			VELOCITY_PATTERN_LIST (VELOCITY_PATTERN_ENTRY)
#undef VELOCITY_PATTERN_ENTRY
		};

		return entries;
	}

	std::size_t verify () {
		const auto entries = all ();
		auto failed = std::size_t {};

		for (const auto& entry : entries) {
			if (!entry.resolve ()) {
				++failed;
				logging::console::print (xs ("[error] signature broken | {}"), entry.name);
			}
		}

		const auto total = entries.size ();
		const auto resolved = total - failed;
		logging::console::print (xs ("signatures resolved: {}/{}"), resolved, total);
		return failed;
	}

} // namespace patterns
