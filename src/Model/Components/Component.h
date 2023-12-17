//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_COMPONENT_H
#define KINGDONKEY_COMPONENT_H

#include "cstddef"


using ComponentID = size_t;

inline ComponentID getComponentTypeId() {
	static ComponentID lastId = 0;
	return lastId++;
}

template<typename T>
inline ComponentID getComponentTypeId() {
	static ComponentID typeId = getComponentTypeId();
	return typeId;
}

class Entity;

class Component {
private:

public:
	Entity *entity = nullptr;

	virtual void init() {}

	virtual void update() {}

	virtual void draw() {}

	virtual ~Component() = default;

};


#endif //KINGDONKEY_COMPONENT_H
