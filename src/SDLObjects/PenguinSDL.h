/*
 * FrogSDL.h
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#ifndef PENGUINSDL_H_
#define PENGUINSDL_H_

#include "../Objects/Engine.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "../Objects/Penguin.h"

namespace SDLGAME{

class PenguinSDL : public GAME::Penguin{
public:
	PenguinSDL();
	virtual ~PenguinSDL();
	void visualize(GAME::Engine* e);
};

}
#endif /* PENGUINSDL_H_ */
