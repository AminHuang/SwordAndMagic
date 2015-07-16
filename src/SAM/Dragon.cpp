#include "Dragon.h"

#include <typeinfo>
class Hero;
#include "Hero.h"

Dragon::Dragon() {
	startatk_ = false;
}


Dragon::~Dragon() {
}


bool Dragon::Attack(Character *user) {
	for (int i = 0; i < characters_ -> size(); i++)
		if (characters_ -> at(i) -> GetType() != 2) {
			Hero *player = dynamic_cast<Hero*>(characters_ -> at(i));
			float k = static_cast<float>(player -> GetMaxHealth()) / 10.0 + atk_;
			player -> GetHurt(user, k);
		}
	return true;
}


void Dragon::Die(Character *killer) {
	table_ -> Die(this);
	return;
}


void Dragon::Set(int health, int atk) {
	health_ = health;
	atk_ = atk;
	return;
}


void Dragon::SetTable(CardStack *cardstack, vector<Character*> *characters, Table *table) {
	characters_ = characters;
	table_ = table;
	return;
}


string Dragon::Display() {
	return "Dragon";
}


bool Dragon::StartAtk() {
	return startatk_;
}


bool Dragon::GetHurt(Character *user, float dam, int type) {
	startatk_ = true;
	healf_ -= dam;
	heal_ = static_cast<int>(healf_);
	if (heal_ <= 0) Die(user);
	return true;
}


bool Dragon::GetHeal(Character *user, float dam, int type) {
	healf_ += dam;
	heal_ = static_cast<int>(healf_);
	return true;
}


int Dragon::GetTeam() {
	return -1;
}
