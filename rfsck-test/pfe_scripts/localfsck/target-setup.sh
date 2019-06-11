#!/usr/bin/env bash
#setup target based on a given backing store file
#usage:./THISFILE BACKING_STORE_FILE

absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

if (( $# > 0 )); then
    BS_FILE=$1
  else
    echo "No Backing Store File! " 
    exit 1
fi

date
echo "###### SETUP iSCSI TARGET"

echo "### check tgtd started"
check_tgtd

date
echo "### define & create an iscsi target name"
sudo $PFE_USR_DIR/tgtadm  --lld iscsi --op new --mode target --tid 1 -T $ISCSI_TARGET_NAME

echo "### add $BS_FILE as backing store"
sudo $PFE_USR_DIR/tgtadm  --lld iscsi --op new --mode logicalunit --tid 1 --lun 1 -b $BS_FILE 

echo "### enable the target to accept any initiator"
sudo $PFE_USR_DIR/tgtadm   --lld iscsi --op bind --mode target --tid 1 -I ALL

echo "### view the target created"
sudo $PFE_USR_DIR/tgtadm  --lld iscsi --op show --mode target
echo ""

echo "check port 3260"
sudo netstat -tulpn | grep 3260
echo ""

echo "####### TARGET SETUP DONE!"

