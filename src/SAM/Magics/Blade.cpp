#ifndef Blade_CPP
#define Blade_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class Blade : public Magic {

	public:
		Blade() {
		}
		~Blade() {
		}
		bool CanUse(Character *user, int turn = 3) {
			return false;
		}
		bool Passive() {
			return false;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			user_ = user;
			receiver_ = receiver;
			Hero *p1 = dynamic_cast<Hero*>(user);
			if (receiver -> GetType() == 1) {
				Hero *p2 = dynamic_cast<Hero*>(receiver);
				p2 -> SetHit(magic);
				p2 -> SetHitFrom(user);
				p2 -> AskAnswer(user, magic);
			} else {
				float dam = 5.0;
				dam = p1 -> CalDam(dam, 0);
				receiver -> GetHurt(user, dam, 0);
			}
			return true;
		}
		void Effect(bool cho = true) {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p1 = dynamic_cast<Hero*>(user);
			Hero *p2 = dynamic_cast<Hero*>(receiver);
			float dam = 5.0;
			dam = p1 -> CalDam(dam, 0);
			p2 -> GetHurt(user, dam, 0);
		}
		string Display() {
			return "Blade";//½£ÈÐ
		}

};



#endif
