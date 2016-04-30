/*
 * Frog.h
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#ifndef PENGUIN_H_
#define PENGUIN_H_

#include "Engine.h"
#include "Projectile.h"
#include <iostream>
#include <string>
#include <deque>

class Penguin{
public:
	Penguin();
	virtual ~Penguin();
	float x;
	float y;
	float w;
	float h;
	float maxw;
	float maxh;
	int timesUp;
	int timesDown;
	std::string dir;
	Projectile* p;
	bool shooting;
	bool floating;
	std::string shootDir;
	virtual void visualize(Engine* e) = 0;
	void addProjectile(Projectile* proj);
	void move(std::string dir, std::string dirM,float speed);
	void moveProjectile();
};

#endif /* PENGUIN_H_ */
