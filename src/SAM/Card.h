#ifndef Card_H
#define Card_H


#include <string>
using namespace std;
class Character;
#include "Character.h"

class Card {

	public:
		Card();
		~Card();
		virtual bool Use(Character *user, Character *receiver, Card *card);
		virtual void Effect();
		virtual string Display();
		int GetID();
		bool SetID(int id);
		int GetType();
		void SetType(int type);
		Character *user_;
		Character *receiver_;
	private:
		int id_;
		int type_;
		// 0 card, 1 BaseCard, 2 MagicCard, 3 Sword
		// harm
		//0 = physic, 1 = fire, 2 = frost, 3 = arcane, 4 = dark, 5 = holy

};



#endif
