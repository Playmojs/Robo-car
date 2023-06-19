<<<<<<< Updated upstream
import msvcrt
import serial
import time

ser = serial.Serial("COM4", baudrate = 115200)
active_input = 1000
buffer = 0
driving_keys = ['w', 'a','s','d']
stopped = True

print ("press 'escape' to quit, drive with WASD")

while 1:
    input = ord(msvcrt.getch().decode()) if msvcrt.kbhit() else 1000

    if input == 27:
        break
    if chr(input) in driving_keys and input != active_input:
        active_input = input
        ser.write(active_input)
        stopped = False
        buffer = 0
        print("Change direction")
    elif chr(input) not in driving_keys and not stopped:
        buffer += 1
        if buffer > 17:
            active_input = input
            ser.write(active_input)
            stopped = True
            print("Stopping")
        print("Buffer: ", buffer)
        
    time.sleep(1/50)

    #Check if WASD pressed
        #Compare input with active input
            #Write new input to serial
            #Change active input
    #If WASD is not pressed
        #Check if active input is WASD
            #Check buffer size
                #Write new input to serial
            #Else:
                #Increase buffer
    #Sleep

=======
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
>>>>>>> Stashed changes
