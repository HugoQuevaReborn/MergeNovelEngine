#pragma once
#include <string>
#include "../core/Math.h" 

class Texture;

class Character
{
public:
	Character() = default;
	Character(const std::string& name);
	Character(std::string&& name) noexcept;

	const std::string GetName();

	void SetName(const std::string& name);
	void SetPosition(const Vec2I& position);
	void SetScale(const Vec2I& scale);
	Vec2I& GetPosition();
	Vec2I& GetScale();

	Texture* texture;
private:
	std::string m_name;
};