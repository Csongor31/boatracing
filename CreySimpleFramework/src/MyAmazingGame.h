#pragma once

class MyAmazingGame
{
public:
	MyAmazingGame() = default;
	~MyAmazingGame();

public:
	void preInit( sf::Framework< MyAmazingGame >& iFramework );
	void postInit( sf::Framework< MyAmazingGame >& iFramework );
	void step( sf::Framework< MyAmazingGame >& iFramework );
	void terminate();

private:
	sf::Grid* gMapGrid_;
	sf::BoatActor* baBoat_ = nullptr;
	sf::BoatActor* baBoatSec_ = nullptr;
	std::list < sf::Actor* > lActors_;
	sf::Sprite spBackGround_;
	bool bTwoPlayer_ = true;
};