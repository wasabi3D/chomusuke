#ifndef CHOMUSUKE_INFRASTRUCTURE_H
#define CHOMUSUKE_INFRASTRUCTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "chomusuke/common.h"

namespace cho {
	class Game {
	private:
		int fps_cap = 150;
		float frame_time_ms = 1000.f / 150;
		bool initialized = false;

	protected:
		bool running = true;
		SDL_Window* window = nullptr;
		SDL_Renderer* win_renderer = nullptr;
		float delta = 0;
		SDL_Color clear_color{ 2, 2, 2, 255 };

	public:
		Game() = default;
		~Game();

		virtual void init(
			const std::string& title,
			int x,
			int y,
			int width,
			int height,
			SDL_Color render_color = { 0, 0, 0, 0 },
			Uint32 flags = SDL_WINDOW_SHOWN,
			Uint32 rend_flags = SDL_RENDERER_ACCELERATED,
			SDL_BlendMode blend_mode = SDL_BLENDMODE_ADD,
			int fps_cap_=150
		);
		void mainloop();
		void retreiveEvents();
		virtual void start(){}
		virtual void death(){}
		inline virtual void processEvent(const SDL_Event& event){}
		inline virtual void update(){}
		inline virtual void draw(){}
	};
}


#endif
