#ifndef MassiveSmash_CPP
#define MassiveSmash_CPP

#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class MassiveSmash : public Magic {

	public:
		MassiveSmash() {
		}
		~MassiveSmash() {
		}
		bool CanUse(Character *user, int turn = 3) {
			return false;
		}
		bool Passive() {
			return true;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			if (receiver -> GetType() == 1) {
				Hero *p2 = dynamic_cast<Hero*>(receiver);
				p2 -> SetHit(magic);
				p2 -> SetHitFrom(user);
				if (p2 -> Have(crusharmor5)) {
					p2 -> ClearState(crusharmor5);
					p2 -> AddState(crusharmor5, user);
				} else if (p2 -> Have(crusharmor4)) {
					p2 -> ClearState(crusharmor4);
					p2 -> AddState(crusharmor5, user);
				} else if (p2 -> Have(crusharmor3)) {
					p2 -> ClearState(crusharmor3);
					p2 -> AddState(crusharmor4, user);
				} else if (p2 -> Have(crusharmor2)) {
					p2 -> ClearState(crusharmor2);
					p2 -> AddState(crusharmor3, user);
				} else if (p2 -> Have(crusharmor1)) {
					p2 -> ClearState(crusharmor1);
					p2 -> AddState(crusharmor2, user);
				} else
					p2 -> AddState(crusharmor1, user);
			}
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "MassiveSmash";//æﬁ¡¶∑€ÀÈ√Õª˜
		}

};



#endif
