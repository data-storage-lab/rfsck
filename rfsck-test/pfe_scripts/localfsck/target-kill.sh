#!/usr/bin/env bash

echo "######### Kill iSCSI Target"
echo "### check tgtd before killing it"
sudo ps -ef|grep -i tgt
echo "### kill tgtd "
sudo killall -9 tgtd
echo "### check tgtd gone"
sudo ps -ef|grep -i tgt

