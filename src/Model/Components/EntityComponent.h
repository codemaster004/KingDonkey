//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_ENTITYCOMPONENT_H
#define KINGDONKEY_ENTITYCOMPONENT_H

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

class EntityComponent {
private:

public:
	Entity *entity = nullptr;

	virtual void init() {}

	virtual void update() {}

	virtual void draw() {}

	virtual ~EntityComponent() = default;

};


#endif //KINGDONKEY_ENTITYCOMPONENT_H
