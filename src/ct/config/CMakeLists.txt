
# root path
ct_file_list(ROOT ${CT_INC} OUTPUT ROOT_INC
	version.hpp
	config.hpp
)

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	api_export.hpp
	os.hpp
	types.hpp
	setup.hpp
	compiler/clang.hpp
	compiler/gcc.hpp
	compiler/msvc.hpp
)

ct_add_header_lib(ctfk_config ${INC} ${ROOT_INC})
