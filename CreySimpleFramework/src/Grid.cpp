#include "Grid.h"

namespace sf
{

void Cell::addActor(sf::Actor* actor)
{ 
	actors_.push_back(actor);
}
void Cell::removeActor(sf::Actor* actor)
{ 
	actors_.remove(actor);
}

Actor* Cell::handleCollisions(Actor* actorToCheck) const
{
	//hajok kivetelevel mindennek kor collisionje van

	float actorMinX = actorToCheck->getPosition().x - (actorToCheck->getWidth() / 2);
	float actorMinY = actorToCheck->getPosition().y - (actorToCheck->getHeight() / 2);

	for (Actor* actor : actors_)
	{
		if (actor == actorToCheck) continue;

		//elforgatjuk a sprite-ot a hajonkhoz merten
		float actorPosX = (glm::cos(glm::radians(-actorToCheck->getAngle())) * (actor->getPosition().x - actorToCheck->getPosition().x)) - (glm::sin(glm::radians(-actorToCheck->getAngle())) * (actor->getPosition().y - actorToCheck->getPosition().y)) + actorToCheck->getPosition().x;
		float actorPosY = (glm::sin(glm::radians(-actorToCheck->getAngle())) * (actor->getPosition().x - actorToCheck->getPosition().x)) + (glm::cos(glm::radians(-actorToCheck->getAngle())) * (actor->getPosition().y - actorToCheck->getPosition().y)) + actorToCheck->getPosition().y;

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
		if ( distance < actor->getWidth())
		{
			std::string slog = "collision (ship x,y, angle; point x,y):";
			slog += " " + std::to_string((int)actorToCheck->getPosition().x);
			slog += " " + std::to_string((int)actorToCheck->getPosition().y);
			slog += " " + std::to_string((int)actorToCheck->getAngle());
			slog += " " + std::to_string((int)actor->getPosition().y);
			slog += " " + std::to_string((int)actor->getPosition().y);
			slog += "\n";
			SFLOG(slog);
			return actor;
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

	cells_[nCurrentTileX][nCurrentTileY].addActor(actor);
}

bool Grid::actorMoved(Actor* movedActor, glm::vec2& vNewPos)
{
	int nNewTileX = vNewPos.x / tileWidth_;
	int nNewTileY = vNewPos.y / tileHeight_;
	int nCurrentTileX = movedActor->getPosition().x / tileWidth_;
	int nCurrentTileY = movedActor->getPosition().y / tileHeight_;

	//ha nekimegyunk a falnak ne engedjuk hogy kimenjunk a palyarol, akar lehetne szolni a hogy tortenjen valami negativ
	if (nNewTileX >= maxTileCountX_)
	{
		vNewPos.x = maxTileCountX_ * tileWidth_ - 1;
	}
	else if (vNewPos.x < 0)
	{
		vNewPos.x = 0;
	}
	else if (nNewTileY >= maxTileCountY_)
	{
		vNewPos.y = maxTileCountY_ * tileHeight_ - 1;
	}
	else if (vNewPos.y < 0)
	{
		vNewPos.y = 0;
	}
	else if (nNewTileX != nCurrentTileX || nNewTileY != nCurrentTileY)
	{
		cells_[nCurrentTileX][nCurrentTileY].removeActor(movedActor);
		cells_[nNewTileX][nNewTileY].addActor(movedActor);
	}
	return true;
}
}