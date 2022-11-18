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
class Command
{
public:
	Command(sf::CommandReceiver* receiver, sf::CommandTypes commandType) : receiver_(receiver), commandType_(commandType) {}
	Command(Command&& command);
	virtual ~Command() {};
	virtual bool execute() = 0;
protected:
	sf::CommandReceiver* receiver_;
	sf::CommandTypes commandType_;
};

class MoveCommand : public Command
{
public:
	using Command::Command;

	bool execute() override;
};
}
