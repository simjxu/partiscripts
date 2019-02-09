import numpy as np
import requests


# data = {
#             'name': 'SimonHA50',
#             'access_token': '39c7655424cc7f16ac8363b2c8913d3cccea141d'
#         }
# response = requests.put('https://api.particle.io/v1/products/8323/devices/1f003c000547373336373936')


filetext = open("HA5-3G-devid.txt")
device_ids = filetext.read().split("\n")

filetext = open("HA5-3G-sernum.txt")
ser_num = filetext.read().split("\n")

combined_array = [['' for col in range(2)] for row in range(len(device_ids))]

for i in range(len(device_ids)):
    combined_array[i][0] = ser_num[i]
    combined_array[i][1] = device_ids[i]
    data = {
        'name': ser_num[i],
        'access_token': '39c7655424cc7f16ac8363b2c8913d3cccea141d'
    }
    url_string = 'https://api.particle.io/v1/products/8323/devices/' + device_ids[i]
    response = requests.put(url_string, data=data)
    print(response)

print(combined_array)