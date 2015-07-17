#ifndef HealthStone_CPP
#define HealthStone_CPP


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

class HealthStone : public Card {
	
	public:
		HealthStone() {
			this -> SetType(1);
		}
		~HealthStone() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			receiver -> GetHeal(user, dynamic_cast<Hero*>(user) -> CalHeal(8.0));
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "HealthStone";//治疗石
		}

};



#endif
