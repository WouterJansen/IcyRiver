/*
 * BackgroundSDL.h
 *
 *  Created on: 19-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_BACKGROUNDSDL_H_
#define SRC_BACKGROUNDSDL_H_

#include "../Objects/Background.h"
#include "../Objects/Engine.h"
#include <locale>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include <stdio.h>
#include<iostream>
#include <vector>
#include <string>


//SDL Class of the background object
class BackgroundSDL : public Background {
public:
	BackgroundSDL();
	void visualize(Engine* e,int rate, int speed); //render the image on screen
	void visualizeOnlyWater(Engine* e,int rate, int speed);
	void moveDown(int linesize);
	virtual ~BackgroundSDL();
};

#endif /* SRC_BACKGROUNDSDL_H_ */
