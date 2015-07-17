#ifndef BuffCard_CPP
#define BuffCard_CPP


#include <string>
using namespace std;
class DeathWish;
#include "..\Magics\DeathWish.cpp"
class ArcaneEcho;
#include "..\Magics\ArcaneEcho.cpp"
class ColdBlood;
#include "..\Magics\ColdBlood.cpp"
class Card;
#include "..\Card.h"

class BuffCard : public Card {

	public:
		BuffCard() {
			this -> SetType(2);
		}
		~BuffCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (profession == 1) {
				DeathWish *deathwish = new DeathWish();
				deathwish -> Use(user, receiver, deathwish);
			}
			if (profession == 2) {
				ArcaneEcho *arcaneecho = new ArcaneEcho();
				arcaneecho -> Use(user, receiver, arcaneecho);
			}
			if (profession == 3) {
				ColdBlood *coldblood = new ColdBlood();
				coldblood -> Use(user, receiver, coldblood);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "BuffCard";//浴血奋战/奥术回响/冷血
		}

};



#endif
