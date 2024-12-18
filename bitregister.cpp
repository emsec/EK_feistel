#include "bitregister.h"

BitRegister::BitRegister(int nbits, quint64 init)
    : mNumberBits(nbits), mBitReg(init)
{;}

void BitRegister::setBitReg(quint64 val)
{
    if (mBitReg == val) return; // nothing to do
    mBitReg = val;
    emit bitRegChanged();
}

quint64 BitRegister::setBitInternal(int ibit, int val, quint64 oldRegVal)
{
    quint64 mask = 1L << (mNumberBits - ibit - 1);
    if (val)
        return (oldRegVal | mask);
    return      oldRegVal & (~mask);
}

void BitRegister::setBit(int ibit, int val)
{
    if (ibit >= mNumberBits) return;
    setBitReg(setBitInternal(ibit, val, mBitReg));
}

void BitRegister::setBits(int ibit, int nbits, quint8 val)
{
    if (!nbits || nbits > 8 || ibit + nbits > mNumberBits) return;
    quint64 newValue = mBitReg;
    for (int iSourceBit = 0; iSourceBit<nbits; iSourceBit++)
    {
        int iTargetBit = ibit + nbits - 1 - iSourceBit;
        newValue = setBitInternal(iTargetBit, (val & (1<<iSourceBit)) ? 1 : 0, newValue);
    }
    setBitReg(newValue);
}

int BitRegister::getBit(int ibit) const
{
    if (ibit >= mNumberBits) return -1;
    quint64 mask = 1L << (mNumberBits - ibit - 1);
    return (mBitReg & mask) ? 1 : 0;
}

void BitRegister::toggleBit(int ibit)
{
    setBit(ibit, getBit(ibit) ? 0 : 1);
}

quint8 BitRegister::getBits(int ibit, int nbits)
{
    Q_ASSERT (nbits > 0 && nbits <= 8 && ibit+nbits <= mNumberBits);
    quint8 mask = 0;
    for (int i = 0; i<nbits; i++)
        mask |= (1 << i);
    quint64 temp = mBitReg >> ((mNumberBits - ibit - nbits));
    return (temp & mask);
}


void BitRegister::setXorResult(const BitRegister* a, const BitRegister* b)
{
    mNumberBits = a->mNumberBits > b->mNumberBits ? a->mNumberBits : b->mNumberBits;
    setBitReg(a->mBitReg ^ b->mBitReg);
}

void BitRegister::setPermutationResult(const BitRegister *before, const PermutationTable& table)
{
    mNumberBits = table.n;
    quint64 newValue = 0;
    for (int iTargetBit=0; iTargetBit<mNumberBits; iTargetBit++)
    {
        int iSourceBit = table.srcBits[iTargetBit] - 1;
        newValue = setBitInternal(iTargetBit, before->getBit(iSourceBit), newValue);
    }
    setBitReg(newValue);
}

void BitRegister::invert()
{
    quint64 newValue = ~mBitReg;
    quint64 mask = 0;
    for (int i=0; i<mNumberBits; i++)
        mask |= (1L << i);
    setBitReg(newValue & mask);
}
