#pragma once

class MyAmazingGame
{
public:
	MyAmazingGame() = default;
	~MyAmazingGame() = default;

public:
	void preInit( sf::Framework< MyAmazingGame >& iFramework );
	void postInit( sf::Framework< MyAmazingGame >& iFramework );
	void step( sf::Framework< MyAmazingGame >& iFramework );

private:
	const glm::vec3 color = { 0.0f, 0.0f, 0.0f };
	const glm::vec2 velHornet = { 2.0f, 2.0f };
	glm::vec2 basePos_;
	sf::Sprite spHornet_;
	sf::Sprite spLayer01_;
	sf::Sprite spLayer02_;
	sf::Sprite spLayer03_;
	sf::Sprite spLayer04_;
	sf::Sprite spLayer05_;
	sf::Sprite spRotatingObject_;
	sf::Sprite spBoom_;
};