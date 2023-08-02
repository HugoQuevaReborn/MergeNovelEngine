#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>

class Font
{
public:
	Font() = default;
	~Font();

	void SetFont(TTF_Font* font);
	void SetFontSize(int size);
	TTF_Font* GetFont();
	std::string font_path;
private:
	TTF_Font* m_font;
};

class FontLoader {
public:
	static TTF_Font* LoadFont(const std::string& font_name,int size);
};