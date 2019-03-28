#!/bin/bash
# You have to do chmod u+x test.sh in order to have it work

# This script takes a list of serial numbers, finds the device ID, and then changes the name of device to the serial number
# declare an array variable
declare -a sernum=(
  PH-170413-HZ74-0
  BTTN-161011-57BP-0
)


## now loop through the above array
for i in "${sernum[@]}"
do
  # #---jq looks inside json to grab the right part. tr trims the quotes
   devid=$(curl -s "https://api.particle.io/v1/serial_numbers/$i?access_token=0e0fbf7cf17091457fde05850708ec057663c9fc" | jq '.device_id' | tr -d \")
  #  echo $devid
  #  echo $i
   resp=$(curl -X PUT https://api.particle.io/v1/products/8184/devices/$devid -d name=$i -d access_token=0e0fbf7cf17091457fde05850708ec057663c9fc)
  #  resp=$(curl -X PUT https://api.particle.io/v1/products/8184/devices/3a003c001947333438373338 -d name=BTTN-161011-57BP-0 -d access_token=70ef2af33fa689cf31ea9e2724a66ed953c3779f)
   echo "$resp"
done

# #---You can access them using echo "${arr[0]}", "${arr[1]}" also