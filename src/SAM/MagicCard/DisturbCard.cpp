#ifndef DisturbCard_CPP
#define DisturbCard_CPP

#include <string>
using namespace std;
class Reflection;
#include "..\Magics\Reflection.cpp"
class CounterSpell;
#include "..\Magics\CounterSpell.cpp"
class ShadowsCloak;
#include "..\Magics\ShadowsCloak.cpp"
class Card;
#include "..\Card.h"

class DisturbCard : public Card {

	public:
		DisturbCard() {
			this -> SetType(2);
		}
		~DisturbCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Magic *magic = dynamic_cast<Hero*>(user) -> GetHit();
			Hero *hero = dynamic_cast<Hero*>(dynamic_cast<Hero*>(user) -> GetHitFrom());
			int profession = dynamic_cast<Hero*>(user) -> GetProfession();
			if (profession == 1){
				Reflection *reflection = new Reflection();
				reflection -> Use(user, receiver, reflection);
			}
			if (profession == 2) {
				CounterSpell *counterspell = new CounterSpell();
				counterspell -> Use(user, receiver, counterspell);
			}
			if (profession == 3) {
				ShadowsCloak *shadowscloak = new ShadowsCloak();
				shadowscloak -> Use(user, receiver, shadowscloak);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "DisturbCard";//盾牌反射/法术反制/暗影斗篷
		}

};



#endif
