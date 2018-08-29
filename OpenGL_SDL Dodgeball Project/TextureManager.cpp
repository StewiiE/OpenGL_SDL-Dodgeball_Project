#include <SDL.h>
#include <iostream>
#include <string.h>
#include "TextureManager.h"

using namespace::std;

TextureManager * TextureManager::mInstance = 0;

TextureManager::TextureManager()
{

}


TextureManager * TextureManager::GetInstance()
{
	if (!mInstance) 
	{
		mInstance = new TextureManager();
	}
	return mInstance;
}

void LoadTexture(string texturePath, int width, int height)
{
}

void BindTexture(string name)
{

}