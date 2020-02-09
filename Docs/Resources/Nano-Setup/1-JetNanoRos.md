# ROS Setup on Nano as per [dusty-nv setup](https://github.com/dusty-nv/jetbot_ros) follow upto catkin workspace setup.

sudo apt-get install -y libqt4-dev qt4-dev-tools libglew-dev glew-utils libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libglib2.0-dev

- After Setup
sudo apt install ros-melodic-rqt
sudo apt install ros-melodic-rqt-image-view
sudo apt install ros-melodic-desktop-full
sudo apt install ros-melodic-rosserial ros-melodic-rosserial-arduino ros-melodic-angles

sudo pip3 install pyserial smbus

- Arduino ROS
`http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup`

## To continue setup of jetbot_ros 
- First install https://github.com/NVIDIA-AI-IOT/jetcam for python cam support
- dusty-nv alternative for jetbot_ros (https://github.com/nicolas-beaufort/jetbot_ros)
- dusty-nv alternative for jetson_utils (https://github.com/nicolas-beaufort/jetson-utils)
- issue solving black screen in csi-camera
    - https://github.com/dusty-nv/jetbot_ros/pull/7
    - take changes from @auroraborghi https://github.com/dusty-nv/jetson-utils/pull/5
    - additional changes: 
        - utils/camera-viewer/camera-viewer.cpp:135:51 - put (void**)&imgRGBA
        - utils/python/bindings/PyCamera.cpp:184:40 - put (void**)&ptr
- Steps:
```
$ cd ~/workspace
$ git clone -b onnx https://github.com/dusty-nv/jetson-inference
$ cd jetson-inference

// Skip submodule init step and do following
$ rm -rf utils/
$ git clone https://github.com/nicolas-beaufort/jetson-utils.git utils
// Now make changes in files of utils as suggested above

$ mkdir build
$ cd build
$ cmake ../
$ make

//Make sure camera runs
$ cd aarch64/bin/
$ ./camera-viewer

//If everything works then run
$ cd ../..
$ sudo make install
```

- Install ros_deep_learning as steps provided

- For jetbot_ros use (git clone https://github.com/nicolas-beaufort/jetbot_ros) and everything will work







