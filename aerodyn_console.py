# AERO DYN CONSOLE
# Designed & Developed by Akhil Jacob
import keyboard
import serial
import config
import time
import random

try:
    ser = serial.Serial(config.SERIAL_PORT, config.BAUD_RATE)
    time.sleep(2)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit(1)

print(config.MSG_LOAD)


def auto_generate_flight_commands():
    commands = [
        config.MSG_FORWARD,
        config.MSG_LEFT,
        config.MSG_RIGHT,
        config.MSG_ASCEND,
        config.MSG_DESCEND,
        config.MSG_STOP,
    ]
    gen_command = random.choice(commands)
    return gen_command


while True:
    if keyboard.is_pressed("up"):
        ser.write(config.MSG_FORWARD)
        print("MANUAL CONTROL → FORWARD")
        time.sleep(0.5)
    elif keyboard.is_pressed("left"):
        ser.write(config.MSG_LEFT)
        print("MANUAL CONTROL → LEFT")
        time.sleep(0.5)
    elif keyboard.is_pressed("right"):
        ser.write(config.MSG_RIGHT)
        print("MANUAL CONTROL → RIGHT")
        time.sleep(0.5)
    elif keyboard.is_pressed("down"):
        ser.write(config.MSG_DESCEND)
        print("MANUAL CONTROL → DESCEND")
        time.sleep(0.5)
    elif keyboard.is_pressed("space"):
        ser.write(config.MSG_STOP)
        print("MANUAL CONTROL → STOP")
        time.sleep(0.5)
    elif keyboard.is_pressed("tab"):
        while True:
            gen_command = auto_generate_flight_commands()
            ser.write(gen_command)
            print(f"AERODYN AUTO PILOT: {gen_command.decode().strip()}")
            time.sleep(2)
            ser.write(config.MSG_STOP)
            time.sleep(5)
            if keyboard.is_pressed("esc"):
                print("Exiting AERO DYN AUTO PILOT mode")
                break
