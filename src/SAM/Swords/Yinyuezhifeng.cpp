#ifndef Yinyuezhifeng_CPP
#define Yinyuezhifeng_CPP



class Sword;
#include "..\Sword.h"
class Comet;
#include "..\Magics\Comet.cpp"

class Yinyuezhifeng : public Sword {
	// chop chop thorn thron chop
	public:
		Yinyuezhifeng() {
		}
		~Yinyuezhifeng() {
		}
		bool Attack(Character *user, Character *receiver, int times) {
		}
		int GetAtk() {
			return 5;
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			if (dynamic_cast<Hero*>(user) -> sword_ != NULL)
				dynamic_cast<Hero*>(user) -> cardstack_ -> Discard(dynamic_cast<Hero*>(user) -> sword_);
			dynamic_cast<Hero*>(user) -> sword_ = this;
		}
		string Display() {
			return "Yinyuezhifeng";
		}
		void UseMagic(Character *user, Character *receiver) {
			Magic *m = new Comet();
			m -> Use(user, receiver, m);
		}

};



#endif
