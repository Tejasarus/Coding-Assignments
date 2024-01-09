from flask import Flask, request
import json
app = Flask(__name__)
import serial

#ser = serial.Serial('/dev/ttyACM0',9600)
val1 = 0
val2 = 0

@app.route('/receive', methods=['POST'])
def receive():
    data = json.loads(request.data)

    global light = 0
    global lock = 0
    global garage = 0
    global temp = 0
    
    print(data['direction'])
    
    if data['direction'] == 'unlock1':
        lock = 1
        
    elif data['direction'] == 'lock1':
        lock = 0
          
    if data['direction'] == 'on1':
        light = 1

    elif data['direction'] == 'off1':
        light = 0
    
    if data['direction'] == 'unlock2':
        garage = 1

    elif data['direction'] == 'lock2':
        garage = 0
    
    if 'temp' in data['direction']:
        temp = int(data['direction'][5:])

    #ser.write((str(light)+ ' ' + str(lock) + ' ' + str(garage) + ' ' + str(temp) + '\n').encode('utf-8'))
    
    return "Woop Woop this finally worked"

if __name__ == '__main__':
    app.run(host='192.168.1.10', port=5000)
    
if temp == 1:
    email_str = email_str + "Your garage door is open." + '\n'
else:
    email_str = email_str + "The temperature inside is: " + actual_temp + " and the temperature that is set is: " + wanted_temp + "." + '\n'