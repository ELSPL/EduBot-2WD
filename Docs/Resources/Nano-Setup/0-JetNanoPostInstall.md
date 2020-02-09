Author: Dwijay Bane
Date: 3/7/2019

Jetpack 4.2v
CUDA 10.166
cuDNN 7.3.1.28 
L4T 32.1
MultiMedia API 32.1
TensorRT 5.0.6.3

## Pre-requisite
```
$ sudo apt update && sudo apt upgrade 
$ sudo apt install synaptic git curl tig python-dev python3-dev aptitude zsh vim
$ sudo apt-get install hud notify-osd
$ sudo apt install minicom gtkterm
$ sudo apt install tree tmux evince gdebi nmap less ack cmake-curses-gui cmake-qt-gui xclip
$ sudo ln -s /usr/bin/evince /usr/bin/acroread
```

## For Clang and LLVM:

[Download](http://releases.llvm.org/download.html#8.0.0) prebuild binaries for AArch64 Linux

Next, extract the archive and move the extracted compilers to /usr/local:
```
$ cd Downloads
$ wget http://releases.llvm.org/8.0.0/clang+llvm-8.0.0-aarch64-linux-gnu.tar.xz
$ tar -xvf clang+llvm-8.0.0-aarch64-linux-gnu.tar.xz
$ rm clang+llvm-8.0.0-aarch64-linux-gnu.tar.xz
$ mv clang+llvm-8.0.0-aarch64-linux-gnu llvm_8.0.0
$ sudo mv llvm_8.0.0 /usr/local
```

At this point, all you need to do is to add Clang 8 and his libraries to your system search paths:

To provide paths to new installation `gedit ~/.bashrc`
```
# LLVM and Clang 8.0.0
# bin
export PATH=/usr/local/llvm_8.0.0/bin:$PATH
# lib
export LD_LIBRARY_PATH=/usr/local/llvm_8.0.0/lib:$LD_LIBRARY_PATH
# include
export CPATH=/usr/local/llvm_8.0.0/include:$CPATH
```

Test if things are working
```
$ source ~/.bashrc
$ sudo ldconfig /usr/local/llvm_8.0.0/lib
$ clang++ --version
```

More Test related to libc++ `gedit test.cpp`
```
#include <iostream>
#include <filesystem>

int main() {
    for(auto &file : std::filesystem::recursive_directory_iterator("./")) {
        std::cout << file.path() << '\n';
    }
}
```

Now Compile and run
```
$ clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic test.cpp -o test -lc++fs
$ ./test
```

## Install swapfile (Ref: https://www.jetsonhacks.com/2019/04/14/jetson-nano-use-more-memory/)
```
$ cd Downloads
$ git clone https://github.com/JetsonHacksNano/installSwapfile 
$ cd installSwapfile
$ sudo mkdir /swapdir
$ ./installSwapfile.sh -d /swapdir -s 8
```

## Run at Max Performance
```
$ cd $HOME
$ bash max_perf.sh
```

## VNC at startup (https://c-nergy.be/blog/?p=12220)
```
$ sudo apt install x11vnc
$ sudo x11vnc -storepasswd /etc/x11vnc.pass
$ sudo chmod 644 /etc/x11vnc.pass
```

Create Service file `sudo gedit /lib/systemd/system/x11vnc.service`
```
[Unit]
Description=Start x11vnc at startup.
After=multi-user.target

[Service]
Type=simple
ExecStart=/usr/bin/x11vnc -loop -forever -bg -rfbport 5900 -xkb -noxrecord -noxfixes -noxdamage -shared -norc -auth /run/user/120/gdm/Xauthority -rfbauth /etc/x11vnc.pass

[Install] 
WantedBy=multi-user.target
```

Now create and initialize service
```
$ sudo systemctl enable x11vnc.service
$ sudo systemctl daemon-reload
$ sudo systemctl start x11vnc.service
$ sudo systemctl status x11vnc.service
$ sudo reboot
```

You will get black screen after login or at login, means x11vnc is running at boot 
but additional steps required to make it work

To Create user session auto-startup run `gnome-session-properties` (Should be done for every user):
- Now click on **Add** -> **Name:** X11VNC-USER-SERVICE **Command:** x11vnc -rfbport 5901 -rfbauth /etc/x11vnc.pass
- Finally click on **Save**

Now on **Host** Side:
- This is little wierd since user port is different it will create new desktop entry :1
- Initialy login using xtightvncviewer <ip-address>:0
- Once logged in it will be black screen, so close it.
- Now open using xtightvncviewer <ip-address>:1

## Python Setup
Install pip for both python2 and python3:
```
$ curl --silent --show-error --retry 5 https://bootstrap.pypa.io/get-pip.py | sudo python2.7
$ curl --silent --show-error --retry 5 https://bootstrap.pypa.io/get-pip.py | sudo python3
$ sudo pip3 install testresources
$ sudo python -m pip install -U --force-reinstall pip
$ pip -V
$ pip3 -V
```

Now install jupyter notebook for both as this will also install ipython:
```
$ sudo pip install jupyter jedi pynvim
$ sudo pip3 install jupyter flake8 jedi pynvim
$ sudo pip3 install matplotlib
```

Now Installing aesthetics and facilities
- oh-my-zsh setup and config
- spacevim setup and plugin config with YCM+Clangd
- tmux setup and plugin config

## GPIO Library
$ cd /opt/nvidia
$ sudo rm -rf jetson-gpio/
$ sudo git clone https://github.com/NVIDIA/jetson-gpio.git
$ cd jetson-gpio
$ sudo python3 setup.py install
$ sudo python2 setup.py install
OR
from PyPI:
$ sudo pip3 install Jetson.GPIO 

$ sudo groupadd -f -r gpio
$ sudo usermod -a -G gpio edutech
$ sudo cp etc/99-gpio.rules /etc/udev/rules.d/
$ sudo udevadm control --reload-rules && sudo udevadm trigger

 





