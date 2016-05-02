/*
 * Window.h
 *
 *  Created on: Feb 26, 2016
 *      Author: wouter
 */

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include "SDL2/SDL.h"
#include <iostream>
#include <string>
#include <vector>

namespace GAME{


//abstract engine object
class Engine {
public:
	Engine();
	float width; // width of resolution.
	float height; // height of resolution.
	bool stop;
	int fontSmallSize;
	int fontLargeSize;
	virtual ~Engine();
	virtual int newWindow(int width, int height) = 0; //create a new SDL window. Parameters are for it's size.
	virtual void loadFonts() = 0;
	virtual void preloadSounds() = 0; //search for all sounds in the Sounds folder and load them into memory ready to be used.
	virtual void preloadTextures() = 0; //search for all textures in the Textures folder and load them into memory ready to be used.
	virtual Uint32 getMillis() = 0; //get current time since start of SDL initialization.
	virtual void logError(std::ostream &os, const std::string &msg) = 0; //Console print function to print out SDL errors.
	virtual void increaseResolution() = 0;
	virtual void decreaseResolution() = 0;
	virtual std::string Poll() = 0; //search the buffer for what key is possibly being pressed and return it.
	virtual void playMusic(const std::string &file, int times) = 0; //load a sound from the memory and play it.
	virtual void playSound(const std::string &file, int times) = 0; //load a sound effect from the memory and play it.
	virtual void renderText(const std::string &message, float x, float y, Uint8 color[], int size, std::string outline) = 0;
	virtual void renderTexture(const std::string &file, float x, float y, float w, float h, bool flip) = 0; //load a texture from the memory and render it.
	virtual void renderTextureTransformed(const std::string &file, float x, float y,float w, float h,bool flip) = 0;
	virtual Uint32 renderTextureAnimated(const std::string &file,const std::string &extention, float x, float y, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed) = 0;//load a texture (from an animated series) from memory and render it.
	virtual Uint32 renderTextureAnimatedTiled(const std::string &file,const std::string &extention, float x, float y, float totalw, float totalh, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed) = 0;//load a texture (from an animated series) from memory and render it for a tiled animation.
	virtual void getSize(const std::string &file, float x, float y, float *w, float *h) = 0; //get the size(width and height) of a image and save it in the w and h pointers of the object.
	virtual void clearFrame() = 0; // clear the renderer.
	virtual void renderFrame() = 0;// render the rendered textures out.
	std::vector<float> transform(float x, float y, float w, float h);
	std::vector<float> transformSize(float w, float h);
};

}
#endif /* SRC_WINDOW_H_ */
