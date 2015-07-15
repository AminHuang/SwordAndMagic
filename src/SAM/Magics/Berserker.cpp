#ifndef Berserker_CPP
#define Berserker_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class Berserker : public Magic {

	public:
		Berserker() {
		}
		~Berserker() {
		}
		bool CanUse(Character *user, int turn = 3) {
			return this -> Use(user, user, this);
		}
		bool Passive() {
			return true;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			p1 -> SetHit(magic);
			p1 -> SetHitFrom(user);
			p1 -> AddState(berserker, user);
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "Berserker";//¿ñÕ½Ê¿
		}

};



#endif
