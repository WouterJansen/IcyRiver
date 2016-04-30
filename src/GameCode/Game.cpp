/*
 * Game.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "Game.h"

Game::Game(Factory* fnew, int height, int width, int gameRatenew) {
	gameRate = gameRatenew;
	lives = 2;
	projectiles = 2;

	linesize = 6.25;
	lastTime = 0;
	score = 0;
	bonuses = 0;
	started = false;

	f = fnew;
	e = f->createEngine();
	b = f->createBackground();
	pn = f->createPenguin();
	pn->addProjectile(f->createProjectile());
	e->newWindow(width, height);

	lm = new LineManager(f,e,b,linesize);
	cm = new CollisionManager();
	em = new ExtraManager(f,e,b,gameRate,linesize);

	pn->maxw = 90;
	pn->maxh = 85;

	readScores();
}

Game::~Game() {
	delete(lm);
	delete(cm);
	delete(em);
	delete(b);
	delete(pn);
	delete(e);
}

void Game::gameLoop(){
	std::cout << "GAME:" << e->getMillis() << " Starting Game..." << std::endl;
		while(true){
			if(e->stop)
				return;
			e->clearFrame();
			b->visualize(e,gameRate,20);
			if((e->getMillis() - lastTime) >= (1000/gameRate)){
				lm->update();
				if(pn->shooting)
					pn->moveProjectile();
				lastTime = e->getMillis();
				int extrasCollision = cm->searchCollisionExtras(pn,em);
				if(extrasCollision == 1){
					lives++;
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Extra Life collected!. Lives left: " << lives << "." << std::endl;
					e->playSound("./sounds/life_take.flac", 0);
				}
				if(extrasCollision == 2){
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Bonus Collected!" << std::endl;
					bonuses++;
					e->playSound("./sounds/bonus_take.wav", 0);
				}
				if(extrasCollision == 3){
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Projectile Collected!" << std::endl;
					projectiles++;
					e->playSound("./sounds/projectile_take.wav", 0);
				}
				if(cm->searchCollision(lm,pn) == 0 && started == true){
					lives--;
					if(lives != 0)
						e->playSound("./sounds/die.flac", 0);
					std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Failure! Life lost. Lives left: " << lives << ". Restarting..." << std::endl;
					lm->clearAll();
					restart(lm);

				}
				if(pn->shooting)
					if(cm->searchProjectileCollision(pn->p,lm)){
						std::cout << "COLLISIONMANAGER:" << e->getMillis() << " Projectile hit obstruction! Deleting obstruction." << std::endl;
						e->playSound("./sounds/projectile_impact.wav", 0);
						pn->shooting = false;
					}
			}
			lm->visualizeAll();
			em->update(lives,projectiles);
			keyEvent(e->Poll(),lm,em);
			scoreManager();
			compareHighscore();
			pn->visualize(e);
			if(pn->shooting)
				pn->p->visualize(e);
			e->renderFrame();
			stateManager(cm,lm,em);
		}
}

void Game::keyEvent(std::string s,LineManager* lm,ExtraManager* em){
	if( s == "Up" ||  s == "Down"){
		if(pn->timesDown == 0 && s == "Up" && pn->y <= ((lm->lines.size() - 7) / 2)*linesize){
			scrollScreen(lm,em);
			pn->timesUp++;
		}
		else{
			pn->move(s,s,linesize);
		}
	}else if(s == "Left" ||  s == "Right"){
		pn->move(s,s,linesize/2);
	}else if(s == "Space"){
		if(!pn->shooting && projectiles > 0){
			pn->shooting = true;
			pn->p->x = pn->x;
			pn->p->y = pn->y;
			pn->shootDir = pn->dir;
			projectiles--;
			std::cout << "GAME:" << e->getMillis() << " Firing projectile. Projectiles left: " << projectiles << "." << std::endl;
		}
	}
}

void Game::scrollScreen(LineManager* lm,ExtraManager* em){
	b->moveDown(linesize);
	em->moveDown();
	lm->moveDown();
}

void Game::stateManager(CollisionManager* cm, LineManager* lm,ExtraManager* em){
	if(started == false)
		start(lm);
	else if(pn->x > 100 || pn->x < 0){
		std::cout << "GAME:" << e->getMillis() << " Life lost. Lives left: " << lives << ". Restarting..." << std::endl;
		lives--;
		lm->clearAll();
		restart(lm);
	}
	if(lives == 0){
		if(compareHighscore()){
			addHighscore(lm,em);
		}
		else
			lose(lm,em);
	}
}

void Game::restart(LineManager* lm){
	b->amountMoveDown = 0;
	b->startVisible = true;
	b->visualize(e,gameRate,20);
	pn->x = 50 - pn->w/2;
	pn->y = ((b->height - b->bottomh)/linesize)*linesize;
	pn->dir = "Right";
	e->playMusic("./music/play.wav",-1);
	pn->floating = true;
}

void Game::start(LineManager* lm){
	std::cout << "GAME:" << e->getMillis() << " Start State initiated." << std::endl;
	int startBool = 0;
	int state = 1;
	e->playMusic("./music/start.wav",-1);
	bool help = false;
	while(startBool == 0){
		e->clearFrame();
		lm->update();
		lm->visualizeAll();
		b->visualizeOnlyWater(e,gameRate,10);
		float w;
		float h;
		std::string s = e->Poll();
		if(!help){

			e->getSize("./textures/logo.png",0,0,&w,&h);
			e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
			Uint8 color[] = {0,0,0,255};
			e->renderText("Press ENTER to start",50,90,color,0,"centre");
			e->getSize("./textures/penguin_dance_1.png",0,0,&w,&h);
			lastTime = e->renderTextureAnimated("./textures/penguin_dance_",".png", 50 - w/2, 50 - h/2, w, h, lastTime,&state, gameRate, 20, 4);
			e->renderFrame();
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				help = true;
		}else{
			e->getSize("./textures/help.png",0,0,&w,&h);
			e->renderTexture("./textures/help.png", 0, 0, w, h,false);
			e->renderFrame();
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				startBool = 1;
		}
	}
	restart(lm);
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game starting..." << std::endl;
	started = true;
}

void Game::lose(LineManager* lm,ExtraManager* em){
	lm->clearAll();
	e->playMusic("./music/lose.wav",-1);
	std::cout << "GAME:" << e->getMillis() << " No lives left. Lose State initiated." << std::endl;
	bool restartBool = false;
	bool show = false;
	while(!restartBool){
		lm->update();
		lm->visualizeAll();
		e->clearFrame();
		b->visualizeOnlyWater(e,gameRate,20);
		float w;
		float h;
		e->getSize("./textures/logo.png",0,0,&w,&h);
		e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
		Uint8 color[] = {0,0,0,255};

		if(show){
			showHighscores();
		}else{
			e->renderText("WASTED",50,50,color,1,"centre");
			e->renderText("Press ENTER to restart",50,60,color,0,"centre");
			e->renderText("Press SPACEBAR to view highscores",50,80,color,0,"centre");
			std::string t = e->Poll();
			if(t == "Space")
				show = true;
		}
		e->renderFrame();
		std::string s = e->Poll();
		if(s == "Return" || s == "Keypad Enter"|| e->stop)
			restartBool = true;
	}
	restart(lm);
	reset(em);
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game Restarting..." << std::endl;
}

void Game::reset(ExtraManager* em){
	lives = 2;
	projectiles = 2;
	bonuses = 0;
	pn->timesUp = 0;
	em->reset();
}

void Game::scoreManager(){
	score = pn->timesUp*1;
	score += bonuses*10;
	Uint8 color[] = {255,255,255,255};
	std::string opening = "Score: ";
	std::string StringInt = static_cast<std::ostringstream*>( &(std::ostringstream() << score) )->str(); // turn the integer into a string
	std::string result =  opening  + StringInt;
	e->renderText(result,97,100 - e->fontSmallSize + 0.5,color, 0,"right");
}

void Game::readScores(){
	std::ifstream f("highscores.txt");
	std::string line;
	while (std::getline(f, line))
	{
		std::istringstream iss(line);
		std::string name;
		int highscore;
		if (!(iss >> name >> highscore)) { break; }
		highscores[highscore] = name;
	}
}

void Game::writeScores(){
	remove("highscores.txt");
	std::ofstream f;
	f.open ("highscores.txt");

	for (std::map<int,std::string>::reverse_iterator it = highscores.rbegin() ; it != highscores.rend(); ++it){
		f << it->second << " " << it->first << "\n";
	}
	f.close();
}

void Game::addHighscore(LineManager* lm,ExtraManager* em){
	lm->clearAll();
	e->playMusic("./music/highscore.wav",-1);
	std::cout << "GAME:" << e->getMillis() << " New highscore detected! Highscore State initiated." << std::endl;
	int restartBool = 0;
	std::string name;
	bool show = false;
	while(restartBool == 0){
		e->clearFrame();
		lm->update();
		b->visualizeOnlyWater(e,gameRate,20);
		float w;
		float h;
		e->getSize("./textures/logo.png",0,0,&w,&h);
		e->renderTexture("./textures/logo.png", 50-(w/2), 10, w, h,false);
		Uint8 color[] = {0,0,0,255};
		Uint8 color2[] = {255,255,255,255};
		std::string s = e->Poll();
		if(show){
			showHighscores();
			if(s == "Return" || s == "Keypad Enter" || e->stop)
				restartBool = 1;
		}else{
			if(e->stop){
				restartBool = 1;
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
			}else if(s == "Backspace"){
				if(!name.empty()){
					name.erase(name.length() -1);
				}
				e->renderText("NEW HIGHSCORE",50,40,color2,1,"centre");
				e->renderText("Type your NAME and press ENTER",50,50,color,0,"centre");
				if(!name.empty()){
					e->renderText(name,50,80,color,0,"centre");
				}
			}else if(name.size() == 10){
				e->renderText("NEW HIGHSCORE",50,40,color2,1,"centre");
				e->renderText("Type your NAME and press ENTER",50,50,color,0,"centre");
				if(!name.empty()){
					e->renderText(name,50,80,color,0,"centre");
				}
				e->renderText("Name can only be 10 characters long!",50,90,color,0,"centre");
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
	restart(lm);
	reset(em);
	std::cout << "GAME:" << e->getMillis() << " Key Pressed. Game Restarting..." << std::endl;
}

bool Game::compareHighscore(){
	if(highscores.empty() || highscores.size() < 5)
		return true;
	for (std::map<int,std::string>::iterator it = highscores.begin() ; it != highscores.end(); ++it){
		if(it->first <= score)
			return true;
	}
	return false;
}

void Game::showHighscores(){
	int i = 0;
	Uint8 color[] = {0,0,0,255};
	Uint8 white[] = {255,255,255,255};
	e->renderText("#",5,40,white,0,"left");
	e->renderText("NAME",10,40,white,0,"left");
	e->renderText("SCORE",95,40,white,0,"Right");

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


