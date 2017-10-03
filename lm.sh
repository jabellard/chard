#!/bin/sh

module="chard"
device="chard"
mode="755"

# load the module
/sbin/insmod ./drv/$module.ko $* || exit 1

# retrieve the module's major number
major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

# remove possilbe stale node, and create a new device node
rm -f /dev/${device}0
mknod /dev/${device}0 c $major 0

