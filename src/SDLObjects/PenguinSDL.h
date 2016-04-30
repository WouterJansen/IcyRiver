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

class PenguinSDL : public Penguin{
public:
	PenguinSDL();
	virtual ~PenguinSDL();
	void visualize(Engine* e);
};

#endif /* PENGUINSDL_H_ */
