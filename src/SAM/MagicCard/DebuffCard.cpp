#ifndef DebuffCard_CPP
#define DebuffCard_CPP


#include <string>
using namespace std;
class DeepWounds;
#include "..\Magics\DeepWounds.cpp"
class ArcaneInstability;
#include "..\Magics\ArcaneInstability.cpp"
class Sap;
#include "..\Magics\Sap.cpp"
class Card;
#include "..\Card.h"

class DebuffCard : public Card {

	public:
		DebuffCard() {
			this -> SetType(2);
		}
		~DebuffCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (receiver -> GetType() == 2) return false;
			if (profession == 1) {
				DeepWounds *deepwounds = new DeepWounds();
				deepwounds -> Use(user, receiver, deepwounds);
			}
			if (profession == 2) {
				ArcaneInstability *arcaneinstability = new ArcaneInstability();
				arcaneinstability -> Use(user, receiver, arcaneinstability);
			}
			if (profession == 3) {
				Sap *sap = new Sap();
				sap -> Use(user, receiver, sap);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "DebuffCard";//重伤/寒冰屏障/假死
		}

};



#endif
