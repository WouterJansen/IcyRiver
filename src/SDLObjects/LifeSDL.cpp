/*
 * LiveSDL.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "LifeSDL.h"

using namespace SDLGAME;

//Extra bonus object. Provides player with an extra life.
LifeSDL::LifeSDL() {
	// TODO Auto-generated constructor stub

}

LifeSDL::~LifeSDL() {
	// TODO Auto-generated destructor stub
}

// Render the life to the screen.
void LifeSDL::visualize(GAME::Engine* e, int gameRate){
	e->getSize("./textures/life_1.png",x,y,&w,&h);
	lastTime = e->renderTextureAnimated("./textures/life_",".png", x, y, w, h, lastTime,&state, gameRate, 2, 20);
}

// Render the life to the GUI.
void LifeSDL::displayLife(GAME::Engine* e,float xi, float yi){
	e->getSize("./textures/life_1.png",xi,yi,&w,&h);
	e->renderTexture("./textures/life_1.png", xi, yi, w, h,false);
}
