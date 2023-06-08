#include "chomusuke/common.h"

SDL_Texture* cho::loadTexture(const std::string& filename, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (!surface) {
		std::cerr << "Failed to load surface! " << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = nullptr;

	if (!texture)
		std::cerr << "Failed to create texture! " << IMG_GetError() << std::endl;
	return texture;
}

TTF_Font* cho::loadFont(const std::string& filename, int font_size) {
	TTF_Font* font = TTF_OpenFont(filename.c_str(), font_size);

	if (!font)
		std::cerr << "Failed to open font! " << TTF_GetError() << std::endl;

	return font;
}

SDL_Texture* cho::makeText(TTF_Font* font, const std::string& text, const SDL_Color& color, SDL_Renderer* renderer, SDL_Rect& out) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surf) {
		std::cerr << "Failed to render text! " << TTF_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* test_text = SDL_CreateTextureFromSurface(renderer, surf);
		
	if (!test_text)
		std::cerr << "Failed to create texture(text)! " << SDL_GetError() << std::endl;

	out.w = surf->w;
	out.h = surf->h;
	SDL_FreeSurface(surf);
	surf = nullptr;
	return test_text;
}