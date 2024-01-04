//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "BitSet.h"


uint8_t BitSet::mask(uint8_t index) {
	// For example, if index is 2, it returns 0b00000100.
	return 1 << index;
}

bool BitSet::checkSize(int index) const {
	return index >= 0 && index < size;
}

void BitSet::set(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
	// update Byte to be equal the same value with altered at index to be true
		dict[index / 8] |= mask(index % 8);
	}
}

bool BitSet::get(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
		// temporary shift Byte bits and check with 0b00000001 to return the true or false
		return (dict[index / 8] >> (index % 8)) & 1;
	}
	return false; // default to false
}

void BitSet::remove(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
		// update Byte to be equal the same value with altered at index to be false
		dict[index / 8] &= ~mask(index % 8);
	}
}


void BitSet::reset() {
	// Loop over all elements
	for (int i = 0; i < size / 8; ++i) {
		dict[i] = 0; // Set to 0, set every bit to false
	}
}
