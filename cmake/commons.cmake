
#
# Create multi option selector
# In CMake GUI this will turn into a combobox
#
# @param variable {STRING}	variable name - MY_VARIABLE
# @param default {STRING}	default value - "default_option"
# @param options {STRING}	available options - "default_option;option_a;option_b"
# @param options {STRING}	description - "Defines the post build command"
#
function (ppr_multi_options variable default options docstring)
	if(NOT DEFINED ${variable})
		set(${variable} ${default})
	endif()

	set(${variable} ${default} CACHE STRING ${docstring})
	set_property(CACHE ${variable} PROPERTY STRINGS ${options})
endfunction()


#
# Create CMake property
#
# @param variable {STRING}	variable name - MY_VARIABLE
# @param default {ANY}		default value - FALSE
# @param type {ANY}		variable type - BOOL
# @param docstring {STRING}	variable description - "Compile static library"
#
function(ppr_set_prop variable default type docstring)
	if(NOT DEFINED ${variable})
        set(${variable} ${default})
    endif()
	message(${variable})
    set(${variable} ${default} CACHE ${type} ${docstring} FORCE)
endfunction()

#
# Create source_group
#
# @param {STRING | STRING[]}  list of files
# @param TREE {STRING}		optional - root directory
# @param NAME {STRING}		optional - custom group name path
# @param IS_IMPL {TOGGLE}	optional - is implementation files (Source Files)
#
macro(ppr_group)
    cmake_parse_arguments(ARGS "IS_IMPL" "TREE;NAME" "" ${ARGN})

	if("TREE" IN_LIST ARGS_KEYWORDS_MISSING_VALUES)
        message(FATAL_ERROR "Missing 'TREE' argument value")
    endif()

	set(_files ${ARGN})

	string(LENGTH "${ARGS_NAME}" _name_length)

	if(_name_length GREATER 0)
		list(POP_BACK _files)
		list(POP_BACK _files)
		set(_prefix ${ARGS_NAME})
	elseif("NAME" IN_LIST ARGS_KEYWORDS_MISSING_VALUES)
		list(POP_BACK _files)
		set(_prefix "")
	else()
		if (ARGS_IS_IMPL)
			set(_prefix ${PURPUR_SOURCE_GROUP})
		else()
			set(_prefix ${PURPUR_HEADER_GROUP})
		endif()
	endif()

	if(ARGS_TREE)
		list(POP_BACK _files)
		list(POP_BACK _files)
	endif()


	if(ARGS_TREE)
		source_group(TREE ${ARGS_TREE} FILES ${_files} PREFIX "${_prefix}")
	else()
		source_group("${_prefix}" FILES ${_files})
	endif()
endmacro()
