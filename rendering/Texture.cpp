#include "Texture.h"
#include "../core/Application.h"

Texture::Texture(SDL_Texture* texture, SDL_Rect texture_coords) 
    : m_texture{ texture }, m_textureCoords{ texture_coords } 
{
}

Texture::Texture(SDL_Texture* texture, Vec2I& _position, Vec2I& _scale)
    : m_texture(texture), position(_position), scale(_scale)
{
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

SDL_Texture* TextureLoader::LoadTexture(const std::string& filename)
{
    std::string path = Application::Get().GetAssetsPath() + "\\texture\\" + filename;

    SDL_Texture* texture;
    texture = IMG_LoadTexture(Application::Get().GetWindow().GetRendererInstance(), path.c_str());

    return texture;
}

SDL_Texture& Texture::GetTexture() {
    return *m_texture;
}

SDL_Rect& Texture::GetTextureCoords() {
    return m_textureCoords;
}

void Texture::SetTexture(SDL_Texture* texture)
{
    if (m_texture != nullptr) 
        SDL_DestroyTexture(m_texture);
    
    m_texture = texture;
}

void Texture::Render()
{
    m_textureCoords.w = scale.x;
    m_textureCoords.h = scale.y;
    m_textureCoords.x = position.x;
    m_textureCoords.y = position.y;

    SDL_RenderCopy(Application::Get().GetWindow().GetRendererInstance(), &GetTexture(), nullptr, &GetTextureCoords());
}
