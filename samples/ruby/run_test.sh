#!/bin/sh

# Clear lights
tddlight c

# Yellow (test are running)
tddlight y
# Sleep a bit to simulate longer tests
sleep 1

ruby tc_simple_number.rb

if [[ $? == 0 ]]; then
    # Green (success)
    tddlight g
else
    # Red (failure)
    tddlight r
fi
