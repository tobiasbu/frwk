#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <ct/core/utils/type_traits.hpp>


template <class T>
void swap(T& a, T& b) {
	T tmp(ct::move(a));
	a = ct::move(b);
	b = ct::move(tmp);
}

template <class T>
void swapMacro(T& a, T& b) {
	T tmp(MOV(a));
	a = MOV(b);
	b = MOV(tmp);
}


class DummyMoveClass {
	public:
	int value = 42;
	DummyMoveClass(int val): value(val) {}
};


TEST_CASE( "move", "[core:utils:type_traits:move]" ) {

	SUBCASE("swap entities") {
		DummyMoveClass a(64);
    	DummyMoveClass b(128);

		swap(a, b);

		REQUIRE(a.value == 128);
		REQUIRE(b.value == 64);

		swap(a, b);

		REQUIRE(a.value == 64);
		REQUIRE(b.value == 128);
    }

	SUBCASE("swap entities with MOV macro") {
		DummyMoveClass a(64);
    	DummyMoveClass b(128);

		swapMacro(a, b);

		REQUIRE(a.value == 128);
		REQUIRE(b.value == 64);

		swapMacro(a, b);

		REQUIRE(a.value == 64);
		REQUIRE(b.value == 128);
    }

}
