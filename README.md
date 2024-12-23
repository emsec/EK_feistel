# EK_feistel
Qt GUI application which illustrates a round of Feistel function generation.

![Feistel Function Screenshot](https://github.com/emsec/EK_feistel/blob/main/doc/screenshot.png "Feistel Function Screenshot")

## Introduction
The app calculates values for the Feistel Function (the _f_-function) from the 32 bit round input R_i obtained from the previous round and the 48-bit round key k_i.

The Feistel Function app is written in C++ and Qt, thus download and compilation is required to run it. While this should work on all major operating system platforms like Windows, macOS, and Linux, the use of Linux is highly recommended. This document describes in particular the installation of Ubuntu Linux version 22.04 LTS with all the tools necessary to run the app. Further down the document there is a step-by-step instruction how to install Ubuntu 22.04 LTS in a VirtualBox machine. At the end of the document there are some hints for other operating systems as well - but please understand that no support will be given for that.

## Preparation to build the Feistel Function App
### Install `git` in Ubuntu 22.04
The most important tool to get access to over 100 million public software repositories is `git`. The safest way for reliable installation instructions is to run everything from the command line. First we need to open a terminal by clicking on "Show Applications" (lower left corner) and "Terminal" icon.

The command to run is
``` shell
sudo apt-get install git
```

#### Run `git` on other platforms
First check whether `git` is already installed. In your terminal / power shell / cmd window type
``` shell
git --version
```
If git is missing this [link](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) might help. However - as previously mentioned this README has the focus on Ubuntu 22.04 user only.

### Download the Feistel Function source code
Go to or create a parent directory of your choice. Issue the command:
``` shell
git clone https://github.com/emsec/EK_feistel
```
This clones the directory `EK_feistel` with all code and resource files.

### Install Required Packages
Yet we need an integrated development environment (IDE) with compiler, toolchain, libraries and plugins. To have all these packages installed enter the `EK_feistel` directory and execute the script `requirements.sh`. Permission to execute the script must be granted first.
``` shell
cd EK_feistel
chmod 755 requirements.sh
./requirements.sh
```

## Build and Run the Feistel Function App
### Build
* Launch Qt-Creator. At first start you are invited to have a guided tour where to find the most important functional elements. Nice, short, and comprehensive. 
* Click on Open project in the menu
* Select the file `feistel.pro` from the directory `EK_feistel`
* On the `Configure Project` screen select `Desktop` and click on `Configure Project`

Troubleshooting : while Qt-Creator should find the necessary kits (C++ compiler, toolchain, linker) automatically when packages are installed in right order as done by `requirements.sh` there is the possibility that a warning message like "missing kit" shows up if one of the installation steps failed. In this case you'll have to add the kit manually to the Qt-Creator. In the menu click on `Tools > Options > Kits > Manual` and select a Qt 5.15 kit.

### Run
Now the Feistel Function app can be started from the Qt-Creator by either
* Click on the green triangle (`run`) in the lower left corner
* Main menu -> Build -> Run
* Key press Ctrl-R

## Thrilled to become a software developer?
If you
* are participant of EK classes and RUB student...
* have fun developing software with Qt and C++ (like this project)...
* like to contribute to a large open source project with users all around the globe...
* like to get paid for your work...

you should apply for a student assistance position (SHK) within the [HAL](https://github.com/emsec/hal) software developer community. HAL is an open source software developed at the Max Planck Institute for Security and Privacy. Its main goal is to support research in the field of hardware reverse engineering.  Send us a quick application along with your latest transcript of records via (e-mail)[mailto:joern.langheinrich@mpi-sp.org]. Feel free to tell a bit about yourself!

### Use the App
When the app starts there are already some demo input values for R_i and k_i entered. The user can enter values of his choice as hex code in the input boxes. Alternatively R_i input bits can be toggled directly by clicking on them. Using the menu entry `Operations` the entire value can be bit-wise inverted.

Feel free to test the functionality of the app, it won't cause any damage since results are not stored, and you can always restart.
Finally, there are some tasks waiting...

## Ubuntu 22.04 LTS guest VM installation
If your current operating system is Windows or macOS you would start to create a virtual machine with at least 30 GB disk space. The following step-by-step procedure assumes that VirtualBox has been installed on the host.

### VirtualBox recommended Settings
The following settings are recommended when setting up the VM with VirtualBox:
* General - Type : Linux
* General - Version : Ubuntu (64-bit)
* System - Base Memory : at least 4096 MB
* System - Processors : at least 2
* Display - Video Memory : 128 MB

### Download and Attach
To install the Ubuntu guest system we have to download the `.iso` file and attach it as virtual DVD. The download source used is [here](https://releases.ubuntu.com/jammy/ubuntu-22.04.5-desktop-amd64.iso) but is also possible to obtain the file via mirror or bittorrent. In VirtualBox the file can be attached via `Settings > Storage > click on Empty DVD icon > Choose a disk file ...`.

### Ubuntu Installation
When starting the (virtual) machine the first time pick the option `Try or Install Ubuntu`. The installation process will walk you through a couple of steps like keyboard language selection, "Normal installation", "Erase disk and install Ubuntu", select timezone from world map, and enter a username and password of your choice. It is recommended to set the checkmark at `log in automatically` to get faster access to the desktop without password authorization when rebooting the VM. At the end of this installation procedure a prompt will ask to remove installation media and to press "Enter". Since VirtualBox will automatically boot the installed system simply pressing `Enter` is good enough.

After the first reboot, Ubuntu will offer a number of services. I'd recommend to skipping or declining each of them. Since the installation procedure and scripts are tested with Ubuntu 22.04 an upgrade to Ubuntu 24 is not recommended.

## Nice to have : Plasma Desktop
This step is not essential, however, it is recommended to switch to plasma desktop. The plasma desktop provides a surface which looks similar to Windows. Additionally, it is based on Qt, thus required libraries for the Feistel Function app are already in place. The most important reason is that the VirtualBox guest tools cooperate better with the host, thus allowing to resize the Ubuntu window at will.
* Log out (symbol upper right corner)
* Click user name on login screen
* Click settings icon (lower right corner)
* Select `Plasma (X11)`
* Log in

### Frequently used Apps in Plasma Desktop
Similar to Windows there is a start button in the lower left corner which can be used to start every available app. The most important apps for this project are "Konsole" (in System) and "Qt Creator" (in Development). I recommend pulling the appropriate icons to the desktop ("Copy Here") so that launching them gets very easy.


## Non Ubuntu 22.04 user
There are other ways to set up the Feistel Function app although not supported by EK team. Since Qt-Creator (once setup correctly) provides everything to have the app compiled, linked, run and if necessary debugged this is a convenient way to go. Qt-Creator can be obtained under open source license, however, the online Windows installer requires (free) registration at Qt company. An overview can be found [here](https://doc.qt.io/qtcreator/creator-overview.html).

There are offline installers as well which are not asking for registration when the computer is disconnected (e.g. flight mode), but then all requirements need to be set up manually. Qt-Creator depends on Qt, C++, Perl, Python and Ruby. Offline installer can be found [here](https://www.qt.io/offline-installers). 

Advanced and experienced macOS user can install Qt-Creator using the homebrew [formulae](https://formulae.brew.sh/cask/qt-creator). Some dependencies have to be setup manually unless you do the registration thing mentioned above.

When asked for the Qt-Version go for 5.15. It might be possible that the app runs under Qt6 as well, but this is completely untested.


