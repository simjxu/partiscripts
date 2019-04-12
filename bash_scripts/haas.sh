#!/bin/bash
# You have to do chmod u+x test.sh in order to have it work

# This script takes a list of serial numbers, finds the device ID, and then changes the name of device to the serial number
# declare an array variable
declare -a sernum=(
  HA50AB913MVNBPR
)


## now loop through the above array
for i in "${sernum[@]}"
do
  # #---jq looks inside json to grab the right part. tr trims the quotes
   devid=$(curl -s "https://api.particle.io/v1/serial_numbers/$i?access_token=82a581c09caf99ab72881eb0bd86686f21f053f4" | jq '.device_id' | tr -d \")
   resp=$(curl -X PUT https://api.particle.io/v1/products/9077/devices/$devid -d name=$i -d access_token=82a581c09caf99ab72881eb0bd86686f21f053f4)
   echo "$resp"
done