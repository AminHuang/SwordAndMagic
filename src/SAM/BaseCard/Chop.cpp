#ifndef Chop_CPP
#define Chop_CPP


#include <string>
#include <typeinfo>
using namespace std;
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"
class Character;
#include "..\Character.h"
class Card;
#include "..\Card.h"


class Chop : public Card {

	public:
		Chop() {
			this -> SetType(1);
		}
		~Chop() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			user_ = user;
			receiver_ = receiver;
			if (receiver -> GetType() == 1) {
				dynamic_cast<Hero*>(receiver) -> AskAnswer(user, card);
			} else if (receiver -> GetType() == 2) {
				this -> Effect();
			}
			return true;
		}
		void Effect() {
			Character *user = user_;
			Character *receiver = receiver_;
			Hero *p1 = dynamic_cast<Hero*>(user);
			receiver -> GetHurt(user, p1 -> CalDam(p1 -> GetAtk(), 0), 0);
		}
		string Display() {
			return "Chop";//斩
		}

};



#endif
