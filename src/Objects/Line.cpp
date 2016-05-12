/*
 * ObstructionLine.cpp
 *
 *  Created on: 23-mrt.-2016
 *      Author: Wouter
 */

#include "Line.h"

using namespace GAME;

// Object of a line containing all obstructions.
Line::Line(float newy, int newtype, float newspeed) {
	y = newy;
	type = newtype;
	speed = newspeed;
}

Line::~Line() {
}

// rendering the entire line of obstructions.
void Line::vizualize(Engine* e){
		if(obstructions.empty() != true){
			for (int unsigned j = 0; j < obstructions.size(); j++){
				if(speed < 0){
					obstructions.at(j)->y = y;
					obstructions.at(j)->visualize(e,true);
				}
				else{
					obstructions.at(j)->y = y;
					obstructions.at(j)->visualize(e,false);
				}
			}
		}
}

// Clear the line of obstructions.
void Line::clear(){
	obstructions.clear();
}

// Move all obstructions in this line at the speed of the line.
void Line::move(){
	if( obstructions.empty() != true){
		for (int unsigned i = 0; i < obstructions.size(); ++i){
			obstructions.at(i)->x += speed;
		}
	}
}
