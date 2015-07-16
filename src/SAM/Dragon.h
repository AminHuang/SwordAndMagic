#ifndef Dragon_H
#define Dragon_H

#include <vector>
using namespace std;
class Character;
#include "Character.h"
class CardStack;
#include "CardStack.h"
class Table;
#include "Table.h"


class Dragon : public Character {

	public:
		Dragon();
		~Dragon();
		bool Attack(Character *user);
		virtual void Die(Character *killer);
		void Set(int health, int atk);
		void SetTable(CardStack *cardstack, vector<Character*> *characters, Table *table);
		virtual string Display();
		bool StartAtk();
		bool GetHurt(Character *user, float dam, int type = 0);
		bool GetHeal(Character *user, float dam, int type = 0);
		int GetTeam();
		Table *table_;
	private:
		int health_;
		int heal_;
		float healf_;
		int atk_;
		bool startatk_;
		vector<Character*> *characters_;

};



#endif
