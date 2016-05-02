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
	fontLargeSize = 0;
	fontSmallSize = 0;
	width = 0;
	height = 0;
	stop = false;
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

std::vector<float> Engine::transform(float x, float y, float w, float h){
	std::vector<float> array;
	array.push_back(x*width/100);
	array.push_back(y*height/100);
	array.push_back(w*width/100);
	array.push_back(h*height/100);
	return array;
}

std::vector<float> Engine::transformSize(float w, float h){
	std::vector<float> array;
	array.push_back(((w*100)/width)*width/800);
	array.push_back(((h*100)/height)*height/640);
	return array;
}
