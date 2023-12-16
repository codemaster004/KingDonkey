//
// Created by Filip Dabkowski on 16/12/2023.
//

#include "DataStore.h"

template<typename T>
void DataStore<T>::expand() {
	auto **newData = new T *[nPartitions + 1];

	for (int i = 0; i < nPartitions; ++i) {
		newData[i] = data[i];
	}

	newData[nPartitions] = new T[partitionSize];

	delete[] data;
	data = newData;

	nPartitions++;
}

template<typename T>
void DataStore<T>::push(T newElement) {
	size_t rowIndex = dataCount / partitionSize;
	size_t columnIndex = dataCount % partitionSize;

	if (rowIndex >= nPartitions) {
		// Expand the first dimension if needed
		expand();
	}

	data[rowIndex][columnIndex] = newElement;
	dataCount++;
}

template<typename T>
T DataStore<T>::get(size_t index) {
	size_t rowIndex = index / partitionSize;
	size_t columnIndex = index % partitionSize;

	return data[rowIndex][columnIndex];
}
