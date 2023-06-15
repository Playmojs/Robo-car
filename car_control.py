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

