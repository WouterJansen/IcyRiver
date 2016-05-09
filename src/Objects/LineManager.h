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
#include <cmath>
#include <limits>
#include "../Objects/Line.h"

#ifndef OBSTRUCTIONMANAGER_H_
#define OBSTRUCTIONMANAGER_H_

namespace GAME{

//Management object that has functionality to take care of the lines and the spawning/despawning of obstructions.
class LineManager {
public:
	LineManager(Factory* fi,Engine* ei,Background* bgi,float linesizei);
	int normalLines; // amount of normal obstruction lines (animals and ice)
	int floaterLines; // amount of floater lines (logs)
	float linesize; // size of a single line.
	Engine* e;
	Factory* f;
	Background* bg;
	std::deque< Line* > lines; // Deque of line objects.
	virtual ~LineManager();
	void update(); // Update all lines. Create them if they don't exist.
	void visualizeAll(); // Visualize all lines and obstructions.
	void clearAll(); // clear the manager of lines.
	void ObstructionSpawner(Line* line); // Create new obstructions inside the lines.
	void moveDown(); // move down all lines.
	std::vector<float> getFloaterLines(); // Get the height values of the floater type lines.
};

}

#endif /* OBSTRUCTIONMANAGER_H_ */


