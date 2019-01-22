#!/bin/bash

# You cannot use spaces in between when setting variables
myvariable=Hello
anothervariable=World

echo $myvariable $anothervariable
echo

# Save bash command results in a variable and then print
mydir=$( ls )
echo $mydir
echo

# Read from a list
listtxt=$( cat list.txt )
echo $listtxt
echo

# math
let a=4*5
echo $a
echo
b=$((3+5 ))
echo $b
echo
c='teststring'
echo 'length of string is' ${#c}
echo

# Basic if statement
if [ 101 -gt 100 ]
then
echo Hey that\'s a large number.
pwd
fi
date

# Find index using regexp
longstring='{"serial_number":"DYNSAB852E9MTDW","product_id":10,"platform_id":10'
echo $longstring

# Strip everything up to and encluding "serial_number"
regex1="${longstring#*serial_number\":\"}"
echo $regex1

# Strip out everything after double quote and comma
regex1="${regex1%%\",*}"
echo $regex1
echo

regex2="{${longstring#*serial_number\":\"}"}%%\",*}"
echo $regex2


s="Info.out.2014-02-08:INFO|SID:sXfzRjbmKbwX7jyaW1sog7n|Browser[Mozilla/5.0 (Windows NT 6.1; WOW64; rv:26.0) Gecko/20100101 Firefox/26.0]"
# strip everything up to and including the first instance of 'Browser['
browser="${s#*Browser[}"

# strip everything after the first ']', again, inclusive
browser="${browser%%]*}"

# ...and show the result...
echo "$browser"