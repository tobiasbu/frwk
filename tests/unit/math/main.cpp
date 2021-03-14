#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <ct/core/assert/assert.hpp>

#include "vec2.test.hpp"
#include "rect.test.hpp"

REGISTER_EXCEPTION_TRANSLATOR(ct::Exception & ex) {
	return doctest::String(ex.what());
}

REGISTER_EXCEPTION_TRANSLATOR(ct::AssertionException & ex) {
	return doctest::String(ex.what());
}


// #include "vec2.test.hpp";

int main(int argc, char** argv) {
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run(); // run

    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests

    int client_stuff_return_code = 0;
    // your program - if the testing framework is integrated in your production code

    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}


