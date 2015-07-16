#ifndef Table_H
#define Table_H

#include <vector>
#include <map>
using namespace std;
class Character;
#include "Character.h"
class CardStack;
#include "CardStack.h"
class Magic;
#include "Magic.h"
class Turn;

class Table {

	public:
		Table();
		~Table();
		bool Act();
		bool Act2();
		void AddCharacter(Character *character, int num, int team);
		void Die(Character *character);
		CardStack *GetCardStack();
	private:
		int act_;
		int num_;
		vector<Character*> *characters_;
		CardStack *cardstack_;
		Turn *turn_;
		//map<Character*, Magic*> *magics_;
		
};



#endif
