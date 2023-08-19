#pragma once
#include <item.h>

class TkRect : public Item {
public:
	virtual void Start() {
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	virtual void Update() {
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		SDL_SetRenderDrawColor(
			g_renderer,
			color.r,
			color.g,
			color.b,
			color.a
		);

		SDL_RenderFillRectF(
			g_renderer,
			&rect
		);
	}
public:
	SDL_Color color;
private:
	SDL_FRect rect;
};