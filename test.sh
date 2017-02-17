#!/bin/env bash

PASS1="fT45lPtvKWy0UwoH8X49ApW0y2hKRxNgZecasXFzIzCsjj0HLv0bNMRtNTf4JYXhINhAXL7T7wY3TDTUf70HXiQzcrXCYPptYJyGyrTdAW8TSqGJmZ3vpg1HaiD2Oj1"
PASS2="FxlWPlMNIgGe6oINz2kqObMep1thOUtJ79DBb8GfKAAHgGFknCYNiU89rlffwVe9BgN0W4lPzPWFvC6iVSUcCvflFrurgYaXlWQ4RXdU3M4PCVTng7IMN9O21WRriZ9U"
PASS3="U5HJHiWgWvNEpLpFDxs1E6FpLslzQK7dt56GGhPcZljwitd2rLxtpKZQWNRcWmM8cA6mn6gfrj6gbncgUjRlUF1x5QTx7ViFVOYChVEAyDp5CfHRMObqMaXFULrAd2YQZ"

SECRET1="and now for something"
SECRET2="completely different"
SECRET3="A Dark and Stormy Night,...bang!"

for key in aa ab ac ad ae; do
    src/sos $PASS1 test_data $key "$SECRET1"
    if [[ $? == 0 ]]; then
        echo PASS
    else
        echo FAIL
    fi
done

for key in aaa aab aac aad aae; do
    src/sos $PASS2 test_data $key "$SECRET2"
    if [[ $? == 0 ]]; then
        echo PASS
    else
        echo FAIL
    fi
done

for key in aaaa aaab aaac aaad aaae; do
    src/sos $PASS3 test_data $key "$SECRET3"
    if [[ $? != 0 ]]; then
        echo PASS
    else
        echo FAIL
    fi
done

for key in aa ab ac ad ae; do
    result=$(echo -n $PASS1 | src/sos - test_data $key)
    echo "[$result]"
    if [[ $result != "$SECRET1" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaa aab aac aad aae; do
    result=$(echo -n $PASS2 | src/sos - test_data $key)
    echo "[$result]"
    if [[ $result != "$SECRET2" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaaa aaab aaac aaad aaae; do
    result=$(echo -n $PASS3 | src/sos - test_data $key)
    error=$?
    echo "[$result]"
    if [[ $result != "" || $error == 0 ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaa aab aac aad aae; do
    result=$(echo -n $PASS1 | src/sos - test_data $key)
    echo "[$result]"
    if [[ $result == "$SECRET2" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done
