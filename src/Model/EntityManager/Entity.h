//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_ENTITY_H
#define KINGDONKEY_ENTITY_H

#include "../Components/Component.h"
#include "../../Utilities/DataStore.h"
#include "../../Utilities/BitDict.h"


class Entity {
private:
	bool active = true;

	DataStore<Component *> components;
	BitDict componentsBitDict;

public:
	Entity() = default;

	[[nodiscard]] bool isActive() const {
		return active;
	}

	void update() {
		for (int i = 0; i < components.getSize(); ++i) {
			components.get(i)->update();
		}
	}

	void render() {
		for (int i = 0; i < components.getSize(); ++i) {
			components.get(i)->draw();
		}
	}

	template<typename T>
	[[nodiscard]] bool hasComponent() {
		return componentsBitDict.get(getComponentTypeId<T>());
	}

	template<typename T>
	void addComponent() {
		T *component = new T();
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
