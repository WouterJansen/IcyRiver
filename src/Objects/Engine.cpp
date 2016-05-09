/*
 * Window.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: wouter
 */

#include "Engine.h"

using namespace GAME;

//abstract engine object
Engine::Engine() {
	fontSmallSize = 6.25; // Standard size of the small font.
	fontLargeSize = 10; // Standard size of the large font.
	width = 0;
	height = 0;
	stop = false;
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

// Transform the coordinates from the game to the pixel values needed for rendering.
std::vector<float> Engine::transform(float x, float y, float w, float h){
	std::vector<float> array;
	array.push_back(x*width/100);
	array.push_back(y*height/100);
	array.push_back(w*width/100);
	array.push_back(h*height/100);
	return array;
}

// Transform the pixel values of the height and width of a texture to the game's coordinate system.
std::vector<float> Engine::transformSize(float w, float h){
	std::vector<float> array;
	array.push_back(((w*100)/width)*width/800); //working a set aspect ratio of 800x640 as standard resolution.
	array.push_back(((h*100)/height)*height/640);
	return array;
}
