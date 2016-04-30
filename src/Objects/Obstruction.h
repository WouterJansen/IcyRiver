/*
 * Obstructor.h
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#ifndef OBSTRUCTION_H_
#define OBSTRUCTION_H_

#include "Engine.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <string>

class Obstruction{
public:
	Obstruction();
	float x;
	float y;
	float w;
	float h;
	std::string variant;
	virtual ~Obstruction();
	virtual void visualize(Engine* e, bool flip) = 0;
	void setVariation(int type);
};

#endif /* OBSTRUCTION_H_ */
