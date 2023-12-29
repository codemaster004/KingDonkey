//
// Created by Filip Dabkowski on 16/12/2023.
//

#ifndef KINGDONKEY_ENTITY_H
#define KINGDONKEY_ENTITY_H

#include "../Components/Component.h"
#include "../../Utilities/DataStructures/DataStore.h"
#include "../../Utilities/DataStructures/BitDict.h"
#include "../Components/PositionComponent.h"


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

	template<typename T, typename... Args>
	void addComponent(Args&&... args);

	template<typename T>
	T *getComponent();

	~Entity() {
		if (hasComponent<PositionComponent>()) {
			getComponent<PositionComponent>()->free();
		}
	};
};

#include "Entity.tpp"

#endif //KINGDONKEY_ENTITY_H
