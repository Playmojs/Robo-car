import msvcrt
import serial
import time

import serial.tools.list_ports
myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
print (myports)

arduino_port = [port for port in myports if 'COM4' in port ][0]
print(arduino_port)

ser = serial.Serial(arduino_port[0], baudrate = 115200, timeout= 0.1, parity = "N")
active_input = 1000
buffer = 0
driving_keys = ['w', 'a','s','d']
stopped = True

print ("press 'escape' to quit, drive with WASD")

while 1:
    input = msvcrt.getch().decode() if msvcrt.kbhit() else chr(1000)
    print(input)

    if ord(input) == 27:
        break
    if input in driving_keys and input != active_input:
        active_input = input
        ser.write(active_input.encode())
        stopped = False
        buffer = 0
    elif input not in driving_keys and not stopped:
        buffer += 1
        if buffer > 8:
            active_input = input
            ser.write(active_input.encode())
            stopped = True
        print("Buffer: ", buffer)
        
    time.sleep(1/50)
    if ser.in_waiting > 0:
        print(ser.readline())