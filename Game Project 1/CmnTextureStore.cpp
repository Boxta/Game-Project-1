#include "CmnTextureStore.h"

void CmnTextureStore::AddTexture(const std::string& key, const std::string& filename)
{
	sf::Texture texture;

	texture.loadFromFile(filename);
	/*Using insert will ensure only create. using array type access "[]" will create or replace but its easier.*/
	TextureStore.insert(std::pair<std::string, sf::Texture> (key, texture));
}

sf::Texture& CmnTextureStore::GetTextureRef(const std::string& key)
{
	assert(TextureStore.size() <= 0);
	return TextureStore.at(key); 	//.at has bounds checking
}

CmnTextureStore::CmnTextureStore()
{
}


CmnTextureStore::~CmnTextureStore()
{
}
