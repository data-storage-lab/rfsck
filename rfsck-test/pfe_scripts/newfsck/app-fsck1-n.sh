#!/usr/bin/env bash
#simple fsck on FSCK1_DEV
#note: -n by default (just to see if there are issues to fix; no recording/replaying/fixing)

#FSCK1_DEV should be exported by other scripts

#if (( $# > 0 )); then

#    FSCK1_DEV=$1
    echo "### sudo e2fsck -fn $FSCK1_DEV"
    sudo e2fsck -fn $FSCK1_DEV

#  else
#    echo "ERROR: No Disk File! " 
#    exit 1
#fi

