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

mkdir -p gauss-0-0_1
mv gauss-0-0_1.bmp gauss-0-0_1
mv gauss-0-0_1Crop.bmp gauss-0-0_1







##############################
#Clean
echo "Cleaning ..."
make clean