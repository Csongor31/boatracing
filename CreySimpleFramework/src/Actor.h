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
	Actor() { sprite_ = std::make_unique<sf::Sprite>(); }

	Sprite* getSprite() { return sprite_.get(); }

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
	std::unique_ptr<sf::Sprite> sprite_;
	glm::vec2 position_;
	sf::u8 width_;
	sf::u8 height_;
	sf::u8 type_;
	sf::ActorType actorType_;
	float angle_ = 0.0f; // degrees
};
}

