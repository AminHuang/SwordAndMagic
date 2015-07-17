#ifndef HuXin_CPP
#define HuXin_CPP


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

class HuXin : public Hero {

	public:
		HuXin(int choose) {
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
		~HuXin() {
			delete magic1;
			delete magic2;
			delete magic3;
		}
		string Display() {
			return "HuXin";
		}
	private:
		Magic *magic1;
		Magic *magic2;
		Magic *magic3;

};



#endif
