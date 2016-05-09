/*
 * ExtraManager.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "ExtraManager.h"

using namespace GAME;

//Management object that has functionality to take care of the spawning,despawning and visualizing of the extra objects.
//These are the bonus, extra life and extra projectiles.
ExtraManager::ExtraManager(Factory* fi,Engine* ei,Background* bgi,int gameRatei, float linesizei) {
	this->f = fi;
	this->e = ei;
	this->bg = bgi;
	this->gameRate = gameRatei;
	this->linesize = linesizei;
	timeVisible = 0; // amount of time a extra has been visible on screen.
	b = f->createBonus(); // use the factory to create on of each.
	l = f->createLife();
	p = f->createProjectile();
	b->x = -50;  // set the begin positions of the extra's to offscreen so they can't be seen.
	b->y = -50;
	l->x = -50;
	l->y = -50;
	p->x = -50;
	p->y = -50;
}

ExtraManager::~ExtraManager() {
	delete(b);
	delete(l);
	delete(p);
}

// Update and spawn/despawn the extras.
void ExtraManager::update(int lives, int projectiles){
	if(b->x == -50 && l->x == -50 && p->x == -50){ // if all are offscreen
		if(e->getMillis() - timeVisible >= 10000){ // and the standard delay time has been reached between extra's.s
			int randChance = rand() % 10000; // a random number is generated
			if(randChance == 1){ // if number is 1 it spawns a new life.
				if(lives != 3){ // only if the maximum amount of lifes hasn't been reached.
					e->playSound("./sounds/extra_spawn.wav", 0);
					randChance = rand() % (int)((100 - bg->bottomh)/linesize); // sets random y coordinate.
					l->y = randChance*linesize;
					randChance = rand() % (int)(80/linesize);   // sets random x coordinate.
					l->x = 5 + randChance*linesize;
					std::cout << "EXTRAMANAGER:" << e->getMillis() << " Extra Life Spawned!" << std::endl;
					timeVisible = e->getMillis();
				}

			// if the random number is a 2 ,3 or 4 (more chance) it spawns a bonus
			}else if(randChance == 2 || randChance == 3 || randChance == 4){
				e->playSound("./sounds/extra_spawn.wav", 0);
				randChance = rand() % (int)((100 - bg->bottomh)/linesize);
				b->y = randChance*linesize;
				randChance = rand() % (int)(80/linesize);
				b->x = 5 + randChance*linesize;
				std::cout << "EXTRAMANAGER:" << e->getMillis() << " Bonus Spawned!" << std::endl;
				timeVisible = e->getMillis();
		    // if the random number is a 5 ,6 or 7 (more chance) it spawns a extra projectiles
			}else if(randChance == 5 || randChance == 6 || randChance == 7){
				if(projectiles != 3){
					e->playSound("./sounds/extra_spawn.wav", 0);
					randChance = rand() % (int)((100 - bg->bottomh)/linesize);
					p->y = randChance*linesize;
					randChance = rand() % (int)(80/linesize);
					p->x = 5 + randChance*linesize;
					std::cout << "EXTRAMANAGER:" << e->getMillis() << " Projectile Spawned!" << std::endl;
					timeVisible = e->getMillis();
				}
			}

		}
	}else{
		//if the standard delay for despawning has been passed the extra is despawned.
		if(e->getMillis() - timeVisible >= 10000){
			std::cout << "EXTRAMANAGER:" << e->getMillis() << " 10 seconds past! Extra despawning." << std::endl;
			reset();
		}
	}
	// visualize all extra's.
	b->visualize(e,gameRate);
	l->visualize(e,gameRate);
	p->visualize(e);
	displayExtras(lives, projectiles); // update the extra lives and projectiles on the GUI.
}

// reset the positions of the extras to offscreen.
void ExtraManager::reset(){
	b->x = -50;
	b->y = -50;
	l->x = -50;
	l->y = -50;
	p->x = -50;
	p->y = -50;
	b->visualize(e,gameRate);
	l->visualize(e,gameRate);
	p->visualize(e);
}

// display the status of the extras on the GUI.
void ExtraManager::displayExtras(int lives, int projectiles){
	for(int i = 0;i < lives;i++){ // display the amount of extra lives left.
		l->displayLife(e, 2 + (i*l->w), 100 - l->h);
	}

	for(int i = 0;i < projectiles;i++){ // display the amount of projectiles left.
		p->displayProjectile(e, 40 + (i*l->w), 100 - l->h);
	}
}

// Move the extras down when the screen is moved downwards.
void ExtraManager::moveDown(){
	if(b->y != -linesize)
		b->y += linesize;
	if(l->y != -linesize)
		l->y += linesize;
	if(p->y != -linesize)
		p->y += linesize;
}
