/*
 * ProjectileSDL.h
 *
 *  Created on: 23-apr.-2016
 *      Author: Wouter
 */

#ifndef SRC_PROJECTILESDL_H_
#define SRC_PROJECTILESDL_H_

#include "../Objects/Engine.h"
#include "../Objects/Projectile.h"
#include <Windows.h>
#include <stdio.h>
#include<iostream>
#include <vector>
#include <string>

class ProjectileSDL : public Projectile{
public:
	ProjectileSDL();
	void visualize(Engine* e);
	void displayProjectile(Engine* e,float xi, float yi);
	virtual ~ProjectileSDL();
};

#endif /* SRC_PROJECTILESDL_H_ */

