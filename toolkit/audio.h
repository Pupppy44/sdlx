#ifdef MINIAUDIO_IMPLEMENTATION
#pragma once
#include <item.h>
#include "../audio/miniaudio.h"

class TkAudio : public Item {
public:
	void Init() {
		ma_engine_init(NULL, &engine);
	}

	virtual void Start() {
		ma_engine_play_sound(&engine, path, NULL);
	}

	void StartAudio() {
		ma_engine_play_sound(&engine, path, NULL);
	}

	void StopAudio() {
		ma_engine_uninit(&engine);
	}
public:
	const char* path;
private:
	ma_engine engine;
};
#endif