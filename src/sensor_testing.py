import serial
import time
import numpy as np
import struct
import serial.tools.list_ports
myports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
arduino_port = [port for port in myports if 'COM3' in port ][0]

ser = serial.Serial(arduino_port[0], baudrate = 9600, timeout= 1, parity = "N")
data_list = np.ones((500,37))
print(data_list)

def ByteStringToArray(input):
    visual_data = [None]*37 
    for i in range(0, 37):
        if 4*i+4 <= len(input):
            visual_data[i] = round(struct.unpack('<f', input[4*i:4*i+4])[0],3)
    return visual_data

ser.write("t:".encode())
time.sleep(3)

for i in range(0, 500):
    print(i)
    ser.write("q:".encode())
    time.sleep(17)
    print(ser.read_until(b'D:'))
    input= ser.read_until(b':')
    sensor_data = ByteStringToArray(input)
    print(sensor_data)
    data_list[i] = sensor_data
print(data_list)
np.savetxt("sensor_test_2_400_ms.csv",data_list)