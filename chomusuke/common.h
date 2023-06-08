#ifndef CHOMUSUKE_COMMON_H
#define CHOMUSUKE_COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

namespace cho {
// This assumes that IMG is initialized
SDL_Texture* loadTexture(const std::string& filename, SDL_Renderer* renderer);

// This assumes that TTF is initialized
TTF_Font* loadFont(const std::string& filename, int font_size);

// Generate SDL_Texture. Exports rect information to out.
SDL_Texture* makeText(TTF_Font* font, const std::string& text, const SDL_Color& color, SDL_Renderer* renderer, SDL_Rect& out);

struct Vector2f {
	float x;
	float y;

	Vector2f():
		x(0),
		y(0)
	{}
	Vector2f(const float x_, const float y_):
		x(x_),
		y(y_)
	{}

	Vector2f operator+(const Vector2f& other) { return { this->x + other.x, this->y + other.y }; }
	Vector2f operator-(const Vector2f& other) { return { this->x - other.x, this->y - other.y }; }
	Vector2f operator*(const float other) { return { this->x * other, this->y * other }; }
};
}

#endif