/*
 * ObstructionLine.h
 *
 *  Created on: 23-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_LINE_H_
#define SRC_LINE_H_

#include "Engine.h"
#include "Obstruction.h"
#include "Background.h"
#include <deque>


class Line {
public:
	Line(float newy, int newtype, float newspeed);
	std::deque<Obstruction*> obstructions;
	float y;
	int type;
	float speed;
	virtual ~Line();
	void vizualize(Engine* e);
	void clear();
	void move();
};

#endif /* SRC_LINE_H_ */
