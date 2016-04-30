/*
 * Bonus.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_BONUS_H_
#define SRC_BONUS_H_

#include "Engine.h"

class Bonus {
public:
	Bonus();
	float x;
	float y;
	float w;
	float h;
	int lastTime;
	int state;
	virtual ~Bonus();
	virtual void visualize(Engine* e, int gameRate) = 0;
};

#endif /* SRC_BONUS_H_ */
