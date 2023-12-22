//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_BITDICT_H
#define KINGDONKEY_BITDICT_H

#include "cstdint"


class BitDict {
private:
	uint8_t *dict;
	uint8_t size;

	static uint8_t mask(uint8_t index);

	[[nodiscard]] bool checkSize(int index) const;

public:
	explicit BitDict(int maxBits=8) : size((uint8_t) (maxBits)) {
		dict = new uint8_t [size / 8];
		for (int i = 0; i < size / 8; ++i) {
			dict[i] = 0;
		}
	}

	void set(int index);

	bool get(int index);

	void remove(int index);

	~BitDict() {
		delete[] dict;
	};
};


#endif //KINGDONKEY_BITDICT_H
