#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../core/Math.h"

class Texture {
public:
	Texture() = default;
	Texture(SDL_Texture* texture, SDL_Rect texture_coords);
	Texture(SDL_Texture* texture, Vec2I& _position, Vec2I& _scale);
	~Texture();

	void SetTexture(SDL_Texture* texture);
	void Render();
	SDL_Texture& GetTexture();
	SDL_Rect& GetTextureCoords();

	Vec2I position;
	Vec2I scale;
private:
	SDL_Texture* m_texture;
	SDL_Rect m_textureCoords;
};

class TextureLoader
{
public:
	static SDL_Texture* LoadTexture(const std::string& filepath);
};

