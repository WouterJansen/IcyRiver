/*
 * Obstructor.h
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#ifndef OBSTRUCTION_H_
#define OBSTRUCTION_H_

#include "Engine.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <string>

namespace GAME{

//abstract obstruction object. Its the object that will be floating on the water.
class Obstruction{
public:
	Obstruction();
	float x; // X Coordinate of the Object.
	float y; // Y Coordinate of the Object.
	float w; // Width of the Object.
	float h; // Height of the Object.
	std::string variant; // Sets the name of the texture variant of the obstruction.
	virtual ~Obstruction();
	virtual void visualize(Engine* e, bool flip) = 0; // Render the obstruction to screen.
	void setVariation(int type); // Sets the texture variation random.
};

}
#endif /* OBSTRUCTION_H_ */
