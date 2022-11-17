#include "MyAmazingGame.h"

void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	grid_ = new sf::Grid( iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight(), 200, 200 );
	spRotatingObject_ = new sf::Sprite();
	spBoom_ = new sf::Sprite();
	boat_ = new sf::BoatActor();
	boat_->getSprite()->setTexture( iFramework.getTextureManager().getTexture( "ship" ) );
	boat_->setWidth(65);
	boat_->setWidth(105);
	boat_->setAngle(45.f);
	boat_->setAcceleration(8);
	boat_->setMaxSpeed(40);
	boat_->setTurnSpeed(5);
	/*spBoat2_ = new sf::BoatSprite();
	spBoat2_->setPlayer(false);
	spBoat2_->setTexture(iFramework.getTextureManager().getTexture("hornet"));
	spBoat2_->setAngle(45.f);
	spBoat2_->setAcceleration(8);
	spBoat2_->setMaxSpeed(40);
	spBoat2_->setTurnSpeed(5);*/
	spBoom_->setTexture( iFramework.getTextureManager().getTexture( "boom" ), 4, 1 );

	spRotatingObject_->setTexture( iFramework.getTextureManager().getTexture( "hornet" ) );
	spRotatingObject_->setPosition( { 100.0f, 100.0f } );

	basePos_ = { iFramework.getWindow().getWindowWidth() / 2, iFramework.getWindow().getWindowHeight() / 2 };
	boat_->setPosition(basePos_);
	//spBoat2_->setPosition( basePos_ + glm::vec2(100.0f, 0.0f));
	spBoom_->setPosition( basePos_ + glm::vec2( 100.0f, 0.0f ) );

	//grid_->addActorToCell(spRotatingObject_);
	//grid_->addActorToCell(spBoom_);
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
	spRotatingObject_->setAngle( spRotatingObject_->getAngle() + 0.5f );

	static sf::u32 frameCnt = 0;
	++frameCnt;
	spBoom_->setTile( frameCnt / 20 % 4, 0 );

	boat_->render();
	//spBoat2_->render();
	spRotatingObject_->render();
	spBoom_->render();
}