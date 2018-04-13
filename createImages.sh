#!/bin/bash
##############################
echo "Making project..."

make
##############################
######Executing###############
echo "Executing..."

if [ $# -lt 1 ];then
    echo "Forgot to give file name"
    exit -1
fi;


./projekt $1


##############################
######Moving files###########
echo "Moving files..."

mkdir -p gauss
mv gauss.bmp gauss
mv gaussCrop.bmp gauss







##############################
#Clean
echo "Cleaning ..."
make clean