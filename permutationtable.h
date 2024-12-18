#pragma once

#include <QtGlobal>

struct PermutationTable
{
    int n;
    const quint8* srcBits;

    static struct PermutationTable expansion;
    static struct PermutationTable final;
};
