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
export NO_FILES=$3
export DEPTH_DIR=$4

if [ ! -d $TEST_DIR ];then
    echo -e "Directory does not exist: $TEST_DIR\n"
    exit 2
fi

if [ ! -d $LOG_DIR ];then
    echo -e "Directory does not exist: $LOG_DIR\n"
    exit 3
fi

if [ $NO_FILES -le 0 ];then
   echo -e "Not a valid 3rd argument: $NO_FILES\n"
   exit 4
fi

if [ $DEPTH_DIR -le 0 ];then
   echo -e "Not a valid 4th argument: $DEPTH_DIR\n"
   exit 5
fi

cd $TEST_DIR

export DIR_ONE=$TEST_DIR/dir1
export DIR_TWO=$TEST_DIR/dir2
export TEST_LOG=$LOG_DIR/wkld_log

create_files(){
#    echo -e "Input 1: $1"
#    echo -e "Input 2: $2\n"

#<<COMMENT1    
    for (( i = 1 ; i <= $NO_FILES ; i++ ))
    do
        FILE=$1/${i}.txt
        #echo -e "Creating file: $FILE"
        CHK_SM=$2/${i}.txt.chksm
        #echo -e "Creating file: $CHK_SM\n\n"
        echo -e "Executing: < /dev/urandom tr -dc | head -c 1024 > $FILE"
        < /dev/urandom tr -dc "[:alnum:]" | head -c 1024 > $FILE
        echo -e "Executing: md5sum $FILE | awk > $CHK_SM\n"
        md5sum $FILE | awk '{ print $1 }' > $CHK_SM
    done 
#COMMENT1
}

#############################################################################################################
#
#                                              MAIN FUNCTION
#
############################################################################################################# 
if [ ! -d $DIR_ONE ];then
    mkdir $DIR_ONE
fi

if [ ! -d $DIR_TWO ];then
    mkdir $DIR_TWO
fi

if [ ! -d $TEST_LOG ];then
    mkdir $TEST_LOG
fi

#cd $DIR_ONE
#create_files
echo -e "Creating test files and check sum values are recorded in log directory\n"
n=0

WORK_DIR=$DIR_ONE
LOG_CHKSM=$TEST_LOG

create_files $WORK_DIR $LOG_CHKSM
#echo -e "\n\n\n\n"
while [ $n -le $DEPTH_DIR ]
do
    WORK_DIR=$WORK_DIR/$n
    LOG_CHKSM=$LOG_CHKSM/$n
    mkdir $WORK_DIR
    mkdir $LOG_CHKSM
    #cd $WORK_DIR
    create_files $WORK_DIR $LOG_CHKSM 
    n=`expr $n + 1`
done

echo -e "Copying files from $DIR_ONE to $DIR_TWO"

cp -a $DIR_ONE/. $DIR_TWO

echo "Test directory: $TEST_DIR"
echo "Log directory: $TEST_LOG"
echo -e "\nDone executing dir_wkld.sh"
