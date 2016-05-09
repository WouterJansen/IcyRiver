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

namespace GAME{

// Object of a line containing all obstructions.
class Line {
public:
	Line(float newy, int newtype, float newspeed);
	std::deque<Obstruction*> obstructions; // Deque of obstruction objects.
	float y; // Current height of the line.
	int type; // Type: 0 = obstruction(ice or animal), 1 = floater (log)
	float speed; // Current speed of the line.
	virtual ~Line();
	void vizualize(Engine* e); // rendering the entire line of obstructions.
	void clear(); // Clear the line of obstructions.
	void move(); // Move all obstructions in this line at the speed of the line.
};

}

#endif /* SRC_LINE_H_ */
