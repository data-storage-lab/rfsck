#!/usr/bin/env bash
#split original IOs to 4KB IOs,
#replay all 4KB IOs (i.e., w/o injecting fault),
#TODO: split IO w/o replaying


#IO range replayed 
REPLAY_END_IO=10000000000 #should be large enough to include all IO  


echo -e "\n################ SPLIT FSWKLD IO"
date
echo ""
#prepare base image
echo "### cp img for splitting IO"
TMP_FILE=${IMG_BS}.tmp #tmp disk for replaying for splitting IO
cp ${IMG_BS} ${TMP_FILE}
sleep 2

echo -e "\n### replay for splitting IO"
$REPLAYER --disk-file ${TMP_FILE} --io-header-log ${FSWKLD_IO_HEAD_LOG}\
    --io-header-split-log ${FSWKLD_IO_HEAD_SPLIT_LOG}  --io-data-log ${FSWKLD_IO_DATA_LOG}\
    --fail-type 0 --start-io  1 --end-io ${REPLAY_END_IO}\
    --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 1\
     2>&1 | tee ${PFE_LOG_DIR}/log.split.fswkld
#    --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 1

	echo "od $FSWKLD_IO_HEAD_SPLIT_LOG to $FSWKLD_IO_HEAD_SPLIT_LOG.od"
	${PFE_SCRIPT_DIR}/od.sh $FSWKLD_IO_HEAD_SPLIT_LOG > $FSWKLD_IO_HEAD_SPLIT_LOG.od 2>&1

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
