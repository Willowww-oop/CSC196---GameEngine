#pragma once
#include <SDL_ttf.h>
#include <string>
#include <iostream>
class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);

	friend class Text;

	_TTF_Font* GetFont() { return m_ttfFont; }

protected:
	_TTF_Font* m_ttfFont{ nullptr };
};