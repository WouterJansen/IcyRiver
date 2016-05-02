/*
 * Start.cpp
 *
 *  Created on: 25-apr.-2016
 *      Author: Wouter
 */

#include "Start.h"

using namespace GAME;

Start::Start() {
	// TODO Auto-generated constructor stub

}

Start::~Start() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char* args[]) {
	srand(time(0));
	GAME::Factory* f = new SDLGAME::FactorySDL();
	GAME::Game* g = new Game(f,640,800,60);
	g->gameLoop();
	delete(g);
	delete(f);
	exit(0);
	return 0;
}

