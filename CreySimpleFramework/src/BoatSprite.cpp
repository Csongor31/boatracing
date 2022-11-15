#include "BoatSprite.h"

namespace sf
{
	void BoatSprite::execute() {
		return;
	}

	void BoatSprite::moveDir(glm::vec2 dir)
	{
		position_ = position_ + dir * vel_;
	}
}
