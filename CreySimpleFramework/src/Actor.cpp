#include "Actor.h"

namespace sf
{
void Actor::setAngle(const float iAngleInDegrees)
{
	angle_ = iAngleInDegrees;
}

float Actor::getAngle() const
{
	return angle_;
}

void Actor::setWidth(const sf::u8 width)
{
	width_ = width;
}

float Actor::getWidth() const
{
	return width_;
}

void Actor::setHeight(const sf::u8 height)
{
	height_ = height;
}

float Actor::getHeight() const
{
	return height_;
}
void Actor::setPosition(const glm::vec2 iPosition)
{
	position_ = iPosition;
}

glm::vec2 Actor::getPosition() const
{
	return position_;
}

void Actor::render()
{
	sprite_->setAngle(angle_);
	sprite_->setPosition(position_);
	sprite_->render();
}
}