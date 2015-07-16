#include "Card.h"


Card::Card() {

}


Card::~Card() {

}


bool Card::Use(Character *user, Character *receiver, Card *card) {
	return false;
}


void Card::Effect() {
	return;
}


string Card::Display() {
	return "";
}


int Card::GetID() {
	return id_;
}


bool Card::SetID(int id) {
	id_ = id;
	return true;
}


int Card::GetType() {
	return type_;
}


void Card::SetType(int type) {
	type_ = type;
}
