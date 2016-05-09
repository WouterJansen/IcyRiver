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

namespace SDLGAME{

//Bonus object. Provides player with 10 extra points.
class BonusSDL : public GAME::Bonus {
public:
	BonusSDL();
	virtual ~BonusSDL();
	void visualize(GAME::Engine* e, int gameRate); // Render the bonus to the screen.
};

}
#endif /* SRC_BONUSSDL_H_ */
