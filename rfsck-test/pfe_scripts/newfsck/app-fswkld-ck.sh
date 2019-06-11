#!/bin/bash

#TODO: check fswkld file content
echo "TODO: $0"
#<<COMMENT1
absme=`readlink -f $0`
abshere=`dirname $absme`

#<<COMMENT1
TEST_WKLD_CHK=$abshere/test_wkld/wkld_validate.sh
echo -e "Executing $TEST_WKLD_CHK $MNT $PFE_LOG_DIR 1"
$TEST_WKLD_CHK $MNT $PFE_LOG_DIR 1
<<COMMENT1

TEST_WKLD_CHK=$abshere/new_wkld/validate.sh
echo -e "Executing $TEST_WKLD_CHK $MNT $PFE_LOG_DIR 10 20"
$TEST_WKLD_CHK $MNT $PFE_LOG_DIR 2 1
COMMENT1
