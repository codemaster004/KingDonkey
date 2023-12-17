//
// Created by Filip Dabkowski on 17/12/2023.
//

template<typename T, typename... Args>
void Entity::addComponent(Args&&... args) {
	T *component = new T(static_cast<Args&&>(args)...);
	component->entity = this;

	components.set(getComponentTypeId<T>(), component);
	componentsBitDict.set(getComponentTypeId<T>());

	component->init();
}

template<typename T>
T *Entity::getComponent() {
	if (!hasComponent<T>()) {
		return nullptr;
	}

	auto compPtr = components.getByKey(getComponentTypeId<T>());
	return (T *) (compPtr);
}