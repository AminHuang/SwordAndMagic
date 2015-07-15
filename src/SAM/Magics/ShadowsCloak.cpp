#ifndef ShadowsCloak_CPP
#define ShadowsCloak_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class ShadowsCloak : public Magic {

	public:
		ShadowsCloak() {
		}
		~ShadowsCloak() {
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
			user_ = user;
			receiver_ = receiver;
			Hero *p1 = dynamic_cast<Hero*>(user);
			p1 -> SetHit(magic);
			p1 -> SetHitFrom(user);
			p1 -> MakeChoice(1, magic);
			return true;
		}
		void Effect(bool cho = true) {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p1 = dynamic_cast<Hero*>(user);
			if (cho)
				p1 -> GetHeal(user, p1 -> CalHeal(5.0, 4), 4);
			else
				p1 -> DrawCard();	
		}
		string Display() {
			return "ShadowsCloak";//°µÓ°¶·Åñ
		}

};



#endif
