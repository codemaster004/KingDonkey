//
// Created by Filip Dabkowski on 04/01/2024.
//

#ifndef KINGDONKEY_VECTOR_H
#define KINGDONKEY_VECTOR_H

#include "cstddef"


template<typename T>
class Vector {
private:
	T *values; ///< Pointer to table of values

	size_t size; ///< Number of element inside
	size_t space; ///< Actually reserved space

	void resize(int newSpace) {
		T *newValues = new T [newSpace];
		for (int i = 0; i < size; ++i) {
			newValues[i] = values[i];
		}

		delete[] values;
		space = newSpace;
		values = newValues;
	}


public:

	Vector<T>() {
		size = 0;
		space = 2;
		values = new T[space];
	}


	explicit Vector<T>(size_t size) : size(0), space(size) {
		values = new T[space];
	};


	~Vector() {
		delete[] values;
	}


	void push(T newElement) {
		if (size == space) {
			resize(size * 2);
		}
		values[size++] = newElement;
	}


	T get(size_t index) {
		return values[index];
	}


	void pop() {
		size--;
	}

	size_t getSize() {
		return size;
	}
};


#endif //KINGDONKEY_VECTOR_H
