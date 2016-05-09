/*
 * Bonus.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_BONUS_H_
#define SRC_BONUS_H_

#include "Engine.h"

namespace GAME{

//abstract extra bonus object. Provides player with 10 extra points.
class Bonus {
public:
	Bonus();
	float x; // X Coordinate of the Object.
	float y; // Y Coordinate of the Object.
	float w; // Width of the Object.
	float h; // Height of the Object.
	int lastTime; // Contains the last timevalue at which the animation was rendered.
	int state;  // which state the picture of the animation is in.
	virtual ~Bonus();
	virtual void visualize(Engine* e, int gameRate) = 0; // Render the bonus to the screen.
};

}

#endif /* SRC_BONUS_H_ */
