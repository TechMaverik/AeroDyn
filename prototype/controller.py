import inputs
import requests


def quick_left():
    url = "http://10.120.3.178/quick_left"
    requests.get(url)


def quick_right():
    url = "http://10.120.3.178/quick_right"
    requests.get(url)


def left():
    url = "http://10.120.3.178/left"
    requests.get(url)


def right():
    url = "http://10.120.3.178/right"
    requests.get(url)


def front():
    url = "http://10.120.3.178/front"
    requests.get(url)


def back():
    url = "http://10.120.3.178/back"
    requests.get(url)


def stop():
    url = "http://10.120.3.178/stop"
    requests.get(url)


pad = inputs.devices.gamepads
if len(pad):
    while True:
        events = inputs.get_gamepad()
        for event in events:

            if event.ev_type == "Key" and event.code == "BTN_START":
                print("START", event.state)  # back
                quick_left()
            if event.ev_type == "Key" and event.code == "BTN_SELECT":
                print("SELECT", event.state)  # start
                quick_right()

            if event.ev_type == "Key" and event.code == "BTN_THUMBL":
                print("THUMBL", event.state)  # left joystick btn
            if event.ev_type == "Key" and event.code == "BTN_THUMBR":
                print("THUMBR", event.state)  # right joystick btn
            if event.ev_type == "Key" and event.code == "BTN_EAST":
                print("B", event.state)  # B
                back()
            if event.ev_type == "Key" and event.code == "BTN_NORTH":
                print("Y", event.state)  # Y
            if event.ev_type == "Key" and event.code == "BTN_WEST":
                print("X", event.state)  # X
            if event.ev_type == "Key" and event.code == "BTN_SOUTH":
                print("A", event.state)  # A
            if event.ev_type == "Key" and event.code == "BTN_TL":
                print("LB", event.state)  # LB
                stop()
            if event.ev_type == "Key" and event.code == "BTN_TR":
                print("RB", event.state)  # RB
                stop()
            if event.ev_type == "Absolute" and event.code == "ABS_Z":
                print("LT", event.state)  # LT
                left()
            if event.ev_type == "Absolute" and event.code == "ABS_RZ":
                print("RT", event.state)  # RT
                right()
            if event.ev_type == "Absolute" and event.code == "ABS_Y":
                print("L_JOY_Y", event.state)  # left joystick y
            if event.ev_type == "Absolute" and event.code == "ABS_X":
                print("L_JOY_X", event.state)  # left joystick x
            if event.ev_type == "Absolute" and event.code == "ABS_RX":
                print("R_JOY_X", event.state)  # right joystick x
            if event.ev_type == "Absolute" and event.code == "ABS_RY":
                print("R_JOY_Y", event.state)  # right joystick y
            if event.ev_type == "Absolute" and event.code == "ABS_HAT0X":
                print("X_1", event.state)  # Dpad X
            if event.ev_type == "Absolute" and event.code == "ABS_HAT0Y":
                print("Y_1", event.state)  # Dpad Y
else:
    print("NO gamepad or Controller found")
