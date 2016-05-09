/*
 * ExtraManager.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_EXTRAMANAGER_H_
#define SRC_EXTRAMANAGER_H_

#include "../Objects/Bonus.h"
#include "../Objects/Life.h"
#include "../Objects/Projectile.h"
#include "../Objects/Engine.h"
#include "../Objects/Background.h"
#include "../Objects/Factory.h"

namespace GAME{

//Management object that has functionality to take care of the spawning,despawning and visualizing of the extra objects.
//These are the bonus, extra life and extra projectiles.
class ExtraManager {
public:
	ExtraManager(Factory* fi,Engine* ei,Background* bgi,int gameRatei, float linesizei);
	Engine* e;
	Factory* f;
	Background* bg;
	Life* l;
	Bonus* b;
	Projectile* p;
	float linesize;
	int gameRate;
	Uint32 timeVisible; // amount of time a extra has been visible on screen.
	virtual ~ExtraManager();
	void update(int lives, int projectiles); // Update and spawn/despawn the extras.
	void reset(); // reset the positions of the extras.
	void displayExtras(int lives, int projectiles); // display the status of the extras on the GUI.
	void moveDown(); // Move the extras down when the screen is moved downwards.
};

}

#endif /* SRC_EXTRAMANAGER_H_ */

