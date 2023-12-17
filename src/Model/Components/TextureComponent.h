//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_TEXTURECOMPONENT_H
#define KINGDONKEY_TEXTURECOMPONENT_H

#include "../../sdl/include/SDL.h"

#include "Component.h"


class TextureComponent : public Component {
private:
	SDL_Rect srcRect{}, destRect{};

	SDL_Texture *texture = nullptr;

public:
	TextureComponent() = default;

	explicit TextureComponent(const char *fileName) {
		setTexture(fileName);
	}

	void init() override;

	void update() override;

	void draw() override;

	void setTexture(const char *fileName);

};


#endif //KINGDONKEY_TEXTURECOMPONENT_H
