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
	if(amountMoveDown == 0)
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, 100, w, h, lastTime, &state, rate, 4, speed); //render the animated water
	else{
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, amountMoveDown, 100, 100 - h, w, h, lastTime, &state, rate, 4, speed); //render the animated water
		lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, amountMoveDown, w, h, lastTime, &state, rate, 4, speed); //render the animated water
	}
	// render the tiled bottom start point image for the entire window width.
	if(startVisible){
		e->getSize("./textures/background_bottom_tile.png",0,0,&w,&h);
		for(int i = 0;i <= 100;i = i + w)
			e->renderTexture("./textures/background_bottom_tile.png", i, 100 - h + amountMoveDown, w, h,false);
		bottomh = h;
	}
	e->getSize("./textures/background_bar.png",0,0,&w,&h);
	e->renderTexture("./textures/background_bar.png", 0, 100 - h, w, h,false);

	if(lines.empty() == false){
		for(int unsigned i = 0;i <= lines.size() - 1; i++){
			e->getSize("./textures/debris.png",0,0,&w,&h);
			e->renderTexture("./textures/debris.png", 0, lines[i], w, h,false);
		}
	}
}

void BackgroundSDL::visualizeOnlyWater(GAME::Engine* e,int rate, int speed){
	float w;
	float h;
	// render the tiled water animation for the entire window.
	e->getSize("./textures/water_tile_1.png",0,0,&w,&h);
	lastTime = e->renderTextureAnimatedTiled("./textures/water_tile_",".png", 0, 0, 100, 100, w, h, lastTime, &state, rate, 4, speed); //render the animated water
}

void BackgroundSDL::moveDown(int linesize){
	if(amountMoveDown >= height)
		amountMoveDown = 0;
	else
		amountMoveDown += linesize;
	if(startVisible){
		if(amountMoveDown >= bottomh){
			startVisible = false;
			bottomh = 0;
		}
	}
}
