#!/bin/sh
set -eu

BUILDDIR=${BUILDDIR:-"./.build"}
BUILDTYPE=${BUILDTYPE:-"debug"}

usage()
{
	echo "Usage: ${0} [OPTIONS]"
	echo "Build and compile whole project."
	echo "Available options:"
	echo "    -h   Print this help (usage)."
}

_msg()
{
	_level="${1:?Missing argument to function}"
	shift

	if [ "${#}" -le 0 ]; then
		echo "${_level}: No content for this message ..."
		return
	fi

	echo "${_level}: ${*}"
}

e_err()
{
	_msg "err" "${*}" >&2
}

cleanup() {
	trap EXIT
}

main()
{
	_start_time="$(date "+%s")"

	while getopts ":h" _options; do
		case "${_options}" in
		h)
			usage
			exit 0
			;;
		:)
			e_err "Option -${OPTARG} requires an argument."
			exit 1
			;;
		?)
			e_err "Invalid option: -${OPTARG}"
			exit 1
			;;
		*)
			e_err "Unknown error"
			exit 1
			;;
		esac
	done


	rm -rf "${BUILDDIR}"
	meson setup --buildtype "${BUILDTYPE}" "${BUILDDIR}"
	meson compile -C "${BUILDDIR}"
	RESULT=$?

	cleanup

	echo "==============================================================================="
	echo "Ran build and compile processes in $(($(date "+%s" || true) - _start_time)) seconds"
	echo "==============================================================================="

	return "${RESULT}"
}

main "${@}"
RESULT=$?

exit "${RESULT}"
