#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <string>

class CmnStore
{
private:
	std::map<const std::string, sf::Texture> TextureStore;
	std::map<const std::string, sf::Font> FontStore;
public:
	void AddTexture(const std::string& key, const std::string& filename);
	sf::Texture& GetTextureRef(const std::string& key);
	void AddFont(const std::string& key, const std::string& filename);
	sf::Font& GetFontRef(const std::string& key);
	CmnStore();
	~CmnStore();
};

