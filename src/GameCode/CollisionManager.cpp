/*
 * CollisionManager.cpp
 *
 *  Created on: 14-mrt.-2016
 *      Author: Wouter
 */

#include "CollisionManager.h"

//Management object that has functionality to take care and look for collision of player and obstructions.
CollisionManager::CollisionManager() {
	// TODO Auto-generated constructor stub

}

CollisionManager::~CollisionManager() {
	// TODO Auto-generated destructor stub
}

// Compares position and size of player object and the obstructions and looks for collision.
bool CollisionManager::searchCollision(LineManager* lm,Penguin* pn){
	if( lm->lines.empty() != true){
		for (int unsigned i = 0; i < lm->lines.size(); ++i){ // checks all lines
			if(fabs(pn->y - lm->lines[i]->y) < 0.001){ // makes sure that the line being checked is the one where the player is currently on.
				float s = lineChecker(lm->lines[i],pn); //searches for collision
				//if a collision is found( it returns 0 if no collision, and the speed of the obstruction object if there is collision)
				pn->floating = false;

				//Now it needs to see what type of line it is (floater or normal obstructions).
				if(lm->lines[i]->type == 1){ // if line type is floater then collision is required and loss is triggered on no collision.
					if(s>0){ //if collision is found and the speed of the line is moving left to right then move penguin at same speed and direction.
						pn->move(pn->dir,"Right",s);
						pn->floating = true;
						return true;
					}else if(s<0){//if collision is found and the speed of the line is moving right to left then move penguin at same speed and direction.
						//the move together function will be called to make the player move at the same speed as the obstruction.
						pn->move(pn->dir,"Left",fabs(s));
						pn->floating = true;
						return true;
					}
					//if the player isn't colliding with a obstruction and isn't in the starting zone, then the player is in the water.
					if(pn->y < lm->lines.size()*pn->h){
						return false;
					}
					//if the player isn't in the water then he is in the starting zone.
					return true;

				}else{ // if line type is obstruction then collision means loss.
					if(s != 0)//if collision is found then loss has to be triggered.
						return false;
					else // if no collision is found then player can continue.
						return true;
				}
			}
		}
	}
	return true;
}

bool CollisionManager::searchProjectileCollision(Projectile* p,LineManager* lm){
	if( lm->lines.empty() != true){
			for (int unsigned i = 0; i < lm->lines.size(); ++i){ // checks all lines
				if(lineChecker(lm->lines[i],p))
					return true; //searches for collision
			}
	}
	return false;
}

int CollisionManager::searchCollisionExtras(Penguin* pn,ExtraManager* em){
	if(pn->y == em->l->y && pn->x >= em->l->x - pn->w/2 && pn->x <= em->l->x + pn->w/2){
		em->reset();
		return 1;
	}
	if(pn->y == em->b->y && pn->x >= em->b->x - pn->w/2 && pn->x <= em->b->x + pn->w/2){
		em->reset();
		return 2;
	}
	if(pn->y == em->p->y && pn->x >= em->p->x - pn->w/2 && pn->x <= em->p->x + pn->w/2){
		em->reset();
		return 3;
	}
	return 0;
}

//Checks a single line for collision.
float CollisionManager::lineChecker(Line* line,Penguin* pn){
	if( line->obstructions.empty() != true){ // make sure line isn't empty
		for (int unsigned i = 0; i < line->obstructions.size(); ++i){ // check for collision for each object of the line.
			if( fabs(pn->y - line->y) < 0.001 // make sure that the player object's and the line are on the same height
			&& (pn->x + pn->w) >= line->obstructions.at(i)->x
			&& pn->x <= (line->obstructions.at(i)->x + line->obstructions.at(i)->w)){
				return line->speed;
			}
		}
		return 0; // if no collision is found.
	}
	return 0; // if line is empty.
}

//Checks a single line for collision.
bool CollisionManager::lineChecker(Line* line,Projectile* p){
	if( line->obstructions.empty() != true){ // make sure line isn't empty
		for (int unsigned i = 0; i < line->obstructions.size(); ++i){ // check for collision for each object of the line.
			if( fabs(p->y - line->y) < 0.001 // make sure that the player object's and the line are on the same height
			&& (p->x + p->w) >= line->obstructions.at(i)->x
			&& p->x <= (line->obstructions.at(i)->x + line->obstructions.at(i)->w)){
				if(line->type == 0){
				delete(line->obstructions.at(i));
				line->obstructions.erase(line->obstructions.begin() + i);
				return true;
				}
			}
		}
		return false; // if no collision is found.
	}
	return false; // if line is empty.
}



