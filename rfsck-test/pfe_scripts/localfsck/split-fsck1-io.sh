#!/usr/bin/env bash
#based on 3_replay_and_check.simple.sh
#split original IOs to 4KB IOs,
#replay all 4KB IOs (i.e., w/o injecting fault),
#the replayed image can be used to verify the correctness of replayer
#TODO: split IO w/o replaying

#absme=`readlink -f $0`
#abshere=`dirname $absme`
#. $abshere/pfe_helper.sh

if (( $# > 0 )); then
    IT=$1
  else
    echo "$0: No Cut #! " 
    exit 1
fi


#IO range replayed 
REPLAY_END_IO=10000000000 #should be large enough to include all IO  


echo -e "\n################ SPLIT FSCK1 IO"
date
echo ""
#prepare base image
echo "### cp img for splitting IO"
TMP_FILE=${IMG_BS}.tmp #tmp disk for replaying for splitting IO
cp ${IMG_BS} ${TMP_FILE}
sleep 2
#pfe_io_head_split_log.fswkld-17.fsck1 !!!
sudo touch $IO_HEAD_SPLIT_LOG.fswkld-$IT.fsck1
echo -e "\n### replay for splitting IO"
$REPLAYER --disk-file ${TMP_FILE} --io-header-log $IO_HEAD_LOG.fswkld-${IT}.fsck1\
    --io-header-split-log $IO_HEAD_SPLIT_LOG.fswkld-$IT.fsck1  --io-data-log $IO_DATA_LOG.fswkld-$IT.fsck1\
    --fail-type 0 --start-io  1 --end-io ${REPLAY_END_IO}\
    --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 1\
     2>&1 | tee ${PFE_LOG_DIR}/log.split.fswkld-$IT.fsck1
#    --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 1

	${PFE_SCRIPT_DIR}/od.sh $IO_HEAD_SPLIT_LOG.fswkld-$IT.fsck1 > $IO_HEAD_SPLIT_LOG.fswkld-$IT.fsck1.od 2>&1

  #if [ -e $STRACE_FILE ]; then
  #	$PFE_SCRIPT_DIR/postproc/map_io2syscall.sh
  #fi

sync;sync;sync

#cp ${TMP_FILE} ${PFE_LOG_DIR}
rm ${TMP_FILE}

#save a copy of the splitted IO head log
#echo "### save a copy of splitted IO head log"
#cp $IO_HEAD_SPLIT_LOG $IO_HEAD_SPLIT_LOG.work 
#sleep 5

date
