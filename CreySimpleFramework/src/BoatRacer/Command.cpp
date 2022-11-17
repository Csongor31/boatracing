#include "Command.h"

namespace sf
{
bool MoveCommand::execute()
{
	sf::MoveDirectionCommandReceiver* receiver = dynamic_cast<sf::MoveDirectionCommandReceiver*>(receiver_);
	if (receiver)
	{
		int x = commandType_ & sf::CommandTypes::RIGHT && !(commandType_ & sf::CommandTypes::LEFT)
			? 1 : commandType_ & sf::CommandTypes::LEFT && !(commandType_ & sf::CommandTypes::RIGHT)
			? -1 : 0;
		int y = commandType_ & sf::CommandTypes::UP && !(commandType_ & sf::CommandTypes::DOWN)
			? 1 : commandType_ & sf::CommandTypes::DOWN && !(commandType_ & sf::CommandTypes::UP)
			? -1 : 0;
		receiver->moveDir(x, y);
		return true;
	}
	return false;
}
}