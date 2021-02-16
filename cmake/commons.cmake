
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
# Note: the first argument must be list of source files.
#
# @param {STRING | STRING[]}	list of files
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
		list(REMOVE_ITEM _files "NAME")
		set(_prefix "")
	else()
		if (ARGS_IS_IMPL)
			list(REMOVE_ITEM _files "IS_IMPL")
			set(_prefix ${PURPUR_SOURCE_GROUP})
		else()
			set(_prefix ${PURPUR_HEADER_GROUP})
		endif()
	endif()

	if(ARGS_TREE)
		list(POP_BACK _files)
		list(POP_BACK _files)
	endif()

	if(NOT _files OR NOT DEFINED _files)
		message(WARNING "Could not parse 'ppr_group'. Missing files list.")
	endif()

	if(ARGS_TREE)
		source_group(TREE ${ARGS_TREE} FILES ${_files} PREFIX "${_prefix}")
	else()
		source_group("${_prefix}" FILES ${_files})
	endif()
endmacro()

#
# Create file list
#
# @param OUTPUT {VAR}		output variable
# @param ROOT {STRING}		optional - root directoy to prepend
# @param CONCAT {TOGGLE}	optional - concat files list to output variable
# @param ... {STRING[]}		list of files
#
macro(ppr_file_list)

	cmake_parse_arguments(ARGS "CONCAT" "ROOT;OUTPUT" "" ${ARGN})

	if (NOT ARGS_OUTPUT)
		message(FATAL_ERROR "Missing 'OUTPUT' argument")
	endif()

	# normalize files to root path
	set(_root "")
	if (ARGS_ROOT)
		set(_root ${ARGS_ROOT})
		string(REPLACE "\\" "/" _root "${_root}")
		if (NOT IS_DIRECTORY ${_root})
			message(FATAL_ERROR "'ROOT' argument is not valid directory")
		endif()

		if (NOT _root MATCHES "\/$")
			set(_root "${_root}/")
		endif()
	endif()

	# clear previous list or concat to output
	if (ARGS_CONCAT)
		set(_files_list ${OUTPUT})
	else()
		if (DEFINED _files_list)
			unset(_files_list)
		endif()
	endif()

	# make list
	foreach(file ${ARGS_UNPARSED_ARGUMENTS})
		set(_current_file ${_root}${file})
		if(EXISTS ${_current_file})
			list(APPEND _files_list ${_current_file})
		else()
			message(WARNING "The file '${_current_file}' does not exists.")
		endif()
	endforeach()

	set(${ARGS_OUTPUT} ${_files_list})

endmacro()
