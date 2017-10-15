#!/bin/bash

module="chard"
device="chard"
mode="755"

# load the module
/sbin/insmod ./drv/$module.ko $* || exit 1

# retrieve the module's major number
major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

# remove possilbe stale node, create a new device node and a link to the node in the cwd
rm -f /dev/${device}0
mknod /dev/${device}0 c $major 0
ln -sf /dev/${device}0 ${device}0
