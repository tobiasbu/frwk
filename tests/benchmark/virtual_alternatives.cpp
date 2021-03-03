#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <iostream>
#include <functional>
#include <chrono>

#include <ct/core/types.hpp>
#include <ct/core/utils/type_traits.hpp>

#include <profiler.hpp>

namespace poly {

	class PureBase {
	public:
		virtual void foo(ct::i32 a) = 0;
	};

	class PureDerived : public PureBase {
	private:
		ct::i32 i = 0;
	public:
		virtual void foo(ct::i32 a) override {
			i = (rand() % 100) + a;
		}
	};

	class Derived : public PureDerived {
	private:
		ct::i32 i = 0;
	public:
		virtual void foo(ct::i32 a) override {
			i = (rand() % 200) + a;
		}
	};

	class DerivedDerived : public Derived {
	private:
		ct::i32 i = 0;
	public:
		virtual void foo(ct::i32 a) override {
			i = (rand() % 300) + a;
		}
	};

	class Container {
	private:
		PureBase * _impl;
	public:
		Container(PureBase * impl): _impl(impl) {}
		void foo(ct::i32 a) {
			_impl->foo(a);
		}
	};

}

namespace direct {

	class Direct {
		private:
			ct::i32 i = 0;
		public:
		Direct() = default;
		void foo(ct::i32 a) {
			i = (rand() % 100) + a;
		}
	};

	class Container {
		private:
		Direct * _impl;
		public:
		Container(Direct * impl): _impl(impl) {}
		void foo(ct::i32 a) {
			_impl->foo(a);
		}
	};

}

namespace crtp {

	template <typename T>
	class Base {
		private:
		friend T;
		Base() = default;
		public:
		void foo(ct::i32 a) {
			static_cast<T*>(this)->foo(a);
		}
	};

	class DerivedImpl : Base<DerivedImpl> {
		private:
		friend class Base<DerivedImpl>;
		ct::i32 i = 0;

		public:
		using Base::Base;

		void foo(ct::i32 a) {
			i = (rand() % 100) + a;
		}
	};

	typedef DerivedImpl Derived;

	class Container {
	private:
		Derived * _impl;
	public:
		Container(Derived * impl): _impl(impl) {}
		void foo(ct::i32 a) {
			_impl->foo(a);
		}
	};

}

namespace fn_map {
	typedef void(*print_fn_ptr)(ct::i32);

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
		void foo(ct::i32 a) {
			_impl.foo(a);
		}
	};

}

TEST_CASE("virtual alternatives") {

	ct::test::Profiler p;
	p.iterations(50000);

	{
        direct::Direct direct;
		p.run("direct", [&] {
			direct.foo(rand() % 100);
		});
    };

	{
        poly::PureDerived derived;
		p.run("abstract > pure derived", [&] {
			derived.foo(rand() % 100);
		});
    }

	{
        poly::Derived derived;
		p.run("pure derived > derived", [&] {
			derived.foo(rand() % 100);
		});
    }

	{
        poly::DerivedDerived derived;
		p.run("derived > derived derived", [&] {
			derived.foo(rand() % 100);
		});
    }

	{
        direct::Container container(new direct::Direct());
		p.run("direct through instance ref", [&] {
			container.foo(rand() % 100);
		});
	}

	{
        poly::Container container(new poly::PureDerived());
		p.run("pure derived through instance ref", [&] {
			container.foo(rand() % 100);
		});
	}

	{
        poly::Container container(new poly::Derived());
		p.run("derived through instance ref", [&] {
			container.foo(rand() % 100);
		});
	}



	{
        poly::Container container(new poly::DerivedDerived());
		p.run("derived derived through instance ref", [&] {
			container.foo(rand() % 100);
		});
	}




	{
        crtp::Container container(new crtp::Derived());
		p.run("crtp", [&] {
			container.foo(rand() % 100);
		});
	}

	{
        fn_map::FnMap * map = new fn_map::FnMap {
	 		[](ct::i32 a) {
	 			auto i = (rand() % 100) + a;
	 		},
	 	};
		fn_map::Container container(map);
		p.run("lambda map", [&] {
			container.foo(rand() % 100);
		});
	}

	{
		fn_map::FnMap map  {
			[](ct::i32 a) {
				auto i = (rand() % 100) + a;
			},
		};
        fn_map::Container container(MOV(map));
		p.run("lambda map with move", [&] {
			container.foo(rand() % 100);
		});
	}

	p.render();
}
