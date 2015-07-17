#ifndef PassCard_CPP
#define PassCard_CPP


#include <string>
using namespace std;
class Avatar;
#include "..\Magics\Avatar.cpp"
class Evocation;
#include "..\Magics\Evocation.cpp"
class BlurredSpeed;
#include "..\Magics\BlurredSpeed.cpp"
class Card;
#include "..\Card.h"

class PassCard : public Card {

	public:
		PassCard() {
			this -> SetType(2);
		}
		~PassCard() {
		}
		bool Use(Character *user, Character *receiver, Card *card) {
			Hero *p1 = dynamic_cast<Hero*>(user);
			int profession = p1 -> GetProfession();
			if (profession == 1) {
				Avatar *avatar = new Avatar();
				avatar -> Use(user, receiver, avatar);
			}
			if (profession == 2) {
				Evocation *evocation = new Evocation();
				evocation -> Use(user, receiver, evocation);
			}
			if (profession == 3) {
				BlurredSpeed *blurredspeed = new BlurredSpeed();
				blurredspeed -> Use(user, receiver, blurredspeed);
			}
			return true;
		}
		void Effect() {
		}
		string Display() {
			return "PassCard";//ÌìÉñÏÂ·²/»½ĞÑ/¼²ÅÜ
		}

};



#endif
