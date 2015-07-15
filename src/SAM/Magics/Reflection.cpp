#ifndef Reflection_CPP
#define Reflection_CPP

#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class Reflection : public Magic {

	public:
		Reflection() {
		}
		~Reflection() {
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
			Hero *p1 = dynamic_cast<Hero*>(user);
			Magic *magic2 = p1 -> GetHit();
			Hero *hero = dynamic_cast<Hero*>(p1 -> GetHitFrom());
			if (hero == NULL) return false;
			receiver_ = hero;
			hero -> SetHit(magic2);
			hero -> SetHitFrom(user);
			//magic2->user_ = user;
			//magic2->receiver_ = hero;
			magic2->Use(user_, receiver_, magic2);
			//printf("!!!!!ref : %s -> %s\n", magic2->user_->Display().c_str(), magic2->receiver_->Display().c_str());
			return true;
		}
		void Effect(bool cho = true) {

		}
		string Display() {
			return "Reflection";//∂‹≈∆∑¥…‰
		}

};




#endif
