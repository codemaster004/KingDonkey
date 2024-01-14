//
// Created by Filip Dabkowski on 17/12/2023.
//

#ifndef KINGDONKEY_TEXTURE_H
#define KINGDONKEY_TEXTURE_H

#include "../../../sdl/include/SDL.h"

#include "EntityComponent.h"
#include "Position.h"


class Texture : public EntityComponent {
private:
	bool flip = false;

	SDL_Rect srcRect{}, destRect{};

	SDL_Texture *texture = nullptr;

	Position *position = nullptr;

public:
	Texture() = default;

	explicit Texture(const char *fileName) {
		setTexture(fileName);
	}

	explicit Texture(const char *fileName, bool removeBackground) {
		setTexture(fileName, removeBackground);
	}

	void init() override;

	void update() override;

	void draw() override;

	void setTexture(const char *fileName, bool removeBackground=false);

	void setFlip(bool newValue);

	void moveSourceTo(int x, int y);

	~Texture() override {
		SDL_DestroyTexture(texture);
	}

};


#endif //KINGDONKEY_TEXTURE_H
