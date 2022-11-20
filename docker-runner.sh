#!/bin/sh
set -eu

DEF_DOCKER_USE_CACHE="yes"
WORKDIR="${WORKDIR:-/workdir}"

REQUIRED_COMMANDS="
	[
	basename
	command
	date
	docker
	echo
	eval
	exit
	getopts
	hostname
	printf
	pwd
	readlink
	test
"
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

e_warn()
{
	_msg "warning" "${*}"
}

e_notice()
{
	_msg "notice" "${*}"
}

init()
{
	src_file="$(readlink -f "${0}")"
	src_dir="${src_file%%${src_file##*/}}"
	src_name="$(basename "${0}")"

	IMAGE_NAME="${IMAGE_NAME:-$(basename "$(pwd | tr '[A-Z]' '[a-z]')"):latest}"

	if ! docker image build \
		            --build-arg "ALPINE_VERSION=${ALPINE_VERSION:-}" \
		            --build-arg "TARGET_ARCH=${TARGET_ARCH:-}" \
		            --network=host \
		            --pull \
		            --tag "${IMAGE_NAME}" "${src_dir}"; then
			e_warn "Failed to build local container, attempting existing container."
	fi

	if ! docker image inspect \
	            "${IMAGE_NAME}" 1> "/dev/null"; then
		e_err "Container '${IMAGE_NAME}' not found, cannot continue."
		exit 1
	fi

	opt_docker_args="--volume '$(pwd):${WORKDIR}' \
	                 --env 'SHUNIT_COLOR=${SHUNIT_COLOR:-always}' \
	                 ${OPT_DOCKER_ARGS:-}"
}

docker_run()
{
	if [ "${src_name#docker_}" != "${src_name}" ]; then
		_argv0="${src_dir#$(pwd)/}./${src_name#docker_}"
	else
		_argv0="/bin/sh"
		echo "Starting shell inside container"
	fi

	eval docker run \
	            --rm \
	            --hostname "$(hostname)" \
	            --interactive \
	            --privileged \
	            --tty \
	            -p 43210:43210 \
	            --workdir "${WORKDIR}" \
	            "${opt_docker_args:-}" \
	            "${IMAGE_NAME}" \
	            "${_argv0:-}" "${@}"
}

check_requirements()
{
	for _cmd in ${REQUIRED_COMMANDS}; do
		if ! _test_result="$(command -V "${_cmd}")"; then
			_test_result_fail="${_test_result_fail:-}${_test_result}\n"
		else
			_test_result_pass="${_test_result_pass:-}${_test_result}\n"
		fi
	done

	if [ -n "${_test_result_fail:-}" ]; then
		e_err "Self-test failed, missing dependencies."
		echo "======================================="
		echo "Passed tests:"
		printf "${_test_result_pass:-none\n}"
		echo "---------------------------------------"
		echo "Failed tests:"
		printf "${_test_result_fail:-none\n}"
		echo "======================================="
		exit 1
	fi
}

main()
{
	_start_time="$(date "+%s")"

	check_requirements
	init
	docker_run "${@}"

	echo "Ran docker container for $(($(date "+%s") - _start_time)) seconds"
}

main "${@}"

exit 0
