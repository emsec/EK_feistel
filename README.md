# EK_feistel
Qt GUI application which illustrates a round of Feistel function generation.

![Feistel Function Screenshot](https://github.com/emsec/EK_feistel/blob/main/doc/screenshot.png "Feistel Function Screenshot")

## Introduction
The goal of the Feistel Function app is to illustrate the most tricky part of the DES algorithm : how the Feistel Function bits needed for encryption are generated. The input of the Feistel Function consists out of the right 32 bit from the value obtained from the previous round and the 48-bit round key. The user can enter these values as hex code in the input boxes. Alternatively bytes of the 32 bit input value can be toggled directly by clicking on them. Using the menu entry `Operations` the entire value can be bitwise inverted by single mouse click.

The Feistel Function app is written in C++ and Qt, thus download and compilation is required to run it. While this should work on all major operating system platforms like Windows, MacOS, and Linux, the use of Ubuntu Linux is highly recommended.

## Download
### Check whether `git` is already installed
Make sure that the command `git` (e.g. `git --version`) is available in your cmd-window, shell or terminal. On Ubuntu the git package gets installed by typing `sudo apt-get install git` in a terminal. The installation procedure for other platform is described [here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

### Download the Feistel Function source code
Go to or create a parent directory of your choice. Issue the command:
``` shell
git clone https://github.com/emsec/EK_feistel
```
This clones the directory `EK_feistel` whith all code and ressource files.

### Download and install Qt-Creator
Installing the Qt-Creator provides a convenient way to get everything that is needed to control, compile, link, and if neccessary to debug the Feistel Function app. An overview can be found [here](https://doc.qt.io/qtcreator/creator-overview.html).

When asked for the Qt-Version go for 5.15.

## Generate and build
* Launch Qt-Creator
* Open project
* Select the file `feistel.pro` from your working directory
* On the `Configure Project` screen select Qt 5.15 and click on `Configure Project`

Now the Feistel Function app can be started from the Qt-Creator by either
* Click on the green triangle (`run`) in the lower left corner
* Main menu -> Build -> Run
* Key press Ctrl-R
