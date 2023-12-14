//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "TextureManager.h"

SDL_Texture *TextureManager::loadTexture(const char *filename, SDL_Renderer *renderer) {
	SDL_Surface *tempSurface = SDL_LoadBMP(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}
