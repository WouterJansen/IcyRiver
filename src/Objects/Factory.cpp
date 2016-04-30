/*
 * Factory.cpp
 *
 *  Created on: 22-feb.-2016
 *      Author: Wouter
 */

#include "Factory.h"

Factory::Factory() {
	// TODO Auto-generated constructor stub

}

Factory::~Factory() {
	// TODO Auto-generated destructor stub
}

Line* Factory::createLine(float newy, int newtype, float newspeed){
	Line* l = new Line(newy, newtype, newspeed);
	return l;
}
