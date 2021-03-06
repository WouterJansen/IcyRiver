/*
 * FrogSDL.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "PenguinSDL.h"

using namespace SDLGAME;

// Penguin object. Its the object that will be the player.
PenguinSDL::PenguinSDL() {
	// TODO Auto-generated constructor stub

}

PenguinSDL::~PenguinSDL() {
	// TODO Auto-generated destructor stub
}

// render the penguin.
void PenguinSDL::visualize(GAME::Engine* e){
	e->getSize("./textures/penguin_forward_water.png",x,y,&w,&h);
	//if the penguin is in the water, use the correct images.
	if(floating == false){
		if(dir == "Up")
			e->renderTexture("./textures/penguin_forward_water.png", x, y, w, h,false);
		if(dir == "Down")
			e->renderTexture("./textures/penguin_aft_water.png", x, y, w, h,false);
		if(dir == "Left")
			e->renderTexture("./textures/penguin_left_water.png", x, y, w, h,false);
		if(dir == "Right")
			e->renderTexture("./textures/penguin_right_water.png", x, y, w, h,false);
	}else{
		if(dir == "Up")
			e->renderTexture("./textures/penguin_forward.png", x, y, w, h,false);
		if(dir == "Down")
			e->renderTexture("./textures/penguin_aft.png", x, y, w, h,false);
		if(dir == "Left")
			e->renderTexture("./textures/penguin_left.png", x, y, w, h,false);
		if(dir == "Right")
			e->renderTexture("./textures/penguin_right.png", x, y, w, h,false);
	}
}
