#include "Character.h"
#include "../rendering/Texture.h"

void Character::SetName(const std::string& name)
{
	m_name = name;
}

void Character::SetPosition(const Vec2I& position)
{
	texture->position.x = position.x;
	texture->position.y = position.y;
}

void Character::SetScale(const Vec2I& scale)
{
	texture->scale.x = scale.x;
	texture->scale.y = scale.y;
}

Character::Character(std::string&& name) noexcept
	: m_name(name), texture(nullptr)
{
}

Character::Character(const std::string& name)
	: m_name(name), texture(nullptr)
{
}

const std::string Character::GetName()
{
	return m_name;
}

Vec2I& Character::GetPosition()
{
	return texture->position;
}

Vec2I& Character::GetScale()
{
	return texture->scale;
}
