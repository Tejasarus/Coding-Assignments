
while True:
    ser = serial.Serial('/dev/ttyACM0',9600)
    line = ser.readline().decode('utf-8').strip()
    print("Received line:", line)