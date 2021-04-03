
# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	detail/setup.hpp
	# vectors
	detail/tvec2.hpp
	detail/tvec2.inl
	detail/tvec3.hpp
	detail/tvec3.inl
	detail/tvec4.hpp
	detail/tvec4.inl
	# matrices
	detail/tmat3.hpp
	detail/tmat3.inl
	detail/tmat4.hpp
	detail/tmat4.inl
	# shapes
	detail/trect.hpp
	detail/trect.inl
	vec.hpp
	rect.hpp
)

ct_add_header_lib(ctfk_math
			  	  SOURCES ${INC}
)

# if(MSVC)
#     add_custom_target(ctfk_math_ide SOURCES ${INC})
# 	set_target_properties(ctfk_math_ide PROPERTIES FOLDER "frwk")
# endif()
