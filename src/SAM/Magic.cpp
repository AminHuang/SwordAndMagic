#include "Magic.h"


Magic::Magic() {

}


Magic::~Magic() {

}


bool Magic::CanUse(Character *user, int turn) {
	return false;
}


bool Magic::Passive() {
	return false;
}


bool Magic::Use(Character *user, Character *receiver, Magic *magic) {
	return false;
}


void Magic::Effect(bool cho) {
	return;
}


string Magic::Display() {
	return "";
}
