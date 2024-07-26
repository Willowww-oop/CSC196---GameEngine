#pragma once
#include "Renderer.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

struct Color;
class Font;
class Renderer;

class Text
{
public:
	friend class Font;
	Text() = default;
	Text(Font* font) : m_font{ font } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

private:
	Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};