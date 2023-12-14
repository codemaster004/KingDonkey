//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_TEXTUREMANAGER_H
#define KINGDONKEY_TEXTUREMANAGER_H

#include "../../sdl/include/SDL.h"

class TextureManager {
public:
	static SDL_Texture *loadTexture(const char*filename, SDL_Renderer *renderer);
};


#endif //KINGDONKEY_TEXTUREMANAGER_H
