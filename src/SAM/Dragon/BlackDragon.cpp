#ifndef BlackDragon_CPP
#define BlackDragon_CPP



class Dragon;
#include "..\Dragon.h"
class Hero;
#include "..\Hero.h"

class BlackDragon : public Dragon {

	public:
		BlackDragon() {
			this -> Set(50, 5);
			this -> SetType(2);
		}
		~BlackDragon() {
		}
		void Die(Character *killer) {
			if (killer -> GetType() == 1)
				dynamic_cast<Hero*>(killer) -> AddState(dragonslayer, this);
			table_ -> Die(this);
			return;
		}
		string Display() {
			return "BlackDragon";
		}

};



#endif
