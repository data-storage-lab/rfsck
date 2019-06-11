#!/usr/bin/env bash
#repeately replay with emulated failures & check


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh


echo -e "\n################################################################"
echo -e "### STAGE #2 : REPLAY & CUT FSWKLD,  DO FSCK1"
echo -e "################################################################"
date
echo ""
echo "LOCALFSCK Directory: $abshere"
####################################################### Config
#total 4KB IOs recorded; get from split-io.sh
LOG_FILE=$PFE_LOG_DIR/log.split.fswkld
TOT_IO_CNT=$(grep replayed $LOG_FILE | awk '{print $7}')
echo "TOT_IO_CNT = $TOT_IO_CNT"

#replay from last
CUT_START_IO=${TOT_IO_CNT} #start from last io


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
    #prepare base image
    #echo "### cp ram baseimge for replay in ram"
    sudo cp ${RAMIMG_REPLAY_BASE} ${RAMIMG_REPLAY_FAULT}
	  sudo chmod 666 ${RAMIMG_REPLAY_FAULT}

    echo "### REPLAY FSWKLD TO #IO ${it}"
    #when split-io=0, only io-header-log will be used, io-header-split-log is useless in replayer
    $REPLAYER --disk-file ${RAMIMG_REPLAY_FAULT} --io-header-log ${IO_HEAD_SPLIT_RAMLOG}\
        --io-header-split-log ${IO_HEAD_SPLIT_RAMLOG}  --io-data-log ${FSWKLD_IO_DATA_LOG}\
        --fail-type 0  --start-io 1  --end-io ${it}\
        --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0 #\
        # 2>&1 | tee $PFE_LOG_DIR/log.replay.$it
    echo "### REPLAY FSWKLD DONE"
    #sync;sync

    
    ############################## do fsck1 
    echo -e "\n### DO FSCK1 (w/o recording)" 
    echo $FSCK1_N_SH
    export FSCK1_DEV=${RAMIMG_REPLAY_FAULT} #used in $FSCK1_SH
    date
    $FSCK1_N_SH 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1
    date
    echo -e "### FSCK1 DONE\n"

    #echo "#=============== IO #${it} DONE"
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

    it=$CUT_START_IO
    while [ ${it} -ge ${CUT_STOP_IO} ] #cut from last IO
    do
        one_cut
        let "it-=1" #cut from last IO
        let "cut_cnt += 1"
    done 
fi

############## Cut method 2: sampling
if [[ $CUT_OPTION == "SAMPLING" ]]; then
    cut_cnt=0

    RAND_SEQ_LENGTH=$TOT_IO_CNT
    SAMPLE_CNT=$(( RAND_SEQ_LENGTH * SAMPLE_PERCENTAGE / 100 ))

    echo -e "\nCUT_OPTION = $CUT_OPTION"
    echo "SAMPLE_PERCENTAGE = $SAMPLE_PERCENTAGE"
    echo "TOT_IO_CNT = $TOT_IO_CNT"

    sample_io
    for it in $(cat $SAMPLE_FILE); do
        echo "$it"
        one_cut
        let "cut_cnt += 1"
    done

fi



date
echo "Total # of fswkld cuts = $cut_cnt"
echo -e "\n################ STAGE #2 DONE!\n"


