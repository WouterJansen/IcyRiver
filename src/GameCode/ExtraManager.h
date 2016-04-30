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
	Uint32 timeVisible;
	virtual ~ExtraManager();
	void update(int lives, int projectiles);
	void reset();
	void displayExtras(int lives, int projectiles);
	void moveDown();
};

#endif /* SRC_EXTRAMANAGER_H_ */
