#ifndef Character_H
#define Character_H


#include <vector>
#include <map>
#include <string>
using namespace std;
class Table;
#include "Table.h"
class CardStack;
#include "CardStack.h"

class Player;
//#include "Player.h"
class Character {

	public:
		Character();
		~Character();
		virtual bool GetHurt(Character *user, float dam, int type = 0);
		virtual bool GetHeal(Character *user, float dam, int type = 0);
		virtual int GetTeam();
		virtual void SetTable(CardStack *cardstack, vector<Character*> *characters, Table *table);
		Player * getPlayer();
		void setPlayer(Player *player);
		virtual string Display();
		int GetType();
		void SetType(int type);
		int GetID();
		void SetID(int ID);
	private:
		int ID_;
		int type_;
		Player *player;
		// 0  character,  1 hero  ,  2 dragon

};



#endif
