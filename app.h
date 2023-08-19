#pragma once
#include <SDL.h>
#undef main

#include <vector>
#include <Windows.h>
#include <functional>
#include <item.h>
#include <audio/miniaudio.h>

class App {
public:
	const char* title;
	int width;
	int height;
	int fps;

	bool Create(const char* _t, int _w, int _h);

	void Start();

	void Loop(auto _loop) {
		loops.push_back(_loop);
	}
	void Event(auto _event) {
		events.push_back(_event);
	}

	void SetTitle(const char* _t);
	void SetBackground(SDL_Color _color);
	void SetMusic(const char* path);

	void AddItem(Item& _item);
	Item* GetItem(Item* _item);
	void RemoveItem(Item* _item);

	void Alert(const char*, const char*);

	SDL_Window* window;
	SDL_Renderer* renderer;
private:
	SDL_DisplayMode display;
	SDL_Color window_color;

	ma_device device;
	ma_decoder decoder;
	ma_device_config deviceConfig;

	std::vector<Item*> items;
	std::vector<std::function<void()>> loops;
	std::vector<std::function<bool(SDL_Event)>> events;

	bool closed;
	bool started;
	bool loop;
};
