"""config.py"""

SERIAL_PORT = "/dev/cu.usbserial-1110"  # Update this to your serial port
BAUD_RATE = 9600
MSG_FORWARD = b"CMD_FORWARD\n"
MSG_LEFT = b"CMD_LEFT\n"
MSG_RIGHT = b"CMD_RIGHT\n"
MSG_ASCEND = b"CMD_ASCEND\n"
MSG_DESCEND = b"CMD_DESCEND\n"
MSG_STOP = b"CMD_STOP\n"
MSG_LOAD = " ####### AERO DYN Console #######\n Designed & Developed by Akhil Jacob\n Press TAB for Auto Pilot Mode\n Press UP, DOWN, LEFT, RIGHT for Manual Control\n Press SPACE to STOP\n"
