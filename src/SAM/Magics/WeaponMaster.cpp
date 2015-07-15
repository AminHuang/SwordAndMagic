#ifndef WeaponMaster_CPP
#define WeaponMaster_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class WeaponMaster : public Magic {

	public:
		WeaponMaster() {
		}
		~WeaponMaster() {
		}
		bool CanUse(Character *user, int turn = 3) {
			Hero *hero = dynamic_cast<Hero*>(user);
			if (hero -> GetSword() != NULL)
				return this -> Use(user, user, this);
			return false;
		}
		bool Passive() {
			return true;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			p1 -> SetHit(magic);
			p1 -> SetHitFrom(user);
			p1 -> AddState(weaponmaster, user);
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "WeaponMaster";//ÎäÆ÷¾«Í¨
		}

};



#endif
