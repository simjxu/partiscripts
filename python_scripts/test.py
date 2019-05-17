import re
import time

#  Open up  the file
filetext = open("multinode.txt", "r")
lines = filetext.readlines()
i = 1
tenthoucount = 0;

while i<len(lines):
  spltstr0 = re.split(" : ", lines[i-1])
  spltstr1 = re.split(" : ", lines[i])
  if spltstr0[1] == spltstr1[1]:
    retries0 = int(spltstr0[0])
    retries1 = int(spltstr1[0])
    if retries1 >= retries0:
      lines.pop(i-1)
      i = i-1
    else:
      lines.pop(i)
      i = i-1
  i += 1

totalretries=[0,0,0,0,0,0,0]
averagetime = 0
for i in range(len(lines)):
  spltstr0 = re.split(" : ", lines[i])
  retries0 = int(spltstr0[0])
  totalretries[retries0] += 1
  averagetime = averagetime + int(spltstr0[1])
  if int(spltstr0[1]) > 7000:
    tenthoucount += 1
  elif int(spltstr0[1]) >= 2000 and retries0 >=3:
    tenthoucount += 1 
  elif int(spltstr0[1]) >= 4000 and retries0 >=2:
    tenthoucount += 1 
  elif int(spltstr0[1]) >= 6000 and retries0 >=1:
    tenthoucount += 1 

print("total retries: ", totalretries)
averagetime = averagetime/len(lines)
print("average time: ", averagetime)
print("skipcount: ", tenthoucount)

#  Open up  the file
filetext = open("multinode.txt", "r")
lines = filetext.readlines()
i = 1
