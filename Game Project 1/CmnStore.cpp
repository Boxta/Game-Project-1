#include "CmnStore.h"

void CmnStore::AddTexture(const std::string& key, const std::string& filename)
{
	sf::Texture texture;

	texture.loadFromFile(filename);
	/*Using insert will ensure only create. using array type access "[]" will create or replace but its easier.*/
	TextureStore.insert(std::pair<std::string, sf::Texture>(key, texture));
}

sf::Texture& CmnStore::GetTextureRef(const std::string& key)
{
	return TextureStore.at(key); 	//.at has bounds checking
}

void CmnStore::AddFont(const std::string & key, const std::string & filename)
{
	sf::Font font;

	font.loadFromFile(filename);
	/*Using insert will ensure only create. using array type access "[]" will create or replace but its easier.*/
	FontStore.insert(std::pair<std::string, sf::Font>(key, font));
}

sf::Font& CmnStore::GetFontRef(const std::string & key)
{
	return FontStore.at(key);		//.at has bounds checking
}

CmnStore::CmnStore()
{
}


CmnStore::~CmnStore()
{
}
