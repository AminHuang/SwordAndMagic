#include <typeinfo>
#include "AI.h"


class Card;
#include "Card.h"
class Chop;
#include "BaseCard\Chop.cpp"
class Thron;
#include "BaseCard\Thorn.cpp"
class Parry;
#include "BaseCard\Parry.cpp"
class Dodge;
#include "BaseCard\Dodge.cpp"
class HealthStone;
#include "BaseCard\HealthStone.cpp"
class DisturbCard;
#include "MagicCard\DisturbCard.cpp"
#include <iostream>
using namespace std;


AI::AI() {
}


AI::~AI() {
}


bool AI::AskAnswer(Character *user, Card *card) {
	if (card -> Display() == "Chop") {
		for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
			if ((*it) -> Display() == "Parry") {
				this -> Use(this, this, *it);
				return true;
			}
		card -> Effect();
		return false;
	}
	if (card -> Display() == "Thorn") {
		for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
			if ((*it) -> Display() == "Dodge") {
				this -> Use(this, this, *it);
				return true;
			}
		card -> Effect();
		return false;
	}
}


bool AI::AskAnswer(Character *user, Magic *magic) {
	for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
		if ((*it) -> Display() == "DisturbCard") {
			this -> Use(this, this, *it);
			return true;
		}
	magic -> Effect();
	return false;
}


class Turn;

bool AI::Act(Turn *turn) {
	this -> TryMagic();
	int k = rand() % 5 + 3;
	int kk = 0;
	while (k--) {
		for (int oo = 0; oo < 100000; oo++);
		if (cards_ -> size() == 0) break;
		bool yes = false;
		for (int i = 0; i < cards_ -> size(); i++)
			if (cards_ -> at(i) -> Display() != "Parry" && cards_ -> at(i) -> Display() != "Dodge"
				&& cards_ -> at(i) -> Display() != "DisturbCard") {
					yes = true;
					if (cards_->at(i)->Display() == "HealthStone" || cards_->at(i)->Display() == "BuffCard"
						|| cards_->at(i)->Display() == "DefenseCard" || cards_->at(i)->Display() == "PassCard") {
						if (cards_->at(i)->Display() != "HealthStone" || GetMaxHealth() - GetHealth() >= 8)
							this->Use(this, this, cards_->at(i));
					}
					else 
						if (cards_ -> at(i) -> Display() == "AoeCard")
							this -> Use(this, NULL, cards_ -> at(i));
						else 
							if (cards_ -> at(i) -> GetType() == 3) 
								this -> Use(this, this, cards_ -> at(i));
							else {
								/*
								if (cards_->at(i)->Display() == "ControlCard") {
									yes = false;
									break;
								}*/
								if (cards_->at(i)->Display() == "Thorn" || cards_->at(i)->Display() == "Chop") {
									if (kk == 3) {
										yes = false;
										break;
									}
									kk++;
								}
								for (int j = 0; j < characters_ -> size(); j++) {
									Character *c = characters_ -> at(j);
									if (c -> GetType() == 2)
										this -> Use(this, characters_ -> at(j), cards_ -> at(i));
									else if (dynamic_cast<Hero*>(characters_ -> at(j)) -> team_ != this -> team_) {
										this -> Use(this, characters_ -> at(j), cards_ -> at(i));
									}
								}
							}
					break;
				}
		if (!yes) break;
	}
	turn->DiscardTurn();
	return true;
}


bool AI::DisCard(int k) {
	vector<int> x;
	x.clear();
	for (int i = 0; i < k; i++) {
		if (cards_->size() == 0) return false;;
		int j = rand() % cards_->size();
		x.push_back(cards_->at(j)->GetID());
		for (vector<Card*>::iterator it = cards_->begin(); it != cards_->end(); it++)
			if ((*it)->GetID() == cards_->at(j)->GetID()) {
				cardstack_->Discard(cards_->at(j));
				cards_->erase(it);
				break;
			}
	}
	this->getPlayer()->getRoom()->discardCards(this->getPlayer()->getSeatId(), x);
	return true;
}


bool AI::MakeChoice(int k, Magic *magic) {
	if (k == 1) {
		if (2.5 * this -> GetHealth() < this -> GetMaxHealth())
			magic -> Effect(true);
		else {
			int j = rand() % 2;
			if (j == 0) magic -> Effect(true);
			else magic -> Effect(false);
			return true;
		}
	}
	if (k == 2) {
		if (cards_ -> size() < 2)
			return false;
		if (2.5 * this -> GetHealth() < this -> GetMaxHealth())
			return true;
		int j = rand() % 2;
		if (j == 0) return true;
		return false;
	}
	if (k == 3) {
		for (vector<Card*>::iterator it = cards_ -> begin(); it != cards_ -> end(); it++)
			if ((*it) -> Display() == "Parry" || (*it) -> Display() == "Chop" ||
			(*it) -> Display() == "Thorn" || (*it) -> Display() == "Dodge" ||
			(*it) -> Display() == "HealthStone") {
				this -> DropACard(*it);
			}
		return true;
	}
	return false;
}


string AI::Display() {
	return "";
}


void AI::TryMagic() {
}
