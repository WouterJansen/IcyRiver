/*
 * ObstructionManager.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "LineManager.h"

using namespace GAME;

//Management object that has functionality to take care of the lines and the spawning/despawning of obstructions.
LineManager::LineManager(Factory* fi,Engine* ei,Background* bgi,float linesizei)
{
	this->f = fi;
	this->e = ei;
	this->bg = bgi;
	this->linesize = linesizei;
	normalLines = 0;
	floaterLines = 0;
}

LineManager::~LineManager() {
}

// Update all lines. Create them if they don't exist.
void LineManager::update(){

	if(lines.empty() == true){ // if no lines exist yet then they have to be made
		for(int i = 0;i < (100 - bg->bottomh)/linesize + 2; i++){ // create as many lines as fit on screen (+ 2 to be used where the start platform is displayed)
			if(normalLines == 3 && floaterLines != 2){ // if 3 normal lines have just been spawned and there aren't 2 floating lines yet
				float randSpeed = -3 + rand() % 6; // create random speed for the line.
				if(randSpeed == 0)randSpeed = -1;
				Line* line = f->createLine((float)i*linesize - (2*linesize),1,(float)randSpeed/10);
				lines.push_back(line);
				floaterLines++;
			}else if(normalLines == 3 && floaterLines == 2){ // if 3 normal lines have been spawned but also 2 floater lines, create normal line again.
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				normalLines = 1;
				floaterLines = 0;
				Line* line = f->createLine((float)i*linesize - (2*linesize),0,(float)randSpeed/10);
				lines.push_back(line);
			}else{ // create normal line.
				normalLines++;
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				Line* line = f->createLine((float)i*linesize - (2*linesize),0,(float)randSpeed/10);
				lines.push_back(line);
			}
		}
	}
	if(lines.empty() != true){ // if lines already have been created.
		for(int unsigned j = 0;j <= lines.size() - 1; j++){
			ObstructionSpawner(lines[j]); // Spawn obstructions for each line.
		}
	}
}

// Visualize all lines and obstructions.
void LineManager::visualizeAll(){
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			lines[i]->vizualize(e);
		}
	}
}

// clear the manager of lines.
void LineManager::clearAll(){
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			lines[i]->clear();
		}
		lines.clear();
	}
}

// Create new obstructions inside the lines.
void LineManager::ObstructionSpawner(Line* line){

	if(line->obstructions.empty() == true){ // if no obstructions were ever made yet.
		line->obstructions.push_front(f->createObstruction());
		if(line->type == 1) // Set variation right if it's a obstruction or floater type line.
			line->obstructions.front()->setVariation(1);
		else
			line->obstructions.front()->setVariation(0);
		line->obstructions.front()->y = line->y; // set height of obstruction to that of the line.
		int random = rand() % 20; // set random starting position offscreen.
		if(line->speed > 0) // if line goes to the right.
			line->obstructions.front()->x = -20 - random;
		else // fi line goes to the left.
			line->obstructions.front()->x = 120 + random;
	}else{ // If lines are already filled with obstructions.
		int random = rand() % 20;
		if(line->speed > 0){ // if line goes to the right.
			// if latest spawned obstruction is already far enouph a new one can be spawned.
			if(line->obstructions.front()->x >= random + 15){
				line->obstructions.push_front(f->createObstruction());
				if(line->type == 1)
					line->obstructions.front()->setVariation(1);
				else
					line->obstructions.front()->setVariation(0);
				line->obstructions.front()->y = line->y;
				line->obstructions.front()->x = -20;
			}
		}else{ // if line goes to the left.
			if(line->obstructions.front()->x <= 100 - random - 10 ){
				line->obstructions.push_front(f->createObstruction());
				if(line->type == 1)
					line->obstructions.front()->setVariation(1);
				else
					line->obstructions.front()->setVariation(0);
				line->obstructions.front()->y = line->y;
				line->obstructions.front()->x = 100 + 20;
			}
		}
	}
	if(line->obstructions.empty() != true){
		if(line->speed > 0){ // if line moves to the right.
			if(line->obstructions.back()->x >= 100){ // if obstruction has moved past the screen.
				delete(line->obstructions.back()); // It can be removed.
				line->obstructions.pop_back();
			}
		}
		else{ // if line moves to the left
			if(line->obstructions.back()->x <= 0 - line->obstructions.back()->w){
				delete(line->obstructions.back());
				line->obstructions.pop_back();
			}
		}
	}
	line->move(); // move all obstructions at the speed of the line.
}

// move down all lines.
void LineManager::moveDown(){
	for(int unsigned i = 0;i <= lines.size() - 1; i++){
		lines[i]->y += linesize;
	}
	if(!bg->startVisible) // if start is no longer visible then the line that is moved off screen
		// will be moved to the top again to be re-used.
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			if(fabs(lines[i]->y - 93.75) < 0.001){
				lines[i]->y = 0;
			}
		}
}

// Get the height values of the floater type lines.
std::vector<float> LineManager::getFloaterLines(){
	std::vector<float> lineHeights;
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			if(lines[i]->type == 1)
				lineHeights.push_back(lines[i]->y);
		}
	}
	return lineHeights;
}
