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

namespace SDLGAME{


// Object of the abstract factory. It helps create the different possible objects of the game
class FactorySDL : public GAME::Factory {
public:
	FactorySDL();
	virtual ~FactorySDL();
	GAME::Engine* createEngine();
	GAME::Penguin* createPenguin();
	GAME::Obstruction* createObstruction();
	GAME::Background* createBackground();
	GAME::Life* createLife();
	GAME::Bonus* createBonus();
	GAME::Projectile* createProjectile();
};

}
#endif /* FACTORYSDL_H_ */

