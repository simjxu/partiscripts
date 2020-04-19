#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a arr=(
  21002c001747373336373936
  51005b001550483553353620
  3a0059001850483553353620
)

## now loop through the above array
for i in "${arr[@]}"
do
  # echo "$i"
  resp=$(curl -X PUT "https://api.particle.io/v1/products/438/devices/$i/disconnect?access_token=70ef2af33fa689cf31ea9e2724a66ed953c3779f")
  echo "$resp"
  # or do whatever with individual element of the array
done

# You can access them using echo "${arr[0]}", "${arr[1]}" also