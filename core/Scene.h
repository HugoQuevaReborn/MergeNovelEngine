#pragma once
#include <vector>
#include <string>

class Texture;
class Character;

class Scene
{
public:
	Scene();
	~Scene();
	Texture& GetBackground();
	Character* GetCharacterByName(std::string& name);
private:
	Texture* m_background;
	std::vector<Character*> m_characters;
};