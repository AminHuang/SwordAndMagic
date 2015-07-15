#ifndef Avatar_CPP
#define Avatar_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class Avatar : public Magic {

	public:
		Avatar() {
		}
		~Avatar() {
		}
		bool CanUse(Character *user, int turn = 3) {
			if (turn == 3)
				return true;
			return false;
		}
		bool Passive() {
			return false;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			p1 -> SetHit(magic);
			p1 -> SetHitFrom(user);
			p1 -> AddState(avatar, user);
			p1 -> DrawCard();
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "Avatar";//ÌìÉñÏÂ·²
		}

};



#endif
