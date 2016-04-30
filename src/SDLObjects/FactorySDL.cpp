/*
 * FactorySDL.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "FactorySDL.h"

FactorySDL::FactorySDL() {
	// TODO Auto-generated constructor stub

}

FactorySDL::~FactorySDL() {
	// TODO Auto-generated destructor stub
}

Engine* FactorySDL::createEngine(){
	EngineSDL* engine = new EngineSDL();
	return engine;
}

Penguin* FactorySDL::createPenguin(){
	PenguinSDL* penguin = new PenguinSDL();
	return penguin;
}

Obstruction* FactorySDL::createObstruction(){
	ObstructionSDL* ob = new ObstructionSDL();
	return ob;
}

Background* FactorySDL::createBackground(){
	BackgroundSDL* b = new BackgroundSDL();
	return b;
}

Life* FactorySDL::createLife(){
	LifeSDL* l = new LifeSDL();
	return l;
}

Bonus* FactorySDL::createBonus(){
	BonusSDL* b = new BonusSDL();
	return b;
}

Projectile* FactorySDL::createProjectile(){
	ProjectileSDL* p = new ProjectileSDL();
	return p;
}
