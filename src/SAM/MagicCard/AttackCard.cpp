#ifndef AttackCard_CPP
#define AttackCard_CPP


#include <string>
using namespace std;
class MortalStrike;
#include "..\Magics\MortalStrike.cpp"
class CelestialAlignment;
#include "..\Magics\CelestialAlignment.cpp"
class Garrote;
#include "..\Magics\Garrote.cpp"
class Card;
#include "..\Card.h"

class AttackCard : public Card {

	public:
		AttackCard() {
			this -> SetType(2);
		}
		~AttackCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (profession == 1) {
				MortalStrike *mortalstrike = new MortalStrike();
				mortalstrike -> Use(user, receiver, mortalstrike);
			}
			if (profession == 2) {
				CelestialAlignment *celestialalignment = new CelestialAlignment();
				celestialalignment -> Use(user, receiver, celestialalignment);
			}
			if (profession == 3) {
				Garrote *garrote = new Garrote();
				garrote -> Use(user, receiver, garrote);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "AttackCard";//致死打击/星穹连线/锁喉
		}

};



#endif
