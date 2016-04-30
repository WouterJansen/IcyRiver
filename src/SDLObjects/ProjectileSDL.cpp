/*
 * ProjectileSDL.cpp
 *
 *  Created on: 23-apr.-2016
 *      Author: Wouter
 */

#include "ProjectileSDL.h"

ProjectileSDL::ProjectileSDL() {
	// TODO Auto-generated constructor stub

}

ProjectileSDL::~ProjectileSDL() {
	// TODO Auto-generated destructor stub
}

void ProjectileSDL::visualize(Engine* e){
	e->getSize("./textures/projectile.png",x,y,&w,&h);
	e->renderTexture("./textures/projectile.png", x, y, w, h,false);
}

void ProjectileSDL::displayProjectile(Engine* e,float xi, float yi){
	e->getSize("./textures/projectile_display.png",xi,yi,&w,&h);
	e->renderTexture("./textures/projectile_display.png", xi, yi, w, h,false);
}
