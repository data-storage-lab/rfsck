#!/usr/bin/env bash
#repeately replay with emulated failures & check


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh


echo -e "\n################################################################"
echo -e "### STAGE #4: REPLAY & CUT FSWKLD,  REPLAY & CUT FSCK1, DO FSCK2"
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

##########################################################

#base image in ram 
sudo cp ${IMG_BS} ${RAMIMG_REPLAY_BASE}
sudo chmod 666 ${RAMIMG_REPLAY_BASE}
#split io head (from split-io.sh) log in ram
sudo cp ${FSWKLD_IO_HEAD_SPLIT_LOG} ${IO_HEAD_SPLIT_RAMLOG}
sudo chmod 666 ${IO_HEAD_SPLIT_RAMLOG}


one_cut() {
    echo -e "\n#===================================================== CUT AT FSWKLD IO# ${it}"
    date

    ############################## replay fswkld until a cut point
    #echo "### cp ram baseimge for replay in ram"
    sudo cp ${RAMIMG_REPLAY_BASE} ${RAMIMG_REPLAY_FAULT}
	  sudo chmod 666 ${RAMIMG_REPLAY_FAULT}

    echo "### REPLAY FSWKLD TO FSWKLD-IO# ${it}"
    #when split-io=0, only io-header-log will be used, io-header-split-log is useless in replayer
    $REPLAYER --disk-file ${RAMIMG_REPLAY_FAULT} --io-header-log ${IO_HEAD_SPLIT_RAMLOG}\
        --io-header-split-log ${IO_HEAD_SPLIT_RAMLOG}  --io-data-log ${FSWKLD_IO_DATA_LOG}\
        --fail-type 0  --start-io 1  --end-io ${it}\
        --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0 #\
        # 2>&1 | tee $PFE_LOG_DIR/log.replay.$it
    echo "### REPLAY FSWKLD DONE"

    
    ############################## replay and cut fsck1, run fsck2 

    FSCK1_SPLIT_LOG_FILE=$PFE_LOG_DIR/log.split.fswkld-$it.fsck1
    FSCK1_TOT_IO_CNT=$(grep replayed $FSCK1_SPLIT_LOG_FILE | awk '{print $7}')
    echo "FSCK1_TOT_IO_CNT = $FSCK1_TOT_IO_CNT"
    ############## Cut FSCK1: exhaustive
    fsck1_cut_cnt=0

    FSCK1_CUT_START_IO=${FSCK1_TOT_IO_CNT} #start from last io
    FSCK1_CUT_STOP_IO=1 #replay all IOs

    echo "FSCK1_CUT_START_IO == $FSCK1_CUT_START_IO"
    echo "FSCK1_CUT_STOP_IO == $FSCK1_CUT_STOP_IO"

    fsck1_it=$FSCK1_CUT_START_IO
    while [ ${fsck1_it} -ge ${FSCK1_CUT_STOP_IO} ] #cut from last IO
    do
        #=================================

        echo -e "\n#---------------------------- cut at fsck1 io# ${fsck1_it}"
        #echo "### cp ram baseimge for replay in ram"
        sudo cp ${RAMIMG_REPLAY_FAULT} ${FSCK1_RAMIMG_REPLAY_FAULT}
        sudo chmod 666 ${FSCK1_RAMIMG_REPLAY_FAULT}

        echo "### REPLAY FSCK1 TO FSCK1-IO# ${fsck1_it}"
        #when split-io=0, only io-header-log will be used, io-header-split-log is useless in replayer
        $REPLAYER --disk-file ${FSCK1_RAMIMG_REPLAY_FAULT} --io-header-log $IO_HEAD_SPLIT_LOG.fswkld-${it}.fsck1\
            --io-header-split-log $IO_HEAD_SPLIT_LOG.fswkld-${it}.fsck1  --io-data-log $IO_DATA_LOG.fswkld-${it}.fsck1\
            --fail-type 0  --start-io 1  --end-io ${fsck1_it}\
            --pfe-err-blk ${ERR_BLOCK_LOG}  --split-io 0 #\
        echo "### REPLAY FSCK1 DONE"
     

        echo -e "\n### DO FSCK2" 
        echo $FSCK2_SH
        export FSCK2_DEV=${FSCK1_RAMIMG_REPLAY_FAULT} 
        date
        $FSCK2_SH 2>&1 | tee $PFE_LOG_DIR/log.fswkld-${it}.fsck1-${fsck1_it}.fsck2
        date
        echo "### FSCK2 DONE"
        #=================================

        let "fsck1_it-=1" #cut from last IO
        let "fsck1_cut_cnt += 1"
    done 



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
echo "PFE_LOG_DIR: $PFE_LOG_DIR"
echo -e "\n################ STAGE #4 DONE!\n"
