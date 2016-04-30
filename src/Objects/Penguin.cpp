/*
 * Frog.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "Penguin.h"

Penguin::Penguin() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	shooting = false;
	maxw = 0;
	maxh = 0;
	timesUp= 0;
	timesDown = 0;
	dir = "Right";
	shootDir = "";
	p = 0;
	floating = true;
}

Penguin::~Penguin() {
	delete(p);
}

void Penguin::addProjectile(Projectile* proj){
	p = proj;
}

void Penguin::move(std::string dir, std::string dirM,float speed){
	this->dir = dir;
	if(dirM == "Up"){
		y -= speed;
		if(timesDown != 0)
			timesDown--;
		else
			timesUp++;
	}
	if(dirM == "Down" && y <= maxh){
		y += speed;
		timesDown++;
	}
	if(dirM == "Left" && x >= 5)
		x -= speed;
	if(dirM == "Right" && x <= maxw)
		x += speed;
}

void Penguin::moveProjectile(){
	if(shootDir == "Up"){
		p->y -= 0.5;
	}
	if(shootDir == "Down"){
		p->y += 0.5;
	}
	if(shootDir == "Right"){
		p->x += 0.5;
	}
	if(shootDir == "Left"){
		p->x -= 0.5;
	}
	if(p->x <= -10 || p->x >= 100 || p->y <= -10 || p->y >= 90){
		shooting = false;
	}

}
