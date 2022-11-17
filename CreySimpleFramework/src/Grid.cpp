#include "Grid.h"

namespace sf
{

sf::Actor* Cell::getActor()
{
	return actor_;
}

void Cell::setActor(sf::Actor* actor)
{ 
	actor_ = actor;
}
void Cell::removeActor()
{ 
	actor_ = nullptr;
}

Actor* Cell::handleCollisions(Actor* actorToCheck) const
{
	if (actor_)
	{
		float actorMinX = actorToCheck->getPosition().x - (actorToCheck->getWidth() / 2);
		float actorMinY = actorToCheck->getPosition().y - (actorToCheck->getHeight() / 2);

		//elforgatjuk a sprite-ot a hajonkhoz merten
		float actorPosX = (glm::cos(glm::radians(-actorToCheck->getAngle())) * (actor_->getPosition().x - actorToCheck->getPosition().x)) - (glm::sin(glm::radians(-actorToCheck->getAngle())) * (actor_->getPosition().y - actorToCheck->getPosition().y)) + actorToCheck->getPosition().x;
		float actorPosY = (glm::sin(glm::radians(-actorToCheck->getAngle())) * (actor_->getPosition().x - actorToCheck->getPosition().x)) + (glm::cos(glm::radians(-actorToCheck->getAngle())) * (actor_->getPosition().y - actorToCheck->getPosition().y)) + actorToCheck->getPosition().y;

		float closestX = actorPosX;
		float closestY = actorPosY;

		if (actorPosX < actorMinX)
		{
			closestX = actorMinX;
		}
		else if (actorPosX > actorMinX + actorToCheck->getWidth())
		{
			closestX = actorMinX + actorToCheck->getWidth();
		}

		if (actorPosY < actorMinY)
		{
			closestY = actorMinY;
		}
		else if (actorPosY > actorMinY + actorToCheck->getHeight())
		{
			closestY = actorMinY + actorToCheck->getHeight();
		}
		float distance = glm::distance(glm::vec2(actorPosX, actorPosY), glm::vec2(closestX, closestY));
		if (distance < actor_->getWidth())
		{
			return actor_;
		}
	}
	return nullptr;
}

const Cell& Grid::getCell(Actor* spSprite)
{
	int nCurrentTileX = spSprite->getPosition().x / tileWidth_;
	int nCurrentTileY = spSprite->getPosition().y / tileHeight_;

	return cells_[nCurrentTileX][nCurrentTileY];
}

void Grid::addActorToCell(Actor* actor)
{
	int nCurrentTileX = actor->getPosition().x / tileWidth_;
	int nCurrentTileY = actor->getPosition().y / tileHeight_;

	cells_[nCurrentTileX][nCurrentTileY].setActor(actor);
}

void Grid::removeActor(Actor* actor)
{
	int nCurrentTileX = actor->getPosition().x / tileWidth_;
	int nCurrentTileY = actor->getPosition().y / tileHeight_;

	cells_[nCurrentTileX][nCurrentTileY].removeActor();
};

bool Grid::actorMoved(Actor* movedActor, glm::vec2& vNewPos)
{
	int nNewTileX = vNewPos.x / tileWidth_;
	int nNewTileY = vNewPos.y / tileHeight_;
	int nCurrentTileX = movedActor->getPosition().x / tileWidth_;
	int nCurrentTileY = movedActor->getPosition().y / tileHeight_;

	//ellenorizzuk, hogy belephetunk e a cellaba
	//letezik-e olyan cella
	//van-e sziget abban a cellaban
	if (nNewTileX >= maxTileCountX_)
	{
		vNewPos.x = maxTileCountX_ * tileWidth_ - 1;
	}
	if (vNewPos.x < 0)
	{
		vNewPos.x = 0;
	}
	if (nNewTileY >= maxTileCountY_)
	{
		vNewPos.y = maxTileCountY_ * tileHeight_ - 1;
	}
	if (vNewPos.y < 0)
	{
		vNewPos.y = 0;
	}
	
	if (maxTileCountX_ > nNewTileX && maxTileCountY_ > nNewTileY)
	{
		sf::Actor* actorInCell = cells_[nNewTileX][nNewTileY].getActor();

		if (actorInCell)
		{
			if (actorInCell->getActorType() == sf::ActorType::Obstacle)
			{
				if (nNewTileX > nCurrentTileX)
				{
					vNewPos.x = nNewTileX * tileWidth_ - 1;
				}
				if (nNewTileX < nCurrentTileX)
				{
					vNewPos.x = (nCurrentTileX)*tileWidth_;
				}
				if (nNewTileY > nCurrentTileY)
				{
					vNewPos.y = nNewTileY * tileHeight_ - 1;
				}
				if (nNewTileY < nCurrentTileY)
				{
					vNewPos.y = (nCurrentTileY)*tileHeight_;
				}
			}
		}
	}
	return true;
}
}