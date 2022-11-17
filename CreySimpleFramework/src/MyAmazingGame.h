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
	const glm::vec3 color = { 0.0f, 0.0f, 0.0f };
	const glm::vec2 velHornet = { 2.0f, 2.0f };
	glm::vec2 basePos_;
	sf::Grid* grid_;
	sf::BoatActor* boat_;
	std::list < sf::Actor* > actors_;
	sf::Sprite spBackGround_;
};