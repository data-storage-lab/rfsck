#!/usr/bin/env bash
# Replay and cut FSCK1 


absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

iter=$1
IMG_LOG_DIR=$PFE_LOG_DIR/images
FAULT_LOG_IMG=$IMG_LOG_DIR/img.128M.empty.ext4.fswkld-${iter}
mkdir $IMG_LOG_DIR
    echo
    echo "### Comparing BACKING_STORE image for IO #${iter} with original image"
    echo
#    <<COMMENT1
    cp ${RAMIMG_REPLAY_FAULT} $FAULT_IMG_COPY
    cp $FAULT_IMG_COPY $FAULT_LOG_IMG
<<COMMENT1
    echo "Executing: mount $FAULT_IMG_COPY  $TEMP_MNT"
    mount $FAULT_IMG_COPY  $TEMP_MNT
    if [ $? -eq 0 ]; then
            #echo "$COPY_FILE mounted to $COPY_FILE_MNT"
            ### Recursively compare all the subdirectories 
            ### inside the two image files. If they differ
            ### then there's an error.
            echo -e "\nExecuting diff --brief -r $TEMP_MNT $COPY_FILE_MNT"
            diff --brief -Nr $TEMP_MNT $COPY_FILE_MNT
            if [ $? -ne 0 ]; then
                if [ ! -d $IMG_LOG_DIR ]; then
                    mkdir $IMG_LOG_DIR
                fi
                #cp $FAULT_IMG_COPY $FAULT_LOG_IMG
            fi
            #sleep 2
        echo "Unmount ${FAULT_IMG_COPY}"
        #sleep 3
        umount $TEMP_MNT
        EC=`echo $?`
        while [ $EC -ne 0 ]
        do
          sleep 0.5
          umount $TEMP_MNT
          EC=`echo $?`
        done
        #sleep 2
    else
        ### FSCK2 fails to fix the corrupted image file
        echo "Unable to mount ${FAULT_IMG_COPY}"
        if [ ! -d $IMG_LOG_DIR ]; then
            mkdir $IMG_LOG_DIR
        fi
        cp $FAULT_IMG_COPY $FAULT_LOG_IMG
    fi
#COMMENT1
COMMENT1
