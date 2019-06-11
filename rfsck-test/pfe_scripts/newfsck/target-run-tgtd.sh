#!/usr/bin/env bash

absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/variables.sh

#arguments for the original tgtd
# "-f, --foreground        make the program run in the foreground\n"
# "-d, --debug debuglevel  print debugging information\n"

#lots of debug info
#sudo ../usr/tgtd -f -d 1  2>&1 | tee log.tgtd 


#run in foreground (has printf outputs)
#sudo $PFE_USR_DIR/tgtd -f --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 \
#    --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1\
#    2>&1 | tee $PFE_LOG_DIR/log.tgtd 

#run in background (no printf outputs)
sudo $PFE_USR_DIR/tgtd --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 \
    --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1\
    2>&1 | tee $PFE_LOG_DIR/log.tgtd 
