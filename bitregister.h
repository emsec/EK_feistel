#pragma once

#include <QObject>
#include "permutationtable.h"

class BitRegister : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberBits READ numberBits WRITE setNumberBits);
    Q_PROPERTY(quint64 bitReg READ bitReg WRITE setBitReg NOTIFY bitRegChanged);

public:
    BitRegister(int nbits=23, quint64 init=0);
    int     numberBits() const     { return mNumberBits; }
    void    setNumberBits(int val) {mNumberBits = val; }
    quint64 bitReg() const         { return mBitReg; }
    void    setBitReg(quint64 val);
    void    setBit(int ibit, int val);
    void    setBits(int ibit, int nbits, quint8 val);
    quint8  getBits(int ibit, int nbits);
    Q_INVOKABLE void toggleBit(int ibit);
    Q_INVOKABLE int  getBit(int ibit) const;

    void setXorResult(const BitRegister* a, const BitRegister* b);
    void setPermutationResult(const BitRegister* before, const PermutationTable& table);
    void invert();
signals:
    void bitRegChanged();
private:
    int mNumberBits;
    quint64 mBitReg;

    quint64 setBitInternal(int ibit, int val, quint64 oldRegVal);
};
