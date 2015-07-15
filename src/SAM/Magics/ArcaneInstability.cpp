#ifndef ArcaneInstability_CPP
#define ArcaneInstability_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class ArcaneInstability : public Magic {

	public:
		ArcaneInstability() {
		}
		~ArcaneInstability() {
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
			if (receiver -> GetType() != 1) return false;
			Hero *p2 = dynamic_cast<Hero*>(receiver);
			p2 -> SetHit(magic);
			p2 -> SetHitFrom(user);
			p2 -> AskAnswer(user, magic);
			return true;
		}
		void Effect(bool cho = true) {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p2 = dynamic_cast<Hero*>(receiver);
			p2 -> AddState(arcaneinstability, user);
		}
		string Display() {
			return "ArcaneInstability";//°ÂÊõ¶¯µ´
		}

};



#endif
