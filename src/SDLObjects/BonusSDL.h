/*
 * BonusSDL.h
 *
 *  Created on: 29-mrt.-2016
 *      Author: Wouter
 */

#ifndef SRC_BONUSSDL_H_
#define SRC_BONUSSDL_H_

#include "../Objects/Bonus.h"
#include "../Objects/Engine.h"

class BonusSDL : public Bonus {
public:
	BonusSDL();
	virtual ~BonusSDL();
	void visualize(Engine* e, int gameRate);
};

#endif /* SRC_BONUSSDL_H_ */
