//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_TEXTUREMANAGER_H
#define KINGDONKEY_TEXTUREMANAGER_H

#include "../../sdl/include/SDL.h"

class TextureManager {
public:
	static SDL_Texture *loadTexture(const char *filename, bool removeBgc=false);

	static void drawTexture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest, bool flip=false);
};


#endif //KINGDONKEY_TEXTUREMANAGER_H
