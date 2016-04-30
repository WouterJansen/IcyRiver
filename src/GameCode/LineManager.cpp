/*
 * ObstructionManager.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "LineManager.h"

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

void LineManager::update(){

	if(lines.empty() == true){
		for(int i = 0;i < (bg->height - bg->bottomh)/linesize + 7; i++){
			if(normalLines == 3 && floaterLines != 2){
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				Line* line = f->createLine((float)i*linesize - (7*linesize),1,(float)randSpeed/10);
				lines.push_back(line);
				floaterLines++;
			}else if(normalLines == 3 && floaterLines == 2){
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				normalLines = 1;
				floaterLines = 0;
				Line* line = f->createLine((float)i*linesize - (7*linesize),0,(float)randSpeed/10);
				lines.push_back(line);
			}else{
				normalLines++;
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				Line* line = f->createLine((float)i*linesize - (7*linesize),0,(float)randSpeed/10);
				lines.push_back(line);
			}
		}
	}
	if(lines.empty() != true){
		for(int unsigned j = 0;j <= lines.size() - 1; j++){
			ObstructionSpawner(lines[j]);
		}
		if(lines.size() < (bg->height - bg->bottomh)/linesize + 6){
			if(normalLines == 3 && floaterLines != 2){
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				Line* line = f->createLine((float)(lines.front()->y - linesize),1,(float)randSpeed/10);
				lines.push_front(line);
				floaterLines++;
			}else if(normalLines == 3 && floaterLines == 2){
				float randSpeed = -3 + rand() % 6;
				if(randSpeed == 0)randSpeed = -1;
				normalLines = 1;
				floaterLines = 0;
				Line* line = f->createLine((float)(lines.front()->y - linesize),0,(float)randSpeed/10);
				lines.push_front(line);
			}else{
				normalLines++;
				float randSpeed = -5 + rand() % 10;
				if(randSpeed == 0)randSpeed = -5;
				Line* line = f->createLine((float)(lines.front()->y - linesize),0,(float)randSpeed/10);
				lines.push_front(line);
			}
		}
	}
}


void LineManager::visualizeAll(){
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			lines[i]->vizualize(e);
		}
	}
}

void LineManager::clearAll(){
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			lines[i]->clear();
		}
		lines.clear();
	}
}

void LineManager::ObstructionSpawner(Line* line){

	if(line->obstructions.empty() == true){
		line->obstructions.push_front(f->createObstruction());
		if(line->type == 1)
			line->obstructions.front()->setVariation(1);
		else
			line->obstructions.front()->setVariation(0);
		line->obstructions.front()->y = line->y;
		int random = rand() % 20;
		if(line->speed > 0)
			line->obstructions.front()->x = -20 - random;
		else
			line->obstructions.front()->x = 120 + random;
	}else{
		int random = rand() % 20;
		if(line->speed > 0){
			if(line->obstructions.front()->x >= random + 15){
				line->obstructions.push_front(f->createObstruction());
				if(line->type == 1)
					line->obstructions.front()->setVariation(1);
				else
					line->obstructions.front()->setVariation(0);
				line->obstructions.front()->y = line->y;
				line->obstructions.front()->x = -20;
			}
		}else{
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
		if(line->speed > 0){
			if(line->obstructions.back()->x >= 100){
				delete(line->obstructions.back());
				line->obstructions.pop_back();
			}
		}
		else{
			if(line->obstructions.back()->x <= 0 - line->obstructions.back()->w){
				delete(line->obstructions.back());
				line->obstructions.pop_back();
			}
		}
	}
	line->move();
}

void LineManager::moveDown(){
	for(int unsigned i = 0;i <= lines.size() - 1; i++){
		lines[i]->y += linesize;
	}
	if(!bg->startVisible)
		lines.pop_back();
}
