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
	size_t nPartitions;
	size_t partitionSize;
	size_t dataCount = 0;

	// Private method to expand the first-dimension array
	void expand();

public:
	// Constructor
	explicit DataStore(size_t N, size_t secondDimSize)
		: nPartitions(N), partitionSize(secondDimSize) {
		data = new T *[nPartitions];

		for (size_t i = 0; i < N; ++i) {
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

	// Add a byte at a specific 'linear' index
	void push(T newElement);

	// Get a byte from a specific 'linear' index
	T get(size_t index);

	size_t getSize() {
		return dataCount;
	}
};

#endif //KINGDONKEY_DATASTORE_H
