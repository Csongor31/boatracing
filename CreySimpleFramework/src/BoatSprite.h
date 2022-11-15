#pragma once

namespace sf 
{

class BoatSprite : public sf::Sprite, public sf::MoveDirectionCommandReceiver
{
public:
	BoatSprite() = default;
	~BoatSprite() = default;
	
	void execute() override;

	void moveDir(glm::vec2 dir) override;

	void SetVelocity(glm::vec2 vel) { vel_ = vel; }

protected:
	glm::vec2 vel_; //jatek soran a default gyorsulas
};

}

