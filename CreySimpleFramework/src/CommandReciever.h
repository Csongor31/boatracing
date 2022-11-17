#pragma once

namespace sf
{
//commandokat lehet neki adni, playert is ezen keresztul tartjuk szamon
class CommandReceiver 
{
public:
	virtual ~CommandReceiver() {};
	bool GetPlayer() { return player_; }
	void setPlayer(bool bPlayer) { player_ = bPlayer; }
	sf::u8 getId() { return id_; }

protected:
	bool player_ = true;
	sf::u8 id_;
};

class MoveDirectionCommandReceiver : virtual public CommandReceiver
{
public:
	virtual void moveDir(sf::s8 x, sf::s8 y) = 0;
};

}