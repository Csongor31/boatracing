#pragma once

namespace sf
{

class Cell
{
public:
	void addActor(sf::Actor* actor);
	void removeActor(sf::Actor* actor);
	Actor* handleCollisions(Actor* actorToCheck) const;

private:
	std::list<sf::Actor*> actors_; //listaban tarolom az elemeket a gyorsabb kiszedegetes erdekeben
};

//spatial partition grid
//csak a hajok mozognak, ezert felosztom a palyat mezokre es mindig csak a hajok cellajaban vegzek utkozes vizsgalatot
// palyakat ugy rendezem, hogy a hajo meretetol fuggoen ne legyenek a sarkokon akadalyok
//ezaltal remelhetoleg kevesebb utkozest kell megnezi
class Grid
{
public:
	Grid(sf::u32 nMapSizeWidth, sf::u32 nMapSizeHeight, sf::u32 nTileSizeWidth, sf::u32 nTileSizeHeight) : tileWidth_(nTileSizeHeight), tileHeight_(nTileSizeHeight)
	{
		maxTileCountX_ = nMapSizeWidth / nTileSizeWidth;
		maxTileCountY_ = nMapSizeHeight / nTileSizeHeight;

		cells_.reserve(maxTileCountX_);
		sf::s8 nRow = 0;
		while (nRow < maxTileCountX_)
		{
			std::vector<sf::Cell> row;
			row.reserve(maxTileCountY_);
			sf::s8 nTile = 0;
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
	bool actorMoved(Actor* movedActor, glm::vec2& vNewPos); //hajo uj cellajat megadjuk, illetve elvegzi a sarkok vizsgalatat

private:
	std::vector<std::vector<Cell> > cells_;
	sf::u32 tileWidth_;
	sf::u32 tileHeight_;
	sf::s8 maxTileCountX_;
	sf::s8 maxTileCountY_;
};
}

