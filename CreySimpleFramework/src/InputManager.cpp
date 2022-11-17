#include "InputManager.h"

namespace sf
{

void InputManager::registerInputTag( const sf::InputTag& iInputTag )
{
	inputTags_.push_back( iInputTag );
}

void InputManager::setMousePosition( const glm::vec2& iPos )
{
	mousePos_ = iPos;
}

void InputManager::handleKey( int iKey, int iScancode, int iAction, int iMods )
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag.getKey() == iKey )
		{
			tag.updateAction( iAction );
			break;
		}
	}
}

void InputManager::step()
{
	for ( auto& tag : inputTags_ )
	{
		tag.finalize();
	}
}

const glm::vec2 InputManager::getMousePos() const
{
	return mousePos_;
}

const bool InputManager::isPressed( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isPressed();
		}
	}
	return false;
}

const bool InputManager::isRepeat( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isRepeat();
		}
	}
	return false;
}

const bool InputManager::isReleased( const sf::InputTag& iTag ) const
{
	for ( auto& tag : inputTags_ )
	{
		if ( tag == iTag )
		{
			return tag.isReleased();
		}
	}
	return false;
}

sf::Command* InputManager::handleInput(sf::CommandReceiver* receiver, bool bPlayerOne )
{
	sf::Command* command = nullptr;
	sf::CommandTypes commandType = sf::CommandTypes::NOCOMMAND;

	if (bPlayerOne)
	{
		if ( isPressed("left") || isRepeat("left") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::LEFT);
		}
		if ( isPressed("right") || isRepeat("right") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::RIGHT);
		}
		if ( isPressed("up") || isRepeat("up") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::UP);
		}
		if ( isPressed("down") || isRepeat("down") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::DOWN);
		}
	}
	else
	{
		if ( isPressed("left2") || isRepeat("left2") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::LEFT);
		}
		if ( isPressed("right2") || isRepeat("right2") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::RIGHT);
		}
		if ( isPressed("up2") || isRepeat("up2") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::UP);
		}
		if ( isPressed("down2") || isRepeat("down2") )
		{
			commandType = (sf::CommandTypes)(commandType | sf::CommandTypes::DOWN);
		}
	}

	if (commandType & sf::CommandTypes::MOVE)
	{
		MoveDirectionCommandReceiver* moveReceiver = dynamic_cast<MoveDirectionCommandReceiver*>(receiver);
		if (moveReceiver)
		{
			command = new MoveCommand(moveReceiver, commandType);
		}
	}

	return command;
}

}