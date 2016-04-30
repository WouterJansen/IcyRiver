/*
 * ObstructorSDL.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "ObstructionSDL.h"

ObstructionSDL::ObstructionSDL() {
}

ObstructionSDL::~ObstructionSDL() {
	// TODO Auto-generated destructor stub
}

void ObstructionSDL::visualize(Engine* e, bool flip){
	e->getSize(variant,x,y,&w,&h);
	e->renderTexture(variant, x, y, w, h,flip);

}

