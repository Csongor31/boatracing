#pragma once

namespace sf 
{
enum CommandTypes
{
	NOCOMMAND = 0,
	LEFT = 1 << 0,
	RIGHT = 1 << 1,
	UP = 1 << 2,
	DOWN = 1 << 3,
	MOVE = LEFT | RIGHT | UP | DOWN,
};

class CommandReceiver;

//Command class, segit multiplayerben es replayben
class Command
{
public:
	Command(sf::CommandReceiver* receiver, sf::CommandTypes commandType) : receiver_(receiver), commandType_(commandType) {}
	virtual ~Command() {};
	virtual bool execute() = 0;
protected:
	sf::CommandReceiver* receiver_;
	sf::CommandTypes commandType_;
};

//move command, iranyt adva elmegy a receiver abba az iranyba
class MoveCommand : public Command
{
public:
	using Command::Command;

	bool execute()
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
};
}
