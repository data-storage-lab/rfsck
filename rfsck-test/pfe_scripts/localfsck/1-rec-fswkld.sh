#!/usr/bin/env bash
#do work and record IO seq.


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

echo -e "\n################################################################"
echo -e "### STAGE #1 : RUN & RECORD FS WKLD"
echo -e "################################################################"
date
echo
#echo "### cp baseimge for fs wkld"
BS_FILE=${IMG_BS}.fswkld
cp ${IMG_BS} ${BS_FILE}
sleep 3

echo "### [target] setup"
sudo $PFE_USR_DIR/tgtd --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 \
    --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1
#    --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1\
#    2>&1 | tee $PFE_LOG_DIR/log.tgtd.work

#setup target
$TARGET_SETUP_SH ${BS_FILE}
sleep 3


#setup initiator
#$PFE_SCRIPT_DIR/initiator-restart-deb.sh 
$INITIATOR_SETUP_SH
sleep 3
#find iscsi dev file
timed_dev_probe
sleep 5

#mount/umount original backing image
echo "### [initiator] mount -o noatime $INIT_DEV $MNT"
#sudo mount -t $PFE_FS -o loop $INIT_DEV $MNT 
#sudo mount $INIT_DEV $MNT  
sudo mount -o noatime $INIT_DEV $MNT  
#make sure can mount
sleep 3
#check_mount
echo "ls -lsit $MNT"
sudo ls -lsit $MNT

sync;sync

###################### DO FS WKLD (tgtd record) 
echo -e "\n### DO FS WKLD (w/ tgtd recording)"
#echo $FSWKLD_SH
TEST_FSWKLD_SH=$abshere/app-fswkld.sh
echo $TEST_FSWKLD_SH
$TEST_FSWKLD_SH 2>&1 | tee $PFE_LOG_DIR/log.app-fswkld
echo -e "### FS WKLD DONE\n"
######################

sleep 3
echo "ls $MNT"
sudo ls -lsit $MNT

echo "### [initiator] umount $INIT_DEV"
sync;sync
sudo umount $MNT
sleep 3 
echo "ls -lsit $MNT"
ls -lsit $MNT


echo "### [target] save io logs"
#save a copy of the workloads' IO logs for replay
cp $IO_HEAD_LOG $FSWKLD_IO_HEAD_LOG
cp $IO_DATA_LOG $FSWKLD_IO_DATA_LOG

#split IO head to 4KB IOs
$abshere/split-fswkld-io.sh  

#od logs
echo "od $FSWKLD_IO_HEAD_LOG to $FSWKLD_IO_HEAD_LOG.od"
$PFE_SCRIPT_DIR/od.sh $FSWKLD_IO_HEAD_LOG > $FSWKLD_IO_HEAD_LOG.od 2>&1
#echo "od $FSWKLD_IO_DATA_LOG to $FSWKLD_IO_DATA_LOG.od"
#$PFE_SCRIPT_DIR/test-od.sh $FSWKLD_IO_DATA_LOG > $FSWKLD_IO_DATA_LOG.od 2>&1



#on the same machine, so simply kill tgtd to end this IO sequence 
$PFE_SCRIPT_DIR/target-kill.sh
sleep 3
sudo rm -rf $MNT/*

#split IOs to 4KB IOs


echo -e "\n################ STAGE #1 DONE!\n"

