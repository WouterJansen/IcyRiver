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


class Projectile {
public:
	Projectile();
	float x;
	float y;
	float w;
	float h;
	virtual void visualize(Engine* e) = 0;
	virtual void displayProjectile(Engine* e, float xi, float yi) = 0;
	virtual ~Projectile();
};

}

#endif /* SRC_PROJECTILE_H_ */
