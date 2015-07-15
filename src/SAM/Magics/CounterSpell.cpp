#ifndef Counterspell_CPP
#define Counterspell_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class CounterSpell : public Magic {

	public:
		CounterSpell() {
		}
		~CounterSpell() {
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
			Hero *hero = dynamic_cast<Hero*>(p1 -> GetHitFrom());
			receiver_ = hero;
			hero -> SetHit(magic);
			hero -> SetHitFrom(user);
			hero -> AskAnswer(user, magic);
			return true;
		}
		void Effect(bool cho = true) {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p1 = dynamic_cast<Hero*>(user);
			dynamic_cast<Hero*>(user_) -> StealCard(receiver_);
		}
		string Display() {
			return "CounterSpell";//法术反制
		}

};



#endif
