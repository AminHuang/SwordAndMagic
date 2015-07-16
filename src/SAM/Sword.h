#ifndef Sword_H
#define Sword_H


#include <string>
using namespace std;
class Card;
#include "Card.h"
class Character;
#include "Character.h"


class Sword : public Card {

	public:
		Sword();
		~Sword();
		virtual bool Attack(Character *user, Character *receiver, int times);
		virtual int GetAtk();
		virtual bool Use(Character *user, Character *receiver, Card *card);
		virtual string Display();
		virtual void UseMagic(Character *user, Character *receiver);
	
};



#endif
