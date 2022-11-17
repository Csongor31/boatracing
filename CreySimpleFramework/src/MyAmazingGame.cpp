#include "MyAmazingGame.h"


static std::vector< std::vector< sf::u8 > > vMapGrid{
{ 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0 },
{ 0, 3, 4, 0, 5, 0, 0, 0, 5, 0, 0, 3, 4, 0, 5, 5, 0, 0, 5, 0 },
{ 0, 1, 2, 0, 5, 0, 0, 0, 5, 0, 0, 1, 2, 0, 5, 0, 3, 4, 5, 0 },
{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 5, 5 },
{ 5, 0, 3, 4, 0, 5, 0, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0, 5, 5 },
{ 5, 0, 1, 2, 0, 5, 0, 6, 5, 0, 3, 4, 0, 5, 0, 5, 5, 5, 0, 5 },
{ 5, 0, 0, 0, 0, 5, 5, 5, 5, 0, 1, 2, 0, 5, 0, 0, 0, 0, 0, 5 },
{ 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5 },
{ 5, 0, 0, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 3, 4, 0, 0, 5, 5 },
{ 5, 0, 0, 5, 0, 3, 4, 0, 5, 0, 0, 0, 0, 5, 1, 2, 0, 0, 5, 5 },
{ 5, 0, 0, 5, 0, 1, 2, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 5 },
{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0 }
};

MyAmazingGame::~MyAmazingGame() 
{ 
	if (grid_) delete grid_; 
	if (boat_) delete boat_; 
	
	while (actors_.empty())
	{
		delete actors_.front();
		actors_.pop_front();
	}
}

void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );

	grid_ = new sf::Grid(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight(), 64, 64);

	boat_ = new sf::BoatActor();
	boat_->setWidth(65);
	boat_->setWidth(105);
	boat_->setAngle(45.f);
	boat_->setAcceleration(5);
	boat_->setMaxSpeed(40);
	boat_->setTurnSpeed(10);
	boat_->setActorType(sf::ActorType::Ship);

	sf::u8 mapGridHeight = vMapGrid.size();
	sf::u8 mapGridWidth = vMapGrid[0].size();
	for ( sf::u8 nRow = 0; nRow < mapGridHeight; ++nRow )
	{
		for ( sf::u8 nTile = 0; nTile < mapGridWidth; ++nTile)
		{
			if ( vMapGrid[nRow][nTile] > 0 && vMapGrid[nRow][nTile] < 6 )
			{
				sf::Actor* actor = new sf::Actor();
				actor->setType(vMapGrid[nRow][nTile]);
				actor->setHeight(64);
				actor->setWidth(64);
				glm::vec2 pos = glm::vec2(nTile * 64 + 32, nRow * 64 + 32);
				actor->setPosition(pos);
				actor->setActorType(vMapGrid[nRow][nTile] == 5 ? sf::ActorType::Treasure : sf::ActorType::Obstacle);
				grid_->addActorToCell(actor);
				actors_.push_back(actor);
			}

			if (vMapGrid[nRow][nTile] == 6)
			{
				boat_->setPosition(glm::vec2(nTile * 64, nRow * 64));
			}
		}
	}
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	for (auto actor : actors_)
	{
		std::string sTextureTag = actor->getType() < 5 ? "tile" + std::to_string(actor->getType()) : "treasurechest" ;
		actor->getSprite()->setTexture(iFramework.getTextureManager().getTexture( sTextureTag.c_str() ));
	}
	boat_->getSprite()->setTexture( iFramework.getTextureManager().getTexture( "ship" ) );
	
	/*spBoat2_ = new sf::BoatSprite();
	spBoat2_->setPlayer(false);
	spBoat2_->setTexture(iFramework.getTextureManager().getTexture("hornet"));
	spBoat2_->setAngle(45.f);
	spBoat2_->setAcceleration(8);
	spBoat2_->setMaxSpeed(40);
	spBoat2_->setTurnSpeed(5);*/

	basePos_ = { iFramework.getWindow().getWindowWidth() / 2, iFramework.getWindow().getWindowHeight() / 2 };
	spBackGround_.setTexture(iFramework.getTextureManager().getTexture("background"));
	spBackGround_.setPosition(basePos_);

}

void MyAmazingGame::step( sf::Framework< MyAmazingGame >& iFramework )
{
	glClearColor( color.r, color.g, color.b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	{
		sf::Command* command = iFramework.getInputManager().handleInput(boat_);
		if (command)
		{
			command->execute();

			delete command;
		}
	}
	/*{
		sf::Command* command = iFramework.getInputManager().handleInput(spBoat2_);
		if (command)
		{
			command->execute();

			delete command;
		}
	}*/

	boat_->step(grid_);
	spBackGround_.render();

	for (auto actor : actors_)
	{
		actor->render();
	}

	boat_->render();
}