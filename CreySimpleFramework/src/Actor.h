#pragma once

namespace sf
{
class Actor : virtual public sf::CommandReceiver
{
public:
	Actor() { sprite_ = std::make_unique<sf::Sprite>(); }
	Sprite* getSprite() { return sprite_.get(); }
	void setAngle(const float iAngleInDegrees);
	float getAngle() const;
	void setWidth(const sf::u8 width );
	float getWidth() const;
	void setHeight(const sf::u8 height);
	float getHeight() const;
	void setPosition(const glm::vec2 iPosition);
	glm::vec2 getPosition() const;
	void render();

protected:
	std::unique_ptr<sf::Sprite> sprite_;
	glm::vec2 position_;
	sf::u8 width_;
	sf::u8 height_;
	float angle_ = 0.0f; // degrees
};
}

