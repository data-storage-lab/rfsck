#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Input directory"
  exit 1
fi

INPUT_LOG_DIR=$1

if [ ! -d $INPUT_LOG_DIR ]; then
  echo "Directory does not exist: $INPUT_LOG_DIR"
  exit 2
fi

TMP_FILE_NAME=temp.txt

TMP_FILE=$INPUT_LOG_DIR/$TMP_FILE_NAME

cd $INPUT_LOG_DIR

ls | sort > $TMP_FILE

while IFS='' read -r line || [[ -n "$line" ]]; do
  if [ "$line" == "$TMP_FILE_NAME" ]; then
    #echo "Inside if"
    continue
  fi
  it=`echo "$line" | sed -r 's/^.{27}//'`
  #echo -e "\t$line - $it"
  STRACE_FILE=strace$it.txt
  echo -e "\t Generating $STRACE_FILE"
  strace -ttt -o $STRACE_FILE e2fsck -fy $line
done < $TMP_FILE

rm $TMP_FILE
exit 0
