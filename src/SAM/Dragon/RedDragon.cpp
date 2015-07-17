#ifndef RedDragon_CPP
#define RedDragon_CPP



class Dragon;
#include "..\Dragon.h"
class Hero;
#include "..\Hero.h"

class RedDragon : public Dragon {

	public:
		RedDragon() {
			this -> Set(20, 2);
			this -> SetType(2);
		}
		~RedDragon() {
		}
		void Die(Character *killer) {
			if (killer -> GetType() == 1)
				dynamic_cast<Hero*>(killer) -> DrawCard(5);
			table_ -> Die(this);
			return;
		}
		string Display() {
			return "RedDragon";
		}

};



#endif
