//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "BitDict.h"


uint8_t BitDict::mask(uint8_t index) {
	// For example, if index is 2, it returns 0b00000100.
	return 1 << index;
}

bool BitDict::checkSize(int index) const {
	return index >= 0 && index < size;
}

void BitDict::set(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
	// update Byte to be equal the same value with altered at index to be true
		dict[index / 8] |= mask(index % 8);
	}
}

bool BitDict::get(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
		// temporary shift Byte bits and check with 0b00000001 to return the true or false
		return (dict[index / 8] >> (index % 8)) & 1;
	}
	return false; // default to false
}

void BitDict::remove(int index) {
	// First check if given index is valid for current dict size
	if (checkSize(index)) {
		// update Byte to be equal the same value with altered at index to be false
		dict[index / 8] &= ~mask(index % 8);
	}
}


void BitDict::reset() {
	// Loop over all elements
	for (int i = 0; i < size / 8; ++i) {
		dict[i] = 0; // Set to 0, set every bit to false
	}
}
