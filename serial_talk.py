import os
import serial

ser = serial.Serial('/dev/tty.usbserial-A925D7BZ', 9600)

old_status = 'off'

while True:
    line = ser.readline().rstrip()
    print line

    new_status = 'on' if (line == 'PIR_HIGH') else 'off'
    print "\033[32m%s --> %s\033[0m" % (old_status, new_status)

    # if old_status == 'on' and new_status == 'off':
    if old_status == 'off' and new_status == 'on':
        os.system('/System/Library/Frameworks/ScreenSaver.framework/Resources/ScreenSaverEngine.app/Contents/MacOS/ScreenSaverEngine')

    old_status = new_status

ser.close()
