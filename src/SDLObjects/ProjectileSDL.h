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

namespace SDLGAME{

//abstract penguin object. Its the object that can be fired by the player and destroy obstruction objects.
class ProjectileSDL : public GAME::Projectile{
public:
	ProjectileSDL();
	void visualize(GAME::Engine* e);
	void displayProjectile(GAME::Engine* e,float xi, float yi); // visualize the projectile on screen.
	virtual ~ProjectileSDL(); // display the projectile on the GUI.
};

}
#endif /* SRC_PROJECTILESDL_H_ */

