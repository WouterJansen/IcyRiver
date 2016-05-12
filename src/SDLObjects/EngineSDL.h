/*
 * WindowSDL.h
 *
 *  Created on: Feb 26, 2016
 *      Author: wouter
 */

#ifndef SRC_WINDOWSDL_H_
#define SRC_WINDOWSDL_H_

#include "../Objects/Engine.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <map>
#include "wtypes.h"

namespace SDLGAME{

//engine object that takes care of all rendering.
class EngineSDL : public GAME::Engine{
public:
	EngineSDL();
	virtual ~EngineSDL();
	SDL_Renderer* ren; // variable on the renderer.
	SDL_Window* win; // variable of the window.
	TTF_Font* fontSmall; // variable for the small font
	TTF_Font* fontLarge; // variable for the large font
	std::map<std::string,Mix_Chunk*> chunkBuf; //buffer where all chunk sound effects files are saved. They are key-mapped by filename.
	std::map<std::string,Mix_Music*> musicBuf; //buffer where all music files are saved. They are key-mapped by filename.
	std::map<std::string,SDL_Texture*> texBuf; //buffer where all textures are saved. They are key-mapped by filename.
	int newWindow(int width, int height); //create a new SDL window. Parameters are for it's size.
	void loadFonts(); // Load all fonts in the right size.
	void preloadSounds();//search for all sounds in the Sounds folder and load them into memory ready to be used.
	void preloadTextures();//search for all textures in the Textures folder and load them into memory ready to be used.
	Uint32 getMillis(); //get current time since start of SDL initialization.
	void logError(std::ostream &os, const std::string &msg); //Console print function to print out SDL errors.
	void increaseResolution(); // Increase the window resolution.
	void decreaseResolution(); // decrease the window resolution.
	std::string Poll(); //search the buffer for what key is possibly being pressed and return it.
	void playMusic(const std::string &file, int times); //load a music sound from the memory and play it.
	void playSound(const std::string &file, int times); //load a sound effect from the memory and play it.
	void renderText(const std::string &message, float x, float y, Uint8 color[], int size, std::string outline);
	void renderTexture(const std::string &file, float x, float y, float w, float h, bool flip); //load a texture from the memory and render it.
	Uint32 renderTextureAnimated(const std::string &file,const std::string &extention, float x, float y, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed); //load a texture (from an animated series) from memory and render it.
	Uint32 renderTextureAnimatedTiled(const std::string &file,const std::string &extention, float x, float y, float totalw, float totalh, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed); //load a texture (from an animated series) from memory and render it for a tiled animation.
	void getSize(const std::string &file, float x, float y,float *w, float *h); //get the size(width and height) of a image and save it in the w and h pointers of the object.
	void clearFrame(); //clear the renderer.
	void renderFrame();// render the rendered textures out.
};

}

#endif /* SRC_WINDOWSDL_H_ */
