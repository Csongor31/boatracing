#include "MyAmazingGame.h"

void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	spHornet_.setTexture( iFramework.getTextureManager().getTexture( "hornet" ) );
	spLayer01_.setTexture( iFramework.getTextureManager().getTexture( "layer01" ) );
	spLayer02_.setTexture( iFramework.getTextureManager().getTexture( "layer02" ) );
	spLayer03_.setTexture( iFramework.getTextureManager().getTexture( "layer03" ) );
	spLayer04_.setTexture( iFramework.getTextureManager().getTexture( "layer04" ) );
	spLayer05_.setTexture( iFramework.getTextureManager().getTexture( "layer05" ) );
	spBoom_.setTexture( iFramework.getTextureManager().getTexture( "boom" ), 4, 1 );

	spRotatingObject_.setTexture( iFramework.getTextureManager().getTexture( "hornet" ) );
	spRotatingObject_.setPosition( { 100.0f, 100.0f } );

	basePos_ = { iFramework.getWindow().getWindowWidth() / 2, iFramework.getWindow().getWindowHeight() / 2 };
	spHornet_.setPosition( basePos_ );
	spBoom_.setPosition( basePos_ + glm::vec2( 50.0f, 0.0f ) );
}

void MyAmazingGame::step( sf::Framework< MyAmazingGame >& iFramework )
{
	glClearColor( color.r, color.g, color.b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	if ( iFramework.getInputManager().isPressed( "left" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( -velHornet.x, 0.0f ) );
		spHornet_.setRenderFlag( sf::RenderFlag::Flip );
	}
	if (iFramework.getInputManager().isRepeat("left"))
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( -velHornet.x, 0.0f ) );
		spHornet_.setRenderFlag( sf::RenderFlag::Flip );
	}
	if ( iFramework.getInputManager().isPressed( "right" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( velHornet.x, 0.0f ) );
		spHornet_.setRenderFlag( sf::RenderFlag::NoEffect );
	}
	if ( iFramework.getInputManager().isRepeat( "right" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( velHornet.x, 0.0f ) );
		spHornet_.setRenderFlag( sf::RenderFlag::NoEffect );
	}
	if ( iFramework.getInputManager().isPressed( "up" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( 0.0f, velHornet.y ) );
	}
	if ( iFramework.getInputManager().isRepeat( "up" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( 0.0f, velHornet.y ) );
	}
	if ( iFramework.getInputManager().isPressed( "down" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( 0.0f, -velHornet.y ) );
	}
	if ( iFramework.getInputManager().isRepeat( "down" ) )
	{
		spHornet_.setPosition( spHornet_.getPosition() + glm::vec2( 0.0f, -velHornet.y ) );
	}

	static float cnt = 0.0f;
	cnt += 0.05f;
	const float s = std::sinf( cnt );

	spLayer01_.setPosition( { basePos_.x + s  * 20.0f, basePos_.y } );
	spLayer02_.setPosition( { basePos_.x + s  * 40.0f, basePos_.y } );
	spLayer03_.setPosition( { basePos_.x + s  * 55.0f, basePos_.y } );
	spLayer04_.setPosition( { basePos_.x + s  * 75.0f, basePos_.y } );
	spLayer05_.setPosition( { basePos_.x + s  * 110.0f, basePos_.y } );

	spRotatingObject_.setAngle( spRotatingObject_.getAngle() + 0.5f );

	static sf::u32 frameCnt = 0;
	++frameCnt;
	spBoom_.setTile( frameCnt / 20 % 4, 0 );

	spLayer01_.render();
	spLayer02_.render();
	spLayer03_.render();
	spLayer04_.render();
	spHornet_.render();
	spLayer05_.render();
	spRotatingObject_.render();
	spBoom_.render();
}