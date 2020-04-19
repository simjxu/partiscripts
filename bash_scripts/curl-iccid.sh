#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a arr=(
  36002d000751363234323834
  380025000647373336373936
  490020000350483553353520
  25003b001050483553353620
  260028000151363131363432
  210020000e47373136343738
  25001d001547373036343935
  5b0039000450483553353520
  23003a000f51363034323832
  280034001247373333353132
  560037001250483553353520
  560035001550483553353520
  260039001250483553353520
  35001f001347373036343935
  39003b001047373136343738
)

## now loop through the above array
for i in "${arr[@]}"
do
  #  echo "$i"
   resp=$(curl -s "https://api.particle.io/v1/products/438/devices/$i?access_token=70ef2af33fa689cf31ea9e2724a66ed953c3779f" | jq '.iccid')
   echo "$resp"
   # or do whatever with individual element of the array
done

# You can access them using echo "${arr[0]}", "${arr[1]}" also