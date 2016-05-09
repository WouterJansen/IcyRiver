/*
 * Projectile.h
 *
 *  Created on: 23-apr.-2016
 *      Author: Wouter
 */

#ifndef SRC_PROJECTILE_H_
#define SRC_PROJECTILE_H_

#include "Engine.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <string>

namespace GAME{

//abstract penguin object. Its the object that can be fired by the player and destroy obstruction objects.
class Projectile {
public:
	Projectile();
	float x; // X Coordinate of the Object.
	float y; // Y Coordinate of the Object.
	float w; // width of the Object.
	float h; // height of the Object.
	std::string shootDir; // direction of the projectile being shot.
	virtual void visualize(Engine* e) = 0; // visualize the projectile on screen.
	virtual void displayProjectile(Engine* e, float xi, float yi) = 0; // display the projectile on the GUI.
	virtual ~Projectile();
};

}

#endif /* SRC_PROJECTILE_H_ */
