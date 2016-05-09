/*
 * BackgroundSDL.cpp
 *
 *  Created on: 19-mrt.-2016
 *      Author: Wouter
 */

#include "BackgroundSDL.h"

using namespace SDLGAME;

//SDL Class of the background object
BackgroundSDL::BackgroundSDL() {
}

BackgroundSDL::~BackgroundSDL() {
	// TODO Auto-generated destructor stub
}

//render the image on screen
void BackgroundSDL::visualize(GAME::Engine* e,int rate, int speed,std::vector<float> lines){
	float w;
	float h;
	// render the tiled water animation for the entire window.
	e->getSize("./textures/water_tile_1.png",0,0,&w,&h);
	if(amountMoveDown == 0) // if background is in default position
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, 100, w, h, lastTime, &state, rate, 4, speed); //render the animated water
	else{
		// if the water has moved down already, render it twice and keep moving it down.
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, amountMoveDown, 100, 100 - amountMoveDown, w, h, lastTime, &state, rate, 4, speed); //render the animated water
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, amountMoveDown, w, h, lastTime, &state, rate, 4, speed); //render the animated water
	}
	// render the tiled bottom start point image for the entire window width.
	if(startVisible){
		e->getSize("./textures/background_bottom_tile.png",0,0,&w,&h);
		for(int i = 0;i <= 100;i = i + w)
			e->renderTexture("./textures/background_bottom_tile.png", i, 100 - h + amountMoveDown, w, h,false);
		bottomh = h;
	}
	//render the black GUI bar at the bottom.
	e->getSize("./textures/background_bar.png",0,0,&w,&h);
	e->renderTexture("./textures/background_bar.png", 0, 100 - h, w, h,false);

	//render the debris on the lines where there are floaters (logs).
	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			e->getSize("./textures/debris.png",0,0,&w,&h);
			e->renderTexture("./textures/debris.png", 0, lines[i], w, h,false);
		}
	}
}

// Render the background but only water.
void BackgroundSDL::visualizeOnlyWater(GAME::Engine* e,int rate, int speed){
	float w;
	float h;
	// render the tiled water animation for the entire window.
	e->getSize("./textures/water_tile_1.png",0,0,&w,&h);
	lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, 100, w, h, lastTime, &state, rate, 4, speed); //render the animated water
}

// Move the background down one size.
void BackgroundSDL::moveDown(int linesize){
	if(amountMoveDown >= 100) // if the water has moved down for an entire screen height it can be reset again.
		amountMoveDown = 0;
	else
		amountMoveDown += linesize; // otherwise move the water down by one linesize.
	if(startVisible){ // if the start is move down beyond being visible, it is turned off.
		if(fabs(amountMoveDown - 2*linesize) < 0.001){
			startVisible = false;
			bottomh = 0;
		}
	}
}
