
#ifndef _CHRONOTRIX_FRWK_TESTS_PROFILER_HPP_
#define _CHRONOTRIX_FRWK_TESTS_PROFILER_HPP_

#include <chrono>

#include <ct/core/types.hpp>
#include <ct/core/config/compiler.hpp>

namespace ct {

	namespace test {

		using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>::type;

		struct Result {
			cstr name;
			std::chrono::nanoseconds duration;
			std::chrono::nanoseconds median;
		};

		class Profiler {

			private:

			u32 _iterations;
			u32 _cases;
			std::vector<Result> _results;

			public:

			Profiler(): _iterations(1000), _cases(1) { }
			~Profiler() noexcept {}

			Profiler& iterations(u32 times) {
				_iterations = times;
				return *this;
			}

			Profiler& cases(u32 n) {
				_cases = n;
				return *this;
			}

			template<typename T>
			NOINLINE Profiler& run(cstr benchmarkName, T&& operation) {

				u32 i = _iterations;
				auto total = std::chrono::nanoseconds::zero();
				Clock::time_point start = Clock::now();
				while (i-- > 0) {
					operation();
				}
				auto elapsed = Clock::now() - start;

				_results.push_back({
					benchmarkName,
					elapsed,
					elapsed / _iterations
				});

				return *this;
			}

			NODISCARD void render() {
				for (auto& r : _results) {
					std::cout << r.name
					<< " | "
					<< (static_cast<double>(r.duration.count()) / 1000000.0) << "ms"
					<< " | "
					<< (static_cast<double>(r.median.count()) / 1000000.0) << "ms"
					<< std::endl;
				}
			}

		};

	}

}

#endif

