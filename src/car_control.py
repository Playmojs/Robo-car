import serial
import time
from getkey import getkey
import struct

import serial.tools.list_ports
myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
arduino_port = [port for port in myports if 'COM3' in port ][0]

ser = serial.Serial(arduino_port[0], baudrate = 9600, timeout= 1, parity = "N")

active_input = 1000
buffer = 0
driving_keys = ['w', 'a','s','d']
function_keys = ['q', 'c','t']
stopped = True
output_queue = []

def DecodeInput(input):
    return input.decode().split("\r")[0]

def ByteStringToArray(input, num_scans):
    visual_data = [None]*num_scans
    for i in range(0, num_scans):
        visual_data[i] = round(struct.unpack('<f', input[4*i:4*i+4])[0],3)
    return visual_data

print ("Press 'escape' to quit, drive with WASD")

while 1:
    key = getkey(blocking = False)
    keyboard_input = key if key else chr(1000)
    if ord(keyboard_input) == 27:
        break

    if keyboard_input in driving_keys and keyboard_input != active_input:
        active_input = keyboard_input
        output_queue.append(active_input)
        stopped = False
        buffer = 0
    elif keyboard_input not in driving_keys and not stopped:
        buffer += 1
        #print(buffer)
        if buffer > 6:
            active_input = keyboard_input
            output_queue.append(active_input)
            stopped = True
    elif keyboard_input in function_keys and keyboard_input != active_input:
        stopped = True
        active_input = keyboard_input
        output_queue.append(active_input)
        if keyboard_input == 't':
            active_input = 1000
    if len(output_queue) > 0:
        print("Output: ", output_queue[0])
        ser.write((output_queue[0] + ':').encode())
        output_queue.pop(0)
        
    time.sleep(1/30)

    if ser.in_waiting == 0:
        continue
    decoder = ser.read_until(b':', 2).decode()
    if decoder == 'V:':
        print(DecodeInput(ser.readline()).split(":")[0])
    elif decoder == 'D:':
        direction = int(ser.read_until(b':').decode().split(":")[0])
        print("Direction: ", direction)
        num_scans = int(ser.read_until(b':').decode().split(":")[0])
        print("Number of scans: ", num_scans)
        input = ser.read(num_scans*4)
        visual_data = ByteStringToArray(input, num_scans)
        active_input = 1000
        print(visual_data)
        ser.flush()
    elif decoder == 'C:':
        input = ser.read_until(b':')
        print(input[0:-1].decode())
        active_input = 1000