#!/usr/bin/env bash
#internal configurations/parameters


######################### Scripts & Executables
export PFE_USR_DIR=${PFE_HOME_DIR}/usr
export REPLAYER=${PFE_USR_DIR}/pfe_replay

export STRACE_FILE=$PFE_LOG_DIR/strace-worklog.txt


######################### iSCSI 
export ISCSI_TARGET_NAME=iqn.2016-06.lustre:node1
export ISCSI_TARGET_IP=127.0.0.1 #local
#script for setup target
export TARGET_SETUP_SH=${PFE_SCRIPT_DIR}/target-setup.sh 
#script for setup initiator
export INITIATOR_SETUP_SH=${PFE_SCRIPT_DIR}/initiator-setup-deb.sh


######################### Disk Images
export IMG_BS=${IMG_DIR}/${IMG_NAME} #full path of backing store
#image in ram (for efficient replay)
export RAMDISK_DIR=${RAMDISK_DIR:=/dev/shm}
export RAMIMG_REPLAY_BASE=${RAMDISK_DIR}/${IMG_NAME}.base
export RAMIMG_REPLAY_FAULT=${RAMDISK_DIR}/${IMG_NAME}.fswkld-fault
export FSCK1_RAMIMG_REPLAY_FAULT=${RAMDISK_DIR}/${IMG_NAME}.fsck1-fault

#backing store base image (where replay starts from)
export IMG_FSWKLD_BASE=${IMG_BS}.fswkld-base
#backing store for applying fs wkld
export IMG_FSWKLD_DOWORK=${IMG_BS}.fswkld-dowork
#target side image for repalying w/ fault
export IMG_FSWKLD_FAULT=${IMG_BS}.fswkld-fault

export IMG_FSCK_BASE=${IMG_BS}.fsck-base
export IMG_FSCK_DOWORK=${IMG_BS}.fsck-dowork
export IMG_FSCK_FAULT=${IMG_BS}.fsck-fault


######################### Logs
#names of default IO logs
export IO_HEAD_LOG=$PFE_LOG_DIR/pfe_io_head_log
export IO_DATA_LOG=$PFE_LOG_DIR/pfe_io_data_log
export IO_HEAD_SPLIT_LOG=${PFE_LOG_DIR}/pfe_io_head_split_log
export ERR_BLOCK_LOG=${PFE_LOG_DIR}/pfe_err_block_log
export TGTD_LOG=${PFE_LOG_DIR}/log.tgtd
#names of IO logs for replay 
export FSWKLD_IO_HEAD_LOG=$IO_HEAD_LOG.fswkld
export FSWKLD_IO_DATA_LOG=$IO_DATA_LOG.fswkld
export FSWKLD_IO_HEAD_SPLIT_LOG=${IO_HEAD_SPLIT_LOG}.fswkld
#export FSCK1_IO_HEAD_LOG=$IO_HEAD_LOG.fsck1
#export FSCK1_IO_DATA_LOG=$IO_DATA_LOG.fsck1
#export FSCK1_IO_HEAD_SPLIT_LOG=${IO_HEAD_SPLIT_LOG}.fsck1
#logs in ram
export IO_HEAD_SPLIT_RAMLOG=${RAMDISK_DIR}/pfe_io_head_split_log

#TESTING - Creating empty FSWKLD_IO_HEAD_SPLIT_LOG
#echo
#echo -e "Executing touch $FSWKLD_IO_HEAD_SPLIT_LOG"
#echo
#touch $FSWKLD_IO_HEAD_SPLIT_LOG


######################### debugfs
export DEBUGFS_DIR=/tmp 


