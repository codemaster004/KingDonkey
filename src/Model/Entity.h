//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_ENTITY_H
#define KINGDONKEY_ENTITY_H

#include "Component.h"
#include "../Utilities/DataStore.h"
#include "../Utilities/BitDict.h"


using ComponentDataStore = DataStore<Component *>;

class Entity {
private:
	bool active = true;

	ComponentDataStore components;
	BitDict componentsBitDict;

public:
	Entity() = default;

	[[nodiscard]] bool isActive() const {
		return active;
	}

	template<typename T>
	[[nodiscard]] bool hasComponent() {
		return componentsBitDict.get(getComponentTypeId<T>());
	}

	template<typename T>
	void addComponent() {
		T *component(new T);
		component->entity = this;
		components.set(getComponentTypeId<T>(), component);
		componentsBitDict.set(getComponentTypeId<T>());
		component->init();
	}

	template<typename T>
	T *getComponent() {
		if (!hasComponent<T>()) {
			return nullptr;
		}

		auto compPtr = components.get(getComponentTypeId<T>());
		return (T *) (compPtr);
	}

	~Entity() = default;
};


#endif //KINGDONKEY_ENTITY_H
