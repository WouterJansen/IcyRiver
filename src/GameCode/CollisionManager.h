/*
 * CollisionManager.h
 *
 *  Created on: 14-mrt.-2016
 *      Author: Wouter
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "../Objects/penguin.h"
#include "ExtraManager.h"
#include "LineManager.h"
#include <tgmath.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

//Management object that has functionality to take care and look for collision of player and obstructions.
class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();
	bool searchCollision(LineManager* lm,Penguin* pn);// Compares position and size of player object and the obstructions and looks for collision.
	bool searchProjectileCollision(Projectile* p,LineManager* lm);
	int searchCollisionExtras(Penguin* pn,ExtraManager* em);
	float lineChecker(Line* line,Penguin* pn); //checks a line for collision with the player.
	bool lineChecker(Line* line,Projectile* p); //checks a line for collision with projectile.
};

#endif /* COLLISIONMANAGER_H_ */

