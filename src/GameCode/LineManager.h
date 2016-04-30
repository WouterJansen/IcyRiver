/*
 * ObstructionManager.h
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "../Objects/Factory.h"
#include "../Objects/Engine.h"
#include "../Objects/Obstruction.h"
#include "../Objects/Background.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <ctime>
#include <string>
#include <deque>
#include <vector>
#include "../Objects/Line.h"

#ifndef OBSTRUCTIONMANAGER_H_
#define OBSTRUCTIONMANAGER_H_

class LineManager {
public:
	LineManager(Factory* fi,Engine* ei,Background* bgi,float linesizei);
	int normalLines;
	int floaterLines;
	float linesize;
	Engine* e;
	Factory* f;
	Background* bg;
	std::deque< Line* > lines;
	virtual ~LineManager();
	void update();
	void visualizeAll();
	void clearAll();
	void ObstructionSpawner(Line* line);
	void moveDown();
};

#endif /* OBSTRUCTIONMANAGER_H_ */
