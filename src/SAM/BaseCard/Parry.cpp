#ifndef Parry_CPP
#define Parry_CPP


#include <string>
#include <typeinfo>
using namespace std;
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"
class Character;
#include "..\Character.h"
class Card;
#include "..\Card.h"

class Parry : public Card {

	public:
		Parry() {
			this -> SetType(1);
		}
		~Parry() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			return false;
		}
		void Effect(Character *user, Character *receiver, Card *card) {
		}
		string Display() {
			return "Parry";//招
		}

};



#endif
