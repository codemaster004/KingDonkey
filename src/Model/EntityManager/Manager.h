//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_MANAGER_H
#define KINGDONKEY_MANAGER_H

#include "../../Utilities/DataStore.h"
#include "Entity.h"

class Manager {
private:
	DataStore<Entity*> entities;

public:
	Manager() = default;

	void update();

	void render();

	void refresh();

	Entity *addEntity();

	Entity *getEntity(size_t index);

	size_t getEntityCount();

	template<typename T, typename... Args>
	Entity *addEntity(Args&&... args);

	~Manager() = default;
};

#include "Manager.tpp"

#endif //KINGDONKEY_MANAGER_H
