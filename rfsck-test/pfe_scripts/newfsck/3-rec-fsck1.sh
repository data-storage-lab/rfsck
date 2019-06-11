#!/usr/bin/env bash
#repeately replay with emulated failures & check


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh


echo -e "\n################################################################"
echo -e "### STAGE #3: REPLAY & CUT FSWKLD,  RUN & RECORD FSCK1"
echo -e "################################################################"
date
echo ""

######################################################## Config
#total 4KB IOs recorded; get from split-io.sh
LOG_FILE=$PFE_LOG_DIR/log.split.fswkld
TOT_IO_CNT=$(grep replayed $LOG_FILE | awk '{print $7}')
echo "TOT_IO_CNT = $TOT_IO_CNT"

#replay from last
CUT_START_IO=${TOT_IO_CNT} #start from last io
#or manually specifiy a cut io 
#CUT_START_IO=1392

##########################################################

#base image in ram 
sudo cp ${IMG_BS} ${RAMIMG_REPLAY_BASE}
sudo chmod 666 ${RAMIMG_REPLAY_BASE}
#split io head (from split-io.sh) log in ram
sudo cp ${FSWKLD_IO_HEAD_SPLIT_LOG} ${IO_HEAD_SPLIT_RAMLOG}
sudo chmod 666 ${IO_HEAD_SPLIT_RAMLOG}


one_cut() {
    echo -e "\n#============================================ CUT AT FSWKLD IO# ${it}"
    date

    ############################## replay
    #echo "### cp ram baseimge for replay in ram"
    sudo cp ${RAMIMG_REPLAY_BASE} ${RAMIMG_REPLAY_FAULT}
	  sudo chmod 666 ${RAMIMG_REPLAY_FAULT}
    #echo "### REPLAY FSWKLD TO #IO ${it}"
    #when split-io=0, only io-header-log will be used, io-header-split-log is useless in replayer
    #$REPLAYER --disk-file ${RAMIMG_REPLAY_FAULT} --io-header-log ${IO_HEAD_SPLIT_RAMLOG}\
    #    --io-header-split-log ${IO_HEAD_SPLIT_RAMLOG}  --io-data-log ${FSWKLD_IO_DATA_LOG}\
    #    --fail-type 0  --start-io 1  --end-io ${it}\
    #    --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0 #\
        # 2>&1 | tee $PFE_LOG_DIR/log.replay.$it
    #echo "### REPLAY FSWKLD DONE"
    #sync;sync
    
    ############################## run & record fsck1 
    echo -e "\n### DO FSCK1 (tgtd recording)" 
    #echo "### cp baseimge for fs wkld"
    BS_FILE=${RAMIMG_REPLAY_FAULT}

    echo "### Setup iscsi target & initiator"
    #echo "run tgtd in background"
    sudo $PFE_USR_DIR/tgtd --pfe-io-header-log ${IO_HEAD_LOG} --pfe-fail-type-tgtd 0 \
        --pfe-err-blk ${ERR_BLOCK_LOG} --pfe-io-data-log ${IO_DATA_LOG} --pfe-enable-record 1
    sleep 1

    #setup target
    $TARGET_SETUP_SH ${BS_FILE}
    sleep 1
    #setup initiator
    $INITIATOR_SETUP_SH
    sleep 1

    #export FSCK1_DEV=${INIT_DEV} #exported in timed_dev_probe
    export FSCK1_DEV=${INIT_VIRTUAL_DEV} #defined in pfe_config.sh; used in $FSCK1_SH
    echo "### run $FSCK1_Y_SH on $FSCK1_DEV"
    $FSCK1_Y_SH 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1-rec 
    #echo "### run $FSCK1_N_SH on $FSCK1_DEV"
    #$FSCK1_N_SH 2>&1 | tee $PFE_LOG_DIR/log.fsck1.${it}.rec 

    echo "### save io logs"
    #save a copy of the workloads' IO logs for replay
    cp $IO_HEAD_LOG $IO_HEAD_LOG.fswkld-$it.fsck1
    cp $IO_DATA_LOG $IO_DATA_LOG.fswkld-$it.fsck1

    #pfe_io_head_split_log.fswkld-17.fsck1 !!!
    #sudo touch $PFE_LOG_DIR/
    $abshere/split-fsck1-io.sh $it 
    #od logs
    #echo "od $FSCK1_IO_HEAD_LOG to $FSCK1_IO_HEAD_LOG.od"
    #$PFE_SCRIPT_DIR/od.sh $FSCK1_IO_HEAD_LOG > $FSCK1_IO_HEAD_LOG.od 2>&1

    #on the same machine, so simply kill tgtd to end this IO sequence 
    $PFE_SCRIPT_DIR/target-kill.sh
    sleep 1

    echo -e "### FSCK1 RECORDING DONE\n"

}



############## Cut method 3: pattern
#if [[ $CUT_OPTION == "PATTERN" ]]; then
    RANKED_IO_FILE=$PFE_LOG_DIR/ranked_io.txt
    cut_cnt=0

    echo "RANKED_IO_FILE = $RANKED_IO_FILE"
    echo "TOT_IO_CNT = $TOT_IO_CNT"

    for it in $(cat $RANKED_IO_FILE); do
        echo "$it"
        one_cut
        let "cut_cnt += 1"
    done
#fi

date
echo "Total # of ranked cuts = $cut_cnt"
echo -e "\n################ STAGE #3 DONE!\n"
