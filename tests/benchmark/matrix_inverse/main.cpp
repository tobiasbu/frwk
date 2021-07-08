#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <profiler.hpp>

#include "algorithms.hpp"
#include "mesa_algorithm.hpp"

void check_algo_are_correct() {
	mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
	auto inv_euclidean = euclidean_space::inverse(src);
	auto inv_glm = glm::inverse(src);
	auto inv_gj_a = gauss_jordan_a::inverse(src);
	auto inv_gj_b = gauss_jordan_b::inverse(src);
	auto inv_mesa = mesa::inverse(src);
	REQUIRE(approximately_equals(inv_euclidean, inv_glm));
	REQUIRE(approximately_equals(inv_euclidean, inv_mesa));
	REQUIRE(approximately_equals(inv_euclidean, inv_gj_a));
	REQUIRE(approximately_equals(inv_euclidean, inv_gj_b));
}

TEST_CASE("benchmark/mat4_inverse") {
	ct::test::Profiler p;
	p.iterations(100000);

	check_algo_are_correct();

	p.run("glm::inverse", [] {
		mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
		auto inv = glm::inverse(src);
	});

	p.run("euclidean_space::inverse", [] {
		mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
		auto inv = euclidean_space::inverse(src);
	});

	p.run("gauss_jordan_b::inverse", [] {
		mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
		auto inv = gauss_jordan_b::inverse(src);
	});

	p.run("gauss_jordan_a::inverse", [] {
		mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
		auto inv = gauss_jordan_a::inverse(src);
	});

	p.run("mesa::inverse", [] {
		mat4 src(1, 4, 1, 5, 3, 7, 9, 8, 7, 11, 12, 13, 10, 6, 4, 9);
		auto inv = mesa::inverse(src);
	});

	p.render();
}
