#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "rapidjson/document.h"

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "debug.h"
#include "Types.h"
#include "static_string.h"
#include "Utils.h"
#include "Window.h"

#include "Texture.cpp"
#include "CommandReciever.h"
#include "Sprite.cpp"
#include "BoatSprite.cpp"
#include "Command.h"
#include "TextureLoaderBase.cpp"
#include "TGATextureLoader.cpp"
#include "TextureManager.cpp"
#include "InputManager.cpp"
#include "Framework.cpp"
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