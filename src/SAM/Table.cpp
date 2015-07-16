#include "Table.h"


#include <typeinfo>
class Turn;
#include "Turn.h"

Table::Table() {
	act_ = 0;
	num_ = 0;
	characters_ = new vector<Character*>();
	characters_ -> clear();
	cardstack_ = new CardStack();
	turn_ = NULL;
}


Table::~Table() {
	if (characters_ != NULL) {
		vector<Character*>::iterator it;
		for (it = characters_ -> begin(); it != characters_ -> end();) {
			Character* character = *it;
			delete character;
			it++;
		}
		delete characters_;
	}
	if (cardstack_ != NULL) delete cardstack_;
}


bool Table::Act() {
	if (turn_ != NULL) delete turn_;
	if (characters_->size() == 0) return false;
	Character *character = characters_->at(act_);
	turn_ = new Turn(character, cardstack_, this);
	turn_->StartTurn();
	return true;
}


bool Table::Act2() {
	//delete turn_;
	/*if (typeid(*character) == 1)
	for (int i = 0; i < characters_ -> size(); i++)
		if (typeid(*characters_ -> at(i)) == 1)
			dynamic_cast<Hero*>(characters_ -> at(i)) -> ClearState();
	*/
	act_++;
	act_ = act_ % characters_ -> size();
	characters_->at(0)->getPlayer()->getRoom()->endTurn();
	//this -> Act();
	return true;
}


void Table::AddCharacter(Character *character, int num, int team) {
	character -> SetTable(cardstack_, characters_, this);
	if (character -> GetType() == 1) {
		dynamic_cast<Hero*>(character) -> SetTeam(team);
		dynamic_cast<Hero*>(character) -> DrawCard(4);
		num_ ++;
	}	
	if (num >= characters_ -> size() || num < 0)
		characters_ -> push_back(character);
	else
		characters_ -> insert(characters_ -> begin() + num, character);
	for (int i = 0; i < characters_ -> size(); i++)
		characters_ -> at(i) -> SetID(i);
	return;
}


void Table::Die(Character *character) {
	for (vector<Character*>::iterator it = characters_ -> begin(); it != characters_ -> end(); it++) {
		if ((*it) -> GetID() == character -> GetID()) {
			if (character -> GetType() == 1)
				num_ --;
			characters_ -> erase(it);
			break;
		}
	}
	bool victory = true;
	bool defeat = true;
	for (int i = 0; i < characters_->size(); i++) {
		if (characters_->at(i)->GetTeam() != 1)
			victory = false;
		if (characters_->at(i)->GetTeam() == 1)
			defeat = false;
	}
	if (victory && !defeat)
		characters_->at(0)->getPlayer()->getRoom()->getRoomScene()->gameOver(1);
	else if (!victory && defeat)
		characters_->at(0)->getPlayer()->getRoom()->getRoomScene()->gameOver(2);
	return;
}


CardStack *Table::GetCardStack() {
	return cardstack_;
}
