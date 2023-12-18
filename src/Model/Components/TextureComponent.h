//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_TEXTURECOMPONENT_H
#define KINGDONKEY_TEXTURECOMPONENT_H

#include "SDL.h"

#include "Component.h"
#include "PositionComponent.h"


class TextureComponent : public Component {
private:
	SDL_Rect srcRect{}, destRect{};

	SDL_Texture *texture = nullptr;

	PositionComponent *position{};

public:
	TextureComponent() = default;

	explicit TextureComponent(const char *fileName) {
		setTexture(fileName);
	}

	void init() override;

	void update() override;

	void draw() override;

	void setTexture(const char *fileName);

	~TextureComponent() override {
		SDL_DestroyTexture(texture);
	}

};


#endif //KINGDONKEY_TEXTURECOMPONENT_H
