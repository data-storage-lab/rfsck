#!/usr/bin/env bash
# Replay and cut FSCK1 


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

echo
echo "Stage 2: Replay and cut FSCK1"
echo

######################################################## Config
#total 4KB IOs recorded; get from split-io.sh
LOG_FILE=$PFE_LOG_DIR/log.split.fswkld
TOT_IO_CNT=$(grep replayed $LOG_FILE | awk '{print $7}')
echo "TOT_IO_CNT = $TOT_IO_CNT"

### Mount first image
export FAULT_IMG_COPY=~/pfe_images/img.128M.empty.ext4.fswkld.fault
export TEMP_MNT=~/pfe_temp_mnt
export COPY_FILE_MNT=~/pfe_copy_mnt
if [ ! -d $COPY_FILE_MNT ];then
   echo "$COPY_FILE_MNT doesn't exist.. Creating one.. "
   mkdir $COPY_FILE_MNT
fi

#replay from last
CUT_START_IO=${TOT_IO_CNT} #start from last io

#base image in ram 
echo "Executing: sudo cp ${IMG_BS} ${RAMIMG_REPLAY_BASE}"
sudo cp ${IMG_BS} ${RAMIMG_REPLAY_BASE}
sudo chmod 666 ${RAMIMG_REPLAY_BASE}
#split io head (from split-io.sh) log in ram
sudo cp ${FSWKLD_IO_HEAD_SPLIT_LOG} ${IO_HEAD_SPLIT_RAMLOG}
sudo chmod 666 ${IO_HEAD_SPLIT_RAMLOG}


one_cut() {
    echo -e "\n#============================================ CUT AT FSCK IO# ${it}"
    date

    ############################## replay
    #prepare base image
    #echo "### cp ram baseimge for replay in ram"
    sudo cp ${RAMIMG_REPLAY_BASE} ${RAMIMG_REPLAY_FAULT}
          sudo chmod 666 ${RAMIMG_REPLAY_FAULT}

    echo "### REPLAY FSCK TO #IO ${it}"
#    echo "$REPLAYER --disk-file ${RAMIMG_REPLAY_FAULT} --io-header-log ${IO_HEAD_SPLIT_RAMLOG} --io-header-split-log ${IO_HEAD_SPLIT_RAMLOG}  --io-data-log ${FSWKLD_IO_DATA_LOG} --fail-type 0  --start-io 1  --end-io ${it} --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0"
    #when split-io=0, only io-header-log will be used, io-header-split-log is useless in replayer
    $REPLAYER --disk-file ${RAMIMG_REPLAY_FAULT} --io-header-log ${IO_HEAD_SPLIT_RAMLOG}\
        --io-header-split-log ${IO_HEAD_SPLIT_RAMLOG}  --io-data-log ${FSWKLD_IO_DATA_LOG}\
        --fail-type 0  --start-io 1  --end-io ${it}\
        --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0 #\
        # 2>&1 | tee $PFE_LOG_DIR/log.replay.$it
    echo "### REPLAY FSWKLD DONE"
    #sync;sync

#    echo "Not running e2fsck"
    ############################## do fsck1 
    echo -e "\n### DO FSCK1 (w/o recording)" 
    echo $FSCK1_Y_SH
    export FSCK1_DEV=${RAMIMG_REPLAY_FAULT} #used in $FSCK1_SH
    date
#    if [ ${ENABLE_STRACE} -eq 0 ]; then
     $FSCK1_Y_SH ${FSCK1_DEV} 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1
#    else
#      STRACE_LOG_FILE=${PFE_LOG_DIR}/log.strace.${it}
#      $FSCK1_Y_SH ${it} 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1
#    fi
    date
    echo -e "### FSCK1 DONE\n"
    echo
    DIFF_CHK=${PFE_SCRIPT_DIR}/diff-chk-imgs.sh
    $DIFF_CHK ${it} 2>&1 | tee $PFE_LOG_DIR/log.diff-chk-${it}.fsck1
<<COMMENT1
    echo "### Comparing BACKING_STORE image for IO #${it} with original image"
    echo
    echo "Executing: cp ${RAMIMG_REPLAY_FAULT} $FAULT_IMG_COPY"
    cp ${RAMIMG_REPLAY_FAULT} $FAULT_IMG_COPY
    echo "Executing: mount $FAULT_IMG_COPY  $TEMP_MNT"
    mount $FAULT_IMG_COPY  $TEMP_MNT
    if [ $? -eq 0 ]; then
        echo "$FAULT_IMG_COPY mounted to $TEMP_MNT"
        echo "Executing: mount $COPY_FILE $COPY_FILE_MNT"
#        mount $COPY_FILE  $COPY_FILE_MNT
#        if [ $? -eq 0 ]; then
#            echo "$COPY_FILE mounted to $COPY_FILE_MNT"
            ### Recursively compare all the subdirectories 
            ### inside the two image files. If they differ
            ### then there's an error.
#            echo "Executing diff -r $TEMP_MNT $COPY_FILE_MNT"
#            diff -r $TEMP_MNT $COPY_FILE_MNT
#            umount $COPY_FILE_MNT
#        else
#            echo "Unable to mount $COPY_FILE"
#            echo "Unmount ${RAMING_REPLAY_FAULT}"
#            sleep 2
#        fi
#        umount $TEMP_MNT
#    else
        ### FSCK2 fails to fix the corrupted image file
#        echo "Unable to mount ${RAMING_REPLAY_FAULT}"
#    fi
    #echo "Executing: cmp -b -n 8388608 ${RAMIMG_REPLAY_FAULT} $COPY_FILE"
    #cmp -b -n 8388608 ${RAMIMG_REPLAY_FAULT} $COPY_FILE
    #echo -e "\n### Done cmp\n"
    #CHKSM_1=`md5sum ${RAMIMG_REPLAY_FAULT}`
    #CHKSM_2=`md5sum $COPY_FILE`
    #echo "$CHKSM_1"
    #echo "$CHKSM_2"
COMMENT1
    echo "#================================================= IO #${it} DONE"
}


############## Cut method 1: cut at every io
if [[ $CUT_OPTION == "EXHAUSTIVE" ]]; then
    cut_cnt=0

    CUT_START_IO=${TOT_IO_CNT} #start from last io
    #let "CUT_STOP_IO = $CUT_START_IO - 1" #replay last 1+1 IOs
    CUT_STOP_IO=1 #replay all IOs

    echo "CUT_OPTION == $CUT_OPTION "
    echo "CUT_START_IO == $CUT_START_IO"
    echo "CUT_STOP_IO == $CUT_STOP_IO"
    echo "Executing: mount $COPY_FILE $COPY_FILE_MNT"
    mount $COPY_FILE  $COPY_FILE_MNT
    it=$CUT_START_IO
    while [ ${it} -ge ${CUT_STOP_IO} ] #cut from last IO
    do
        one_cut
        let "it-=1" #cut from last IO
        let "cut_cnt += 1"
    done
    umount $COPY_FILE_MNT
    ############################## do fsck1 
    #sudo cp ${RAMIMG_REPLAY_BASE} ${RAMIMG_REPLAY_FAULT}
    #      sudo chmod 666 ${RAMIMG_REPLAY_FAULT}

    #echo -e "\n### DO FSCK1 (w/o recording)" 
    #echo $FSCK1_N_SH
    #export FSCK1_DEV=${RAMIMG_REPLAY_FAULT} #used in $FSCK1_SH
    #date
    #$FSCK1_N_SH 2>&1 | tee $PFE_LOG_DIR/log.fswkld-1.fsck1
    #date
    echo -e "### FSCK1 DONE\n"
    #it=1
    #echo "#=============== IO #${it} DONE"

fi


date
echo "Total # of fswkld cuts = $cut_cnt"
echo -e "\n################ STAGE #2 DONE!\n"
