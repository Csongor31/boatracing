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
{ 5, 0, 7, 5, 0, 3, 4, 0, 5, 0, 0, 0, 0, 5, 1, 2, 0, 0, 5, 5 },
{ 5, 0, 0, 5, 0, 1, 2, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 5 },
{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0 }
};

MyAmazingGame::~MyAmazingGame() 
{ 
	if (gMapGrid_) delete gMapGrid_; 
	if (baBoat_) delete baBoat_; 
	if (baBoatSec_) delete baBoatSec_;
	while (lActors_.empty())
	{
		delete lActors_.front();
		lActors_.pop_front();
	}
}

void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );

	gMapGrid_ = new sf::Grid(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight(), 64, 64);

	baBoat_ = new sf::BoatActor(true);
	baBoat_->setHeight(37);
	baBoat_->setWidth(64);
	baBoat_->setAngle(45.f);
	baBoat_->setAcceleration(5);
	baBoat_->setMaxSpeed(40);
	baBoat_->setTurnSpeed(10);
	baBoat_->setActorType(sf::ActorType::Ship);

	if (bTwoPlayer_)
	{
		baBoatSec_ = new sf::BoatActor(false);
		baBoatSec_->setHeight(37);
		baBoatSec_->setWidth(64);
		baBoatSec_->setAngle(-45.f);
		baBoatSec_->setAcceleration(5);
		baBoatSec_->setMaxSpeed(40);
		baBoatSec_->setTurnSpeed(10);
		baBoatSec_->setActorType(sf::ActorType::Ship);
	}

	size_t nMapGridHeight = vMapGrid.size();
	size_t nMapGridWidth = vMapGrid[0].size();
	for ( sf::u8 nRow = 0; nRow < nMapGridHeight; ++nRow )
	{
		for ( sf::u8 nTile = 0; nTile < nMapGridWidth; ++nTile)
		{
			if ( vMapGrid[nRow][nTile] > 0 && vMapGrid[nRow][nTile] < 6 )
			{
				sf::Actor* aActor = new sf::Actor();
				aActor->setType(vMapGrid[nRow][nTile]);
				aActor->setHeight(vMapGrid[nRow][nTile] == 5 ? 32 : 64);
				aActor->setWidth(vMapGrid[nRow][nTile] == 5 ? 32 : 64);
				glm::vec2 vPos = glm::vec2(nTile * 64 + 32, nRow * 64 + 32);
				aActor->setPosition(vPos);
				aActor->setActorType(vMapGrid[nRow][nTile] == 5 ? sf::ActorType::Treasure : sf::ActorType::Obstacle);
				gMapGrid_->addActorToCell(aActor);
				lActors_.push_back(aActor);
			}

			if (vMapGrid[nRow][nTile] == 6)
			{
				baBoat_->setPosition(glm::vec2(nTile * 64, nRow * 64));
			}

			if ( bTwoPlayer_ && vMapGrid[nRow][nTile] == 7)
			{
				baBoatSec_->setPosition(glm::vec2(nTile * 64, nRow * 64));
			}
		}
	}
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	for (auto aActor : lActors_)
	{
		std::string sTextureTag = aActor->getType() < 5 ? "tile" + std::to_string(aActor->getType()) : "treasurechest" ;
		aActor->getSprite()->setTexture(iFramework.getTextureManager().getTexture( sTextureTag.c_str() ));
	}
	baBoat_->getSprite()->setTexture( iFramework.getTextureManager().getTexture( "ship" ) );
	
	if (bTwoPlayer_)
	{
		baBoatSec_->getSprite()->setTexture(iFramework.getTextureManager().getTexture("ship2"));
	}
	spBackGround_.setTexture(iFramework.getTextureManager().getTexture("background"));
	spBackGround_.setPosition({ iFramework.getWindow().getWindowWidth() / 2, iFramework.getWindow().getWindowHeight() / 2 });
}

void MyAmazingGame::step( sf::Framework< MyAmazingGame >& iFramework )
{
	//glClearColor( color.r, color.g, color.b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	{
		sf::Command* command = iFramework.getInputManager().handleInput(baBoat_, baBoat_->getPlayer());
		if (command)
		{
			command->execute();
			delete command;
		}
	}
	sf::Actor* aActor = baBoat_->step(gMapGrid_);

	if (aActor)
	{
		gMapGrid_->removeActor(aActor);
		std::list<sf::Actor*>::iterator findIter = std::find(lActors_.begin(), lActors_.end(), aActor);
		delete (*findIter);
		lActors_.erase(findIter);

		baBoat_->incrementScore();
	}

	if (bTwoPlayer_)
	{
		sf::Command* command = iFramework.getInputManager().handleInput(baBoatSec_, baBoatSec_->getPlayer());
		if (command)
		{
			command->execute();
			delete command;
		}
		aActor = baBoatSec_->step(gMapGrid_);

		if (aActor)
		{
			gMapGrid_->removeActor(aActor);
			std::list<sf::Actor*>::iterator findIter = std::find(lActors_.begin(), lActors_.end(), aActor);
			delete (*findIter);
			lActors_.erase(findIter);

			baBoatSec_->incrementScore();
		}
	}

	spBackGround_.render();

	for (auto aActor : lActors_)
	{
		aActor->render();
	}

	baBoat_->render();

	if (bTwoPlayer_) baBoatSec_->render();
}

void MyAmazingGame::terminate()
{
	sf::u8 nScore = baBoat_->getScore();
	std::string sScore = "Player One Score: " + std::to_string(nScore) + "\n";
	SFLOG(sScore.c_str());

	if (bTwoPlayer_)
	{
		nScore = baBoatSec_->getScore();
		sScore = "Player Two Score: " + std::to_string(nScore) + "\n";
		SFLOG(sScore.c_str());
	}
}