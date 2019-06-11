#!/usr/bin/env bash
#local configurations
#change all  paths to your local environment
absme=`readlink -f $0`
abshere=`dirname $absme`

######### repos dir 
export PFE_HOME_DIR=/home/dsl/project/grad_project/copy_scsi_tool #!!!CHANGE TO YOUR PATH TO THE REPOS 
#export PFE_SCRIPT_DIR=~/localfsck  #cp -r scsi-tool/localfsck ~/localfsck
export PFE_SCRIPT_DIR=$PFE_HOME_DIR/pfe_scripts/newfsck  
# FS worklod and checker
export FSWKLD_SH=${PFE_SCRIPT_DIR}/app-fswkld.sh
export FSCK1_N_SH=${PFE_SCRIPT_DIR}/app-fsck1-n.sh
export FSCK1_Y_SH=${PFE_SCRIPT_DIR}/app-fsck1-y.sh
export FSCK2_SH=${PFE_SCRIPT_DIR}/app-fsck2.sh

#target side img
export IMG_DIR=~/pfe_images
if [ ! -d $IMG_DIR ];then
    echo "no $IMG_DIR, creating one ..."
    sudo mkdir $IMG_DIR
    sudo chmod 777 $IMG_DIR
fi
export IMG_NAME=img.128M.empty.ext4 #should create it beforehand


#target side log dir
export PFE_LOG_DIR=~/pfe_logs
if [ ! -d $PFE_LOG_DIR ];then
    echo "no $PFE_LOG_DIR, creating one ..."
    sudo mkdir $PFE_LOG_DIR
    sudo chmod 777 $PFE_LOG_DIR
fi

#initiator side mount point
export MNT=~/pfe_mnt 
if [ ! -d $MNT ];then
    echo "no $MNT, creating one ..."
    sudo mkdir $MNT
    sudo chmod 777 $MNT
fi

#initiator side virtual  device
export INIT_VIRTUAL_DEV=/dev/sdc #CHANGE TO YOURS!!!

#export INIT_VIRTUAL_DEV=/dev/sdb #CHANGE TO YOURS!!!

######### fault injection methods
export CUT_OPTION=EXHAUSTIVE #cut all 
#export CUT_OPTION=SAMPLING; export SAMPLE_PERCENTAGE=1  #sample N out of 100
#export CUT_OPTION=PATTERN #cut based on io pattern; need CUT_PATTERN_FILE

######### profiling for worker: strace or pintool or none
#export PROFILER=pintool
#export PROFILER=strace #default
export PROFILER=none 

######### profiling for checker: strace or pintool or none
#export PROFILER_CK=pintool
#export PROFILER_CK=strace
export PROFILER_CK=none #default 

export PFE_IO_BLOCK_SIZE=4096
#export ENABLE_STRACE=1

######### other configs 
#. $abshere/pfe_internal.sh
