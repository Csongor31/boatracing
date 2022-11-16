#pragma once

namespace sf
{

class Cell
{
public:
	void addSprite(sf::Sprite* sprite) { sprites_.push_back(sprite); }
	void removeSprite(sf::Sprite* sprite) { sprites_.remove(sprite); }

	Sprite* handleCollisions(Sprite* boatSprite) const
	{
		//hajok kivetelevel mindennek kor collisionje van

		float boatSpriteMinX = boatSprite->getPosition().x - (boatSprite->getWidth() / 2);
		float boatSpriteMinY = boatSprite->getPosition().y - (boatSprite->getHeight() / 2);

		for (Sprite* sprite : sprites_)
		{
			if (sprite == boatSprite) continue;

			//elforgatjuk a sprite-ot a hajonkhoz merten
			float spritePosX = (glm::cos(glm::radians(boatSprite->getAngle())) * (sprite->getPosition().x - boatSprite->getPosition().x)) - (glm::sin(glm::radians(boatSprite->getAngle())) * (sprite->getPosition().y - boatSprite->getPosition().y)) + boatSprite->getPosition().x;
			float spritePosY = (glm::sin(glm::radians(boatSprite->getAngle())) * (sprite->getPosition().x - boatSprite->getPosition().x)) + (glm::cos(glm::radians(boatSprite->getAngle())) * (sprite->getPosition().y - boatSprite->getPosition().y)) + boatSprite->getPosition().y;

			float closestX = spritePosX;
			float closestY = spritePosY;

			if (spritePosX < boatSpriteMinX)
			{
				closestX = boatSpriteMinX;
			}
			else if (spritePosX > boatSpriteMinX + boatSprite->getWidth())
			{
				closestX = boatSpriteMinX + boatSprite->getWidth();
			}

			if (spritePosY < boatSpriteMinY)
			{
				closestY = boatSpriteMinY;
			}
			else if (spritePosY > boatSpriteMinY + boatSprite->getHeight())
			{
				closestY = boatSpriteMinY + boatSprite->getHeight();
			}
			if (glm::distance(glm::vec2(spritePosX, spritePosY), glm::vec2(closestX, closestY)) < sprite->getWidth())
			{
				return sprite;
			}
		}

		return nullptr;
	}

private:
	std::list<sf::Sprite*> sprites_; //listaban tarolom az elemeket a gyorsabb kiszedegetes erdekeben
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
		sf::s8 nTileCountX = nMapSizeWidth / nTileSizeWidth;
		sf::s8 nTileCountY = nMapSizeHeight / nTileSizeHeight;

		cells_.reserve(nTileCountX);
		sf::s8 nRow = 0;
		while (nRow < nTileCountX)
		{
			std::vector<sf::Cell> row;
			row.reserve(nTileCountY);
			sf::s8 nTile = 0;
			while (nTile < nTileCountY)
			{
				row.push_back(sf::Cell());
				nTile++;
			}
			cells_.push_back(row);
			nRow++;
		}
	}

	const Cell& getCell(Sprite* spSprite)
	{
		int nCurrentTileX = spSprite->getPosition().x / tileWidth_;
		int nCurrentTileY = spSprite->getPosition().y / tileHeight_;

		return cells_[nCurrentTileX][nCurrentTileY];
	}

	void addSpriteToCell(Sprite* spSprite)
	{
		int nCurrentTileX = spSprite->getPosition().x / tileWidth_;
		int nCurrentTileY = spSprite->getPosition().y / tileHeight_;

		cells_[nCurrentTileX][nCurrentTileY].addSprite(spSprite);
	}

	bool spriteMoved(Sprite* movedSprite, glm::vec2 vPrevPos)
	{
		int nCurrentTileX = movedSprite->getPosition().x / tileWidth_;
		int nCurrentTileY = movedSprite->getPosition().y / tileHeight_;
		int nPrevTileX = vPrevPos.x / tileWidth_;
		int nPrevTileY = vPrevPos.y / tileHeight_;

		if (nPrevTileX != nCurrentTileX || nPrevTileY != nCurrentTileY)
		{
			cells_[nPrevTileX][nPrevTileY].removeSprite(movedSprite);
			cells_[nCurrentTileX][nCurrentTileY].addSprite(movedSprite);
			return true;
		}

		return false;
	}

private:
	std::vector<std::vector<Cell> > cells_;
	sf::u32 tileWidth_;
	sf::u32 tileHeight_;
};
}

