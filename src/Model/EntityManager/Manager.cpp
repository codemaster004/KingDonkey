//
// Created by Filip Dabkowski on 17/12/2023.
//

#include "Manager.h"

void Manager::update() {
	for (int i = 0; i < entities.getSize(); ++i) {
		entities.get(i)->update();
	}
}

void Manager::render() {
	for (int i = 0; i < entities.getSize(); ++i) {
		entities.get(i)->render();
	}
}

void Manager::refresh() {
	for (int i = 0; i < entities.getSize(); ++i) {
		if (!entities.get(i)->isActive()) {
			// TODO: remove from store
		}
	}
}

Entity *Manager::addEntity() {
	auto *newEntity = new Entity();
	entities.push(newEntity);
	return newEntity;
}

Entity *Manager::getEntity(size_t index)  {
	return entities.get(index);
}

size_t Manager::getEntityCount() {
	return entities.getSize();
}
