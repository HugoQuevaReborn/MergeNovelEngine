#include "Scene.h"
#include "../rendering/Texture.h"
#include "../entity/Character.h"

Scene::Scene() 
{
	m_background = new Texture();
}

Scene::~Scene() 
{
	delete m_background;
}

Texture& Scene::GetBackground()
{
	return *m_background;
}

Character* Scene::GetCharacterByName(std::string& name)
{
	for (auto* character : m_characters)
	{
		if (character->GetName() == name)
			return character;
	}

	return nullptr;
}