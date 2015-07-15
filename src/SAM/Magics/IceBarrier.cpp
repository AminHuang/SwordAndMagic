#ifndef IceBarrier_CPP
#define IceBarrier_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class IceBarrier : public Magic {

	public:
		IceBarrier() {
		}
		~IceBarrier(){
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
			if (!p1 -> MakeChoice(3)) return false;
			p1 -> SetHit(magic);
			p1 -> SetHitFrom(user);
			p1 -> AddState(shield, user);
			p1 -> Shield(p1 -> GetAtk());
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "IceBarrier";//寒冰护体
		}

};



#endif
