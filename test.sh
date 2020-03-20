#!/bin/bash
# general testing script utilising valgrind

PROGRAM=$1
TESTS=$2

VALGRIND="valgrind
        --error-exitcode=15
        --leak-check=full
        --show-leak-kinds=all
        --errors-for-leak-kinds=all
        -q"

if [[ $# != 2 ]]
then
    echo -e "\e[93mToo little arguments (Expected 2).\e[0m"
    exit 1
fi

OUT=./test_tmp.out
ERR=./test_tmp.err

for f in $TESTS/*.in
do
    $VALGRIND $PROGRAM <$f >$OUT 2>$ERR
    
    RESPONSE=$?

    if [ $RESPONSE == 1 ]
    then
        echo -e "\e[91m${f%.in} - FAILED: memory couldn't be allocated.\e[0m"
    elif [ $RESPONSE == 15 ]
    then
        echo -e "\e[91m${f%.in} - FAILED: problem with memory allocation (valgrind).\e[0m"
    elif [ $RESPONSE != 0 ]
    then
        echo -e "\e[91m${f%.in} - FAILED: code $RESPONSE.\e[0m"
    elif ! diff $OUT ${f%in}out &>/dev/null
    then
        echo -e "\e[91m${f%.in} - FAILED: different output.\e[0m"
    elif ! diff $ERR ${f%in}err &>/dev/null
    then
        echo -e "\e[91m${f%.in} - FAILED: different error output.\e[0m"
    else
        echo -e "\e[92m${f%.in} - PASSED.\e[0m"
    fi
done

rm -f $OUT
rm -f $ERR
