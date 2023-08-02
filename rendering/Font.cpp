#include "Font.h"
#include "../core/Application.h"
#include <iostream>

TTF_Font* FontLoader::LoadFont(const std::string& font_name, int size)
{
	std::string path = Application::Get().GetAssetsPath() + "\\font\\" + font_name;

	return TTF_OpenFont(path.c_str(), size);
}

Font::~Font()
{
	TTF_CloseFont(GetFont());
}

TTF_Font* Font::GetFont()
{
	return m_font;
}

void Font::SetFont(TTF_Font* font)
{
	if (m_font != nullptr)
		TTF_CloseFont(m_font);

	m_font = font;
}

void Font::SetFontSize(int size)
{
	if (m_font == nullptr) return;

	TTF_SetFontSize(m_font, size);
}
