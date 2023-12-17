//
// Created by Filip Dabkowski on 15/12/2023.
//

#include "TextureManager.h"
#include "../Utilities/Utility.h"
#include "../Game.h"

SDL_Texture *TextureManager::loadTexture(const char *filename) {
	const char *path = joinStrings("Assets/", filename); // TODO: config define

	SDL_Surface *tempSurface = SDL_LoadBMP(path);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	delete[] path;

	return texture;
}

void TextureManager::drawTexture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest) {
	SDL_RenderCopy(Game::renderer, texture, src, dest);
}
