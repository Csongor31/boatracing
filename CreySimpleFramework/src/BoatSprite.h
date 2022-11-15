#pragma once

namespace sf 
{

class BoatSprite : public sf::Sprite, public sf::MoveDirectionCommandReceiver
{
public:
	BoatSprite() = default;
	~BoatSprite() = default;
	
	void execute() override;

	//kiszamolja, hogy melyik iranyban mekkora sebesseggel kene mennie
	void moveDir(glm::vec2 dir) override;
	void step();

	void SetVelocity(glm::vec2 vel) { vel_ = vel; }
	void SetAcceleration(float acc) { acc_ = acc; }

protected:
	int currentVelX_ = 0; //aktualis sebesseg x-re
	int currentVelY_ = 0; //aktualis sebess y-ra
	glm::vec2 vel_; //jatek soran a max sebesseg
	float acc_;		//gyorsulas	
};

}

