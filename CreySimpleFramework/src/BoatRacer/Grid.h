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
	sf::Actor* aActor_; //listaban tarolom az elemeket a gyorsabb kiszedegetes erdekeben
};

class Grid
{
public:
	Grid(sf::u16 nMapSizeWidth, sf::u16 nMapSizeHeight, sf::u8 nTileSizeWidth, sf::u8 nTileSizeHeight) : nTileWidth_(nTileSizeHeight), nTileHeight_(nTileSizeHeight)
	{
		nMaxTileCountX_ = nMapSizeWidth / nTileSizeWidth;
		nMaxTileCountY_ = nMapSizeHeight / nTileSizeHeight;

		vvCells_.reserve(nMaxTileCountX_);
		sf::u8 nRow = 0;
		while (nRow < nMaxTileCountX_)
		{
			std::vector<sf::Cell> row;
			row.reserve(nMaxTileCountY_);
			sf::u8 nTile = 0;
			while (nTile < nMaxTileCountY_)
			{
				row.push_back(sf::Cell());
				nTile++;
			}
			vvCells_.push_back(row);
			nRow++;
		}
	}
	~Grid() = default;

	const Cell& getCell(Actor* aActor);
	void addActorToCell(Actor* aActor);
	void removeActor(Actor* aActor);
	bool actorMoved(Actor* aMovedActor, glm::vec2& vNewPos);

private:
	std::vector<std::vector<Cell> > vvCells_;
	sf::u8 nTileWidth_;
	sf::u8 nTileHeight_;
	sf::u8 nMaxTileCountX_;
	sf::u8 nMaxTileCountY_;
};
}

