#!/usr/bin/env bash

#record IO seq of FSCK1.


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

echo 
echo "Stage 1: Run and Record FSCK1_Y"
#echo "### cp baseimge for fs wkld"
BS_FILE=${IMG_BS}.fswkld
cp ${IMG_BS} ${BS_FILE}

#if [ ${ENABLE_STRACE} -eq 1 ]; then
    echo "STRACE enabled"
    STRACE_LOG_FILE=${PFE_LOG_DIR}/log.strace
#fi

sleep 3

echo "### [target] setup"
#echo "sudo $PFE_USR_DIR/tgtd --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1"
sudo $PFE_USR_DIR/tgtd --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 \
    --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1

#setup target
echo "$TARGET_SETUP_SH ${BS_FILE}"
$TARGET_SETUP_SH ${BS_FILE}
sleep 3

#setup initiator
#$PFE_SCRIPT_DIR/initiator-restart-deb.sh 
$INITIATOR_SETUP_SH
sleep 3
#find iscsi dev file
timed_dev_probe
sleep 5

echo
echo
echo "Waiting for manual FSCK"
echo
sleep 10

#TODO RUN FSCK1_Y
export FSCK1_DEV=${INIT_VIRTUAL_DEV} #defined in pfe_config.sh; used in $FSCK1_SH
echo "### run $FSCK1_Y_SH on $FSCK1_DEV"
#if [ ${ENABLE_STRACE} -eq 0 ]; then
#  $FSCK1_Y_SH $FSCK1_DEV 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1-rec
#else
#  strace -ttt -o $STRACE_LOG_FILE $FSCK1_Y_SH 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1-rec
#fi

echo "### [target] save io logs"
#save a copy of the workloads' IO logs for replay
echo "cp $IO_HEAD_LOG $FSWKLD_IO_HEAD_LOG"
cp $IO_HEAD_LOG $FSWKLD_IO_HEAD_LOG
echo "cp $IO_DATA_LOG $FSWKLD_IO_DATA_LOG"
cp $IO_DATA_LOG $FSWKLD_IO_DATA_LOG

#split IO head to 4KB IOs
$abshere/split-fswkld-io.sh

#od logs
echo "od $FSWKLD_IO_HEAD_LOG to $FSWKLD_IO_HEAD_LOG.od"
$PFE_SCRIPT_DIR/od.sh $FSWKLD_IO_HEAD_LOG > $FSWKLD_IO_HEAD_LOG.od 2>&1

#on the same machine, so simply kill tgtd to end this IO sequence 
$PFE_SCRIPT_DIR/target-kill.sh

#COPY_FILE=${BS_FILE}.copy
echo "Saving a copy of backing store to $COPY_FILE"
echo "Execting: cp ${BS_FILE} ${COPY_FILE}"
cp ${BS_FILE} ${COPY_FILE}
sleep 3
