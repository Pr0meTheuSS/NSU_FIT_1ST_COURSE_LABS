// "Copyright [2022] Y.Olimpiev"
#include "BitSet.h"


/* +++++++++++++++++++++++ BitSet +++++++++++++++++++++++*/

u_char GetBit(TBitSet bit_set, size_t index) {
    size_t byteIndex = index / BITS_IN_BYTES;
    size_t bitIndex = index % BITS_IN_BYTES;
    return bit_set.Set[byteIndex] & (1 << bitIndex);
}


void SetBit(TBitSet bit_set, size_t index) {
    size_t byteIndex = index / BITS_IN_BYTES;
    size_t bitIndex = index % BITS_IN_BYTES;
    bit_set.Set[byteIndex] |= (1 << bitIndex);
}
