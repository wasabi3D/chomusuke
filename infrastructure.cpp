#include "chomusuke/infrastructure.h"


void cho::Game::init(
	const std::string& title,
	int x,
	int y,
	int width,
	int height,
	SDL_Color render_color,
	Uint32 flags,
	Uint32 rend_flags,
	SDL_BlendMode blend_mode,
	int fps_cap_)
{
	if (initialized) return; 
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Failed to initialize!" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
	if (!window) {
		std::cerr << "Failed to create window!" << std::endl;
		return;
	}

	win_renderer = SDL_CreateRenderer(window, -1, rend_flags);
	if (!win_renderer) {
		std::cerr << "Failed to create renderer!" << std::endl;
		return;
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		std::cerr << "Failed to init IMG! " << IMG_GetError() << std::endl;

	if (TTF_Init() < 0)
		std::cerr << "Failed to init TTF! " << TTF_GetError() << std::endl;

	SDL_SetRenderDrawBlendMode(win_renderer, blend_mode);
	clear_color = render_color;

	fps_cap = fps_cap_;
	frame_time_ms = 1000.f / fps_cap;
	initialized = true;
	start();
}

cho::Game::~Game() {
	death();
	if(window)
		SDL_DestroyWindow(window);
	window = nullptr;

	if (win_renderer)
		SDL_DestroyRenderer(win_renderer);
	win_renderer = nullptr;
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return;
}

void cho::Game::retreiveEvents() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0) {
		switch (ev.type) {
		case SDL_QUIT:
			// End
			running = false;
			break;

		default:
			processEvent(ev);
			break;
		}
	}
}

void cho::Game::mainloop() {
	while (running) {
		Uint64 frame_start_timing = SDL_GetPerformanceCounter();

		// Clear window
		if (win_renderer) {
			SDL_SetRenderDrawColor(win_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			SDL_RenderClear(win_renderer);
		}

		// Register events
		retreiveEvents();

		// Update objects
		update();

		// Draw
		draw();

		// Update window
		if(win_renderer)
			SDL_RenderPresent(win_renderer);

		Uint64 end = SDL_GetPerformanceCounter();
		float pref_freq = (float)SDL_GetPerformanceFrequency();
		float secondsElapsed = (end - frame_start_timing) / pref_freq;
		Uint32 wait_time = (Uint32)std::max(0.0f, std::floor(frame_time_ms - secondsElapsed * 1000.0f));
		if (wait_time > 0)
			SDL_Delay(wait_time);

		delta = (SDL_GetPerformanceCounter() - frame_start_timing) / pref_freq;
	} 
}