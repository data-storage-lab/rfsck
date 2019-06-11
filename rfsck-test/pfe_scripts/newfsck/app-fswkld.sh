#!/usr/bin/env bash
#simple fs worklod

#$MNT is the mount point of the fs to test
#MNT defined in pfe_config.sh
absme=`readlink -f $0`
abshere=`dirname $absme`

#<<COMMENT1
#FILE=$MNT/test.ext4.node1 
#sudo dd if=/dev/zero of=$FILE bs=4K count=10 conv=sync
#absme=`readlink -f $0`
#abshere=`dirname $absme`

TEST_TEST=$abshere/test_wkld/test_wkld.sh
echo -e "Executing workload: $TEST_TEST $MNT $PFE_LOG_DIR 1\n"
$TEST_TEST $MNT $PFE_LOG_DIR 1
echo -e "Done executing workload\n"

<<COMMENT1
TEST_TEST=$abshere/fs_inod/fs_inod_test.sh
echo -e "Executing workload: $TEST_TEST $MNT 10 10 10\n"
$TEST_TEST $MNT 10 10 10 

<<COMMENT1
# 2>&1 | tee $PFE_LOG_DIR/log.txt
echo -e "Done executing workload\n"
#COMMENT1

TEST_TEST=$abshere/test_wkld/test_wkld.sh
echo -e "Executing workload: $TEST_TEST $MNT $PFE_LOG_DIR 2\n"
$TEST_TEST $MNT $PFE_LOG_DIR 5
echo -e "Done executing workload\n"


TEST_TEST=$abshere/new_wkld/dir_wkld.sh
echo -e "Executing workload $TEST_TEST $MNT $PFE_LOG_DIR 10 10"
$TEST_TEST $MNT $PFE_LOG_DIR 2 1
echo -e "Done executing workload\n"
COMMENT1
