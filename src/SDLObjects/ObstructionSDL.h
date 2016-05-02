/*
 * ObstructorSDL.h
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#ifndef OBSTRUCTIONSDL_H_
#define OBSTRUCTIONSDL_H_

#include "../Objects/Engine.h"
#include "../Objects/Obstruction.h"
#include <Windows.h>
#include <stdio.h>
#include<iostream>
#include <vector>
#include <string>

namespace SDLGAME{

class ObstructionSDL : public GAME::Obstruction{
public:
	ObstructionSDL();
	virtual ~ObstructionSDL();
	void visualize(GAME::Engine* e,bool flip);
};

}

#endif /* OBSTRUCTIONSDL_H_ */
