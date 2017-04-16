#include "TileManager.h"

std::vector<TileManager::Tile> TileManager::CreateLayerTiles(int layertilewidth, int layertileheight,
	int width, int height,
	std::vector<AnimatedSprite::Animation> animations,
	std::string textureid,
	CmnTextureStore& cmn
	)
{
	std::vector<TileManager::Tile> tilelist;

	for (int w = 0; w < layertilewidth; w++)
	{
		for (int h = 0; h < layertileheight; h++)
		{
			Tile tile = { w * width, h * height,
				width, height,
				animations,
				textureid, 
				cmn, 
				false };
			
			tilelist.push_back(tile);
		}
	}

	return tilelist;
}

void TileManager::AddTileLayer(int layerid, std::vector<Tile> tiles)
{
	mTileStore[layerid] = tiles;
}

void TileManager::Initiate(CmnTextureStore& cmn)
{

	/*For Each Tile Layer*/
	for (auto& _layer : mTileStore)
	{
		/*Iterator Over Each Tile and Initiate*/
		for (auto& _tiles : _layer.second)
		{
			_tiles.Initiate(0, 2);
			
		}
	}

}

void TileManager::Update(const float dt)
{
	if (mTileStore.size() <= 0)
		return;

	/*For Each Tile Layer*/
	for (auto& _layer : mTileStore)
	{
		/*Iterator Over Each Tile and Update*/
		for (auto& _tiles : _layer.second)
		{
			_tiles.Update(dt);
		}
	}
}

void TileManager::Draw(sf::RenderWindow & wnd)
{
	/*For Each Tile Layer*/
	for (auto& _layer : mTileStore)
	{
		/*Iterator Over Each Tile and Draw*/
		for (auto& _tiles : _layer.second)
		{
			_tiles.Draw(wnd);
		}
	}
}

TileManager::TileManager()
{

}


TileManager::~TileManager()
{
}

TileManager::Tile::Tile(int _x, int _y, 
	int _w, int _h, 
	std::vector<AnimatedSprite::Animation>& anicollection, 
	std::string texturesheetid, 
	CmnTextureStore& cmn, 
	bool isAnimating)
	:
	mAnimationCollection(anicollection),
	mPositionX(_x),
	mPositionY(_y),
	mTileWidth(_w),
	mTileHeight(_h),
	mType(texturesheetid),
	mTileSprite(cmn.GetTextureRef(mType),
		mTileWidth, mTileHeight,
		mPositionX, mPositionY,
		mAnimationCollection),
	mIsAnimating(isAnimating)
{
	mTileSprite.setAnimation(mIsAnimating);
}

void TileManager::Tile::Initiate(const int animation, const int frame)
{

	mTileSprite.Initiate(animation, frame);
}

void TileManager::Tile::Update(const float dt)
{
	mTileSprite.Update(dt);
}

void TileManager::Tile::Draw(sf::RenderWindow & wnd)
{
	mTileSprite.Draw(wnd);
}
