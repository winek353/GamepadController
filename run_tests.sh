#!/bin/bash


currentTime=`date +"%m-%d-%y_%T"`
mkdir -p TestResults/$currentTime

logsFile=TestResults/$currentTime/JoypadHandlerTest.out

./JoypadHandlerTest &> $logsFile

if [ "$?" -eq "0" ]; then
    echo "All test passed! - good job"
else
    echo "Some of tests failed - please check results in $logsFile"
fi

cp $logsFile ./last_test_results.txt
