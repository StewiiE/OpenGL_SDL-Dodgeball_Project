#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "Texture.h"
#include <map>

using namespace ::std;

class TextureManager
{
private:
	static TextureManager * mInstance;
	map<string, Texture2D*> mTextures;
	TextureManager();


public:
	static TextureManager * GetInstance();
	void LoadTexture(string texturePath, int width, int height);
	void BindTexture(string name);
};


#endif //_TEXTUREMANAGER_H