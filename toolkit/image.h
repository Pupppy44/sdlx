#pragma once
#include <SDL.h>
#include <item.h>

class TkImage : public Item {
public:
	virtual void Start() {
		SDL_Surface* iSurf = SDL_LoadBMP(path);
		if (color_key.r != 0) {
			SDL_SetColorKey(iSurf, true, ((color_key.r & 0xff) << 16) + ((color_key.g & 0xff) << 8) + (color_key.b & 0xff));
		}

		imageBox.x = x;
		imageBox.y = y;
		imageBox.w = iSurf->w;
		imageBox.h = iSurf->h;

		w = iSurf->w;
		h = iSurf->h;

		image = SDL_CreateTextureFromSurface(
			g_renderer,
			iSurf
		);

		SDL_FreeSurface(iSurf);
	}

	virtual void Update() {
		SDL_RenderCopyF(
			g_renderer,
			image,
			NULL,
			&imageBox
		);
	}

	virtual void Stop() {
		SDL_DestroyTexture(image);
	}

	void SetColorKey(SDL_Color color) {
		color_key = color;
	}
public:
	const char* path;
private:
	SDL_Color color_key = {0,0,0};
private:
	SDL_Texture* image;
	SDL_FRect imageBox;
};