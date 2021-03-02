#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <nanobench.h>

#include <iostream>
#include <functional>
#include <chrono>

#include <ct/core/types.hpp>
#include <ct/core/utils/type_traits.hpp>

namespace classic {

	class Base {
	public:
		Base() = default;
		virtual void foo() = 0;
	};

	class Derived : public Base {
	public:
		ct::i32 i = 0;
		void foo() override {
			i = rand() % 100;
		}
	};

	class Container {
	private:
		Base * _impl;
	public:
		Container(Base * impl): _impl(impl) {}
		void foo() {
			_impl->foo();
		}
	};

}

namespace direct {

	class Direct {
		private:
			ct::i32 i = 0;
		public:
		Direct() = default;
		void foo() {
			i = rand() % 100;
		}
	};

	class Container {
		private:
		Direct * _impl;
		public:
		Container(Direct * impl): _impl(impl) {}
		void foo() {
			_impl->foo();
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
		void foo() {
			as_underlying()->foo();
		}
	};

	class DerivedImpl : Base<DerivedImpl> {
		private:
		friend class Base<DerivedImpl>;
		ct::i32 i = 0;

		public:
		using Base::Base;

		void foo() {
			i = rand() % 100;
		}
	};

	typedef DerivedImpl Derived;

	class Container {
	private:
		Derived * _impl;
	public:
		Container(Derived * impl): _impl(impl) {}
		void foo() {
			_impl->foo();
		}
	};

}

namespace fn_map {
	typedef void(*print_fn_ptr)();

	struct FnMap {
		FnMap() = default;
		FnMap(FnMap && map) = default;
		FnMap(const FnMap & map) = default;
		print_fn_ptr foo;
	};

	class Container {
	private:
		FnMap  _impl;
	public:
		explicit Container(FnMap && impl): _impl(MOV(impl)) {}
		Container(FnMap * impl): _impl(*impl) {}
		void foo() {
			_impl.foo();
		}
	};

}

TEST_CASE("virtual alternatives") {

	ankerl::nanobench::Bench b;
    b.title("virtual alternatives")
		.unit("uint64_t")
		.warmup(100)
		.minEpochIterations(5000)
		.epochs(11);
    b.performanceCounters(true);

	{
        direct::Direct direct;
		b.run("direct calls", [&] {
			direct.foo();
		});
    };

	{
        direct::Container container(new direct::Direct());
		b.run("through instance ref", [&] {
			container.foo();
		});
	}


    {
        classic::Container container(new classic::Derived());
		b.run("polymorphism", [&] {
			container.foo();
		});
    }


	{
        crtp::Container container(new crtp::Derived());
		b.run("crtp", [&] {
			container.foo();
		});
	}

	{
        fn_map::FnMap * map = new fn_map::FnMap {
	 		[]() {
	 			auto i = rand() % 100;
	 		},
	 	};
		fn_map::Container container(map);
		b.run("lambda map", [&] {
			container.foo();
		});
	}

	{
		fn_map::FnMap map  {
			[]() {
				auto i = rand() % 100;
			},
		};
        fn_map::Container container(MOV(map));
		b.run("lambda map with move", [&] {
			container.foo();
		});
	}
}
