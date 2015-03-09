#!/bin/bash


currentTime=`date +"%m-%d-%y_%T"`
mkdir -p TestResults/$currentTime

logsFile=TestResults/$currentTime/JoypadHandlerTest.out
./JoypadHandlerTest --gtest_list_tests > regressionList.txt

testSuite=""
testName=""

while read line;
do
    if [[ $line =~ .*\. ]]; then
        testSuite=$line
    else
        testName=$line

        mkdir -p TestResults/$currentTime/$testSuite$testName
        ./JoypadHandlerTest --gtest_filter=$testSuite$testName &> TestResults/$currentTime/$testSuite$testName/gtest.txt
        testResult=$?
        mv debug.txt TestResults/$currentTime/$testSuite$testName

        if [ $testResult -eq 0 ];
        then
            echo -e "\e[32m   PASSED   $testSuite$testName\e[0m"
            rm -Rf TestResults/$currentTime/$testSuite$testName
        else
            echo -e "\e[31m   FAILED   $testSuite$testName\e[0m"
        fi

    fi
done < regressionList.txt
rm -f regressionList.txt
