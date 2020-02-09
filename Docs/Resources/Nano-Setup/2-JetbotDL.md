## Installing Tensorflow

$ sudo apt-get update
$ sudo apt-get install libhdf5-serial-dev hdf5-tools libhdf5-dev zlib1g-dev zip libjpeg8-dev

$ sudo pip3 install -U pip testresources setuptools
$ sudo pip3 install -U numpy==1.16.1 future==0.17.1 mock==3.0.5 h5py==2.9.0 keras_preprocessing==1.0.5 keras_applications==1.0.8 gast==0.2.2 enum34 futures protobuf

For Tensorflow 2.0
$ sudo pip3 install --pre --extra-index-url https://developer.download.nvidia.com/compute/redist/jp/v42 tensorflow-gpu

For Tensorflow 1.xx Latest
$ sudo pip3 install --pre --extra-index-url https://developer.download.nvidia.com/compute/redist/jp/v42 'tensorflow-gpu<2'


## Install pytorch

Ref https://devtalk.nvidia.com/default/topic/1049071/jetson-nano/pytorch-for-jetson-nano/

## Replace Adafruit_MotorHAT
$ sudo chmod 777 /usr/local/lib/python3.6/dist-packages/Adafruit_MotorHAT/Adafruit_MotorHAT_Motors.py
$ cp Adafruit_MotorHAT_Motors.py /usr/local/lib/python3.6/dist-packages/Adafruit_MotorHAT/Adafruit_MotorHAT_Motors.py

## Viewing I2C bus
$ sudo apt-get install libi2c-dev i2c-tools




