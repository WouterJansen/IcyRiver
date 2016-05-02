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
	Uint32 lastTime;  // contains the last timevalue at which the animation was rendered
	int state; //which state the picture of the animation is in
	float bottomh;
	float height;
	int amountMoveDown;
	bool startVisible;
	virtual ~Background();
	virtual void visualize(Engine* e,int rate, int speed, std::vector<float> lines) = 0; //render the image on screen
	virtual void visualizeOnlyWater(Engine* e,int rate, int speed) = 0;
	virtual void moveDown(int linesize) = 0;
};

}

#endif /* SRC_BACKGROUND_H_ */


