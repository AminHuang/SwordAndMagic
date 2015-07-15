#ifndef ArcaneEcho_CPP
#define ArcaneEcho_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"


class ArcaneEcho : public Magic {

	public:
		ArcaneEcho() {
		}
		~ArcaneEcho() {
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
			p1 -> AddState(arcaneecho, user);
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "ArcaneEcho";//°ÂÊõ»ØÏì
		}

};



#endif
