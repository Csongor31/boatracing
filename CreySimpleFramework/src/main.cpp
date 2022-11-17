#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "rapidjson/document.h"

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "CreySimpleFramework/debug.h"
#include "CreySimpleFramework/Types.h"
#include "CreySimpleFramework/static_string.h"
#include "CreySimpleFramework/Utils.h"
#include "CreySimpleFramework/Window.h"

#include "CreySimpleFramework/Texture.cpp"
#include "BoatRacer/CommandReciever.h"
#include "BoatRacer/Command.cpp"
#include "CreySimpleFramework/Sprite.cpp"
#include "BoatRacer/Actor.cpp"
#include "BoatRacer/Grid.cpp"
#include "BoatRacer/BoatActor.cpp"
#include "CreySimpleFramework/TextureLoaderBase.cpp"
#include "CreySimpleFramework/TGATextureLoader.cpp"
#include "CreySimpleFramework/TextureManager.cpp"
#include "CreySimpleFramework/InputManager.cpp"
#include "CreySimpleFramework/Framework.cpp"
#include "MyAmazingGame.cpp"

int main( void )
{
	sf::Framework< MyAmazingGame > framework = {};
	const bool ret = framework.init();
	if ( !ret )
	{
		framework.terminate();
		return -1;
	}
	framework.loop();
	framework.terminate();
	return 0;
}