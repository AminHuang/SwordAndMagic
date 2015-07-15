#ifndef Blind_CPP
#define Blind_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class Blind : public Magic {

	public:
		Blind() {
		}
		~Blind() {
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
			if (receiver -> GetType() != 1) {
				p1 -> DrawCard(1);
				return true;
			}
			Hero *p2 = dynamic_cast<Hero*>(receiver);
			p2 -> SetHit(magic);
			p2 -> SetHitFrom(user);
			p2 -> AskAnswer(user, magic);
			return true;
		}
		void Effect(bool cho = true) {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p1 = dynamic_cast<Hero*>(user);
			Hero *p2 = dynamic_cast<Hero*>(receiver);
			p2 -> AddState(blind, user);
			p1 -> DrawCard(1);
		}
		string Display() {
			return "Blind";//ÖÂÃ¤
		}

};



#endif
