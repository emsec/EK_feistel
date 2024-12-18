#pragma once

#include <QtGlobal>

const int numberFeistelBoxes = 8;

class SBox
{
    quint8 mInit[64];
public:
    SBox(quint8* init);
    quint8 lookup(quint8 sixBits) const;

    static SBox* feistelFactory(int index);
};
