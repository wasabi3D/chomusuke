#ifndef CHOMUSUKE_INFRASTRUCTURE_H
#define CHOMUSUKE_INFRASTRUCTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <memory>
#include <stack>
#include <functional>
#include "chomusuke/common.h"

namespace cho {
	constexpr int DEFAULT_FPS_LIMIT = 150;


	struct SDLPointers {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
	};


	class IScene {
	public:
		virtual ~IScene() = default;
		// If your program segfaults consider checking what is passed to this 
		virtual void start(std::shared_ptr<void> data, SDLPointers pointers) = 0;
		virtual void processEvent(const SDL_Event& event) = 0;
		virtual void draw(SDLPointers pointers) = 0;

		// Called before draw
		virtual void update(float delta) = 0; 

		// Called after draw
		virtual void lateUpdate(float delta) = 0;  

		// Called at the end of a frame
		virtual bool isEndOfScene() = 0; 

		// Called when the scene ends.
		virtual std::shared_ptr<void> processDeath() = 0;  
	};


	class LoopManager {
	private:
		int fps_cap = DEFAULT_FPS_LIMIT;
		float frame_time_ms = 1000.f / DEFAULT_FPS_LIMIT;
		bool initialized = false;

	protected:
		SDLPointers sdl_ptrs;
		float delta = 0;
		SDL_Color clear_color{ 2, 2, 2, 255 };
		std::shared_ptr<IScene> current_scene;

	public:
		LoopManager() = default;
		~LoopManager();

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
			int fps_cap_ = DEFAULT_FPS_LIMIT
		);
		std::shared_ptr<void> executeScene(std::shared_ptr<IScene> scene, std::shared_ptr<void> startup_data);
	};
}


#endif
