//
// Created by Filip Dabkowski on 17/12/2023.
//

template<typename T, typename... Args>
Entity *Manager::addEntity(Args&&... args) {
	T* newEntity = new T(static_cast<Args&&>(args)...);
	entities.push(newEntity);
	return newEntity;
}
