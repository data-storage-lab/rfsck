#!/bin/bash

absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_config.sh


LOGS_DIR=~/pfe_logs
if [ ! -d $LOGS_DIR ];then
    echo "no $LOGS_DIR, creating one ..."
    sudo mkdir $LOGS_DIR
    sudo chmod 777 $LOGS_DIR
fi


#it=1
#it_num=1 #total iteration number
#while [ $it -le $it_num ]; do

    #ts of this run
    THISDATE=`date +"%y%m%d"`
    THISTIME=`date +"%T" | sed s/":"//g`
    THIS=$THISDATE$THISTIME

    #log dir for this run 
    export PFE_LOG_DIR=$LOGS_DIR/logs-fsck-cutopt-$CUT_OPTION-${SAMPLE_PERCENTAGE=100}.$THIS
    #update PFE_LOG_DIR related config
    . $abshere/pfe_internal.sh 
    #create log dir
    echo $PFE_LOG_DIR
    if [ ! -d $PFE_LOG_DIR ]; then
        mkdir $PFE_LOG_DIR
    fi

    #save config of this run
    cp $abshere/pfe_config.sh $PFE_LOG_DIR
    echo
    echo -e "Executing touch $FSWKLD_IO_HEAD_SPLIT_LOG"
    echo
    touch $FSWKLD_IO_HEAD_SPLIT_LOG
    echo
    echo -e "Executing touch $ERR_BLOCK_LOG"
    echo
    touch $ERR_BLOCK_LOG
    ls -l $PFE_LOG_DIR

    ############################ (1) run & record FS wkld (w/ tgtd)
    $abshere/1-rec-fswkld.sh 2>&1 | tee ${PFE_LOG_DIR}/log.1-rec-fswkld
    #$abshere/split-fswkld-io.sh  
    ############################ (2) replay & cut FS wkld, then run fsck1 (emulate 1st power fault & 1st fsck) 
    $abshere/2-run-fsck1.sh 2>&1 | tee ${PFE_LOG_DIR}/log.2-run-fsck1
    #rank fsck1 results based on the number of necessary "Fix", create ranked_io.txt
    $abshere/generate-ranked-io.sh
#<<COMMENT1    
    ############################ (3) for fsck1 results containing "Fix": 
    #based on ranked_io.txt, replay FS wkld to the cut point; run & record fsck1 (w/ tgtd); 
    $abshere/3-rec-fsck1.sh 2>&1 | tee ${PFE_LOG_DIR}/log.3-rec-fsck1

    ############################ (4) 
    #based on ranked_io.txt, replay FS wkld to the cut point; replay and cut fsck1, and run fsck2 (emulate 2nd power fault & 2nd fsck)
    $abshere/4-run-fsck2.sh 2>&1 | tee ${PFE_LOG_DIR}/log.4-run-fsck2
#COMMENT1


#  it=$((it+1))
#done

