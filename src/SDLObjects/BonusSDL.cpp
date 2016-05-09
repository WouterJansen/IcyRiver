/*
 * BonusSDL.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "BonusSDL.h"

using namespace SDLGAME;

//Bonus object. Provides player with 10 extra points.
BonusSDL::BonusSDL() {
	// TODO Auto-generated constructor stub

}

BonusSDL::~BonusSDL() {
	// TODO Auto-generated destructor stub
}

// Render the bonus to the screen.
void BonusSDL::visualize(GAME::Engine* e, int gameRate){
	e->getSize("./textures/bonus_1.png",x,y,&w,&h);
	lastTime = e->renderTextureAnimated("./textures/bonus_",".png", x, y, w, h, lastTime,&state, gameRate, 4, 10);
}
