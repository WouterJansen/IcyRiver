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

class LifeSDL : public GAME::Life {
public:
	LifeSDL();
	virtual ~LifeSDL();
	void visualize(GAME::Engine* e, int gameRate);
	void displayLife(GAME::Engine* e,float xi, float yi);
};

}

#endif /* SRC_LIFESDL_H_ */
