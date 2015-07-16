#ifndef Magic_H
#define Magic_H


#include <string>
#include <vector>
#include <map>
using namespace std;
class Character;
#include "Character.h"

class Magic {

	public:
		Magic();
		~Magic();
		virtual bool CanUse(Character *user, int turn = 3);
		virtual bool Passive();
		virtual bool Use(Character *user, Character *receiver, Magic *magic);
		virtual void Effect(bool cho = true);
		virtual string Display();
		Character *user_;
		Character *receiver_;

};



#endif
