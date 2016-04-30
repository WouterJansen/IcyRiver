/*
 * FactorySDL.h
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#ifndef FACTORYSDL_H_
#define FACTORYSDL_H_

#include "../Objects/Engine.h"
#include "EngineSDL.h"
#include "../Objects/Factory.h"
#include "../Objects/Obstruction.h"
#include "ObstructionSDL.h"
#include "../Objects/Projectile.h"
#include "ProjectileSDL.h"
#include "../Objects/Penguin.h"
#include "PenguinSDL.h"
#include "../Objects/Background.h"
#include "BackgroundSDL.h"
#include "../Objects/Life.h"
#include "LifeSDL.h"
#include "../Objects/Bonus.h"
#include "BonusSDL.h"

class FactorySDL : public Factory {
public:
	FactorySDL();
	virtual ~FactorySDL();
	Engine* createEngine();
	Penguin* createPenguin();
	Obstruction* createObstruction();
	Background* createBackground();
	Life* createLife();
	Bonus* createBonus();
	Projectile* createProjectile();
};

#endif /* FACTORYSDL_H_ */

