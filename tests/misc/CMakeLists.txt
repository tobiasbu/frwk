set(SRC
	${CATCH_MAIN}
	${TESTS_DIR}/misc/virtual_alternatives.cpp
)

ct_group(${CATCH_MAIN} TREE ${TESTS_DIR} NAME "_")
ct_group(${SRC} TREE ${TESTS_DIR} NAME "misc")

ct_add_test(tests_ctfk_misc "${SRC}" DEPENDS chronotrix_core)
