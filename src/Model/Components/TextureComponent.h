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
	bool flip = false;

	SDL_Rect srcRect{}, destRect{};

	SDL_Texture *texture = nullptr;

	PositionComponent *position = nullptr;

public:
	TextureComponent() = default;

	explicit TextureComponent(const char *fileName) {
		setTexture(fileName);
	}

	explicit TextureComponent(const char *fileName, bool removeBackground) {
		setTexture(fileName, removeBackground);
	}

	void init() override;

	void update() override;

	void draw() override;

	void setTexture(const char *fileName, bool removeBackground=false);

	void setFlip(bool newValue);

	void moveSourceTo(int x, int y);

	~TextureComponent() override {
		SDL_DestroyTexture(texture);
	}

};


#endif //KINGDONKEY_TEXTURECOMPONENT_H
