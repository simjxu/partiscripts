import re
import time
import numpy as np 

# VERSION 1 of PARSER -------------------------------
filetext = open("ppinterval.txt")
textlines = filetext.read().split("\n")

# Edit these:
timeinterval = 10     # minutes

devicedict = {}
coreid_begin = "\"coreid\":\""
coreid_end = "\""
date_begin = "\"published_at\":\""
date_end = "\""
data_begin = "\"data\":\""
data_end = "\""
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

  # Grab date
  date = re.search(date_begin + "(.*)" + date_end, 
                    textlines[i]).group(1)
  devicedict[coreid].append([0,0,0])
  devicedict[coreid][i][0] = date

  # Grab the data 
  data = re.search(data_begin + "(.*)" + data_end, 
                    textlines[i]).group(1)
  devicedict[coreid][i][1] = data

  # 3rd column convert date to seconds
  dateobj = time.strptime(date, particle_date_format) 
  devicedict[coreid][i][2] = time.mktime(dateobj)

misscounts = {}
# Analyze each coreid data
for id in devicedict:
  misscounts[id] = 0

  # Create an array of times for the coreid
  time_arr = []
  for j in range(len(devicedict[id])):
    time_arr[j] = devicedict[id][j][2]

  # Create an array of differences
  time_diff = np.diff(time_arr)
  for item in time_arr:
    # Add the amount of missed publishes there are
    misscounts[id] += round(item/(10*60000)-1)

print(misscounts)



# # VERSION 2 OF PARSER ---------------------------------
# filetext = open("ppinterval.txt")
# textlines = filetext.read().split("\n")

# devicedict = {}

# # Put all data into an array
# for i in range(len(textlines)):
#   segments = textlines[i].split(",")

#   # Grab coreid
#   coreid = segments[1].split(" coreid=")[1]

#   # Determine if the entry already exists
#   try:
#     devicedict[coreid]
#   except KeyError:
#     devicedict[coreid] = []

#   # Grab date
#   date = segments[3].split(" published_at=")[1].split("Z}")[0]
#   devicedict[coreid][len(devicedict[coreid])][0] = date

#   # Grab the data 
#   data = segments[0].split("{data=")[1]
#   devicedict[coreid][len(devicedict[coreid])][1] = data

# misscounts = {}
# # Analyze
# for id in devicedict:
#   misscounts[id] = 0
#   for j in len(devicedict[id]):
#     # pull first item in array, which is the date

#     # Convert the date into a time

#     # subtract 1st time from 2nd time

#     miscounts[id] += intermiss