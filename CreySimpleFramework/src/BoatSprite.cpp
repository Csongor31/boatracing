#include "BoatSprite.h"

namespace sf
{
	void BoatSprite::execute() {
		return;
	}

	void BoatSprite::moveDir(glm::vec2 dir)
	{
		//glm::vec2-ben a float valamiert pontos
		if ( glm::abs(dir.x) != 0 )
		{
			currentVelX_ += dir.x * 2;
		}

		if (glm::abs(dir.y) != 0)
		{
			currentVelY_ += dir.y * 2;
		}
	}

	void BoatSprite::step() 
	{
		//mivel a movedir csak gombnyomasra csinal barmit, igy ott 2-vel novekszik a sebbesseg, a step-ben meg mindig csokken eggyel az ertek 
		currentVelX_ = currentVelX_ > 0 ? currentVelX_ - 1 : currentVelX_ < 0 ? currentVelX_ + 1 : 0;
		currentVelY_ = currentVelY_ > 0 ? currentVelY_ - 1 : currentVelY_ < 0 ? currentVelY_ + 1 : 0;

		glm::vec2 velocity = { currentVelX_ * acc_, currentVelY_ * acc_ };

		velocity.x = glm::min(velocity.x, vel_.x);
		velocity.x = glm::max(velocity.x, -vel_.x);
		velocity.y = glm::min(velocity.y, vel_.y);
		velocity.y = glm::max(velocity.y, -vel_.y);

		position_ = position_ + velocity;
	}
}
