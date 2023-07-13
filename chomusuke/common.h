#ifndef CHOMUSUKE_COMMON_H
#define CHOMUSUKE_COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <type_traits>

namespace cho {
// This assumes that IMG is initialized
SDL_Texture* loadTexture(const std::string& filename, SDL_Renderer* renderer);

// This assumes that TTF is initialized
TTF_Font* loadFont(const std::string& filename, int font_size);

// Generate SDL_Texture. Exports rect information to out.
SDL_Texture* makeText(TTF_Font* font, const std::string& text, const SDL_Color& color, SDL_Renderer* renderer, SDL_Rect& out);

template<typename T> requires std::is_arithmetic<T>::value
struct Vector2 {
	T x;
	T y;

	Vector2():
		x(),
		y()
	{}
	Vector2(const T x_, const T y_):
		x(x_),
		y(y_)
	{}

	Vector2<T> operator+(const Vector2<T>& other) { return { this->x + other.x, this->y + other.y }; }
	Vector2<T> operator-(const Vector2<T>& other) { return { this->x - other.x, this->y - other.y }; }
	Vector2<T> operator*(const int other) { return { this->x * other, this->y * other }; }
	Vector2<T> operator*(const float other) { return { this->x * other, this->y * other }; }
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
}


#endif