#pragma once
#include <item.h>
#include <SDL_ttf.h>

class TkText : public Item {
public:
	virtual void Start() {
		if (!TTF_WasInit()) {
			TTF_Init();
		}

		ttfFont = TTF_OpenFont(font, px);

		SDL_Surface* txtSurf = TTF_RenderUTF8_Blended_Wrapped(
			ttfFont,
			text,
			color,
			w
		);

		textTxre = SDL_CreateTextureFromSurface(
			g_renderer,
			txtSurf
		);

		textBox.x = x;
		textBox.y = y;
		textBox.w = txtSurf->w;
		textBox.h = txtSurf->h;

		SDL_FreeSurface(txtSurf);
		TTF_CloseFont(ttfFont);
	}

	virtual void Update() {
		SDL_RenderCopyF(
			g_renderer,
			textTxre,
			NULL,
			&textBox
		);
	}
public:
	const char* text;
	const char* font;
	float px;
	SDL_Color color;
private:
	SDL_Texture* textTxre;
	SDL_FRect textBox;
	TTF_Font* ttfFont;
};