//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_DATASTORE_H
#define KINGDONKEY_DATASTORE_H

#include "cstddef"

template <typename T>
class DataStore {

private:
	T **values;
	size_t **keys;
	size_t boxSize;
	size_t nBoxes = 1;
	size_t length = 0;

	// Private method to expand the first-dimension array
	void expand();

	size_t getIndex(size_t key);

	size_t getEmptyIndex(size_t index);

	void pushKey(size_t key);

public:
	// Constructor
	explicit DataStore(size_t baseSize = 8)
		: boxSize(baseSize) {
		values = new T *[nBoxes];
		keys = new size_t *[nBoxes];

		for (size_t i = 0; i < nBoxes; ++i) {
			values[i] = new T[boxSize];
			keys[i] = new size_t [boxSize];
		}
	}

	// Destructor to free allocated memory
	~DataStore() {
		for (size_t i = 0; i < nBoxes; ++i) {
			delete[] values[i];
			delete[] keys[i];
		}
		delete[] values;
		delete[] keys;
	}

	void push(T newElement);

	void set(size_t index, T newElement);

	T get(size_t index);

	T getByKey(size_t index);

	size_t getSize() {
		return length;
	}
};

#include "DataStore.tpp"

#endif //KINGDONKEY_DATASTORE_H
