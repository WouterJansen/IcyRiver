/*
 * Live.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "Life.h"

using namespace GAME;

//abstract extra bonus object. Provides player with an extra life.
Life::Life() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	state = 1;
	lastTime = 0;
}

Life::~Life() {
	// TODO Auto-generated destructor stub
}
