//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_DATASTORE_H
#define KINGDONKEY_DATASTORE_H

#include "cstddef"


template <typename T>
class DataStore {

private:
	T **data;
	size_t partitionSize;
	size_t nPartitions = 1;
	size_t dataCount = 0;

	// Private method to expand the first-dimension array
	void expand();

public:
	// Constructor
	explicit DataStore(size_t baseSize = 8)
		: partitionSize(baseSize) {
		data = new T *[nPartitions];

		for (size_t i = 0; i < nPartitions; ++i) {
			data[i] = new T[partitionSize];
		}
	}

	// Destructor to free allocated memory
	~DataStore() {
		for (size_t i = 0; i < nPartitions; ++i) {
			delete[] data[i];
		}
		delete[] data;
	}

	void push(T newElement);

	void set(size_t index, T newElement);

	T get(size_t index);

	size_t getSize() {
		return dataCount;
	}
};

#include "DataStore.tpp"

#endif //KINGDONKEY_DATASTORE_H
