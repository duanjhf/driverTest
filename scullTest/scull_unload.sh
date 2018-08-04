#!/bin/sh
module="scull"
device="scull"

# remove stale nodes
rm -f /dev/${device} /dev/${device}[0-3]
