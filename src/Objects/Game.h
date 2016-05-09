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

namespace GAME{

class Game {
public:
	Game(Factory* fnew, int height, int width, int gameRatenew);
	virtual ~Game();
	int gameRate; // the game's tickrate. The rate at which most of the game is calculated. Independent of framerate.
	float linesize; // size of a single line.
	Uint32 lastTime; // Last time the tickrate was reached.
	int score; // current score.
	std::map<int,std::string> highscores; // Map of all current highscores.
	int lives; // current amount of extra lives.
	int bonuses; // current amount of bonusses collected.
	int projectiles; // current amount of projectiles left.
	Penguin* pn;
	Engine* e;
	Factory* f;
	Background* b;
	LineManager* lm;
	CollisionManager* cm;
	ExtraManager* em;
	bool started; // boolean to know if the game has started (beyond the start screens)
	void gameLoop(); // main game loop.
	void keyEvent(std::string s); //to determine what happens when a certain key is pressed.
	void scrollScreen(); // scroll the screen one linesize down.
	void stateManager(); // Manager of the gamestate (start,highscore,loss)
	void restart(); // Restart the game to it's begin positions. (life lost)
	void start(); // Start the game. Initiate start screen, help screen.
	void lose(); // State when all lives are lost and no highscore is made.
	void reset(); // Reset the game after all lives are lost and game is restarted.
	void scoreManager(); // Manager of the displaying and calculating of the current score.
	void readScores(); // Read in the scores of the textfile highscores.txt.
	void writeScores(); // Write current highscores to the textfile highscores.txt
	void addHighscore(); // Add a new highscore.
	bool compareHighscore(); // compare the current score with the highscores.
	void showHighscores(); // Display highscores on screen.
};

}

#endif /* GAME_H_ */

