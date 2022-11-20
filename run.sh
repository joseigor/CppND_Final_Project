#!/bin/sh
set -eu

BUILDDIR=${BUILDDIR:-"./.build"}
APP_PATH=${APP_PATH:-"${BUILDDIR}/src/dbus_server"}

echo "==============================================================================="
echo "Starting application ..."
echo "==============================================================================="

"${APP_PATH}" "${@}"
