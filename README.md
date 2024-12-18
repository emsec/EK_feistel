# EK_feistel
Qt GUI application which illustrates a round of Feistel function generation.

![Feistel Function Screenshot](https://raw.githubusercontent.com/emsec/EK_feistel/main/doc/screenshot.png "Feistel Function Screenshot")

## Introduction
The goal og the Feistel Function app is to illustrate the most difficult part of the DES algorithm : how the Feistel Function bits are generated from the input of the encryption round. The input comprises the right half of the message bits created by the previous round and the 48-bit round key.

The Feistel Function app is written in C++ and Qt, thus download and compilation is required to run it. While this should work on all major operating system platforms like Windows, MacOS, and Linux, the use of Linux is highly recommended.


## Download

``` shell
git clone https://github.com/emsec/EK_feistel
```

## Generate and build

### Qt Creator

To build these projects, open `Qt.Exmples.pro` file with [Qt Creator](https://doc.qt.io/qtcreator/creator-overview.html).
