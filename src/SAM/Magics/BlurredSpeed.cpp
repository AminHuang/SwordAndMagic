#ifndef BlurredSpeed_CPP
#define BlurredSpeed_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class BlurredSpeed : public Magic {

	public:
		BlurredSpeed() {
		}
		~BlurredSpeed() {
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
			p1 -> DrawCard(4);
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "BlurredSpeed";//疾跑
		}

};



#endif
