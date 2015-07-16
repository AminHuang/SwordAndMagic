#include "Sword.h"


Sword::Sword() {
	this -> SetType(3);
}


Sword::~Sword() {
}


bool Sword::Attack(Character *user, Character *receiver, int times) {
	return false;
}


int Sword::GetAtk() {
	return 0;
}


bool Sword::Use(Character *user, Character *receiver, Card *card) {
	return false;
}


string Sword::Display() {
	return "";
}


void Sword::UseMagic(Character *user, Character *receiver) {
}
