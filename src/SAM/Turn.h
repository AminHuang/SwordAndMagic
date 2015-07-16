#ifndef Turn_H
#define Turn_H


class Character;
#include "Character.h"
class CardStack;
#include "CardStack.h"
class Hero;
#include "Hero.h"

class Turn {

	public:
		Turn();
		Turn(Character *character, CardStack *cardstack, Table *table);
		~Turn();
		bool StartTurn();
		bool DrawTurn();
		bool SeedTurn();
		bool PlayTurn();
		bool DiscardTurn();
		bool EndTurn();
	private:
		Character *character_;
		CardStack *cardstack_;
		Table *table_;
		Hero *player_;
		int act_;

};



#endif
