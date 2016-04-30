/*
 * BonusSDL.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "BonusSDL.h"

BonusSDL::BonusSDL() {
	// TODO Auto-generated constructor stub

}

BonusSDL::~BonusSDL() {
	// TODO Auto-generated destructor stub
}

void BonusSDL::visualize(Engine* e, int gameRate){

	e->getSize("./textures/bonus_1.png",x,y,&w,&h);
	lastTime = e->renderTextureAnimated("./textures/bonus_",".png", x, y, w, h, lastTime,&state, gameRate, 4, 10);
}
