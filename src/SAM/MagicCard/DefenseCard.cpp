#ifndef DefenseCard_CPP
#define DefenseCard_CPP


#include <string>
using namespace std;
class DieAfterSword;
#include "..\Magics\DieAfterSword.cpp"
class IceBlock;
#include "..\Magics\IceBlock.cpp"
class CheatedDeath;
#include "..\Magics\CheatedDeath.cpp"
class Card;
#include "..\Card.h"

class DefenseCard : public Card {

	public:
		DefenseCard() {
			this -> SetType(2);
		}
		~DefenseCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			int profession = dynamic_cast<Hero*>(user) -> GetProfession();
			if (profession == 1) {
				DieAfterSword *dieaftersword = new DieAfterSword();
				dieaftersword -> Use(user, receiver, dieaftersword);
			}
			if (profession == 2) {
				IceBlock *iceblock = new IceBlock();
				iceblock -> Use(user, receiver, iceblock);
			}
			if (profession == 3) {
				CheatedDeath *cheateddeath = new CheatedDeath();
				cheateddeath -> Use(user, receiver, cheateddeath);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "DefenseCard";//½£ÔÚÈËÔÚ/º®±ùÆÁÕÏ/¼ÙËÀ
		}

};



#endif
