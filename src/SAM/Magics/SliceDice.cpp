#ifndef SliceDice_CPP
#define SliceDice_CPP


#include <typeinfo>
class Magic;
#include "..\Magic.h"
class Character;
#include "..\Character.h"
class Hero;
#include "..\Hero.h"
class Dragon;
#include "..\Dragon.h"

class SliceDice : public Magic {

	public:
		SliceDice() {
		}
		~SliceDice() {
		}
		bool CanUse(Character *user, int turn = 3) {
			if (dynamic_cast<Hero*>(user) -> GetSword() == NULL)
				return false;
			if (turn == 3)
				return true;
			return false;
		}
		bool Passive() {
			return false;
		}
		bool Use(Character *user, Character *receiver, Magic *magic) {
			Hero *p1 = dynamic_cast<Hero*>(user);	
			p1 -> BaoDao();
			return true;
		}
		void Effect(bool cho = true) {
		}
		string Display() {
			return "SliceDice";//½£ÈÐÂÒÎè
		}

};



#endif
