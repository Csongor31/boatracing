#pragma once

namespace sf
{
static sf::u8 nextId_ = 0;

class CommandReceiver 
{
public:
	CommandReceiver() { id_ = (++nextId_);  }
	virtual ~CommandReceiver() {};
	bool operator==( const CommandReceiver& rhs ) { return (*this).getId() == rhs.getId(); }

	sf::u8 getId() const { return id_; }

protected:
	sf::u8 id_;
};

class MoveDirectionCommandReceiver : virtual public CommandReceiver
{
public:
	virtual void moveDir(sf::s8 x, sf::s8 y) = 0;
};

}