#!/bin/bash
#
# clang-format-all: a tool to run clang-format on an entire project
# Copyright (C) 2016 Evan Klitzke <evan@eklitzke.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# Adapted from https://github.com/eklitzke/clang-format-all

function usage {
    echo "usage:"
	echo "	$0 DIR..."
    exit 1
}

if [ $# -eq 0 ]; then
    usage
fi


# Variable that will hold the name of the clang-format command
FMT=""

# Some distros just call it clang-format. Others (e.g. Ubuntu) are insistent
# that the version number be part of the command. We prefer clang-format if
# that's present, otherwise we work backwards from highest version to lowest
# version.
for clangfmt in clang-format{,-{4,3}.{9,8,7,6,5,4,3,2,1,0}}; do
    if which "$clangfmt" &>/dev/null; then
        FMT="$clangfmt"
        break
    fi
done

# Check if we found a working clang-format
if [ -z "$FMT" ]; then
    echo "failed to find clang-format"
    exit 1
fi

# function dir_resolve() {
# 	cd "$1" 2>/dev/null || return $?  # cd to desired directory; if fail, quell any error messages but return exit status
# 	echo "`pwd -P`" # output full, link-resolved path
# }

# if [[ "${$1:0:1}" == / || "${$1:0:2}" == ~[/a-z] ]]
# then
#     echo "Absolute"
# else
#     echo "Relative"
# fi


# Check all of the arguments first to make sure they're all directories
for dir in "$@"; do
    if [ ! -d "${dir}" ]; then
        echo "${dir} is not a directory"
        usage
    fi
done

function realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

# Find a dominating file, starting from a given directory and going up.
function find-dominating-file() {
    if [ -r "$1"/"$2" ]; then
        return 0
    fi
    if [ "$1" = "/" ]; then
        return 1
    fi
    find-dominating-file "$(realpath "$1"/..)" "$2"
    return $?
}

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    MSYS_NT*)   machine=Windows;;
	*) machine="UNKNOWN:${unameOut}"
esac


EXTENSIONS=(h hh hpp c cc cpp)

if [[ $machine == "Windows" ]]; then

	function getPaths() {
		local extension=$1
		ret=$(cmd.exe //c dir "${input_dir}" //b //s | findstr \.${extension}$)
	}

	files=()
	old_IFS=$IFS
	IFS=$'\n\r'
	for input_dir in "$@"; do
		for ext in "${EXTENSIONS[@]}"; do
			getPaths "${ext}"
			if [[ -n "$ret" ]]; then
				files=("${files[@]}" ${ret})
			fi
		done
	done
	"${FMT}" -i "${files[@]}"

else
	# Run clang-format -i on all of the things
	for input_dir in "$@"; do
		pushd "${input_dir}" &>/dev/null
		if ! find-dominating-file . .clang-format; then
			echo "Failed to find dominating .clang-format starting at $PWD"
			continue
		fi

			find . \
				\( -name '*.c' \
				-o -name '*.cc' \
				-o -name '*.cpp' \
				-o -name '*.h' \
				-o -name '*.hh' \
				-o -name '*.hpp' \) \
				-exec "${FMT}" -i '{}' \;
		popd &>/dev/null
	done
fi
