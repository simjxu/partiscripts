#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
resp=$(curl -s "https://api.particle.io/v1/products/10227/devices?access_token=f50ed1f5d34f82227bf7919f66c172953537ab18" | jq 'id')
echo "$resp"

# You can access them using echo "${arr[0]}", "${arr[1]}" also