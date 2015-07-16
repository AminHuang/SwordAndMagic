#include "CardStack.h"


class Chop;
#include "BaseCard\Chop.cpp"
class Dodge;
#include "BaseCard\Dodge.cpp"
class HealthStone;
#include "BaseCard\HealthStone.cpp"
class Parry;
#include "BaseCard\Parry.cpp"
class Thorn;
#include "BaseCard\Thorn.cpp"
class AoeCard;
#include "MagicCard\AoeCard.cpp"
class AttackCard;
#include "MagicCard\AttackCard.cpp"
class BuffCard;
#include "MagicCard\BuffCard.cpp"
class ControlCard;
#include "MagicCard\ControlCard.cpp"
class DebuffCard;
#include "MagicCard\DebuffCard.cpp"
class DefenseCard;
#include "MagicCard\DefenseCard.cpp"
class DisturbCard;
#include "MagicCard\DisturbCard.cpp"
class PassCard;
#include "MagicCard\PassCard.cpp"

CardStack::CardStack() {
	cardstack_ = new vector<Card*>();
	cardstack_ -> clear();
	desertstack_ = new vector<Card*>();
	desertstack_ -> clear();
	cards_ = new vector<Card*>();
	cards_ -> clear();
	num_ = 0;
	Card *p;
	
	
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	p = new Chop();
	this -> NewCard(p);
	
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	p = new Dodge();
	this -> NewCard(p);
	
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	p = new Parry();
	this -> NewCard(p);
	
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	p = new Thorn();
	this -> NewCard(p);
	
	p = new HealthStone();
	this -> NewCard(p);
	p = new HealthStone();
	this -> NewCard(p);
	p = new HealthStone();
	this -> NewCard(p);
	p = new HealthStone();
	this -> NewCard(p);
	p = new HealthStone();
	this -> NewCard(p);
	
	
	p = new AoeCard();
	this -> NewCard(p);
	p = new AoeCard();
	this -> NewCard(p);
	p = new AoeCard();
	this -> NewCard(p);
	
	p = new AttackCard();
	this -> NewCard(p);
	p = new AttackCard();
	this -> NewCard(p);
	p = new AttackCard();
	this -> NewCard(p);
	
	p = new BuffCard();
	this -> NewCard(p);
	p = new BuffCard();
	this -> NewCard(p);
	p = new BuffCard();
	this -> NewCard(p);
	
	p = new ControlCard();
	this -> NewCard(p);
	p = new ControlCard();
	this -> NewCard(p);
	
	p = new DebuffCard();
	this -> NewCard(p);
	p = new DebuffCard();
	this -> NewCard(p);
	p = new DebuffCard();
	this -> NewCard(p);
	
	p = new DefenseCard();
	this -> NewCard(p);
	p = new DefenseCard();
	this -> NewCard(p);
	p = new DefenseCard();
	this -> NewCard(p);
	
	/*
	p = new DisturbCard();
	this -> NewCard(p);
	p = new DisturbCard();
	this -> NewCard(p);
	p = new DisturbCard();
	this -> NewCard(p);
	*/
	
	p = new PassCard();
	this -> NewCard(p);
	p = new PassCard();
	this -> NewCard(p);
	p = new PassCard();
	this -> NewCard(p);
	
	
	for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
		cardstack_ -> push_back(*it);
	this -> Shuffle();
}


CardStack::~CardStack() {
	if (cardstack_ != NULL) delete cardstack_;
	if (desertstack_ != NULL) delete desertstack_;
	if (cards_ != NULL) {
		for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
			delete &(*it);
		delete cards_;
	}
}


Card *CardStack::GetTheTop() {
	if (cardstack_->size() == 0) {
		if (desertstack_->size() == 0) {
			printf("error\n");
			return NULL;
		}
		cardstack_ = desertstack_;
		desertstack_ = new vector<Card*>();
		desertstack_ -> clear();
		this -> Shuffle();
	}
	Card *card = cardstack_ -> at(0);
	cardstack_ -> erase(cardstack_ -> begin());
	return card;
}


bool CardStack::Shuffle() {
	vector<Card*> *cardstack = new vector<Card*>();
	srand((int)time(0));
	while (cardstack_ -> size() > 0) {
		int k = rand() % cardstack_ -> size();
		cardstack -> push_back(cardstack_ -> at(k));
		cardstack_ -> erase(cardstack_ -> begin() + k);
	}
	vector<Card*> *ppp = cardstack_;
	cardstack_ = cardstack;
	delete ppp;
	return true;
}


bool CardStack::Discard(Card *card) {
	desertstack_ -> push_back(card);
	return true;
}


void CardStack::NewCard(Card *card) {
	cards_ -> push_back(card);
	card -> SetID(num_);
	num_ ++;
}


Card *CardStack::GetCard(int id) {
	return cards_ -> at(id);
}


void CardStack::Display() {
	printf("cards\n");
	for (int i = 0; i < cards_ -> size(); i++)
		printf("%s %d\n", cards_ -> at(i) -> Display().c_str(), cards_ -> at(i) -> GetID());
	printf("\ncardstack_\n");
	for (int i = 0; i < cardstack_ -> size(); i++)
		printf("%s %d\n", cardstack_ -> at(i) -> Display().c_str(), cardstack_ -> at(i) -> GetID());
	printf("\ndesertstack_\n");
	for (int i = 0; i < desertstack_ -> size(); i++)
		printf("%s %d\n", desertstack_ -> at(i) -> Display().c_str(), desertstack_ -> at(i) -> GetID());
	printf("\n");
}
