import msvcrt
import serial
import time

ser = serial.Serial("COM4", baudrate = 115200)
active_input = 1000
buffer = 0
driving_keys = ['w','a','s','d']
stopped = True

print ("press 'escape' to quit, drive with WASD")

while (input:=ord(msvcrt.getch().decode()) if msvcrt.kbhit() else 1000) != 27:
    #Stop if new input is 27 (ascii code for esc)
    #Check if WASD pressed
    if chr(input) in driving_keys:
        #Compare new input with active input
        if input!=active_input:
            #Change active input into new input
            active_input=input
            #Write new input to serial
            ser.write(active_input)
            # Set stopped to False
            stopped=False
            # Reset buffer
            buffer=0
            print("Change direction")
        print("Driving")
    #If WASD is not pressed
    elif not stopped:
        # Increment buffer
        buffer+=1
        # Check if buffer size >= 10
        if buffer>=10:
            # Update active input
            active_input=input
            # Write to serial
            ser.write(active_input)
            # Set stopped to True
            print("Stopping")
        print(f"Buffer: {buffer}")
    # Wait 0.02 seconds
    time.sleep(0.02)

