#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a arr=(
  e00fce68084f581617a543c1
  e00fce6830d6d3e2a50e6e0a
  e00fce683f0d52ab51227010
  e00fce686056fbfc34c216d0
  e00fce6843c3de0bf66dd2c1
  e00fce68b38017c02133c784
  e00fce68f87e89fa26d55299
  e00fce68dcc2782aae3ea7d3
  e00fce68553c16d0c1ee2294
  e00fce6827a42b6f47322b91
  e00fce6827112fa58f13ad12
  e00fce689e90ce16704a3fae
  e00fce68262f68be7a012fc1
  e00fce68037889515ee56090
  e00fce68528040c8d455390e
  e00fce68a8cc45e1d931480c
  e00fce6871b13cbb4986ab0a
)

## now loop through the above array
for i in "${arr[@]}"
do
  #  echo "$i"
   resp=$(curl -s "https://api.particle.io/v1/products/9783/devices/$i?access_token=dc0066a56047e23b6e4e25638fd278e86f563e9" | jq '.serial_number')
   echo "$resp"
   # or do whatever with individual element of the array
done

# You can access them using echo "${arr[0]}", "${arr[1]}" also