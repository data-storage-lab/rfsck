#!/usr/bin/env bash
#do work and record IO seq.

echo -e "\n\nExecuting dir_wkld.sh\n\n"

absme=`readlink -f $0`
abshere=`dirname $absme`

if [ $# -ne 4 ];then
    echo -e "Require 4 input arguments."
    echo -e "Example: dir_wkld.sh <TEST_DIRECTORY> <PFE_LOG_DIR> <NO_OF_FILES> <DEPTH_OF_SUB_DIRECTORIES>"
    exit 1
fi

export TEST_DIR=$1
export LOG_DIR=$2
export NUM_FILES=$3
export DEPTH_DIR=$4

export TEST_DIR2=$TEST_DIR/dir2
export TEST_LOG=$LOG_DIR/wkld_log

for (( j=0 ; j <= $DEPTH_DIR; j++ ))
do
    for (( i=1 ; i <=$NUM_FILES ; i++ ))
    do
        FILE=$TEST_DIR2/${i}.txt
        CHK_SM=$TEST_LOG/${i}.txt.chksm
        #echo -e "\tVerifying file: $FILE"
        #echo -e "\tChecksum file: $CHK_SM"
        CHKSM_VAL=`md5sum $FILE | awk '{ printf $1 }'`
        diff -u --ignore-all-space $CHK_SM <(echo "$CHKSM_VAL")
        TMP=`echo $?`
        if [ $TMP -ne 0 ];then
            echo -e "File changed: $FILE"
        fi
    done
    TEST_DIR2=$TEST_DIR2/$j
    TEST_LOG=$TEST_LOG/$j
done

echo -e "\nTest directory: $TEST_DIR"
echo -e "Log directory: $LOG_DIR/wkld_log\n"

echo -e "Done executing validate.sh\n"
exit 0

