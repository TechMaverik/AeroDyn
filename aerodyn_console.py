import keyboard
import serial
import time

# Change COM port (Check Arduino IDE → Tools → Port)
ser = serial.Serial('/dev/tty.usbserial-110', 9600)  # Windows example
# For Mac/Linux use something like '/dev/ttyUSB0'

time.sleep(2)

print("Press UP arrow to send FORWARD command")

while True:
    if keyboard.is_pressed("up"):
        ser.write(b"FORWARD\n")
        print("UP Arrow Pressed → FORWARD Sent")
        time.sleep(0.5)