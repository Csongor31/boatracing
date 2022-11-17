#include "Grid.h"

namespace sf
{

sf::Actor* Cell::getActor()
{
	return aActor_;
}

void Cell::setActor(sf::Actor* actor)
{ 
	aActor_ = actor;
}
void Cell::removeActor()
{ 
	aActor_ = nullptr;
}

Actor* Cell::handleCollisions(Actor* aActorToCheck) const
{
	if (aActor_)
	{
		float nActorMinX = aActorToCheck->getPosition().x - (aActorToCheck->getWidth() / 2);
		float nActorMinY = aActorToCheck->getPosition().y - (aActorToCheck->getHeight() / 2);

		float nActorPosX = (glm::cos(glm::radians(-aActorToCheck->getAngle())) * (aActor_->getPosition().x - aActorToCheck->getPosition().x)) - (glm::sin(glm::radians(-aActorToCheck->getAngle())) * (aActor_->getPosition().y - aActorToCheck->getPosition().y)) + aActorToCheck->getPosition().x;
		float nActorPosY = (glm::sin(glm::radians(-aActorToCheck->getAngle())) * (aActor_->getPosition().x - aActorToCheck->getPosition().x)) + (glm::cos(glm::radians(-aActorToCheck->getAngle())) * (aActor_->getPosition().y - aActorToCheck->getPosition().y)) + aActorToCheck->getPosition().y;

		float nClosestX = nActorPosX;
		float nClosestY = nActorPosY;

		if (nActorPosX < nActorMinX)
		{
			nClosestX = nActorMinX;
		}
		else if (nActorPosX > nActorMinX + aActorToCheck->getWidth())
		{
			nClosestX = nActorMinX + aActorToCheck->getWidth();
		}

		if (nActorPosY < nActorMinY)
		{
			nClosestY = nActorMinY;
		}
		else if (nActorPosY > nActorMinY + aActorToCheck->getHeight())
		{
			nClosestY = nActorMinY + aActorToCheck->getHeight();
		}
		float distance = glm::distance(glm::vec2(nActorPosX, nActorPosY), glm::vec2(nClosestX, nClosestY));
		if (distance < aActor_->getWidth())
		{
			return aActor_;
		}
	}
	return nullptr;
}

const Cell& Grid::getCell(Actor* spSprite)
{
	sf::s8 nCurrentTileX = (sf::u8) ( spSprite->getPosition().x / nTileWidth_ );
	sf::s8 nCurrentTileY = (sf::u8) ( spSprite->getPosition().y / nTileHeight_ );

	return vvCells_[nCurrentTileX][nCurrentTileY];
}

void Grid::addActorToCell(Actor* aActor)
{
	sf::u8 nCurrentTileX = (sf::u8) ( aActor->getPosition().x / nTileWidth_ );
	sf::u8 nCurrentTileY = (sf::u8) ( aActor->getPosition().y / nTileHeight_ );

	vvCells_[nCurrentTileX][nCurrentTileY].setActor(aActor);
}

void Grid::removeActor(Actor* aActor)
{
	sf::u8 nCurrentTileX = (sf::u8) ( aActor->getPosition().x / nTileWidth_ );
	sf::u8 nCurrentTileY = (sf::u8) ( aActor->getPosition().y / nTileHeight_ );

	vvCells_[nCurrentTileX][nCurrentTileY].removeActor();
};

bool Grid::actorMoved(Actor* aMovedActor, glm::vec2& vNewPos)
{
	sf::u8 nNewTileX = (sf::u8) (vNewPos.x / nTileWidth_);
	sf::u8 nNewTileY = (sf::u8) (vNewPos.y / nTileHeight_);
	sf::u8 nCurrentTileX = (sf::u8) ( aMovedActor->getPosition().x / nTileWidth_ );
	sf::u8 nCurrentTileY = (sf::u8) ( aMovedActor->getPosition().y / nTileHeight_ );

	if (nNewTileX >= nMaxTileCountX_)
	{
		vNewPos.x = (float) nMaxTileCountX_ * nTileWidth_ - 1;
	}
	if (vNewPos.x < 0)
	{
		vNewPos.x = 0;
	}
	if (nNewTileY >= nMaxTileCountY_)
	{
		vNewPos.y = (float) nMaxTileCountY_ * nTileHeight_ - 1;
	}
	if (vNewPos.y < 0)
	{
		vNewPos.y = 0;
	}
	
	if (nMaxTileCountX_ > nNewTileX && nMaxTileCountY_ > nNewTileY)
	{
		sf::Actor* actorInCell = vvCells_[nNewTileX][nNewTileY].getActor();

		if (actorInCell)
		{
			if (actorInCell->getActorType() == sf::ActorType::Obstacle)
			{
				if (nNewTileX > nCurrentTileX)
				{
					vNewPos.x = (float) nNewTileX * nTileWidth_ - 1;
				}
				if (nNewTileX < nCurrentTileX)
				{
					vNewPos.x = (float) nCurrentTileX * nTileWidth_;
				}
				if (nNewTileY > nCurrentTileY)
				{
					vNewPos.y = (float) nNewTileY * nTileHeight_ - 1;
				}
				if (nNewTileY < nCurrentTileY)
				{
					vNewPos.y = (float) nCurrentTileY * nTileHeight_;
				}
			}
		}
	}
	return true;
}
}