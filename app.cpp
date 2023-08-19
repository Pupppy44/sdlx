#include "app.h"
#include <iostream>

bool App::Create(const char* _t, int _w, int _h) {
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	title = _t; width = _w; height = _h;

	window = SDL_CreateWindow(_t, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_GetCurrentDisplayMode(0, &display);

	return 1;
}

void App::Start() {
	started = true;
	for (auto i : items) {
		i->Start();
	}

	while (!closed) {
		loop = true;
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			closed = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x = event.button.x;
			int y = event.button.y;

			int index = 0;
			auto copy = items;
			for (auto i : copy) {
				if ((x > i->x) && (x < i->x + i->w) && (y > i->y) && (y < i->y + i->h)) {
					if (index > items.size()) continue;
					for (auto &e : items[index]->clickEvents) {
						e(event.button);
					}
				}
				index++;
				copy.clear();
			}
		}

		for (auto e : events) {
			e(event);
		}

		for (auto f : loops) {
			f();
		}

		loop = false;

		SDL_SetRenderDrawColor(renderer, window_color.r, window_color.g, window_color.b, window_color.a);

		SDL_RenderClear(renderer);

		for (auto i : items) {
			if (!i->Enabled) continue;
			i->Update();
		}

		SDL_RenderPresent(renderer);

		fps = display.refresh_rate;

		SDL_Delay(1000 / display.refresh_rate);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void App::SetTitle(const char* _t) {
	title = _t;

	SDL_SetWindowTitle(window, _t);
}

void App::SetBackground(SDL_Color _color) {
	window_color = _color;
}

void MusicCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

	(void)pInput;
}

void App::SetMusic(const char* path) {
	if (ma_device_is_started(&device)) {
		ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);
	}

	ma_decoder_init_file(path, NULL, &decoder);

	ma_data_source_set_looping(&decoder, MA_TRUE);

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = decoder.outputFormat;
	deviceConfig.playback.channels = decoder.outputChannels;
	deviceConfig.sampleRate = decoder.outputSampleRate;
	deviceConfig.dataCallback = MusicCallback;
	deviceConfig.pUserData = &decoder;

	ma_device_init(NULL, &deviceConfig, &device);
	ma_device_start(&device);
}

void App::AddItem(Item &_item) {
	_item.g_window = window;
	_item.g_renderer = renderer;
	_item.Enabled = true;
	items.push_back(&_item);


	if (started) {
		_item.Start();
	}
	else {
	}
}

Item* App::GetItem(Item* _item) {
	return items[std::find(items.begin(), items.end(), _item) - items.begin()];
}

void App::RemoveItem(Item* _item) {
	_item->Stop();
	_item->Enabled = 0;
	items.erase(std::find(items.begin(), items.end(), _item));
}

void App::Alert(const char* _m, const char* _c) {
	MessageBoxA(
		NULL,
		_m,
		_c,
		MB_ICONHAND
	);
}