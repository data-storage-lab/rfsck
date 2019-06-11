#!/bin/bash

absme=`readlink -f $0`
abshere=`dirname $absme`

echo 
echo -e "Executing generate_ranked_io.sh"
#export PFE_LOG_DIR=/home/rameshwar/pfe_logs/logs-fsck-cutopt-EXHAUSTIVE-100.160729143313

echo "Log Directory: ${PFE_LOG_DIR}"
echo "Total replayed IOs: ${TOT_IO_CNT}"

cd ${PFE_LOG_DIR}

if [[ -z "${PFE_LOG_DIR}" ]];then
    echo "Log directory path not set, exiting..."
    exit 1
fi


if [ ! -d ${PFE_LOG_DIR} ];then
    echo "no $PFE_LOG_DIR, please ensure that this directory is available"
    exit 2
fi

OUTPUT_FILE=${PFE_LOG_DIR}/ranked_io.txt
#echo "Executing: ls log.fswkld-* | wc -l"
TEMP_NUM="$(ls log.fswkld-* | wc -l)"
echo "Number of FSCK files: $TEMP_NUM"
echo "Creating $OUTPUT_FILE"
if [ $TEMP_NUM -eq 1 ];then
  echo "1" > $OUTPUT_FILE
  else
    grep -c "Fix?" log.fswkld-* | sed -r 's/^.{11}//' | sed 's/.fsck[0-9]*:/-/g' | sort -t '-' -k 2 -r | sed '/[0-9]-0/d' | cut -d '-' -f1 > $OUTPUT_FILE
fi
echo "Contents of $OUTPUT_FILE:"
more $OUTPUT_FILE
echo
echo "Done"

