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
	spBoat_ = new sf::BoatSprite();
	spBoat_->setTexture( iFramework.getTextureManager().getTexture( "hornet" ) );
	spBoat_->setAngle(45.f);
	spBoat_->setAcceleration(8);
	spBoat_->setMaxSpeed(40);
	spBoat_->setTurnSpeed(5);
	/*spBoat2_ = new sf::BoatSprite();
	spBoat2_->setPlayer(false);
	spBoat2_->setTexture(iFramework.getTextureManager().getTexture("hornet"));
	spBoat2_->setAngle(45.f);
	spBoat2_->setAcceleration(8);
	spBoat2_->setMaxSpeed(40);
	spBoat2_->setTurnSpeed(5);*/
	spLayer01_.setTexture( iFramework.getTextureManager().getTexture( "layer01" ) );
	spLayer02_.setTexture( iFramework.getTextureManager().getTexture( "layer02" ) );
	spLayer03_.setTexture( iFramework.getTextureManager().getTexture( "layer03" ) );
	spLayer04_.setTexture( iFramework.getTextureManager().getTexture( "layer04" ) );
	spLayer05_.setTexture( iFramework.getTextureManager().getTexture( "layer05" ) );
	spBoom_->setTexture( iFramework.getTextureManager().getTexture( "boom" ), 4, 1 );

	spRotatingObject_->setTexture( iFramework.getTextureManager().getTexture( "hornet" ) );
	spRotatingObject_->setPosition( { 100.0f, 100.0f } );

	basePos_ = { iFramework.getWindow().getWindowWidth() / 2, iFramework.getWindow().getWindowHeight() / 2 };
	spBoat_->setPosition(basePos_);
	//spBoat2_->setPosition( basePos_ + glm::vec2(100.0f, 0.0f));
	spBoom_->setPosition( basePos_ + glm::vec2( 100.0f, 0.0f ) );

	grid_->addSpriteToCell(spRotatingObject_);
	grid_->addSpriteToCell(spBoom_);
}

void MyAmazingGame::step( sf::Framework< MyAmazingGame >& iFramework )
{
	glClearColor( color.r, color.g, color.b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	{
		sf::Command* command = iFramework.getInputManager().handleInput(spBoat_);
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

	spBoat_->step(grid_);
	//spBoat2_->step(grid_);


	//static float cnt = 0.0f;
	//cnt += 0.05f;
	const float s = 1.f;

	spLayer01_.setPosition( { basePos_.x + s  * 20.0f, basePos_.y } );
	spLayer02_.setPosition( { basePos_.x + s  * 40.0f, basePos_.y } );
	spLayer03_.setPosition( { basePos_.x + s  * 55.0f, basePos_.y } );
	spLayer04_.setPosition( { basePos_.x + s  * 75.0f, basePos_.y } );
	spLayer05_.setPosition( { basePos_.x + s  * 110.0f, basePos_.y } );

	spRotatingObject_->setAngle( spRotatingObject_->getAngle() + 0.5f );

	static sf::u32 frameCnt = 0;
	++frameCnt;
	spBoom_->setTile( frameCnt / 20 % 4, 0 );

	spLayer01_.render();
	spLayer02_.render();
	spLayer03_.render();
	spLayer04_.render();
	spBoat_->render();
	//spBoat2_->render();
	spLayer05_.render();
	spRotatingObject_->render();
	spBoom_->render();
}