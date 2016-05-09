/*
 * Background.cpp
 *
 *  Created on: 19-mrt.-2016
 *      Author: Wouter
 */

#include "Background.h"

using namespace GAME;

//abstract background object
Background::Background() {
	state = 1;
	lastTime = 0;
	bottomh = 80;
	amountMoveDown = 0;
	startVisible = true;
}

Background::~Background() {
	// TODO Auto-generated destructor stub
}


