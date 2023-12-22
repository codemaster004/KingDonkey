//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "BitDict.h"


uint8_t BitDict::mask(uint8_t index) {
	return 1 << index;
}

bool BitDict::checkSize(int index) const {
	return index >= 0 && index < size;
}

void BitDict::set(int index) {
	if (checkSize(index)) {
		dict[index / 8] |= mask(index % 8);
	}
}

bool BitDict::get(int index) {
	if (checkSize(index)) {
		return (dict[index / 8] >> (index % 8)) & 1;
	}
	return false;
}

void BitDict::remove(int index) {
	if (checkSize(index)) {
		dict[index / 8] &= ~mask(index % 8);
	}
}
