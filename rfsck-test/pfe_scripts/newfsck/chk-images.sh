#!/bin/bash

INPUT_FILE=/home/dsl/project/grad_project/copy_scsi_tool/pfe_scripts/newfsck/chk_imgs.txt
WORK_DIR=/home/dsl/project/grad_project/copy_scsi_tool/pfe_scripts/newfsck
CNT=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    IMAGES_DIR=$line/images
    #echo "cd $line"
    cd $line
    #echo "ls log.diff-chk-* -l | wc -l"
    TOT_CUT_CNT=`ls log.diff-chk-* -l | wc -l`
    IMGS_CNT=0
    if [ -d $IMAGES_DIR ]; then
        cd $IMAGES_DIR
        IMGS_CNT=`ls -l | wc -l`
        let "IMGS_CNT=IMGS_CNT-1" 
        #echo "$line : $TOT_CUT_CNT : $IMGS_CNT"
        #echo "$line : $TOT_CUT_CNT : $IMGS_CNT" >> $WORK_DIR/imgs_cnt.txt
        let "CNT+=1"
    fi
    echo "$line : $TOT_CUT_CNT : $IMGS_CNT"
    echo "$line : $TOT_CUT_CNT : $IMGS_CNT" >> $WORK_DIR/imgs_cnt.txt
done < $INPUT_FILE

echo -e "\n\nTotal failure scenarios: $CNT"
exit 0
