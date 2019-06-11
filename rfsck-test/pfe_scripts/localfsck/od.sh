#!/usr/bin/env bash
#od -Ad -x ./logread | tee logtmp

absme=`readlink -f $0`
abshere=`dirname $absme`

#for reading recorded io seq
if (( $# > 0 )); then
    echo $#
    #dumpfile=dump.$(basename $1)
    #sudo od -Ad --width=32 -t u8 $1 > ${dumpfile} 2>&1
    #echo "DONE dumping $(basename $1) to ${dumpfile}"
    sudo od -Ad -v --width=64 -t u8 $1 
else
	#dump defaut file
   sudo od -Ad -v --width=64 -t u8 ./pfe_io_head_log > log_dump 2>&1
fi

