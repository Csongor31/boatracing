#include "Actor.h"

namespace sf
{
void Actor::setAngle(const float nAngleInDegrees)
{
	nAngle_ = nAngleInDegrees;
}

float Actor::getAngle() const
{
	return nAngle_;
}

void Actor::setActorType(sf::ActorType actorType)
{
	actorType_ = actorType;
}

sf::ActorType Actor::getActorType() const
{
	return actorType_;
}

void Actor::setType(const sf::u8 nType)
{
	nType_ = nType;
}

sf::u8 Actor::getType() const
{
	return nType_;
}

void Actor::setWidth(const sf::u8 nWidth)
{
	nWidth_ = nWidth;
}

sf::u8 Actor::getWidth() const
{
	return nWidth_;
}

void Actor::setHeight(const sf::u8 nHeight)
{
	nHeight_ = nHeight;
}

sf::u8 Actor::getHeight() const
{
	return nHeight_;
}
void Actor::setPosition(const glm::vec2 vPosition)
{
	vPosition_ = vPosition;
}

glm::vec2 Actor::getPosition() const
{
	return vPosition_;
}

void Actor::render()
{
	spSprite_->setAngle(nAngle_);
	spSprite_->setPosition(vPosition_);
	spSprite_->render();
}
}