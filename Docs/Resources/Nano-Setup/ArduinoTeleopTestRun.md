1. Start roscore master in one terminal `$ roscore`

2. Make sure arduino is connected to jetson nano and programmed with Buggy_server from arduinoIDE

3. Now run arduino serial python node in new terminl to send commands from arduino to ros master
```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```

4. Now open another seperate terminal for keyboard teleop control
```
$ rosrun simple_motor key_controller
```
