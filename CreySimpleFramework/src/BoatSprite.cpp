#include "BoatSprite.h"

namespace sf
{
	void BoatSprite::moveDir(sf::s8 x, sf::s8 y)
	{
		if (x != 0) angle_ += -x * glm::sin(glm::radians(angle_)) * turnSpeed_;

		if (y != 0) angle_ +=  y * glm::cos(glm::radians(angle_)) * turnSpeed_;


		if ( x == 1 && currentVelX_ < maxSpeed_)
		{
			currentVelX_ += 8;
		}
		else if (x == -1 && currentVelX_ > -maxSpeed_)
		{
			currentVelX_ -= 8;
		}

		if (y == 1 && currentVelY_ < maxSpeed_)
		{
			currentVelY_ += 8;
		}
		else if (y == -1 && currentVelY_ > -maxSpeed_)
		{
			currentVelY_ -= 8;
		}
	}

	sf::Command* BoatSprite::step(sf::Grid* grid) 
	{
		currentVelX_ = currentVelX_ > 0 ? currentVelX_ - 1 : currentVelX_ < 0 ? currentVelX_ + 1 : 0;
		currentVelY_ = currentVelY_ > 0 ? currentVelY_ - 1 : currentVelY_ < 0 ? currentVelY_ + 1 : 0;

		glm::vec2 velocity = { currentVelX_ * .1f, currentVelY_ * .1f };

		position_ = position_ + velocity;

		grid->spriteMoved(this, (position_ - velocity));

		Sprite* collidedSprite = grid->getCell(this).handleCollisions(this);

		if (collidedSprite)
		{
			return nullptr; // vissza fogunk adni egy collide commandot, ami majd megmondja, hogy mit csinaljunk
		}

		return nullptr;
	}
}
