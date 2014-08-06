import time
import serial

teststring = [
        "hello world",
        "0123456789ABCDE",
        "0123456789ABCDEF",
        "0123456789ABCDEFx",
        "0123456789ABCDEFxy",
        "0123456789ABCDEFxyz",
]

ser = serial.Serial('/dev/tty.usbserial-A925D7BZ', 9600)

for s in teststring:
    print s
    ser.write(s)
    time.sleep(3)

ser.close()
