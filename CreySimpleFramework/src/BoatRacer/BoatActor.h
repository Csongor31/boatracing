#pragma once

namespace sf
{
class PlayerControl
{
public:
	PlayerControl(bool bPlayerOne) : playerOne_(bPlayerOne) {}
	bool getPlayer() { return playerOne_; }

protected:
	bool playerOne_ = true;
};

class BoatActor : public sf::Actor, virtual public sf::MoveDirectionCommandReceiver, public PlayerControl
{
public:
	BoatActor() = default;
	BoatActor(bool bPlayerOne) : sf::Actor(), PlayerControl(bPlayerOne) {};
	~BoatActor() = default;

	//kiszamolja, hogy melyik iranyban kene mennie
	void moveDir(sf::s8 x, sf::s8 y) override;
	sf::Actor* step(sf::Grid * grid);

	void setMaxSpeed(sf::s8 maxSpeed) { maxSpeed_ = maxSpeed; }
	void setAcceleration(sf::s8 acceleration) { acceleration_ = acceleration; }
	void setTurnSpeed(sf::s8 turnSpeed) { turnSpeed_ = turnSpeed; }

protected:
	sf::s8 currentVelX_ = 0; //current velocity on x
	sf::s8 currentVelY_ = 0; //current velocity on y
	sf::s8 acceleration_; //acceleration step
	sf::s8 maxSpeed_; //max velocity
	sf::s8 turnSpeed_; // how fast the boat turns
};
}

