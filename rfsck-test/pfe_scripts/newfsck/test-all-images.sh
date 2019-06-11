#!/bin/bash
i=0
TEST_IMG_DIR=~/pfe_images
TEST_SCRIPT_DIR=/home/dsl/project/grad_project/copy_scsi_tool/pfe_scripts/newfsck
INPUT_FILE=$TEST_SCRIPT_DIR/image2.txt
#CRPT_IMG_DIR=/home/dsl/project/copy_e2fsprogs/e2fsprogs
CRPT_IMG_DIR=/home/dsl/project/f2fs-tools/images
RUN_SCRIPT=$TEST_SCRIPT_DIR/run.sh
while IFS='' read -r line || [[ -n "$line" ]]; do
    CRPT_IMG_FILE=$CRPT_IMG_DIR/$line
    #CRPT_IMG_FILE=$line
    echo "$i: $CRPT_IMG_FILE"
    if [ -f $CRPT_IMG_FILE ]; then
        cp $CRPT_IMG_FILE $TEST_IMG_DIR/img.128M.empty
        cp $TEST_IMG_DIR/img.128M.empty $TEST_IMG_DIR/img.128M.empty.ext4
        $RUN_SCRIPT $CRPT_IMG_FILE
    else
        echo "File not found: $CRPT_IMG_FILE"
    fi
    let "i+=1"
done < $INPUT_FILE
