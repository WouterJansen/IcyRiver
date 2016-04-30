/*
 * Game.h
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#ifndef GAME_H_
#define GAME_H_

#include "../Objects/Factory.h"
#include "../Objects/Engine.h"
#include "../Objects/Background.h"
#include "../Objects/Penguin.h"
#include "../Objects/Obstruction.h"
#include "CollisionManager.h"
#include "ExtraManager.h"
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <map>
#include "LineManager.h"

class Game {
public:
	Game(Factory* fnew, int height, int width, int gameRatenew);
	virtual ~Game();
	int gameRate;
	float linesize;
	int score;
	std::map<int,std::string> highscores;
	int lives;
	int bonuses;
	int projectiles;
	Penguin* pn;
	Engine* e;
	Factory* f;
	Background* b;
	Uint32 lastTime;
	LineManager* lm;
	CollisionManager* cm;
	ExtraManager* em;
	bool started;
	void gameLoop();
	void keyEvent(std::string s,LineManager* lm,ExtraManager* em);
	void scrollScreen(LineManager* lm,ExtraManager* em);
	void stateManager(CollisionManager* cm, LineManager* om,ExtraManager* em);
	void scoreManager();
	void readScores();
	void writeScores();
	bool compareHighscore();
	void restart(LineManager* lm);
	void start(LineManager* lm);
	void showHighscores();
	void addHighscore(LineManager* lm,ExtraManager* em);
	void lose(LineManager* lm,ExtraManager* em);
	void reset(ExtraManager* em);
};

#endif /* GAME_H_ */

