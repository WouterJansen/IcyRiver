/*
 * Live.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_LIFE_H_
#define SRC_LIFE_H_

#include "Engine.h"

namespace GAME{

//abstract extra bonus object. Provides player with an extra life.
class Life {
public:
	Life();
	float x; // X Coordinate of the Object.
	float y; // Y Coordinate of the Object.
	float w; // Width of the Object.
	float h; // Height of the Object.
	int lastTime; // Contains the last timevalue at which the animation was rendered.
	int state; // which state the picture of the animation is in.
	virtual ~Life();
	virtual void visualize(Engine* e, int gameRate) = 0; // Render the life to the screen.
	virtual void displayLife(Engine* e, float xi, float yi) = 0; // Render the life to the GUI.
};

}

#endif /* SRC_LIFE_H_ */
