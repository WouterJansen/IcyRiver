/*
 * Game.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "Game.h"

using namespace GAME;

// The main Game object that holds most of the game features.
Game::Game(Factory* fnew, int height, int width, int gameRatenew) {
	gameRate = gameRatenew; // the game's tickrate. The rate at which most of the game is calculated. Independent of framerate.
	linesize = 6.25; // size of a single line.

	lastTime = 0; // Last time the tickrate was reached.

	lives = 2; // Start amount of extra lives.
	projectiles = 2; // start amount of projectiles.
	score = 0;
	bonuses = 0;

	started = false;

	f = fnew; // using the factory to create all new needed objects.
	e = f->createEngine();
	b = f->createBackground();
	pn = f->createPenguin();
	pn->addProjectile(f->createProjectile());
	e->newWindow(width, height);

	lm = new LineManager(f,e,b,linesize); // Creating all seperate manager objects.
	cm = new CollisionManager();
	em = new ExtraManager(f,e,b,gameRate,linesize);

	pn->maxw = 90; // Set the maximum positions that the player can go to.
	pn->maxh = 85;

	readScores(); // Read in the scores of the textfile highscores.txt.
}

Game::~Game() {
	delete(lm);
	delete(cm);
	delete(em);
	delete(b);
	delete(pn);
	delete(e);
}

// main game loop.
void Game::gameLoop(){
	std::cout << "GAME:" << e->getMillis() << " Starting Game..." << std::endl;
		while(true){
			if(e->stop) // if the engine has been set to Stop, the main gameLoop is exited.
				return;
			e->clearFrame(); // clear the renderer.
			b->visualize(e,gameRate,20,lm->getFloaterLines()); // visualize the background.
			if((e->getMillis() - lastTime) >= (1000/gameRate)){ // See if tickrate is reached yet since lasttime.
				lastTime = e->getMillis();
				lm->update(); // Update all lines.
				if(pn->shooting){// if the penguin state is shooting a projectile, this projectile has to be moved each tickrate.
					pn->moveProjectile();
					if(cm->searchProjectileCollision(pn->p,lm)){ // search for collision of projectile with obstructions.
										std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Projectile hit obstruction! Deleting obstruction." << std::endl;
										e->playSound("./sounds/projectile_impact.wav", 0);
										pn->shooting = false;
					}
				}
				int extrasCollision = cm->searchCollisionExtras(pn,em); // search for collision with extra's.
				if(extrasCollision == 1){ // if collision with extra life.
					lives++;
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Extra Life collected!. Lives left: " << lives << "." << std::endl;
					e->playSound("./sounds/life_take.flac", 0);
				}
				if(extrasCollision == 2){ // if collision with bonus points.
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Bonus Collected!" << std::endl;
					bonuses++;
					e->playSound("./sounds/bonus_take.wav", 0);
				}
				if(extrasCollision == 3){ // if collision with extra projectile.
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Projectile Collected!" << std::endl;
					projectiles++;
					e->playSound("./sounds/projectile_take.wav", 0);
				}
				if(cm->searchCollision(lm,pn) == 0 && started == true){ // search for collision with obstructions.
					lives--;
					if(lives != 0)
						e->playSound("./sounds/die.flac", 0);
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Failure! Life lost. Lives left: " << lives << ". Restarting..." << std::endl;
					for(int unsigned i = 0;i <= lm->lines.size() - 1; i++){ //reset the bottom lines so the starting platform can be shown again.
						if(fabs(lm->lines.at(i)->y - 87.5) < 0.001){
							lm->lines.at(i)->y = -6.25;
						}else if(fabs(lm->lines.at(i)->y - 81.25) < 0.001){
							lm->lines.at(i)->y = -12.5;
						}
					}
					restart(); // restart the game.
				}
			}
			lm->visualizeAll(); // visualize all obstructions.
			em->update(lives,projectiles); // update the extra's.
			keyEvent(e->Poll()); // check for a key being pressed.
			scoreManager(); // Update the score.
			pn->visualize(e); // visualize the player's penguin.
			if(pn->shooting) // if projectile is fired it has to be rendered.
				pn->p->visualize(e);
			e->renderFrame(); // Render the frame.
			stateManager(); // Set the state of the game.
		}
}

//to determine what happens when a certain key is pressed.
void Game::keyEvent(std::string s){
	if( s == "Up" ||  s == "Down"){ // If up or down key is pressed
		if(pn->timesDown == 0 && s == "Up" && pn->y <= 50){ // And the player is in the middle of the screen.
			scrollScreen(); // Move the screen down.
			pn->timesUp++;
		}
		else{
			pn->move(s,s,linesize); // if not move the player.
		}
	}else if(s == "Left" ||  s == "Right"){ // Move player left and right.
		pn->move(s,s,linesize/2);
	}else if(s == "Space"){ // Shoot a projectile.
		if(!pn->shooting && projectiles > 0){
			pn->shooting = true;
			pn->p->x = pn->x; // set position of projectile to that of the penguin.
			pn->p->y = pn->y;
			pn->p->shootDir = pn->dir; // set the direction of the projectile to that of the penguin.
			projectiles--;
			std::cout << "GAME:" << e->getMillis() << " Firing projectile. Projectiles left: " << projectiles << "." << std::endl;
		}
	}
}

// scroll the screen one linesize down.
void Game::scrollScreen(){
	b->moveDown(linesize); // scroll the background.
	em->moveDown(); // scroll the extras.
	lm->moveDown(); // scroll the lines.
}

// Manager of the gamestate (start,highscore,loss)
void Game::stateManager(){
	if(started == false) // if the game hasn't been started yet, then start the game.
		start();
	else if(pn->x > 100 || pn->x < 0){ // if player is outside of allowed area.
		std::cout << "GAME:" << e->getMillis() << " Life lost. Lives left: " << lives << ". Restarting..." << std::endl;
		lives--;
		lm->clearAll();
		restart();
	}
	if(lives == 0){ // if player is out of lives.
		if(compareHighscore()){ // check for new highscore.
			addHighscore(); // if new highscore trigger highscore state.
		}
		else
			lose(); // if no new highscore trigger lost state.
	}
}

// Restart the game to it's begin positions. (life lost)
void Game::restart(){
	b->amountMoveDown = 0; // visualize background again with starting conditions.
	b->startVisible = true;
	b->visualize(e,gameRate,20,lm->getFloaterLines());
	pn->x = 50 - pn->w/2; // reset player's penguin position.
	pn->y = ((100 - b->bottomh)/linesize)*linesize;
	pn->dir = "Right"; // reset layer's penguin direction.
	e->playMusic("./music/play.wav",-1);
	pn->floating = true;
}

// Start the game. Initiate start screen, help screen.
void Game::start(){
	std::cout << "GAME:" << e->getMillis() << " Start State initiated." << std::endl;
	int startBool = 0;
	int state = 1;
	e->playMusic("./music/start.wav",-1);
	bool help = false;
	while(startBool == 0){ // while loop during which start screen is shown.
		e->clearFrame();
		lm->update();
		lm->visualizeAll();
		b->visualizeOnlyWater(e,gameRate,10); // visualize background.
		float w;
		float h;
		std::string s = e->Poll(); // get the current pressed key.
		if(!help){ // If helpscreen state isn't triggered yet, show start screen.

			//render logo and animated penguin.
			e->getSize("./textures/logo.png",0,0,&w,&h);
			e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
			Uint8 color[] = {0,0,0,255};
			e->renderText("Press ENTER to start",50,90,color,0,"centre");
			e->getSize("./textures/penguin_dance_1.png",0,0,&w,&h);
			lastTime = e->renderTextureAnimated("./textures/penguin_dance_",".png", 50 - w/2, 50 - h/2, w, h, lastTime,&state, gameRate, 20, 4);
			e->renderFrame();

			// if ENTER is pressed, show help screen.
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				help = true;
		}else{
			// if help screen is triggered, show it.
			e->getSize("./textures/help.png",0,0,&w,&h);
			e->renderTexture("./textures/help.png", 0, 0, w, h,false);
			e->renderFrame();

			// if ENTER is pressed, start screen can be exited and game can be started.
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				startBool = 1;
		}
	}
	restart();
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game starting..." << std::endl;
	started = true;
}

// State when all lives are lost and no highscore is made.
void Game::lose(){
	lm->clearAll();
	e->playMusic("./music/lose.wav",-1);
	std::cout << "GAME:" << e->getMillis() << " No lives left. Lose State initiated." << std::endl;
	bool restartBool = false;
	bool show = false;
	while(!restartBool){ // while loop during which loss screen is shown.
		lm->update();
		lm->visualizeAll();
		e->clearFrame();
		b->visualizeOnlyWater(e,gameRate,20); // visualize background.
		float w;
		float h;
		e->getSize("./textures/logo.png",0,0,&w,&h);
		e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
		Uint8 color[] = {0,0,0,255};

		if(show){ // if highscore state is triggered, render highscores.
			showHighscores();
		}else{ // if not render the LOSS text.
			e->renderText("WASTED",50,50,color,1,"centre");
			e->renderText("Press ENTER to restart",50,60,color,0,"centre");
			e->renderText("Press SPACEBAR to view highscores",50,80,color,0,"centre");
			std::string t = e->Poll();
			if(t == "Space") // if SPACE is pressed, trigger highscore.
				show = true;
		}
		e->renderFrame();
		std::string s = e->Poll(); // If ENTER is pressed, exit loss screen and reset the game.
		if(s == "Return" || s == "Keypad Enter"|| e->stop)
			restartBool = true;
	}
	restart();
	reset();
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game Restarting..." << std::endl;
}

// Reset the game after all lives are lost and game is restarted.
void Game::reset(){
	lives = 2;
	projectiles = 2;
	bonuses = 0;
	pn->timesUp = 0;
	em->reset();
}

// Manager of the displaying and calculating of the current score.
void Game::scoreManager(){
	score = pn->timesUp*1; // score is the amount of times the player moved up.
	score += bonuses*10; // And has all bonusses added.

	// Render the current score on screen.
	Uint8 color[] = {255,255,255,255};
	std::string opening = "Score: ";
	std::string StringInt = static_cast<std::ostringstream*>( &(std::ostringstream() << score) )->str(); // turn the integer into a string
	std::string result =  opening  + StringInt;
	e->renderText(result,97,100 - e->fontSmallSize + 0.5,color, 0,"right");
}

// Read in the scores of the textfile highscores.txt.
void Game::readScores(){
	std::ifstream f("highscores.txt"); // if file doesn't exist, it is created.
	std::string line;
	while (std::getline(f, line)) // Read in line per line.
	{
		std::istringstream iss(line);
		std::string name;
		int highscore;
		if (!(iss >> name >> highscore)) { break; }
		highscores[highscore] = name; // add each highscore and name to the map.
	}
}

// Write current highscores to the textfile highscores.txt
void Game::writeScores(){
	remove("highscores.txt"); // remove the file to remove old scores.
	std::ofstream f;
	f.open ("highscores.txt"); // create new file.

	// write a new line with the score and name of each highscore.
	for (std::map<int,std::string>::reverse_iterator it = highscores.rbegin() ; it != highscores.rend(); ++it){
		f << it->second << " " << it->first << "\n";
	}
	f.close();
}

// Add a new highscore. Allowing player to enter his name and add it to the list of highscores.
void Game::addHighscore(){
	lm->clearAll();
	e->playMusic("./music/highscore.wav",-1);
	std::cout << "GAME:" << e->getMillis() << " New highscore detected! Highscore State initiated." << std::endl;
	int restartBool = 0;
	std::string name;
	bool show = false;
	while(restartBool == 0){  // while loop during which add highscore screen is shown.
		e->clearFrame();
		lm->update();
		b->visualizeOnlyWater(e,gameRate,20); // visualize background.
		float w;
		float h;
		e->getSize("./textures/logo.png",0,0,&w,&h);
		e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
		Uint8 color[] = {0,0,0,255};
		Uint8 color2[] = {255,255,255,255};
		std::string s = e->Poll();
		if(show){ // if show highscore state is triggered.
			showHighscores();
			// If ENTER is pressed, exit highscore screen and restart game.
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				restartBool = 1;
		}else{// Else if entering highscore state is entered.
			if(e->stop){
				restartBool = 1;
			// if ENTER is pressed, new highscore is added to the list.
			}else if(s == "Return" || s == "Keypad Enter"){
				if(!name.empty()){
					if(highscores.size() == 5){
						highscores.erase(highscores.begin());
					}
					highscores[score] = name;
					writeScores();
					std::cout << "GAME:" << e->getMillis() << " New highscore added! Name: " << name << " score: " << score << "." << std::endl;
					show = true;
				}
			// If BACKSPACE is pressed, one character is removed from name.
			}else if(s == "Backspace"){
				if(!name.empty()){
					name.erase(name.length() -1);
				}
				e->renderText("NEW HIGHSCORE",50,40,color2,1,"centre");
				e->renderText("Type your NAME and press ENTER",50,50,color,0,"centre");
				if(!name.empty()){
					e->renderText(name,50,80,color,0,"centre");
				}
			// If maximum name size of 10 is reached, don't allow new addition and display error message.
			}else if(name.size() == 10){
				e->renderText("NEW HIGHSCORE",50,40,color2,1,"centre");
				e->renderText("Type your NAME and press ENTER",50,50,color,0,"centre");
				if(!name.empty()){
					e->renderText(name,50,80,color,0,"centre");
				}
				e->renderText("Name can only be 10 characters long!",50,90,color,0,"centre");
			// If none of the above, add the new letter to the name.
			}else{
				if(s.size() == 1){
					name += s;
				}
				e->renderText("NEW HIGHSCORE",50,40,color2,1,"centre");
				e->renderText("Type your NAME and press ENTER",50,50,color,0,"centre");
				if(!name.empty()){
					e->renderText(name,50,80,color,0,"centre");
				}
			}
		}
		e->renderFrame();
	}
	restart();
	reset();
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game Restarting..." << std::endl;
}

// compare the current score with the highscores.
bool Game::compareHighscore(){
	if(highscores.empty() || highscores.size() < 5)
		return true;
	// compare all highscores with current scores and return true if new score is higher then one of them.
	for (std::map<int,std::string>::iterator it = highscores.begin() ; it != highscores.end(); ++it){
		if(it->first <= score)
			return true;
	}
	return false;
}

// Display highscores on screen.
void Game::showHighscores(){
	int i = 0;
	Uint8 color[] = {0,0,0,255};
	Uint8 white[] = {255,255,255,255};
	e->renderText("#",5,40,white,0,"left");
	e->renderText("NAME",10,40,white,0,"left");
	e->renderText("SCORE",95,40,white,0,"Right");

	//For each highscore, display it on screen.
	for (std::map<int,std::string>::reverse_iterator it = highscores.rbegin() ; it != highscores.rend(); ++it){
		std::string StringIntScore = static_cast<std::ostringstream*>( &(std::ostringstream() << it->first) )->str();
		std::string StringInt = static_cast<std::ostringstream*>( &(std::ostringstream() << i+1) )->str(); // turn the intiger into a string
		e->renderText(StringInt,5,50+(i*(e->fontSmallSize+1)),color,0,"left");
		e->renderText(it->second,10,50+(i*(e->fontSmallSize+1)),color,0,"left");
		e->renderText(StringIntScore,95,50+(i*(e->fontSmallSize+1)),color,0,"Right");
		i++;
	}
	e->renderText("Press ENTER to restart",50,90,color,0,"centre");
}


