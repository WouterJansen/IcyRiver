/*
 * Live.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_LIFE_H_
#define SRC_LIFE_H_

#include "Engine.h"

class Life {
public:
	Life();
	float x;
	float y;
	float w;
	float h;
	int lastTime;
	int state;
	virtual ~Life();
	virtual void visualize(Engine* e, int gameRate) = 0;
	virtual void displayLife(Engine* e, float xi, float yi) = 0;
};

#endif /* SRC_LIFE_H_ */
