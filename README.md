# EK_feistel
Qt GUI application which illustrates a round of Feistel function generation.

![Feistel Function Screenshot](https://github.com/emsec/EK_feistel/blob/main/doc/screenshot.png "Feistel Function Screenshot")

## Introduction
The goal of the Feistel Function app is to illustrate the most tricky part of the DES algorithm : how the Feistel Function bits needed for encryption are generated. The input of the Feistel Function consists out of the right 32 bit from the value obtained from the previous round and the 48-bit round key. The user can enter these values as hex code in the input boxes. Alternatively bytes of the 32 bit input value can be toggled directly by clicking on them. Using the menu entry `Operations` the entire value can be bitwise inverted by single mouse click.

The Feistel Function app is written in C++ and Qt, thus download and compilation is required to run it. While this should work on all major operating system platforms like Windows, MacOS, and Linux, the use Linux is highly recommended. This document describes in particular the installation of Ubuntu Linux version 22.04 LTS with all the tools neccessary to run the app. Further down the document there are some hints for other operating systems as well but please understand that no support will be granted.

## Ubuntu 22.04 LTS guest VM installation
If the current operating system is Windows or MacOS you would start to create a virtual machine with at least 30 GB disk space. The following step-by-step procedure assumes that VirtualBox has been installed on the host.

### VirtualBox recommanded Settings
The following settings are recommended when setting up the VM with VirtualBox:
* General - Type : Linux
* General - Version : Ubuntu (64-bit)
* System - Base Memory : at least 4096 MB
* System - Processors : at least 2
* Display - Video Memory : 128 MB

### Download and Attach
To install the Ubuntu guest system we have to download the `.iso` file and attach it as virtual DVD. The download source used here [is](https://releases.ubuntu.com/jammy/ubuntu-22.04.5-desktop-amd64.iso) but is also possible to obtain the file via mirror or bittorrent. In VirtualBox the file can be attached via `Settings > Storage > click on Empty DVD icon > Choose a disk file ...`.

### Ubuntu Installation
When starting the (virtual) machine the first time pick the option 'Try or Install Ubuntu'. The installation process will walk you through a couple of steps like keyboard, "Normal installation", "Erase disk and install Ubuntu", select timezone from world map, and type user name and password of your choice. It is recommended to set the checkmark at "log in automatically" to get faster access to the desktop without password authorization when rebooting the VM. At the end of this installation procedure a prompt will ask to remove installation media and to press "Enter". Since VirtualBox will automatically boot the installed system simply pressing "Enter" is good enough.

After the first reboot Ubuntu will offer a number of services. I'd recommend to skip or decline each of them, especially the very time consuming upgrades.

## Preparation to build the Feistel Function App
### Install `git` in Ubuntu 22.04
The most important tool to get access to over 100 million public software repositories is `git`. The safest way for reliable installation instructions is to run everything from the command line. First we need to open a terminal by clicking on "Show Applications" (lower left corner) and "Terminal" icon.

The command to run is
``` shell
sudo apt-get install git
```

### Install `git` on other platforms
First check whether `git` is already installed. In your terminal / power shell / cmd window type
``` shell
git --version
```
If git is missing this [link](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) might help. However - as previously mentioned this installation instruction has the focus on Ubuntu 22.04 user.

### Download the Feistel Function source code
Go to or create a parent directory of your choice. Issue the command:
``` shell
git clone https://github.com/emsec/EK_feistel
```
This clones the directory `EK_feistel` whith all code and ressource files.

### Install Required Packages
Yet we need an integrated development environment (IDE) with compiler, toolchain, libraries and plugins. To have all these packages installed enter the `EK_feistel` directory and execute the script `requirements.sh`. Permission to execute the script must be granted first.
``` shell
cd EK_feistel
chmod 755 requirements.sh
./requirements.sh
```

### Switch to Plasma Desktop
This step is not essential, however, it is recommended to switch to plasma desktop. The plasma desktop provides a surface which looks familiar to a Windows user. Additionally it is based on Qt, thus required libraries for the Feistel Function app are already in place. The most important reason is that the VirtualBox guest tools cooparate better with the host, thus allowing to resize the Ubuntu window at will.
* Log out (symbol upper right corner)
* Click user name on login screen
* Click settings icon (lower right corner)
* Select `Plasma (X11)`
* Log in

### Nice to have in Plasma Desktop
Similar to Windows there is a start button in the lower left corner which can be used to start every available app. The most important ones are "Konsole" (in System) and "Qt Creator" (in Development). I use to pull the appropriate icons to the desktop ("Copy Here") so that launching them gets very easy.

## Build an Run the Feistel Function App
### Build
* Launch Qt-Creator. At first start you are invited to have a guided tour where to find the most important functional elements. Nice, short, and comprehensive. 
* Open project from menu
* Select the file `feistel.pro` from your working directory
* On the `Configure Project` screen select `Desktop` and click on `Configure Project`

### Run
Now the Feistel Function app can be started from the Qt-Creator by either
* Click on the green triangle (`run`) in the lower left corner
* Main menu -> Build -> Run
* Key press Ctrl-R

### Play
Feel free to test the functionality of the app, it won't cause any damage since results are not stored and you can always restart.
Finally there are some tasks waiting ...

## Non Ubuntu 22.04 user
There are other ways to set up the Feistel Function app although not supported by EK team. Since Qt-Creator (once setup correctly) provides everything to have the app compiled, linked, run and if neccessary debuged this is a convenient way to go. Qt-Creator can be obtained under open source license, however, the online Windows installer requires (free) registration at Qt company. An overview can be found [here](https://doc.qt.io/qtcreator/creator-overview.html).

There are offline installer as well which are not asking for registration when the computer is disconnected (e.g. flight mode), but then all requirements need to be set up manually. Qt-Creator depends on Qt, C++, Perl, Python and Ruby. Offline installer can be found [here](https://www.qt.io/offline-installers). 

MacOS user (who know what they are doing) can install Qt-Creator using the homebrew [formulae](https://formulae.brew.sh/cask/qt-creator). Some dependencies have to be setup manually unless you do the registration thing mentioned above.

When asked for the Qt-Version go for 5.15. It might be possible that the app runs under Qt6 as well but this is completly untested.

## Thrilled to become a software developer?
If you
* are participant of EK classes and RUB student ...
* have fun developing software with Qt and C++ (like this project) ...
* like to contribute to a large open source project with users all around the globe ...
* like to get paid for your work ...
you should apply for a student assistance position (SHK) within the [HAL](https://github.com/emsec/hal) software developer community.


