#pragma once

namespace sf 
{
class BoatSprite : public sf::Sprite, public sf::MoveDirectionCommandReceiver
{
public:
	BoatSprite() = default;
	~BoatSprite() = default;
	
	//kiszamolja, hogy melyik iranyban mekkora sebesseggel kene mennie
	void moveDir(sf::s8 x, sf::s8 y) override;
	sf::Command* step(sf::Grid* grid);

	void setMaxSpeed(sf::s8 maxSpeed) { maxSpeed_ = maxSpeed; }
	void setAcceleration(sf::s8 acceleration) { acceleration_ = acceleration; }
	void setTurnSpeed(sf::s8 turnSpeed) { turnSpeed_ = turnSpeed; }

protected:
	sf::s8 currentVelX_ = 0; //aktualis sebesseg x-re, ez max maxSpeed_ lehet
	sf::s8 currentVelY_ = 0; //aktualis sebesseg y-ra
	sf::s8 acceleration_; //framenkenti gyorsulas
	sf::s8 maxSpeed_; //jatek soran a max sebesseg
	sf::s8 turnSpeed_;
};
}

