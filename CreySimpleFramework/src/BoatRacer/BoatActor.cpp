#include "BoatActor.h"

namespace sf
{
bool PlayerControl::getPlayer() const
{
	return bPlayerOne_; 
}
sf::u8 PlayerControl::getScore() const 
{
	return nScore_; 
}

void PlayerControl::incrementScore()
{
	++nScore_;
}

void BoatActor::moveDir(sf::s8 nXDir, sf::s8 nYDir)
{
	if (nXDir != 0) nAngle_ += -nXDir * glm::sin(glm::radians(nAngle_)) * nTurnSpeed_;
	if (nYDir != 0) nAngle_ += nYDir * glm::cos(glm::radians(nAngle_)) * nTurnSpeed_;


	if (nXDir == 1 && nCurrentVelX_ < nMaxSpeed_)
	{
		nCurrentVelX_ = nCurrentVelX_ + nAcceleration_ < nMaxSpeed_ ? nCurrentVelX_ + nAcceleration_ : nMaxSpeed_;
	}
	else if (nXDir == -1 && nCurrentVelX_ > -nMaxSpeed_)
	{
		nCurrentVelX_ = nCurrentVelX_ - nAcceleration_ > -nMaxSpeed_ ? nCurrentVelX_ - nAcceleration_ : -nMaxSpeed_;
	}

	if (nYDir == 1 && nCurrentVelY_ < nMaxSpeed_)
	{
		nCurrentVelY_ = nCurrentVelY_ + nAcceleration_ < nMaxSpeed_ ? nCurrentVelY_ + nAcceleration_ : nMaxSpeed_;
	}
	else if (nYDir == -1 && nCurrentVelY_ > -nMaxSpeed_)
	{
		nCurrentVelY_ = nCurrentVelY_ - nAcceleration_ > -nMaxSpeed_ ? nCurrentVelY_ - nAcceleration_ : -nMaxSpeed_;
	}
}

void BoatActor::setMaxSpeed(sf::s8 nMaxSpeed) 
{ 
	nMaxSpeed_ = nMaxSpeed;
}

void BoatActor::setAcceleration(sf::s8 nAcceleration) 
{ 
	nAcceleration_ = nAcceleration;
}

void BoatActor::setTurnSpeed(sf::s8 nTurnSpeed) 
{ 
	nTurnSpeed_ = nTurnSpeed;
}

sf::Actor* BoatActor::step(sf::Grid* gGrid)
{
	nCurrentVelX_ = nCurrentVelX_ > 0 ? nCurrentVelX_ - 1 : nCurrentVelX_ < 0 ? nCurrentVelX_ + 1 : 0;
	nCurrentVelY_ = nCurrentVelY_ > 0 ? nCurrentVelY_ - 1 : nCurrentVelY_ < 0 ? nCurrentVelY_ + 1 : 0;

	if (nCurrentVelX_ || nCurrentVelY_)
	{
		glm::vec2 velocity = { nCurrentVelX_ * .1f, nCurrentVelY_ * .1f };
		glm::vec2 newPos = vPosition_ + velocity;
		gGrid->actorMoved(this, newPos);

		vPosition_ = newPos;

		return gGrid->getCell(this).handleCollisions(this);
	}
	return nullptr;
}
}
