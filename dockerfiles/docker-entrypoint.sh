#!/bin/sh
set -eu

# start D-Bus
dbus-uuidgen > /var/lib/dbus/machine-id

# Dbus session bus is needed
export DBUS_SESSION_BUS_ADDRESS="${DBUS_SESSION_BUS_ADDRESS:-$(dbus-daemon --fork --print-address --session)}"

# get rid of /bin/sh argument passed from docker-runner.sh
if [ "$1" = "/bin/sh" ]
then
    shift
fi

# this way it's working regardless if unsing docker-runner.sh
# or "docker run ... CMD param" directly
if [ "$#" -gt 0 ]
then
    "${@}"
else
    /usr/bin/env sh
fi
