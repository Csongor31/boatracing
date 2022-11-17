#pragma once

namespace sf
{

class PlayerControl
{
public:
	PlayerControl(bool bPlayerOne) : bPlayerOne_(bPlayerOne) {}
	bool getPlayer() const;
	sf::u8 getScore() const;
	void incrementScore();

protected:
	bool bPlayerOne_ = true;
	sf::u8 nScore_ = 0;
};

class BoatActor : public sf::Actor, public sf::MoveDirectionCommandReceiver, public PlayerControl
{
public:
	BoatActor() = default;
	BoatActor(bool bPlayerOne) : sf::Actor(), PlayerControl(bPlayerOne) {};
	~BoatActor() = default;

	//kiszamolja, hogy melyik iranyban kene mennie
	void moveDir(sf::s8 x, sf::s8 y) override;
	sf::Actor* step(sf::Grid * grid);

	void setMaxSpeed(sf::s8 maxSpeed);
	void setAcceleration(sf::s8 acceleration);
	void setTurnSpeed(sf::s8 turnSpeed);

protected:
	sf::s8 nCurrentVelX_ = 0; //current velocity on x
	sf::s8 nCurrentVelY_ = 0; //current velocity on y
	sf::s8 nAcceleration_; //acceleration step
	sf::s8 nMaxSpeed_; //max velocity
	sf::s8 nTurnSpeed_; // how fast the boat turns
};
}

