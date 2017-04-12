#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <assert.h>

class CmnTextureStore
{
private:
	std::map<const std::string, sf::Texture> TextureStore;
public:
	void AddTexture(const std::string& key, const std::string& filename);
	sf::Texture& GetTextureRef(const std::string& key);

	CmnTextureStore();
	~CmnTextureStore();
};

