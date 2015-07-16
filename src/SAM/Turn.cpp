#include "Turn.h"


#include <typeinfo>
class Character;
#include "Character.h"
class CardStack;
#include "CardStack.h"
class Hero;
#include "Hero.h"
class Dragon;
#include "Dragon.h"

Turn::Turn() {
	character_ = NULL;
	cardstack_ = NULL;
}


Turn::Turn(Character *character, CardStack *cardstack, Table *table) {
	character_ = character;
	cardstack_ = cardstack;
	table_ = table;
}


Turn::~Turn() {
}


bool Turn::StartTurn() {
	if (character_ -> GetType() == 1) {
		player_ = dynamic_cast<Hero*>(character_);
		player_ -> States(0);
		if (player_ -> Have(skiptotalturn))
			return EndTurn();
		return DrawTurn();
	}
	if (character_ -> GetType() == 2) {
		Dragon *dragon = dynamic_cast<Dragon*>(character_);
		if (dragon -> StartAtk())
			dragon -> Attack(character_);
		return true;
	}
	return false;
}


bool Turn::DrawTurn() {
	//printf("aa: %s\n'", player_->Display().c_str());
	if (player_ -> Have(skipdrawturn))
		return SeedTurn();
	player_ -> States(1);
	player_ -> DrawCard(2);
	return SeedTurn();
}


bool Turn::SeedTurn() {
	player_ -> States(2);
	return PlayTurn();
}


bool Turn::PlayTurn() {
	player_ -> States(3);
	if (player_ -> Have(skipactturn) || player_ -> Have(iceblock))
		return DiscardTurn();
	player_->Act(this);
	//return DiscardTurn();
}


bool Turn::DiscardTurn() {
	player_ -> States(4);
	if (player_ -> Have(skipdiscardturn))
		return SeedTurn();
	if (player_ -> Have(skipdiscard))
		return EndTurn();
	int i = player_ -> GetHealth();
	if (player_ -> Have(crafty))
		i = player_ -> GetMaxHealth() / 2;
	i = i / 10 + 1;
	//printf("aa: %d %d\n", i, player_->cards_->size());
	if (player_ -> cards_ -> size() > i)
		player_ -> DisCard(player_ -> cards_ -> size() - i);
	return EndTurn();
}


bool Turn::EndTurn() {
	player_->States(5);
	//player_->getPlayer()->getRoom()->getRoomScene()->resort(player_->getPlayer()->getSeatId());
	table_->Act2();
	return true;
}
