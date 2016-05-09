/*
 * Factory.h
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "Engine.h"
#include "Obstruction.h"
#include "Projectile.h"
#include "Penguin.h"
#include "Background.h"
#include "Line.h"
#include "Life.h"
#include "Bonus.h"


namespace GAME{

//Abstract object of the abstract factory. It helps create the different possible objects of the game.
class Factory {
public:
	Factory();
	virtual ~Factory();
	virtual Engine* createEngine() = 0;
	virtual Penguin* createPenguin() = 0;
	virtual Obstruction* createObstruction() = 0;
	virtual Background* createBackground() = 0;
	virtual Life* createLife() = 0;
	virtual Bonus* createBonus() = 0;
	virtual Projectile* createProjectile() = 0;
	Line* createLine(float newy, int newtype, float newspeed);
};

}

#endif /* FACTORY_H_ */
