/*
 * Projectile.cpp
 *
 *  Created on: 23-apr.-2016
 *      Author: Wouter
 */

#include "Projectile.h"

using namespace GAME;

//abstract penguin object. Its the object that can be fired by the player and destroy obstruction objects.
Projectile::Projectile() {
	x = 100;
	y = 100;
	w = 0;
	h = 0;
	shootDir = "";
}

Projectile::~Projectile() {
	// TODO Auto-generated destructor stub
}
