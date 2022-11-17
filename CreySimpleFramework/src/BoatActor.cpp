#include "BoatActor.h"

namespace sf
{
void BoatActor::moveDir(sf::s8 x, sf::s8 y)
{
	if (x != 0) angle_ += -x * glm::sin(glm::radians(angle_)) * turnSpeed_;
	if (y != 0) angle_ += y * glm::cos(glm::radians(angle_)) * turnSpeed_ ;


	if (x == 1 && currentVelX_ < maxSpeed_)
	{
		currentVelX_ = currentVelX_ + acceleration_ < maxSpeed_ ? currentVelX_ + acceleration_ : maxSpeed_;
	}
	else if (x == -1 && currentVelX_ > -maxSpeed_)
	{
		currentVelX_ = currentVelX_ - acceleration_ > -maxSpeed_ ? currentVelX_ - acceleration_ : -maxSpeed_;
	}

	if (y == 1 && currentVelY_ < maxSpeed_)
	{
		currentVelY_ = currentVelY_ + acceleration_ < maxSpeed_ ? currentVelY_ + acceleration_ : maxSpeed_;
	}
	else if (y == -1 && currentVelY_ > -maxSpeed_)
	{
		currentVelY_ = currentVelY_ - acceleration_ > -maxSpeed_ ? currentVelY_ - acceleration_ : -maxSpeed_;
	}
}

sf::Actor* BoatActor::step(sf::Grid* grid)
{
	currentVelX_ = currentVelX_ > 0 ? currentVelX_ - 1 : currentVelX_ < 0 ? currentVelX_ + 1 : 0;
	currentVelY_ = currentVelY_ > 0 ? currentVelY_ - 1 : currentVelY_ < 0 ? currentVelY_ + 1 : 0;

	if (currentVelX_ || currentVelY_)
	{
		glm::vec2 velocity = { currentVelX_ * .1f, currentVelY_ * .1f };
		glm::vec2 newPos = position_ + velocity;
		grid->actorMoved(this, newPos);

		position_ = newPos;

		return grid->getCell(this).handleCollisions(this);
	}
	return nullptr;
}
}
