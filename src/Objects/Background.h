/*
 * Background.h
 *
 *  Created on: 19-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_BACKGROUND_H_
#define SRC_BACKGROUND_H_

#include "Engine.h"
#include <vector>

namespace GAME{


//abstract background object
class Background {
public:
	Background();
	Uint32 lastTime;  // Contains the last timevalue at which the animation was rendered.
	int state; //which state the picture of the animation is in.
	float bottomh; // Size of the starting platform at the bottom.
	float amountMoveDown; // How much the screen has been moved.
	bool startVisible; // Boolean to check if the starting platform is visible to the player.
	virtual ~Background();
	virtual void visualize(Engine* e,int rate, int speed, std::vector<float> lines) = 0; // Render the background.
	virtual void visualizeOnlyWater(Engine* e,int rate, int speed) = 0; // Render the background but only water.
	virtual void moveDown(int linesize) = 0; // Move the background down one size.
};

}

#endif /* SRC_BACKGROUND_H_ */


