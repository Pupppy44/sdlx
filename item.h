#pragma once
#include <SDL.h>
#include <vector>
#include <functional>

class Item {
public:
	Item();

	virtual void Start() {};
	virtual void Update() {};
	virtual void Stop() {};

	void Click(auto _event) {
		clickEvents.push_back(_event);
	}
public:
	bool Enabled = true;

	float x;
	float y;
	float w;
	float h;
public:
	SDL_Window* g_window;
	SDL_Renderer* g_renderer;

	std::vector<std::function<void(SDL_MouseButtonEvent)>> clickEvents;
};