#ifndef Dodge_CPP
#define Dodge_CPP


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

class Dodge : public Card {

	public:
		Dodge() {
			this -> SetType(1);
		}
		~Dodge() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			return false;
		}
		void Effect() {
		}
		string Display() {
			return "Dodge";//闪
		}

};



#endif
