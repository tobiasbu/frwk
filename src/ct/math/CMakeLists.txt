
# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	detail/setup.hpp
	detail/tml_vec2.hpp
	detail/tml_vec2.inl
)

ct_add_header_lib(ctfk_math
			   SOURCES ${INC}
)

# if(MSVC)
#     add_custom_target(ctfk_math_ide SOURCES ${INC})
# 	set_target_properties(ctfk_math_ide PROPERTIES FOLDER "frwk")
# endif()
