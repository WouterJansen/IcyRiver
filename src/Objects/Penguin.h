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

namespace GAME{

//abstract penguin object. Its the object that will be the player.
class Penguin{
public:
	Penguin();
	virtual ~Penguin();
	float x; // X Coordinate of the player.
	float y; // Y Coordinate of the player.
	float w; // Width of the Object.
	float h; // Height of the Object.
	float maxw; // Maximum x coordinate the player can go to
	float maxh; // Maximum y coordinate the player can go to
	int timesUp; // the amount of times the player has moved upwards.
	int timesDown; // the amount of times the player has moved downwards since the last time the player went up.
	std::string dir; // direction the player is moving/looking.
	Projectile* p;
	bool shooting; // State if the player is shooting.
	bool floating; // state if the player is on an object/land or in the water.
	virtual void visualize(Engine* e) = 0; // render the penguin.
	void addProjectile(Projectile* proj); // add a projectile to the penguin's projectile slot.
	void move(std::string dir, std::string dirM,float speed); // move the player's penguin.
	void moveProjectile(); // move the projectile when it's being fired.
};

}

#endif /* PENGUIN_H_ */
