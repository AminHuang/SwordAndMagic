#include "Character.h"


Character::Character() {
	type_ = 0;
}


Character::~Character() {
}


bool Character::GetHurt(Character *user, float dam, int type) {
	return false;
}


bool Character::GetHeal(Character *user, float dam, int type) {
	return false;
}


int Character::GetTeam() {
	return -1;
}


void Character::SetTable(CardStack *cardstack, vector<Character*> *characters, Table* table) {
	return;
}


string Character::Display() {
	return "";
}


int Character::GetID() {
	return ID_;
}


void Character::SetID(int ID) {
	ID_ = ID;
}


int Character::GetType() {
	return type_;
}


void Character::SetType(int type) {
	type_ = type;
}


void Character::setPlayer(Player *player) {
	this->player = player;
}


Player * Character::getPlayer() {
	return this->player;
}
