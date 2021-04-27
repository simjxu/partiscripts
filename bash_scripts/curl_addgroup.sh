#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a arr=(
e00fce68594ff09aa342ea29
e00fce681b13eef48c3f4042
e00fce686552b17b2009ab9b
e00fce686ff64e8f0f33f55f
e00fce68967984a6c345b7e4
e00fce687426467d1ec9021f
e00fce68d3b29ce638ab877a
e00fce68e8639e1c4b6241b2
e00fce6840c616dc3f6719fe
e00fce684ee2c4dced500145
e00fce686e5185996eb18e33
e00fce688f91cb21e0f060ea
e00fce688ec68b52e0fac783
e00fce682acdb7bdf4c4c89f
e00fce68ed2bf82f04ef8406
e00fce682a0b2af0e828d2f0
e00fce689c2515cedb7a138b
e00fce681fd04380365ac27e
e00fce68238fae3d293142e2
e00fce68bbbb3cb3c7347258
e00fce681101832044acc594
e00fce68eecd353e3b9f30e9
e00fce686fb816eaefce607e
e00fce68556c75d554fe14db
e00fce6884b344b3dc22521c
e00fce687950248636b117ed
e00fce68c5397be8242551d5
e00fce68c1b14961c599534b
e00fce68b7994e79515b700d
e00fce68a583c1087fee58c0
e00fce6843bf17dbd5ce2435
e00fce681306eaf8afcae91c
e00fce6834c28624b4e0397c
e00fce68f41bdeb6764ec8e6
e00fce68601b6b7932fbdc98
e00fce688f5ea12947875536
e00fce68a209c5d4760feb29
e00fce68cd89496d91a63c45
e00fce689668a43cdeec47cc
e00fce68b2e7d9a58761c959
e00fce68628eabedbde5eac9
e00fce68159cf08919e5447d
e00fce6818e1d1f461dc16e9
e00fce68214e424b3ddfd369
e00fce682520f146c1dab018
e00fce6896ec7f355085297f
e00fce68aab76904285de59c
e00fce689c819e64da54b2f3
e00fce6898731331dde41e5f
e00fce685d3d2269301315cf
e00fce68fa28ae0445fc9c79
e00fce6883bd459f86b90a05
e00fce68269e8f41af19f5ab
e00fce6830b3bfbdada26882
e00fce686a4690e266250515
e00fce68c33294179e3e0c3b
e00fce680215e94deab437b9
e00fce6823d4077e5bcf0341
e00fce684864e85e429a6420
e00fce6843bab8fe0198cf5f
e00fce683db7f4949e9a0d74
e00fce68c7a8b51851d2590b
e00fce68177450e6f16be9d9
e00fce684b1f25e24b4b029e
e00fce688a0a481be17cd170
e00fce68a391052b34eadd8b
e00fce681056357cc77b70e4
e00fce685c9e94395a96c590
e00fce68cda976e511290f34
e00fce681b63239237e3dbdc
e00fce686703fadd5d793db9
e00fce685b4a5e99ec5c103f
e00fce6883d3defc83138dd2
e00fce685eb45dda1f8a9451
e00fce6860791473dbeea1f5
e00fce68dafe9309e4b594c1
e00fce68c92b9e1c35b8ee49
e00fce68c9a98af84b7337cc
e00fce689dbd8048dc418ea3
e00fce68c1c96a38c2e3bfcf
e00fce68d83ab311ec01a687
e00fce68c96092f2b3023332
e00fce686e2388a3359d3896
e00fce680995ea41c8d9100b
e00fce68e112b8834494e19a
e00fce687f5db11284145723
e00fce6833e8b5b9ebb9aa44
e00fce6809d84aface78977d
e00fce68d4a967d98561e940
e00fce687af5586fd6877460
e00fce6859bc3ee201c3afea
e00fce68f9d0dbca32c3e037
e00fce68c5123fc206438e5a
e00fce689b91d16fbf5a6fd7
e00fce683f010978c6087a36
)

## now loop through the above array
for i in "${arr[@]}"
do
  #  echo "$i"
  #  resp=$(curl -X PUT https://api.particle.io/v1/products/10227/devices/$i -d groups[]="2020_01_90pcs&groups[]=abo&groups[]=v005&groups[]=2head" -d access_token=c2aae22606d35f8b7c0eac2911d877b9fe61d549)
   resp=$(curl -X PUT https://api.particle.io/v1/products/10227/devices/$i -d groups[]="2019_11_23_180pcs" -d access_token=f50ed1f5d34f82227bf7919f66c172953537ab18)
   echo "$resp"
   # or do whatever with individual element of the array
done

# Example if you use terminal (need additional quotes)
# curl -X PUT "https://api.particle.io/v1/products/9783/devices/e00fce68608eac603398cd5e" -d groups[]="2020_01_90pcs&groups[]=abo&groups[]=v005" -d access_token=c2aae22606d35f8b7c0eac2911d877b9fe61d549
# You can access them using echo "${arr[0]}", "${arr[1]}" also



# Example of looping:
# for ((i=1;i<5;i+=1)); do echo "${i}" ; done