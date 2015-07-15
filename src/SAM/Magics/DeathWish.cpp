#ifndef DeathWish_CPP
#define DeathWish_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class DeathWish : public Magic {

	public:
		DeathWish() {
		}
		~DeathWish() {
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
			p1 -> AddState(deathwish, user);
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "DeathWish";//浴血奋战
		}

};



#endif
