
#include <doctest.h>

#include <ct/math/detail/trect.hpp>

typedef ct::trect<ct::f32> rect;
typedef ct::trect<ct::i32> recti;

TEST_CASE("math/rect") {

	SUBCASE("default constructors") {
		rect rect0;
		CHECK(rect0.x == 0.f);
		CHECK(rect0.y == 0.f);
		CHECK(rect0.width == 0.f);
		CHECK(rect0.height == 0.f);

		rect rect1(32.f, 128.f, 640.f, 480.f);
		CHECK(rect1.x == 32.f);
		CHECK(rect1.y == 128.f);
		CHECK(rect1.width == 640.f);
		CHECK(rect1.height == 480.f);

		rect rect2(ct::tvec2<ct::f32>(48, -64), ct::tvec2<ct::f32>(1024, 2048));
		CHECK(rect2.x == 48.f);
		CHECK(rect2.y == -64.f);
		CHECK(rect2.width == 1024.f);
		CHECK(rect2.height == 2048.f);
	};

	SUBCASE("copy constructors") {
		rect rect0(32.f, 128.f, 640.f, 480.f);
		auto rect1(rect0);
		CHECK(rect0.x == rect1.x);
		CHECK(rect0.y == rect1.y);
		CHECK(rect0.width == rect1.width);
		CHECK(rect0.height == rect1.height);

		rect rect2(32.f, 128.f, 640.f, 480.f);
		auto rect3(MOV(rect2));
		CHECK(rect2.x == rect3.x);
		CHECK(rect2.y == rect3.y);
		CHECK(rect2.width == rect3.width);
		CHECK(rect2.height == rect3.height);
	};

	SUBCASE("array subscriptors: []") {
		recti rect0(80, 128, 176, 224);
		CHECK(rect0[0] == 80);
		CHECK(rect0[1] == 128);
		CHECK(rect0[2] == 176);
		CHECK(rect0[3] == 224);
		#ifdef CT_ASSERT_ENABLED
			CHECK_THROWS(rect0[4] == 272);
		#endif

	}

	SUBCASE("top left and bottom right") {
		recti rect0(2048, -1024, 100, 100);
		CHECK(rect0.top_left() == ct::tvec2<ct::i32>(2048, -1024));
		CHECK(rect0.bottom_right() == ct::tvec2<ct::i32>(2148, -924));
	}

	SUBCASE("center") {
		recti rect0(-96, 96, 512, 480);
		CHECK(rect0.center() == ct::tvec2<ct::i32>(160, 336));
	}

	SUBCASE("contains") {
		recti rect0(48, 640, 240, 160);
		CHECK(rect0.contains(rect0.center()));
		CHECK(rect0.contains(ct::tvec2<ct::i32>(100, 700)) == true);
		CHECK(rect0.contains(ct::tvec2<ct::i32>(168, 639)) == false); // top
		CHECK(rect0.contains(ct::tvec2<ct::i32>(168, 800)) == false); // bottom
		CHECK(rect0.contains(ct::tvec2<ct::i32>(47, 720)) == false); // left
		CHECK(rect0.contains(ct::tvec2<ct::i32>(288, 720)) == false); // right
		CHECK(rect0.contains(ct::tvec2<ct::i32>(290, 800)) == false);
	}

	SUBCASE("intersects") {
		recti rect0(-16, -16, 160, 160);
		recti rect1(0, 0, 64, 64);
		rect1.position = rect0.top_left();
		rect1.x -= 176;
		CHECK(rect0.intersects(rect1)); // bottom right
		rect1.y += 160;
		CHECK(rect0.intersects(rect1)); // top right
		rect1.position = rect0.bottom_right();
		rect1.x -= 32;
		CHECK(rect0.intersects(rect1)); // top left
		rect1.y -= 176;
		CHECK(rect0.intersects(rect1)); // bottom left
	}


}
