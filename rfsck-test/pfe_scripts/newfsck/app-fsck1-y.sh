#!/usr/bin/env bash
#simple fsck on FSCK1_DEV
#note: -n by default (just to see if there are issues to fix; no recording/replaying/fixing)

#FSCK1_DEV should be exported by other scripts

#if (( $# > 0 )); then

    FSCK1_DEV=$1
#it=$1
#echo "### sudo e2fsck -fy $FSCK1_DEV"
#sudo e2fsck -fy $FSCK1_DEV
#E2FSCK_NEW_EXEC=/home/dsl/project/copy_e2fsprogs/e2fsprogs/build/e2fsck/e2fsck
#E2FSCK_NEW_EXEC=/home/dsl/project/grad_project/copy_e2fsprogs/e2fsck/e2fsck
#E2FSCK_NEW_EXEC=/home/dsl/project/xfsprogs-dev/repair/xfs_repair

#echo "### xfs_repair $FSCK1_DEV"
#xfs_repair $FSCK1_DEV


#    if [ ${ENABLE_STRACE} -eq 0 ]; then
#      echo "### sudo $E2FSCK_NEW_EXEC /dev/sdd"
#      sudo $E2FSCK_NEW_EXEC /dev/sdd

#UNDO_FILE=${PFE_LOG_DIR}/e2fsck.$it.undo

#if [ $it -eq 0 ]; then
#      echo "### sudo e2fsck -z $UNDO_FILE -fy $FSCK1_DEV"
#      sudo e2fsck -z $UNDO_FILE -fy $FSCK1_DEV
#else
#      echo "### sudo e2fsck -fy $FSCK1_DEV"
#      sudo e2fsck -fy $FSCK1_DEV
       echo "### sudo fsck.f2fs -f $FSCK1_DEV"
       sudo fsck.f2fs -f $FSCK1_DEV
#fi
#echo "### sudo e2fsck -fy $FSCK1_DEV"
#sudo e2fsck -fy $FSCK1_DEV
#    else
#      STRACE_LOG_FILE=${PFE_LOG_DIR}/log.strace.${it}
#      echo "### sudo strace -ttt -o $STRACE_LOG_FILE $E2FSCK_NEW_EXEC -fy $FSCK1_DEV"
#      sudo strace -ttt -o $STRACE_LOG_FILE $E2FSCK_NEW_EXEC -fy $FSCK1_DEV
#       echo "### sudo strace -ttt -o $STRACE_LOG_FILE e2fsck -fy $FSCK1_DEV"
#       sudo strace -ttt -o $STRACE_LOG_FILE e2fsck -fy $FSCK1_DEV
#    fi

#  else
#    echo "ERROR: No Disk File! " 
#    exit 1
#fi

