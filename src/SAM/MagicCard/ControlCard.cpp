#ifndef ControlCard_CPP
#define ControlCard_CPP


#include <string>
using namespace std;
class StormBolt;
#include "..\Magics\StormBolt.cpp"
class Polymorph;
#include "..\Magics\Polymorph.cpp"
class Blind;
#include "..\Magics\Blind.cpp"
class Card;
#include "..\Card.h"

class ControlCard : public Card {

	public:
		ControlCard() {
			this -> SetType(2);
		}
		~ControlCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (profession == 1) {
				StormBolt *stormbolt = new StormBolt();
				stormbolt -> Use(user, receiver, stormbolt);
			}
			if (profession == 2) {
				Polymorph *ploymorph = new Polymorph();
				ploymorph -> Use(user, receiver, ploymorph);
			}
			if (profession == 3) {
				Blind *blind = new Blind();
				blind -> Use(user, receiver, blind);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "ControlCard";//风暴之锤/变羊/致盲
		}

};



#endif
