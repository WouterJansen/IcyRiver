/*
 * ExtraManager.cpp
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#include "ExtraManager.h"

ExtraManager::ExtraManager(Factory* fi,Engine* ei,Background* bgi,int gameRatei, float linesizei) {
	this->f = fi;
	this->e = ei;
	this->bg = bgi;
	this->gameRate = gameRatei;
	this->linesize = linesizei;
	timeVisible = 0;
	b = f->createBonus();
	l = f->createLife();
	p = f->createProjectile();
	b->x = -50;
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

void ExtraManager::update(int lives, int projectiles){
	if(b->x == -50 && l->x == -50 && p->x == -50){
		if(e->getMillis() - timeVisible >= 20000){
			int randChance = rand() % 10000;
			if(randChance == 1){
				if(lives != 3){
					e->playSound("./sounds/extra_spawn.wav", 0);
					randChance = rand() % (int)((100 - bg->bottomh)/linesize);
					l->y = randChance*linesize;
					randChance = rand() % (int)(80/linesize);
					l->x = 5 + randChance*linesize;
					std::cout << "GAME:" << e->getMillis() << " EXTRAMANAGER: Extra Life Spawned!" << std::endl;
					timeVisible = e->getMillis();
				}
			}else if(randChance == 2 || randChance == 3 || randChance == 4){
				e->playSound("./sounds/extra_spawn.wav", 0);
				randChance = rand() % (int)((bg->height - bg->bottomh)/linesize);
				b->y = randChance*linesize;
				randChance = rand() % (int)(80/linesize);
				b->x = 5 + randChance*linesize;
				std::cout << "GAME:" << e->getMillis() << " EXTRAMANAGER: Bonus Spawned!" << std::endl;
				timeVisible = e->getMillis();
			}else if(randChance == 5 || randChance == 6 || randChance == 7){
				if(projectiles != 3){
					e->playSound("./sounds/extra_spawn.wav", 0);
					randChance = rand() % (int)((bg->height - bg->bottomh)/linesize);
					p->y = randChance*linesize;
					randChance = rand() % (int)(80/linesize);
					p->x = 5 + randChance*linesize;
					std::cout << "GAME:" << e->getMillis() << " EXTRAMANAGER: Projectile Spawned!" << std::endl;
					timeVisible = e->getMillis();
				}
			}

		}
	}else{
		if(e->getMillis() - timeVisible >= 10000){
			std::cout << "GAME:" << e->getMillis() << " EXTRAMANAGER: 10 seconds past! Extra despawning." << std::endl;
			reset();
		}
	}
	b->visualize(e,gameRate);
	l->visualize(e,gameRate);
	p->visualize(e);
	displayExtras(lives, projectiles);
}

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

void ExtraManager::displayExtras(int lives, int projectiles){
	for(int i = 0;i < lives;i++){
		l->displayLife(e, 2 + (i*l->w), 100 - l->h);
	}

	for(int i = 0;i < projectiles;i++){
		p->displayProjectile(e, 40 + (i*l->w), 100 - l->h);
	}
}

void ExtraManager::moveDown(){
	if(b->y != -linesize)
		b->y += linesize;
	if(l->y != -linesize)
		l->y += linesize;
	if(p->y != -linesize)
		p->y += linesize;
}
