//
// Created by Filip Dabkowski on 15/12/2023.
//

#ifndef KINGDONKEY_GAMEVIEW_H
#define KINGDONKEY_GAMEVIEW_H

#include "TextureManager.h"


class GameView {
private:
	char text[128]{};

	int frameCount = 0;
	double fpsTimer = 0;
	double currentFps = 0;

	SDL_Renderer* renderer;
	SDL_Texture* charTexture;

	void renderText(char *string, int startX, int topY);

public:
	explicit GameView(SDL_Renderer* ren);

	void update(double delta);

	void render();

};


#endif //KINGDONKEY_GAMEVIEW_H
