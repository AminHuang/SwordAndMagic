#ifndef HuXueDong_CPP
#define HuXueDong_CPP


class Hero;
#include "..\Hero.h"
class Magic;
#include "..\Magic.h"
class UnDragonBreath;
#include "..\Magics\UnDragonBreath.cpp"
class UnMeteor;
#include "..\Magics\UnMeteor.cpp"
class Fireball;
#include "..\Magics\Fireball.cpp"
class IceBarrier;
#include "..\Magics\IceBarrier.cpp"

class HuXueDong : public Hero {

	public:
		HuXueDong(int choose) {
			UnDragonBreath *undragonbreath = new UnDragonBreath();
			magic1 = undragonbreath;
			UnMeteor *unmeteor = new UnMeteor();
			magic2 = unmeteor;
			if (choose == 1) {
				Fireball *fireball = new Fireball();
				magic3 = fireball;
			} else {
				IceBarrier *icebarrier = new IceBarrier();
				magic3 = icebarrier;
			}
			this -> Set(60, 2, 4, magic1, magic2, magic3);
			this -> SetType(1);
		}
		~HuXueDong() {
			delete magic1;
			delete magic2;
			delete magic3;
		}
		string Display() {
			return "HuXueDong";
		}
	private:
		Magic *magic1;
		Magic *magic2;
		Magic *magic3;

};



#endif
