/*
 * FactorySDL.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "FactorySDL.h"

using namespace SDLGAME;


FactorySDL::FactorySDL() {
	// TODO Auto-generated constructor stub

}

FactorySDL::~FactorySDL() {
	// TODO Auto-generated destructor stub
}

GAME::Engine* FactorySDL::createEngine(){
	EngineSDL* engine = new EngineSDL();
	return engine;
}

GAME::Penguin* FactorySDL::createPenguin(){
	PenguinSDL* penguin = new PenguinSDL();
	return penguin;
}

GAME::Obstruction* FactorySDL::createObstruction(){
	ObstructionSDL* ob = new ObstructionSDL();
	return ob;
}

GAME::Background* FactorySDL::createBackground(){
	BackgroundSDL* b = new BackgroundSDL();
	return b;
}

GAME::Life* FactorySDL::createLife(){
	LifeSDL* l = new LifeSDL();
	return l;
}

GAME::Bonus* FactorySDL::createBonus(){
	BonusSDL* b = new BonusSDL();
	return b;
}

GAME::Projectile* FactorySDL::createProjectile(){
	ProjectileSDL* p = new ProjectileSDL();
	return p;
}
