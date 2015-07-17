#ifndef HuXinAI_CPP
#define HuXinAI_CPP


class AI;
#include "..\AI.h"
class Hero;
#include "..\Hero.h"
class Magic;
#include "..\Magic.h"
class MassiveSmash;
#include "..\Magics\MassiveSmash.cpp"
class Armageddon;
#include "..\Magics\Armageddon.cpp"
class WeaponMaster;
#include "..\Magics\WeaponMaster.cpp"
class Berserker;
#include "..\Magics\Berserker.cpp"

class HuXinAI : public AI {

	public:
		HuXinAI(int choose) {
			MassiveSmash *massivesmash = new MassiveSmash();
			magic1 = massivesmash;
			Armageddon *armageddon = new Armageddon();
			magic2 = armageddon;
			if (choose == 1) {
				WeaponMaster *weaponmaster = new WeaponMaster();
				magic3 = weaponmaster;
			} else {
				Berserker *berserker = new Berserker();
				magic3 = berserker;
			}
			this -> Set(60, 1, 6, magic1, magic2, magic3);
			this -> SetType(1);
		}
		~HuXinAI() {
			delete magic1;
			delete magic2;
			delete magic3;
		}
		string Display() {
			return "HuXinAI";
		}
		void TryMagic() {
			Character *c = NULL;
			for (int i = 0; i < characters_ -> size(); i++)
				if (characters_ -> at(i) -> GetTeam() != this -> GetTeam()) {
					c = characters_ -> at(i);
					break;
				}
			if (magic2 -> CanUse(this))
				magic2 -> Use(this, c, magic2);
		}
	private:
		Magic *magic1;
		Magic *magic2;
		Magic *magic3;

};



#endif
