import serial
import time
import requests

# Setup serial connection to arduino
DEVICE = 'COM3'
BAUD = 9600
arduino = serial.Serial(DEVICE, BAUD)
time.sleep(5)

# I'm going to use a var to check if I've seen the color before
color = 'black'

# Read the thingspeak feed to get the current color
while True:
    try:
        resp = requests.get('http://api.thingspeak.com/channels/1417/field/1/last.json')
        cheerlights = resp.json()['field1']
    except:
        pass
    
    if cheerlights != color:
        #New color, do stuff
        arduino.write(cheerlights.encode('ascii', 'ignore'))
        print(cheerlights)
        color = cheerlights
        time.sleep(16)
