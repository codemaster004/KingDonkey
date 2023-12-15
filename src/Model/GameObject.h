//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_GAMEOBJECT_H
#define KINGDONKEY_GAMEOBJECT_H

#include "../../sdl/include/SDL.h"

class GameObject {
private:

	int xPos;
	int yPos;

	double distance = 0;

	SDL_Renderer *renderer;
	SDL_Texture *objTexture;
	SDL_Rect srcRect{}, destRect{};

public:
	GameObject(const char *textureFile, SDL_Renderer *ren, int x, int y);

	~GameObject() = default;

	void update(double delta);

	void render();
};


#endif //KINGDONKEY_GAMEOBJECT_H
