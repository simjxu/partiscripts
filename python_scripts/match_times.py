import numpy as np 
import re             # For regular expressions
import time 

# Briggs wifi data should have publishes every 5 minutes

filetext = open("briggswifitest.txt")
textlines = filetext.read().split("\n")

devicedict = {}
coreid_begin = "\"coreid\":\""
coreid_end = "\"}"
date_begin = "\"published_at\":\""
date_end = "\",\"coreid"
data_begin = "RSSI: "
data_end = "Blocking"
particle_date_format = '%Y-%m-%dT%H:%M:%S.%fZ'

# Put all data into an array
for i in range(len(textlines)):

  # Grab coreid
  coreid = re.search(coreid_begin + "(.*)" + coreid_end, 
                    textlines[i]).group(1)

  # Determine if the entry already exists
  try:
    devicedict[coreid]
  except KeyError:
    devicedict[coreid] = []

  # Grab date (1st column)
  date = re.search(date_begin + "(.*)" + date_end, 
                    textlines[i]).group(1)
  devicedict[coreid].append([0,0,0])
  devicedict[coreid][len(devicedict[coreid])-1][0] = date

  # Grab the data (2nd column)
  data = re.search(data_begin + "(.*)" + data_end, 
                    textlines[i]).group(1)
  devicedict[coreid][len(devicedict[coreid])-1][1] = data

  # 3rd column convert date to seconds
  dateobj = time.strptime(date, particle_date_format) 
  devicedict[coreid][len(devicedict[coreid])-1][2] = time.mktime(dateobj)

# First confirm how many misses
for ID in devicedict:
  miss_count = 0
  for i in range(1,len(devicedict[coreid])):
    print(devicedict[coreid][i][2])
    print(devicedict[coreid][i][2]-devicedict[coreid][i-1][2])
    diff = (devicedict[coreid][i][2]-devicedict[coreid][i-1][2])/300
    if diff > 1.5:            # If we see more than one 5 minute window
      miss_count += diff
  




