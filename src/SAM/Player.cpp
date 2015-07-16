#include "Player.h"
#include "Room.h"

using std::cerr;
using std::endl;
using std::cout;
Player::Player() {
	this->_ready = false;
	this->_seatId = -1;
	this->_role = -1;
	this->_room = nullptr;
	this->_auto = true;
	this->_cardNum = 0;
	this->hpVal = 30;
	this->attackVal = 4;
	this->_hitNum = 1;
	for (int i = 0; i < 20; i++) {
		this->_cardArray[i] = 0;
	}
	this->_userData = -1;
}
Player::Player(Character *_hero) {
	this->_ready = false;
	this->_seatId = -1;
	this->_role = -1;
	this->_room = nullptr;
	this->_auto = true;
	this->_cardNum = 0;
	
	this->_hitNum = 1;
	for (int i = 0; i < 20; i++) {
		this->_cardArray[i] = 0;
	}
	this->_userData = -1;
	this->_hero = _hero;
	auto hero = dynamic_cast<Hero*>(_hero);
	this->hpVal = hero->GetHealth();
	this->attackVal = hero->GetAtk();
	hero->setPlayer(this);
}
int Player::getRole() {
	return this->_role;
}
int Player::getSeatId() {
	return this->_seatId;
}
void Player::setHp(Label *hp) {
	this->hp = hp;
}
Label * Player::getHp() {
	return this->hp;
}
void Player::setHpVal(int hpVal) {
	this->hpVal = hpVal;
}
int Player::getHpVal() {
	return this->hpVal;
}
bool Player::isReady() {
	return this->_ready;
}
bool Player::isAuto() {
	return this->_auto;
}
int Player::getCardNum() {
	return this->_cardNum;
}

void Player::setRole(int _role) {
	this->_role = _role;
}
void Player::setSeatId(int _seatId) {
	this->_seatId = _seatId;
}
void Player::setReady(bool _ready) {
	this->_ready = _ready;
}
void Player::setHitNum(int hitNum) {
	this->_hitNum = hitNum;
}
int Player::getHitNum() {
	return this->_hitNum;
}
void Player::setAuto(bool _auto) {
	this->_auto = _auto;
}

void Player::addCard(int _cardId) {
	this->_cardArray[_cardId]++;
	this->_cardNum++;
}
void Player::addCard(std::vector<int>_cardids) {
	for (int i = 0; i < _cardids.size(); i++) {
		this->addCard(_cardids[i]);
	}
}
void Player::removeCard(int _cardId) {
	this->_cardArray[_cardId]--;
	this->_cardNum--;
	if (this->_cardNum < 0) {
		cerr << "Error : _cardNum can't smaller than 0!" << endl;
		this->_cardNum = 0;
	}
}
int * Player::getCards() {
	return this->_cardArray;
}

void Player::playCard(int cardId, int targetSid) {
	cout << "Info : sid " << this->getSeatId() << " play card " << cardId << endl;
	/*
	if (cardId == 1) {
		if (this->getHitNum() <= 0)
			cout << "Error : hitNum less than 0 but play card hit!" << endl;
		this->setHitNum(this->getHitNum() - 1);
	}
	if (cardId > 0) {
		if (this->_cardArray[cardId] <= 0) {
			cerr << "Error : don't have this card!" << endl;
			return;
		}
		this->removeCard(cardId);
	}
	*/
	Room * room = this->getRoom();
	room->playCard(this->getSeatId(), cardId, targetSid);
}
Room * Player::getRoom() {
	return this->_room;
}
void Player::enterRoom(Room *_room) {
	if (_room == nullptr) {
		cerr << "Error : When enterRoom, the room is null" << endl;
		return;
	}
	this->_room = _room;
	_room->addPlayer(this);
}
void Player::leaveRoom() {
	if (this->_room == nullptr) {
		cerr << "When leaveRoom, the room is null" << endl;
	}
	this->_room = nullptr;
	this->_room->removePlayer(this);
}
void Player::handle(int cardId) {

}

void Player::setLocation(Vec2 loc) {
	this->_loc = loc;
}

Vec2 Player::getLocation() {
	return this->_loc;
}

void Player::setHeadPicSize(Size size) {
	this->_headPicSize = size;
}

Size Player::getHeadPicSize() {
	return this->_headPicSize;
}

void Player::setCharacter(Character *_hero) {
	this->_hero = _hero;
	auto hero = dynamic_cast<Hero*>(_hero);
	this->hpVal = hero->GetHealth();
	this->attackVal = hero->GetAtk();
	hero->setPlayer(this);
}

Character * Player::getHero() {
	return this->_hero;
}

int Player::getTeamId() {
	return this->teamId;
}

int Player::getAttackVal() {
	return this->attackVal;
}

void Player::setAttackVal(int attack) {
	this->attackVal = attack;
}

Label * Player::getAttack() {
	return this->attack;
}

void Player::setAttack(Label *attack) {
	this->attack = attack;
}


Sprite *Player::getHeadPic() {
	return this->headPic;
}

void Player::setHeadPic(Sprite *headPic) {
	this->headPic = headPic;
}

void Player::setTeamId(int teamId) {
	this->teamId = teamId;
}



void Player::addBuff(string buffName) {
	for (auto _buffName : buffs) {
		if (_buffName == buffName)
			return;
	}
	this->buffs.push_back(buffName);
	this->getRoom()->getRoomScene()->addBuff(this->getSeatId(), buffName, buffs.size());
}

void Player::updateBuff(map<State, Character *> *states) {
	vector<string> buffNames;

	for (auto _state :*states) {
		auto state = _state.first;
		string buffName = "";
		switch (state) {
		case mortalwounds:
			buffName = "mortalwounds";
			break;
		case silent:
			buffName = "silent";
			break;
		case deathwish:
			buffName = "deathwish";
			break;
		case arcaneecho:
			buffName = "arcaneecho";
			break;
		case coldblood:
			buffName = "coldblood";
			break;
		case deepwounds:
			buffName = "deepwounds";
			break;
		case arcaneinstability:
			buffName = "arcaneinstability";
			break;
		case dieaftersword:
			buffName = "dieaftersword";
			break;
		case iceblock:
			buffName = "iceblock";
			break;
		case cheateddeath:
			buffName = "cheateddeath";
			break;
		case damageimmunity:
			buffName = "damageimmunity";
			break;
		case skipdrawturn:
			buffName = "skipdrawturn";
			break;
		case skipactturn:
			buffName = "skipactturn";
			break;
		case skiptotalturn:
			buffName = "skiptotalturn";
			break;
		case skipdiscardturn:
			buffName = "skipdiscardturn";
			break;
		case skipdiscard:
			buffName = "skipdiscard";
			break;
		case blind:
			buffName = "blind";
			break;
		case avatar:
			buffName = "avatar";
			break;
		case sweep:
			buffName = "sweep";
			break;
		case heal:
			buffName = "heal";
			break;
		case harm:
			buffName = "harm";
			break;
		case weaponmaster:
			buffName = "weaponmaster";
			break;
		case berserker:
			buffName = "berserker";
			break;
		case shield:
			buffName = "shield";
			break;
		case stealth:
			buffName = "stealth";
			break;
		case	crafty:
			buffName = "crafty";
			break;
		case unmeteor:
			buffName = "unmeteor";
			break;
		case crusharmor1:
			buffName = "crusharmor1";
			break;
		case crusharmor2:
			buffName = "crusharmor2";
			break;
		case crusharmor3:
			buffName = "crusharmor3";
			break;
		case crusharmor4:
			buffName = "crusharmor4";
			break;
		case crusharmor5:
			buffName = "crusharmor5";
			break;
		case dragonslayer:
			buffName = "dragonslayer";
			break;
		}
		//cout << buffName << endl;
		buffNames.push_back(buffName);
	}
	this->getRoom()->addBuff(this->getSeatId(), buffNames);
}

void Player::setTurn(Turn *turn) {
	this->turn = turn;
}

Turn *Player::getTurn() {
	return this->turn;
}