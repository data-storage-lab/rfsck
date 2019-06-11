#!/usr/bin/env bash
#testing multiple initiators on one machine

absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh

echo "######### Setup iSCSI Initiators"

echo "### restart iscsi"
sudo  /etc/init.d/open-iscsi restart

echo "### discover target" 
#127.0.0.1 for local
#sudo iscsiadm --mode discovery --type sendtargets --portal 164.107.119.55
echo "sudo iscsiadm --mode discovery --type sendtargets --portal $ISCSI_TARGET_IP" 
sudo iscsiadm --mode discovery --type sendtargets --portal $ISCSI_TARGET_IP

echo "### login target 1"
#sudo iscsiadm --mode node --targetname iqn.2013-01.diskfault:emulator --portal 164.107.119.55:3260 --login
echo "sudo iscsiadm --mode node --targetname $ISCSI_TARGET_NAME --portal $ISCSI_TARGET_IP:3260 --login"
sudo iscsiadm --mode node --targetname $ISCSI_TARGET_NAME --portal $ISCSI_TARGET_IP:3260 --login


echo "###### Initiators  setup DONE!"


