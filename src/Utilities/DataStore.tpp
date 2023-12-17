//
// Created by Filip Dabkowski on 16/12/2023.
//


template<typename T>
void DataStore<T>::expand() {
	auto **newData = new T *[nBoxes + 1];
	auto **newKeys = new size_t *[nBoxes + 1];

	for (int i = 0; i < nBoxes; ++i) {
		newData[i] = values[i];
		newKeys[i] = keys[i];
	}

	newData[nBoxes] = new T[boxSize];
	newKeys[nBoxes] = new size_t[boxSize];

	delete[] values;
	delete[] keys;

	values = newData;
	keys = newKeys;

	nBoxes++;
}

template<typename T>
void DataStore<T>::pushKey(size_t key) {
	size_t index = getEmptyIndex(key);
	keys[index / boxSize][index % boxSize] = key;
}

template<typename T>
size_t DataStore<T>::getIndex(size_t key) {
	for (int i = 0; i < length; ++i) {
		if (keys[length / boxSize][ length % boxSize] == key) {
			return i;
		}
	}
	return 0;
}

template<typename T>
size_t DataStore<T>::getEmptyIndex(size_t index) {
	size_t foundIndex = getIndex(index);
	if (foundIndex > 0) {
		return foundIndex;
	}
	return length;
}

template<typename T>
void DataStore<T>::push(T newElement) {
	set(length, newElement);
}

template<typename T>
void DataStore<T>::set(size_t index, T newElement) {
	size_t rowIndex = length / boxSize;

	if (rowIndex >= nBoxes) {
		expand();
	}

	pushKey(index);

	values[rowIndex][length % boxSize] = newElement;
	length += 1;
}

template<typename T>
T DataStore<T>::get(size_t index) {
	size_t rowIndex = index / boxSize;
	size_t columnIndex = index % boxSize;

	return values[rowIndex][columnIndex];
}

template<typename T>
T DataStore<T>::getByKey(size_t key) {
	size_t index = getIndex(key);
	return get(index);
}
