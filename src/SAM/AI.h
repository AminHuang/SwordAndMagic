#ifndef AI_H
#define AI_H


class Hero;
#include "Hero.h"
class Character;
#include "Character.h"
class Card;
#include "Card.h"
class Magic;
#include "Magic.h"


class AI : public Hero {

	public:
		AI();
		~AI();
		bool AskAnswer(Character *user, Card *card);
		bool AskAnswer(Character *user, Magic *magic);
		bool Act(Turn *turn); 
		bool DisCard(int k = 2);
		bool MakeChoice(int k, Magic *magic = NULL);
		virtual string Display();
		virtual void TryMagic();

};



#endif
