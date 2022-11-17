#pragma once

class MyAmazingGame
{
public:
	MyAmazingGame() = default;
	~MyAmazingGame() { if (grid_) delete grid_; if (boat_) delete boat_; if (spRotatingObject_) delete spRotatingObject_; if (spBoom_) delete spBoom_; };

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
	sf::Sprite* spRotatingObject_;
	sf::Sprite* spBoom_;
	sf::Sprite spBackGround_;
};