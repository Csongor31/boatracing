#pragma once

namespace sf
{

class Cell
{
public:
	sf::Actor* getActor();
	void setActor(sf::Actor* actor);
	void removeActor();
	Actor* handleCollisions(Actor* actorToCheck) const;

private:
	sf::Actor* actor_; //listaban tarolom az elemeket a gyorsabb kiszedegetes erdekeben
};

class Grid
{
public:
	Grid(sf::u16 nMapSizeWidth, sf::u16 nMapSizeHeight, sf::u8 nTileSizeWidth, sf::u8 nTileSizeHeight) : tileWidth_(nTileSizeHeight), tileHeight_(nTileSizeHeight)
	{
		maxTileCountX_ = nMapSizeWidth / nTileSizeWidth;
		maxTileCountY_ = nMapSizeHeight / nTileSizeHeight;

		cells_.reserve(maxTileCountX_);
		sf::u8 nRow = 0;
		while (nRow < maxTileCountX_)
		{
			std::vector<sf::Cell> row;
			row.reserve(maxTileCountY_);
			sf::u8 nTile = 0;
			while (nTile < maxTileCountY_)
			{
				row.push_back(sf::Cell());
				nTile++;
			}
			cells_.push_back(row);
			nRow++;
		}
	}

	const Cell& getCell(Actor* actor);
	void addActorToCell(Actor* actor);
	void removeActor(Actor* actor);
	bool actorMoved(Actor* movedActor, glm::vec2& vNewPos);

private:
	std::vector<std::vector<Cell> > cells_;
	sf::u8 tileWidth_;
	sf::u8 tileHeight_;
	sf::u8 maxTileCountX_;
	sf::u8 maxTileCountY_;
};
}

