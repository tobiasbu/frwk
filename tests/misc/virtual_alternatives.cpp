#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>
#include <iostream>
#include <functional>
#include <chrono>

#include <ct/core/utils/type_traits.hpp>

constexpr int ITERATIONS = 1024;

namespace classic {

	class Base {
	public:
		Base() = default;
		virtual void print(const char * str) = 0;
	};

	class Derived : public Base {
	public:
		void print(const char * str) {
			std::cout << str << std::endl;
		}
	};

	class Container {
	private:

		Base * _impl;

	public:
		Container(Base * impl): _impl(impl) {}
		void print(const char * str) {
			_impl->print(str);
		}
	};

}

namespace direct {

	class Direct {
		public:
		Direct() = default;
		void print(const char * str) {
			std::cout << str << std::endl;
		}
	};

	class Container {
		private:
		Direct * _impl;
		public:
		Container(Direct * impl): _impl(impl) {}
		void print(const char * str) {
			_impl->print(str);
		}
	};

}

namespace crtp {

	template <typename T>
	class Base {
		private:

		friend T;
		Base() = default;

		inline T * as_underlying() {
			return static_cast<T*>(this);
		}

		public:
		void print(const char * str) {
			as_underlying()->_print(str);
		}
	};

	class DerivedImpl : Base<DerivedImpl> {
		private:
		friend class Base<DerivedImpl>;

		public:
		using Base::Base;

		void print(const char * str) {
			std::cout << str << std::endl;
		}
	};

	class Derived : public DerivedImpl {};


	class Container {
	private:
		Derived * _impl;
	public:
		Container(Derived * impl): _impl(impl) {}
		void print(const char * str) {
			_impl->print(str);
		}
	};


}

namespace fn_map {
	typedef void(*print_fn_ptr)(const char *);

	struct FnMap {
		FnMap() = default;
		FnMap(FnMap && map) = default;
		FnMap(const FnMap & map) = default;
		print_fn_ptr print;
	};

	class Container {
	private:
		FnMap  _impl;
	public:
		explicit Container(FnMap && impl): _impl(MOV(impl)) {}
		Container(FnMap * impl): _impl(*impl) {}
		void print(const char * str) {
			_impl.print(str);
		}
	};

}


TEST_CASE("virtual alternatives") {

	std::cout.setstate(std::ios_base::failbit);

    BENCHMARK_ADVANCED("polymorphism")(Catch::Benchmark::Chronometer meter) {
        classic::Container container(new classic::Derived());

		return meter.measure([&container] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				container.print("hello");
			}
		});
    };

	BENCHMARK_ADVANCED("direct calls")(Catch::Benchmark::Chronometer meter) {
        direct::Direct direct;

		return meter.measure([&direct] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				direct.print("hello");
			}
		});
    };

	BENCHMARK_ADVANCED("through instance ref")(Catch::Benchmark::Chronometer meter) {
        direct::Container container(new direct::Direct());

		return meter.measure([&container] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				container.print("hello");
			}
		});
    };


	BENCHMARK_ADVANCED("crtp - static polymorphism")(Catch::Benchmark::Chronometer meter) {
        crtp::Container container(new crtp::Derived());

		return meter.measure([&container] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				container.print("hello");
			}
		});
    };

	BENCHMARK_ADVANCED("lambda map with pointer")(Catch::Benchmark::Chronometer meter) {
		fn_map::FnMap * map = new fn_map::FnMap {
			[](const char * str) {
				std::cout << str << std::endl;
			},
		};
        fn_map::Container container(map);

		return meter.measure([&container] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				container.print("hello");
			}
		});
    };

	BENCHMARK_ADVANCED("lambda map with move semantics")(Catch::Benchmark::Chronometer meter) {
		fn_map::FnMap map = fn_map::FnMap {
			[](const char * str) {
				std::cout << str << std::endl;
			},
		};
        fn_map::Container container(MOV(map));

		return meter.measure([&container] {
			for (int i = 0; i < ITERATIONS; i += 1) {
				container.print("hello");
			}
		});
    };

}
