//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_BITDICT_H
#define KINGDONKEY_BITDICT_H

#include "cstdint"


class BitDict {
private:
	uint64_t dict;
	uint8_t size;

	static uint64_t mask(uint8_t index);

	bool checkSize(int index) const;

public:
	explicit BitDict(int maxBits=8) : size((uint8_t) (maxBits)) {
		dict = 0;
	}

	void set(int index);

	bool get(int index);

	void remove(int index);

	~BitDict() = default;
};


#endif //KINGDONKEY_BITDICT_H
