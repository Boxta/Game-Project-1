#pragma once
#include <map>
#include <vector>
#include <string>
#include "AnimatedSprite.h"
#include "SFML\Window.hpp"
#include "CmnTextureStore.h"


/*Manages Tiles and Layers*/
class TileManager
{
public:
	class Tile
	{
	public:
		Tile() = default;
		Tile(int _x, int _y,
			int _w, int _h,
			std::vector<AnimatedSprite::Animation>& anicollection,
			std::string texturesheetid,
			CmnTextureStore& store,
			bool isAnimating);
	private:
		std::string mType = "null";
		std::vector<AnimatedSprite::Animation> mAnimationCollection;
		AnimatedSprite mTileSprite;
		int mPositionX = 0;
		int mPositionY = 0;
		int mTileWidth = 0;
		int mTileHeight = 0;
		bool mIsAnimating = false;
	public:
		void Initiate(const int animation, const int frame);
		void Update(const float dt);
		void Draw(sf::RenderWindow& wnd);
	};

private:
	/*Store For All Tiles For All Layers*/
	std::map<int, std::vector<Tile>> mTileStore;
	
public:
	std::vector<Tile> CreateLayerTiles(int layertilewidth, int layertileheight,
		int width, int height,
		std::vector<AnimatedSprite::Animation> animations,
		std::string textureid,
		CmnTextureStore& cmn,
		bool animating);
	void AddTileLayer(int layerid, std::vector<Tile> tiles);

	void Initiate(CmnTextureStore& cmn);
	void Update(const float dt);
	void Draw(sf::RenderWindow& wnd);
public:
	TileManager();
	~TileManager();
};

