//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_ENTITYCOMPONENT_H
#define KINGDONKEY_ENTITYCOMPONENT_H

#include "cstddef"


inline size_t getComponentTypeId() {
	static size_t lastId = 0;
	return lastId++;
}


template<typename T>
inline size_t getComponentTypeId() {
	static size_t typeId = getComponentTypeId();
	return typeId;
}


class Entity;


class EntityComponent {
private:

public:
	Entity* entity = nullptr;


	virtual void init() {}


	virtual void update() {}


	virtual void draw() {}


	virtual ~EntityComponent() = default;

};


#endif //KINGDONKEY_ENTITYCOMPONENT_H
