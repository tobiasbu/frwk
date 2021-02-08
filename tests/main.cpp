#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#define COMPACT_OUTPUT 0

int main(int argc, char* argv[])
{
	Catch::Session session; // There must be exactly one instance

	 // Now pass the new composite back to Catch so it uses that

	#if COMPACT_OUTPUT
		const char* args[] = { argv[0], "-s" , "-r", "compact" };

		int returnCode = session.applyCommandLine(4, args);
		if (returnCode != 0) {// Indicates a command line error
			printf("Failed to parse arguments. Exit code %d", returnCode);
			return returnCode;
		}
	#endif

	// writing to session.configData() or session.Config() here
	// overrides command line args
	// only do this if you know you need to

	int numFailed = session.run();

	// numFailed is clamped to 255 as some unices only use the lower 8 bits.
	// This clamping has already been applied, so just return it here
	// You can also do any post run clean-up here
	return numFailed;
}
