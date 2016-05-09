/*
 * LiveSDL.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_LIFESDL_H_
#define SRC_LIFESDL_H_

#include "../Objects/Engine.h"
#include "../Objects/Life.h"
#include <iostream>

namespace SDLGAME{

//Extra bonus object. Provides player with an extra life.
class LifeSDL : public GAME::Life {
public:
	LifeSDL();
	virtual ~LifeSDL();
	void visualize(GAME::Engine* e, int gameRate); // Render the life to the screen.
	void displayLife(GAME::Engine* e,float xi, float yi);  // Render the life to the GUI.
};

}

#endif /* SRC_LIFESDL_H_ */
