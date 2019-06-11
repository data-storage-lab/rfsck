#!/usr/bin/env bash
#do work and record IO seq.

echo -e "\n\nExecuting test_wkld.sh\n\n"

absme=`readlink -f $0`
abshere=`dirname $absme`

if [ $# -eq 0 ]; then
    echo "No input arguments passed"
    exit 1
fi

export TEST_LOG=$2/wkld_log
export TEST_DIR=$1
export CNT=$3

if [ ! -d $TEST_LOG ]; then
    echo "$TEST_LOG folder does not exist.. Creating one.. "
    mkdir $TEST_LOG
fi

#cd $TEST_DIR
<<TESTING
export TEST_FILE1=$TEST_DIR/file1.test
export TEST_FILE2=$TEST_DIR/file2.test
export TEST_FILE3=$TEST_DIR/file3.test
export TEST_CHKSM1=$TEST_LOG/file1.test.chksm
export TEST_CHKSM2=$TEST_LOG/file2.test.chksm
export TEST_CHKSM3=$TEST_LOG/file3.test.chksm

echo "Creating file of size 12288 bytes: $TEST_FILE1"

< /dev/urandom tr -dc "[:alnum:]" | head -c 12288 > ${TEST_FILE1}
md5sum ${TEST_FILE1} | awk '{ print $1 }' > $TEST_CHKSM1

echo -e "Checksum value stored in $TEST_CHKSM1\n"
echo "Creating another file of size 12288 bytes: $TEST_FILE2"

< /dev/urandom tr -dc "[:alnum:]" | head -c 12288 > ${TEST_FILE2}
md5sum ${TEST_FILE2} | awk '{ print $1 }' > $TEST_CHKSM2

echo -e "Checksum value stored in $TEST_CHKSM2\n"
echo "Combining two files into another file: $TEST_FILE3"

cat ${TEST_FILE1} ${TEST_FILE2} > ${TEST_FILE3} 
md5sum ${TEST_FILE3} | awk '{ print $1 }' > $TEST_CHKSM3
echo -e "Checksum value stored in $TEST_CHKSM3"
TESTING

for (( i = 1; i <= $CNT; i++ ))
do 
    for(( j = 1; j <= 2; j++ ))
    do
        TEST_FILE=$TEST_DIR/file${i}${j}.test
        < /dev/urandom tr -dc "[:alnum:]" | head -c 12288 > $TEST_FILE
        md5sum $TEST_FILE | awk '{ printf $1 }' > $TEST_LOG/file${i}${j}.test.chksm
    done
    cat $TEST_DIR/file${i}1.test $TEST_DIR/file${i}2.test > $TEST_DIR/file${i}3.test
    md5sum $TEST_DIR/file${i}3.test | awk '{ printf $1 }' > $TEST_LOG/file${i}3.test.chksm
done

echo -e "\nLog Directory: $TEST_LOG"
echo -e "\nWorking Directory: $TEST_DIR"
echo -e "\n\nDone executing test_wkld.sh\n\n"

exit 0
