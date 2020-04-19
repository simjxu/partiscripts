#!/bin/bash

# You have to do chmod u+x test.sh in order to have it work
# declare an array variable
declare -a arr=(
  e00fce68e5657136b0403ea4
  e00fce680df0825a9a6db6f6
  e00fce68fd899c300f53729e
  e00fce687eccbfe3f048c07a
  e00fce68d96efec8e243cfa8
  e00fce68a3482fd6df5bc7b6
  e00fce6877f4dba3c73601ac
  e00fce68440f27f924e1cdd0
  e00fce685221dc60b4513743
  e00fce68feb915c6aa49a1cc
  e00fce688bf47c8b32da56b0
  e00fce683792878b2f29ee8e
  e00fce68368f8e037a265bdf
  e00fce68bb0d6397d13796da
  e00fce68c1aba6f18face6f5
  e00fce680f76d55cc6f314c8
  e00fce68d6e75ed194f23884
  e00fce686a62234aca8f2ec9
  e00fce68dc9e55bd62136158
  e00fce68ac495b79faa619e4
  e00fce68f2ef3b553626952f
  e00fce6812d1c1d44fcb7e43
  e00fce6897c54f104507d83b
  e00fce687aa0742fbbdc54a6
  e00fce684920c0392bc30f9b
  e00fce6801e6e4136494daa1
  e00fce68f1da891678eb786c
  e00fce685382ca231aa12701
  e00fce68fb2a8c475e313fd2
  e00fce68849cf7e0a4959501
  e00fce68ee42aef3b5f24d28
  e00fce6871eebb9074de6c78
  e00fce683e6235fd56a33f1f
  e00fce686288f1ced81bb2c2
  e00fce68cda3485ead7e9e64
  e00fce68e5c2aa545f915801
  e00fce687bbeaf4f64094f67
  e00fce6813da4e9c382c3938
  e00fce6867e7973f67b63860
  e00fce68e5bb85da0a9e9034
  e00fce6808d08766e14e3a0e
  e00fce683ee299d69ea2a6b6
  e00fce6820b09f903efe096f
  e00fce68011bb70f7e965021
  e00fce6814d88c200c7bb57f
  e00fce6886b687ebcac9890d
  e00fce688146da9c5e6ad2dd
  e00fce680ce44bfa8ac40c41
  e00fce685cf5e733f4d72481
  e00fce6843ee6cb8751e30a7
  e00fce685441133621891aa9
  e00fce68fba772c439713c40
  e00fce689603c8c98822e684
  e00fce682ce717acdb62e151
  e00fce68e4de66482b9c3a83
  e00fce68dfbf1474684948d7
  e00fce686028f1a23e7079a0
  e00fce68c22d209f73cbd1c4
  e00fce6869d138a8d1e4b786
  e00fce68c411c616e173138c
  e00fce68afc765a1ef806588
  e00fce68dbbe71c96c10a7c5
  e00fce689a523752af19c61e
  e00fce68b585ea485e6799c5
  e00fce68608eac603398cd5e
)

## now loop through the above array
for i in "${arr[@]}"
do
  #  echo "$i"
   resp=$(curl -X PUT https://api.particle.io/v1/products/9783/devices/$i -d groups[]="2020_01_90pcs&groups[]=abo&groups[]=v005&groups[]=2head" -d access_token=c2aae22606d35f8b7c0eac2911d877b9fe61d549)
   echo "$resp"
   # or do whatever with individual element of the array
done

# Example if you use terminal (need additional quotes)
# curl -X PUT "https://api.particle.io/v1/products/9783/devices/e00fce68608eac603398cd5e" -d groups[]="2020_01_90pcs&groups[]=abo&groups[]=v005" -d access_token=c2aae22606d35f8b7c0eac2911d877b9fe61d549
# You can access them using echo "${arr[0]}", "${arr[1]}" also



# Example of looping:
# for ((i=1;i<5;i+=1)); do echo "${i}" ; done