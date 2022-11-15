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

//commandokat lehet neki adni, playert is ezen keresztul tartjuk szamon
class CommandReceiver 
{
public:
	void SetAction(sf::CommandTypes currentAction) { currentAction_ = currentAction; }
	bool GetPlayer() { return player_; }
	virtual void execute() = 0;

protected:
	CommandTypes currentAction_ = CommandTypes::NOCOMMAND;
	bool player_ = true;
};

class MoveDirectionCommandReceiver : public CommandReceiver
{
public:
	virtual void execute() {

		float x = currentAction_ & sf::CommandTypes::RIGHT ? 1.f : currentAction_ & sf::CommandTypes::LEFT ? -1.f : 0.f;
		float y = currentAction_ & sf::CommandTypes::UP ? 1.f : currentAction_ & sf::CommandTypes::DOWN ? -1.f : 0.f;

		moveDir( glm::vec2(x, y) );
	}
	virtual void moveDir(glm::vec2 direction) = 0;
};

}