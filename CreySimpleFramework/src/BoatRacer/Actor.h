#pragma once

namespace sf
{
enum ActorType {
	Obstacle,
	Ship,
	Treasure
};

class Actor : virtual public sf::CommandReceiver
{
public:
	Actor() : sf::CommandReceiver() { spSprite_ = std::make_unique<sf::Sprite>(); }
	~Actor() = default;

	Sprite* getSprite() { return spSprite_.get(); }

	void setAngle( const float iAngleInDegrees );
	float getAngle() const;

	void setActorType( sf::ActorType actorType );
	sf::ActorType getActorType() const;

	void setType( const sf::u8 type );
	sf::u8 getType() const;

	void setWidth( const sf::u8 width );
	sf::u8 getWidth() const;

	void setHeight( const sf::u8 height );
	sf::u8 getHeight() const;

	void setPosition( const glm::vec2 iPosition );
	glm::vec2 getPosition() const;

	void render();

protected:
	std::unique_ptr<sf::Sprite> spSprite_;
	glm::vec2 vPosition_;
	sf::u8 nWidth_;
	sf::u8 nHeight_;
	sf::u8 nType_;	//used in MyAmazingGame pre- and postinit for texture loading
	sf::ActorType actorType_;
	float nAngle_ = 0.0f; // degrees
};
}

