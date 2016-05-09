/*
 * Bonus.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "Bonus.h"

using namespace GAME;

//abstract extra bonus object. Provides player with 10 extra points.
Bonus::Bonus() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	state = 1;
	lastTime = 0;
}

Bonus::~Bonus() {
	// TODO Auto-generated destructor stub
}


