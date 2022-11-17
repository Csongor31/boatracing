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

private:
	glm::vec2 basePos_;
	sf::Grid* grid_;
	sf::BoatActor* boat_ = nullptr;
	sf::BoatActor* boat2_ = nullptr;
	std::list < sf::Actor* > actors_;
	sf::Sprite spBackGround_;
	bool bTwoPlayer_ = true;
};