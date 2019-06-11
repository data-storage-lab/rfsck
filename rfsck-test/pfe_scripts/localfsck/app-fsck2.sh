#!/usr/bin/env bash
#simple fsck on FSCK2_DEV

absme=`readlink -f $0`
abshere=`dirname $absme`
. $abshere/pfe_helper.sh
#FSCK2_DEV should be exported by outer scripts

#check w/o fix
echo "# sudo e2fsck -fn $FSCK2_DEV"
sudo e2fsck -fn $FSCK2_DEV

#check and fix
echo "# sudo e2fsck -fy $FSCK2_DEV"
sudo e2fsck -fy $FSCK2_DEV

#see if can mount after fix
echo "# sudo mount $FSCK2_DEV $MNT"
sudo mount $FSCK2_DEV $MNT
sleep 1

#TODO: add checking for file content
#echo "# sudo $abshere/app-fswkld-ck.sh"
#$abshere/app-fswkld-ck.sh
echo "# sudo /home/rameshwar/assignment/grad_project/copy_scsi_tool/pfe_scripts/localfsck/app-fswkld-ck.sh"
/home/rameshwar/assignment/grad_project/copy_scsi_tool/pfe_scripts/localfsck/app-fswkld-ck.sh

echo "# sudo umount $MNT"
sudo umount $MNT
