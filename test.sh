#!/bin/env bash

PASS1="fT45lPtvKWy0UwoH8X49ApW0y2hKRxNgZecasXFzIzCsjj0HLv0bNMRtNTf4JYXhINhAXL7T7wY3TDTUf70HXiQzcrXCYPptYJyGyrTdAW8TSqGJmZ3vpg1HaiD2Oj1"
PASS2="FxlWPlMNIgGe6oINz2kqObMep1thOUtJ79DBb8GfKAAHgGFknCYNiU89rlffwVe9BgN0W4lPzPWFvC6iVSUcCvflFrurgYaXlWQ4RXdU3M4PCVTng7IMN9O21WRriZ9U"
PASS3="U5HJHiWgWvNEpLpFDxs1E6FpLslzQK7dt56GGhPcZljwitd2rLxtpKZQWNRcWmM8cA6mn6gfrj6gbncgUjRlUF1x5QTx7ViFVOYChVEAyDp5CfHRMObqMaXFULrAd2YQZ"

for key in aa ab ac ad ae; do
    src/sos $PASS1 test_data $key "and now for something"
done

for key in aaa aab aac aad aae; do
    src/sos $PASS2 test_data $key "completely different"
done

for key in aaaa aaab aaac aaad aaae; do
    src/sos $PASS3 test_data $key "A Dark and Stormy Night"
done

for key in aa ab ac ad ae; do
    result=$(echo -n $PASS1 | src/sos - test_data $key)
    echo $result
    if [[ $result != "and now for something" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaa aab aac aad aae; do
    result=$(echo -n $PASS2 | src/sos - test_data $key)
    echo $result
    if [[ $result != "completely different" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaaa aaab aaac aaad aaae; do
    result=$(echo -n $PASS3 | src/sos - test_data $key)
    echo $result
    if [[ $result != "A Dark and Stormy Night" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done

for key in aaaa aaab aaac aaad aaae; do
    result=$(echo -n $PASS1 | src/sos - test_data $key)
    echo $result
    if [[ $result == "A Dark and Stormy Night" ]]; then
        echo FAIL
    else
        echo PASS
    fi
done
