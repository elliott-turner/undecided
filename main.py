import serial
import pyautogui

ser = serial.Serial('/dev/cu.usbmodem143301')  # open serial port

debounced_l = True
debounced_r = True

dead_zone = 20
x_offset = 0
y_offset = 0

while True:
    try:
        data = ser.readline().decode("utf-8").split(' ')

        x = float(data[0])
        y = float(data[1])
        l = bool(int(data[2]))
        r = bool(int(data[3]))

        x = x + x_offset
        y = y + y_offset

        if -dead_zone <= x <= dead_zone: x = 0
        if -dead_zone <= y <= dead_zone: y = 0

        if x < 0: x += dead_zone
        if x > 0: x -= dead_zone
        if y < 0: y += dead_zone
        if y > 0: y -= dead_zone

        if not l and debounced_l:
            pyautogui.click(button='left')
            debounced_l = False
        if l and not debounced_l:
            debounced_l = True

        if not r and debounced_r:
            pyautogui.click(button='right')
            debounced_r = False
        if r and not debounced_r:
            debounced_r = True

        pyautogui.moveRel(x, y)
    except KeyboardInterrupt:
        break
    except:
        pass

ser.close()
