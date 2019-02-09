#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a sernum=(
  HA50AB904PM358E
  HA50AB904UPM6WE
)

declare -a devid=(
  HA50AB904PM358E
  HA50AB904UPM6WE
)

## now loop through the above array
for i in "${arr[@]}"
do
  #  echo "$i"
   resp=$(curl -s "https://api.particle.io/v1/serial_numbers/$i?access_token=39c7655424cc7f16ac8363b2c8913d3cccea141d" | jq '.device_id')
   echo "$resp"
   # or do whatever with individual element of the array
done

# You can access them using echo "${arr[0]}", "${arr[1]}" also