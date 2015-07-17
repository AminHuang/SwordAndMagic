#ifndef AoeCard_CPP
#define AoeCard_CPP


#include <string>
using namespace std;
class Sweep;
#include "..\Magics\Sweep.cpp"
class CometStorm;
#include "..\Magics\CometStorm.cpp"
class SliceDice;
#include "..\Magics\SliceDice.cpp"
class Card;
#include "..\Card.h"

class AoeCard : public Card {

	public:
		AoeCard() {
			this -> SetType(2);
		}
		~AoeCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (profession == 1) {
				Sweep *s = new Sweep();
				s -> Use(user, receiver, s);
			}
			if (profession == 2) {
				CometStorm *cometstorm = new CometStorm();
				cometstorm -> Use(user, receiver, cometstorm);
			}
			if (profession == 3) {
				SliceDice *slicedice = new SliceDice();
				slicedice -> Use(user, receiver, slicedice);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "AoeCard";//ºáÉ¨/åçĞÇ·ç±©/½£ÈĞÂÒÎè
		}

};



#endif
