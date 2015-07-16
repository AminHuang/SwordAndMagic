#include "Hero.h"
#include <time.h>

class Comet;
#include "Magics\Comet.cpp"
class Blade;
#include "Magics\Blade.cpp"
#include "Global.h"
#include <iostream>
using std::cout;
using std::endl;

Hero::Hero() {
	states_ = new map<State, Character*>();
	cards_ = new vector<Card*>();
	sword_ = NULL;
	health_ = 0;
	profession_ = 0;
	choose_ = 0;
	maxheal_ = 0;
	heal_ = 0;
	healf_ = 0;
	atk_ = 0;
	addatk_ = 0;
	shield_ = 0;
	hit_ = NULL;
	this->hitfrom_ = NULL;
	this->table_ = NULL;
	sword_ = NULL;
	huixiang_ = 0;
	attacken_ = false;
}


Hero::~Hero() {
	if (states_ != NULL) delete states_;
	if (cards_ != NULL) delete cards_;
}


bool Hero::HaveMagic(string magic) {
	if (magic1_ != NULL) if (magic1_ -> Display() == magic) return true;
	if (magic2_ != NULL) if (magic2_->Display() == magic) return true;
	if (magic3_ != NULL) if (magic3_->Display() == magic) return true;
	return false;
}


bool Hero::Attack(Character *user, Character *receiver, int times) {
	attacken_ = true;
	if (sword_ == NULL) return false;
	return sword_ -> Attack(user, receiver, times);
}


bool Hero::Use(Character *user, Character *receiver, Card *card) {
	if (card == NULL) return false;
	if (card -> Display() == "Chop" || card -> Display() == "Thorn") attacken_ = true;
	if (card->GetType() != 3) {
		vector<Card*>::iterator it;
		for (it = cards_->begin(); it != cards_->end(); it++)
			if ((*it)->GetID() == card->GetID()) {
				cards_->erase(it);
				cardstack_->Discard(card);
				break;
			}
	}
	if (this -> Have(arcaneecho)) {
		if (huixiang_ < 4) {
			huixiang_++;
			this -> DrawCard(1);
		}
	}
	if (this -> Have(arcaneinstability)) {
		if (this->cards_->size() > 0)
			this -> DropACard(this -> cards_ -> at(0));
	}
	cout << "User : " << user->Display() << " play a card" << card->Display() << endl;
	auto player = this->getPlayer();
	if (player->getSeatId() != Global::getPlayer()->getSeatId()) {
		if (receiver == nullptr) {
			player->playCard(card->GetID(), -1);
		}
		else {
			player->playCard(card->GetID(), receiver->getPlayer()->getSeatId());
		}
	}
	bool ye = card -> Use(user, receiver, card);
	this->getPlayer()->getRoom()->updateHp(this->getPlayer()->getSeatId(), heal_);
	this->getPlayer()->getRoom()->updateAttack(this->getPlayer()->getSeatId(), this -> GetAtk());
	this->getPlayer()->updateBuff(this->states_);
	return ye;
}


bool Hero::AskAnswer(Character *user, Card *card) {
	this->getPlayer()->getRoom()->query(user->getPlayer()->getSeatId(), card->GetID(), this->getPlayer()->getSeatId());
	return false;
}


bool Hero::AskAnswer(Character *user, Magic *magic) {
	this->getPlayer()->getRoom()->query(user->getPlayer()->getSeatId(), magic,this->getPlayer()->getSeatId());
	return false;
}


bool Hero::Have(State state) {
	map<State, Character*>::iterator it;
	it = states_ -> find(state);
	if (it == states_ -> end()) return false;
	return true;
}


bool Hero::AddState(State state, Character *user) {
	map<State, Character*>::iterator it;
	it = states_ -> find(state);
	if (it == states_ -> end())
		states_ -> insert(pair<State, Character*> (state, user));
	this->getPlayer()->updateBuff(this->states_);
	printf("%d  get %s\n", state, user->Display().c_str());
	return true;
}


bool Hero::States(int turn) {
	if (turn == 0) {
		attacken_  = false;
		huixiang_ = 0;
		if (this -> Have(deepwounds)) {
			this -> MakeChoice(2);
/*
			if (this -> MakeChoice(2) == 1)
				this -> DisCard();
			else {
				map<State, Character*>::iterator it;
				it = states_ -> find(deepwounds);
				Hero *hero = dynamic_cast<Hero*>(it -> second());
				float dam = hero -> CalDam(8, 0);
				this -> GetHurt(hero, dam, 0);
			}
*/
			this -> ClearState(deepwounds);
		}
		if (this -> Have(dieaftersword)) {
			this -> ClearState(dieaftersword);
		}
		if (this -> Have(iceblock)) {
			this -> ClearState(iceblock);
		}
		if (this -> Have(cheateddeath)) {
			this -> ClearState(cheateddeath);
		}
		if (this -> Have(damageimmunity)) {
			this -> ClearState(damageimmunity);
		}
		if (this -> Have(weaponmaster)) {
			this -> ClearState(weaponmaster);
		}
		if (this -> Have(berserker)) {
			this -> ClearState(berserker);
		}
		if (this -> Have(shield)) {
			if (shield_ < 0.001) {
				shield_ = 0.0;
				this -> ClearState(shield);
			}
		}
		if (this -> Have(stealth)) {
			this -> ClearState(stealth);
		}
		if (this -> Have(crafty)) {
			this -> ClearState(crafty);
		}
	}
	if (!this -> Have(silent)) {
		if (magic1_ != NULL) magic1_ -> CanUse(this, turn);
		if (magic2_ != NULL) magic2_ -> CanUse(this, turn);
		if (magic3_ != NULL) magic3_ -> CanUse(this, turn);
	}
	if (turn == 5) {
		if (this -> Have(mortalwounds)) {
			this -> ClearState(mortalwounds);
		}
		if (this -> Have(silent)) {
			this -> ClearState(silent);
		}
		if (this -> Have(deathwish)) {
			this -> ClearState(deathwish);
		}
		if (this -> Have(arcaneecho)) {
			this -> ClearState(arcaneecho);
		}
		if (this -> Have(coldblood)) {
			this -> ClearState(coldblood);
			this -> LostAll();
		}
		if (this -> Have(arcaneinstability)) {
			this -> ClearState(arcaneinstability);
		}
		if (this -> Have(blind)) {
			this -> ClearState(blind);
		}
		if (this -> Have(avatar)) {
			this -> ClearState(avatar);
		}
		if (this -> Have(sweep)) {
			this -> ClearState(sweep);
		}
		if (this -> Have(weaponmaster)) {
			this -> ClearState(weaponmaster);
		}
		if (this -> Have(berserker)) {
			this -> ClearState(berserker);
		}
		if (this -> Have(shield)) {
			if (shield_ < 0.001) {
				shield_ = 0.0;
				this -> ClearState(shield);
			}
		}
		if (this -> Have(stealth)) {
			this -> ClearState(stealth);
		}
		if (this -> Have(crafty)) {
			this -> ClearState(crafty);
		}
		if (this -> Have(unmeteor)) {
			this -> ClearState(unmeteor);
		}
		if (this->Have(skipdrawturn)) {
			this->ClearState(skipdrawturn);
		}
		if (this->Have(skipactturn)) {
			this->ClearState(skipactturn);
		}
		if (this->Have(skiptotalturn)) {
			this->ClearState(skiptotalturn);
		}
		if (this->Have(skipdiscardturn)) {
			this->ClearState(skipdiscardturn);
		}
		if (this->Have(skipdiscard)) {
			this->ClearState(skipdiscard);
		}
		if (this -> Have(crusharmor1)) {
			this -> ClearState(crusharmor1);
		} else if (this -> Have(crusharmor2)) {
			this -> ClearState(crusharmor2);
		} else if (this -> Have(crusharmor3)) {
			map<State, Character*>::iterator it;
			it = states_ -> find(crusharmor3);
			this -> AddState(crusharmor1, it -> second);
			this -> ClearState(crusharmor3);
		} else if (this -> Have(crusharmor4)) {
			map<State, Character*>::iterator it;
			it = states_ -> find(crusharmor4);
			this -> AddState(crusharmor2, it -> second);
			this -> ClearState(crusharmor4);
		} else if (this -> Have(crusharmor5)) {
			map<State, Character*>::iterator it;
			it = states_ -> find(crusharmor5);
			this -> AddState(crusharmor3, it -> second);
			this -> ClearState(crusharmor5);
		}
	}
	if (shield_ > 0) this -> AddState(shield, this);
	this->getPlayer()->updateBuff(this->states_);
	return true;
}


bool Hero::ClearState(State state) {
	map<State, Character*>::iterator it;
	it = states_ -> find(state);
	if (it != states_ -> end())
		states_ -> erase(it);
	this->getPlayer()->updateBuff(this->states_);
	return true;
}


/*
bool Hero::DeepWounds() {
}
*/


bool Hero::AddCard(Card *card) {
	cards_ -> push_back(card);
	return true;
}


bool Hero::DropACard(Card *card) {
	vector<Card*>::iterator it;
	for (it = cards_ -> begin(); it != cards_ -> end(); it++)
		if ((*it) -> GetID() == card -> GetID()) {
			cards_ -> erase(it);
			cardstack_ -> Discard(card);
			vector<int> x;
			x.push_back(card->GetID());
			this->getPlayer()->getRoom()->discardCards(this->getPlayer()->getSeatId(),x);
			return true;
		}
	if (it == cards_ -> end()) return false;
	return true;
}


bool Hero::Act(Turn *turn) {
	this->getPlayer()->setTurn(turn);
	this->getPlayer()->getRoom()->startTurn();
	return true;
}


bool Hero::DisCard(int k) {
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


bool Hero::LostAll() {
	while (cards_ -> size() > 0) {
		cardstack_ -> Discard(*(cards_ -> begin()));
		cards_ -> erase(cards_ -> begin());
	}
	if (sword_ != NULL)
		cardstack_ -> Discard(sword_);
	sword_ = NULL;
	return true;
}


/*
void Hero::SetChoose(int choose) {
	choose_ = choose;
	if (profession_ == 1) {
		if (choose_ == 1) {
		}
		if (choose_ == 2) {
		}
	}
	if (profession_ == 2) {
		if (choose_ == 1) {
		}
		if (choose_ == 2) {
		}
	}
	if (profession_ == 3) {
		if (choose_ == 1) {
		}
		if (choose_ == 2) {
		}
	}
}
*/


void Hero::Set(int health, int profession, int atk, Magic *magic1, Magic *magic2, Magic *magic3) {
	health_ = health;
	healf_ = health;
	heal_ = health;
	profession_ = profession;
	atk_ = atk;
	magic1_ = magic1;
	magic2_ = magic2;
	magic3_ = magic3;
}


void Hero::SetTable(CardStack *cardstack, vector<Character*> *characters, Table* table) {
	cardstack_ = cardstack;
	characters_ = characters;
	table_ = table;
}


string Hero::Display() {
	return "Hero";
}


/*
void Hero::JudgeMagic(int turn) {
}
*/


class MassiveSmash;
#include "Magics\MassiveSmash.cpp"


bool Hero::GetHurt(Character *user, float dam, int type) {
	if (this -> Have(dieaftersword) && type == 0)
		return true;
	if (this -> Have(iceblock))
		return true;
	if (this -> Have(damageimmunity))
		return true;
	if (user -> GetType() == 1)
		if (dynamic_cast<Hero*>(user) -> HaveMagic("MassiveSmash") && type == 0) {
			MassiveSmash *m = new MassiveSmash();
			m -> Use(user, this, m);
		}
	if (this -> Have(stealth))
		if (dam >= 1.0) dam -= 1.0;
	if (this -> Have(crusharmor1) && type == 0)
		dam += 1.0;
	if (this -> Have(crusharmor2) && type == 0)
		dam += 2.0;
	if (this -> Have(crusharmor3) && type == 0)
		dam += 3.0;
	if (this -> Have(crusharmor4) && type == 0)
		dam += 4.0;
	if (this -> Have(crusharmor5) && type == 0)
		dam += 5.0;
	if (this -> Have(unmeteor) && type == 0)
		this -> ClearState(unmeteor);
	if (this -> Have(shield)) {
		if (shield_ >= dam) {
			shield_ -= dam;
			if (shield_ < 0.001)
				this -> ClearState(shield);
		} else {
			dam -= shield_;
			shield_ = 0.0;
			if (this -> Have(unmeteor) && type == 1) {
				map<State, Character*>::iterator it;
				it = states_ -> find(unmeteor);
				Hero *p = dynamic_cast<Hero*>(it -> second);
				this -> ClearState(unmeteor);
				this -> GetHurt(p, p -> CalDam(15.0, 1), 1);
			}
		}
	}
	healf_ -= dam;
	heal_ = (int)(healf_);
	this->getPlayer()->getRoom()->updateHp(this->getPlayer()->getSeatId(), heal_);
	if (heal_ <= 0)
		this -> Die(user);

	return true;
}


bool Hero::GetHeal(Character *user, float dam, int type) {
	if (this -> Have(mortalwounds))
		dam *= 0.2;
	healf_ += dam;
	if (healf_ > (float)(health_))
		healf_ = (float)(health_);
	heal_ = (int)(healf_);
	this->getPlayer()->getRoom()->updateHp(this->getPlayer()->getSeatId(), heal_);
	return true;
}


int Hero::GetHealth() {
	return heal_;
}


int Hero::GetMaxHealth() {
	return health_;
}


int Hero::GetAtk() {
	int k = atk_;
	if (this -> Have(avatar))
		k += 4;
	if (this -> Have(dragonslayer))
		k += 2;
	if (this -> Have(weaponmaster))
		k += 1;
	if (sword_ != NULL)
		k += sword_ -> GetAtk();
	return k;
}


int Hero::GetProfession() {
	return profession_;
}


int Hero::GetTeam() {
	return team_;
}


bool Hero::SetTeam(int team) {
	team_ = team;
	return true;
}

/*
int Hero::GetID() {
	return id_;
}


bool Hero::SetID(int id) {
	id_ = id;
	return true;
}
*/

Card *Hero::GetSword() {
	return sword_;
}


Magic *Hero::GetHit() {
	return hit_;
}


bool Hero::SetHit(Magic *hit) {
	//if (hit_ != NULL && hit != hit_)
		//delete hit_;
	hit_ = hit;
	return true;
}


Character *Hero::GetHitFrom() {
	return hitfrom_;
}


bool Hero::SetHitFrom(Character *hitfrom) {
	hitfrom_ = dynamic_cast<Hero*>(hitfrom);
	return true;
}


Card *Hero::StealCard(Character *receiver) {
	Hero *p = dynamic_cast<Hero*>(receiver);
	if (p->cards_->size() == 0) return NULL;
	int k = rand() % (p -> cards_ -> size());
	Card *c = p -> cards_ -> at(k);
	for (vector<Card*>::iterator it = p -> cards_ -> begin(); it != p -> cards_ -> end(); it ++)
		if ((*it) -> GetID() == c -> GetID()) {
			p -> cards_ -> erase(it);
			break;
		}
	this -> AddCard(c);
	this->getPlayer()->getRoom()->getRoomScene()->moveCard(receiver->getPlayer()->getSeatId(), c->GetID(), this->getPlayer()->getSeatId());
	return c;
}


bool Hero::MakeChoice(int k, Magic *magic) {
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
		if (cards_ -> size() < 2) {
			map<State, Character*>::iterator it;
			it = states_ -> find(deepwounds);
			this->GetHurt(it->second,  dynamic_cast<Hero*>( it->second)->CalDam(8, 0), 0);
			return false;
		}
		if (2.5 * this -> GetHealth() < this -> GetMaxHealth()) {
			this->DisCard(2);
		}
		int j = rand() % 2;
		if (j == 0) {
			map<State, Character*>::iterator it;
			it = states_ -> find(deepwounds);
			this->GetHurt(it->second, dynamic_cast<Hero*>(it->second)->CalDam(8, 0), 0);
			return true;
		}
		this -> DisCard(2);
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
	return true;
}


void Hero::DrawCard(int k) {
	vector<int> cards;
	while (k--) {
		auto card = cardstack_->GetTheTop();
		this->AddCard(card);
		cards.push_back(card->GetID());
	}
	this->getPlayer()->getRoom()->addCards(this->getPlayer()->getSeatId(), cards);
}


void Hero::ClearAllStates() {
	states_ -> clear();
	this->getPlayer()->updateBuff(this->states_);
}


bool Hero::CometStorm() {
	srand((int)time(0));
	int a[1000];
	int n = characters_->size();
	for (int i = 0; i < n; i++) a[i] = 0;
	for (int i = 0; i < 7; i++) {
		n = characters_->size();
		int yes = false;
		for (int j = 0; j < n; j++) if (a[j] < 3 && characters_ -> at(j) -> GetTeam() != team_) yes = true;
		if (!yes) break;
		int k = rand() % n;
		while (a[k] > 2 || characters_ -> at(k) -> GetTeam() == team_) k = rand() % n;
		a[k]++;
		Comet *c = new Comet();
		c -> Use(this, characters_ -> at(k), c);
	}
	return true;
}


bool Hero::BaoDao() {
	this -> DropACard(sword_);
	sword_ = NULL;
	int n = characters_ -> size();
	for (int i = 0; i < n; i++) {
		Character *c = characters_ -> at(i);
		if (c -> GetTeam() != team_) {
			Blade *b = new Blade();
			b -> Use(this, c, b);
		}
	}
	return true;
}


float Hero::CalDam(float dam, int type) {
	if (this -> Have(dragonslayer))
		dam *= 1.2;
	if (this -> Have(blind))
		return 0.0;
	if (this -> Have(berserker))
		this -> GetHeal(this, this -> CalHeal(1.0, 0), 0);
	if (this -> Have(deathwish)) {
		this -> GetHeal(this, this -> CalHeal(dam / 3.0 * 2.0, 0), 0);
		dam += dam / 3.0;
	}
	if (this -> Have(coldblood))
		dam *= 1.5;
	if (this -> Have(berserker))
		this -> GetHeal(this, this -> CalHeal(1.0, 0), 0);
	if (this -> Have(sweep)) {
		//cout << "123" << endl;
		srand((int)time(0));
		int n = characters_ -> size();
		int k = rand() % n;
		while (characters_ -> at(k) -> GetTeam() == team_) k = rand() % n;
		characters_ -> at(k) -> GetHurt(this, dam / 2.0, 0);
	}
	return dam;
}


float Hero::CalHeal(float dam, int type) {
	if (this -> Have(dragonslayer))
		dam *= 1.2;
	return dam;
}


/*
bool Hero::DiscardABaseCard() {
}
*/


bool Hero::Shield(float dam) {
	shield_ += dam;
	this -> AddState(shield, this);
	return true;
}


bool Hero::Attack() {
	return attacken_;
}


void Hero::Die(Character* killer) {
	if (this -> Have(cheateddeath)) {
		healf_ = 10.0;
		heal_ = (int)(healf_);
		this -> AddState(damageimmunity, this);
		this -> DrawCard(3);
		return;
	}
	this -> LostAll();
	table_ -> Die(this);
}
/*
void Hero::setPlayer(Player *player) {
	this->player = player;
}


Player * Hero::getPlayer() {
	return this->player;
}
*/
