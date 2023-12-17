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

	template<typename T, typename... Args>
	Entity *addEntity(Args&&... args);

	~Manager() = default;
};

#include "Manager.tpp"

#endif //KINGDONKEY_MANAGER_H
