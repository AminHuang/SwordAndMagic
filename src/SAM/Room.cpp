#include "Room.h"
#include "Utils.h"
#include "Global.h"
#include "SAM\Heros\HuXueDong.cpp"
#include "SAM\Heros\HuXin.cpp"
#include "SAM\Heros\HuXinAI.cpp"

using std::cerr;
using std::cout;
using std::endl;

bool Room::init() {
	for (int i = 0; i < Room::MAX_PLAYER; i++) {
		this->_playerArr[i] = nullptr;
	}
	this->_playerCnt = 0;
	this->_roomScene = nullptr;
	this->_rid = Room::_ridGenerator();
	this->_status = Consts::RoomType::wait;
	this->setIsActable(true);
	
	return true;
}

void Room::setRoomScene(OnGame * roomScene) {
	this->_roomScene = roomScene;
}

OnGame * Room::getRoomScene() {
	return this->_roomScene;
}

void Room::addPlayer(Player *_player) {
	
	if (_player == nullptr) {
		cerr << "When addPlayer, the player is null" << endl;
		return;
	}
	for (int i = 0; i < Room::MAX_PLAYER; i++) {
		if (this->_playerArr[i] == nullptr) {
			cout << "Info : add player seatid is " << i << endl;
			this->_playerArr[i] = _player;
			_player->setSeatId(i);
			this->_playerCnt++;
			return;
		}
	}
	
	cerr << "Error : The room is full!" << endl;
}
void Room::removePlayer(Player *_player) {
	if (_player == nullptr) {
		cerr << "When removePlayer, the player is null" << endl;
		return;
	}
	auto seatId = _player->getSeatId();
	if (seatId < 0 || seatId > Room::MAX_PLAYER) {
		cerr << "Invalid seatId!" << endl;
		return;
	}
	if (this->_playerArr[seatId] == nullptr) {
		cerr << "The seat is empty!" << endl;
		return;
	}
	else {
		this->_playerArr[seatId] = nullptr;
	}
	this->_playerCnt--;
	if (_playerCnt < 0) {
		cerr << "The playerCnt less than 0!" << endl;
		_playerCnt = 0;
	}
}
Player *Room::getPlayerBySeatId(int seatId) {
	return this->_playerArr[seatId];
}
/**开始游戏
1.给房间的所有用户发牌
*/
void Room::startGame() {
	this->schedule(schedule_selector(Room::playCard), 2.0f);
	//发牌阶段
	int cardType = 2;
	srand(time(0));
	for (int i = 0; i < this->_playerCnt; i++) {
		Player *player = this->getPlayerBySeatId(i);

		//dynamic_cast<Hero *>(player->getHero())->DrawCard(4);


		/*
		int num = 5;
		std::vector<int> tmp;
		while (num--) {

			auto cardId = Utils::random() * cardType;
			cout << "Info : player "<<i<<" add card "<<(int)cardId<< endl;
			player->addCard((int)cardId);
			tmp.push_back(cardId);
		}
		this->_roomScene->add(player->getSeatId(), tmp);
		*/
	}
	

	//其他
	
}
void Room::gameOver() {
	//
}
void Room::playCard(int sid, int cardId, int targetId) {
	cout << "Info : sid " << sid << " play card " << cardId <<", targetId is "<< targetId<<endl;
	if (cardId == -1) {
		return;
	}
	Player *player = this->getPlayerBySeatId(sid);
	auto hero = player->getHero();
	auto card = this->getTable()->GetCardStack()->GetCard(cardId);
	if (sid == Global::getPlayer()->getSeatId()) {
		this->_roomScene->playCard(sid, cardId, targetId);
		if (targetId == -1) {
			dynamic_cast<Hero *>(hero)->Use(hero, nullptr, card);
		}
		else {
			dynamic_cast<Hero *>(hero)->Use(hero, this->getPlayerBySeatId(targetId)->getHero(), card);
		}
	}
	else {
		playTurn turn = playTurn(sid,cardId,targetId,Consts::playCard);
		this->turns.push(turn);
	}
}
void Room::setTurn(int sid, int cardId, int targetSid) {
	//this->new_turn.sid = sid;
	//this->new_turn.cardId = cardId;
	//this->new_turn.targetSid = targetSid;
}
//Turn Room::getTurn() {
	//return this->new_turn;
//}
void Room::next() {
	int sid = this->getCurSId();
	int nextSid = (sid + 1) % this->_playerCnt;
	this->setCurSid(nextSid);
	Player *player = this->getPlayerBySeatId(nextSid);
	player->setHitNum(1);
	if (player->isAuto()) {
		if (player->getCards()[1] > 0)
			player->playCard(1, 0);
		else {
			this->next();
		}
	}
}
void Room::playCard(float dt) {
	//cout << turns.size() << endl;
	//cout << "-----" << endl;
	if (!this->turns.empty() && this->getIsActable()) {
		
		this->setIsActable(false);
		auto turn = turns.front();
		int sid = turn.sid;
		int targetSid = turn.targetSid;
		int cardId = turn.cardId;
		auto magic = turn.magic;
		auto cards = turn.cardIds;
		//cout << turn.type << endl;
		switch (turn.type) {
		case Consts::playCard:
			this->_roomScene->playCard(sid, cardId, targetSid);
			turns.pop();
			break;
		case Consts::queryCard:
			this->_status = Consts::RoomType::cardQuery;
			this->getRoomScene()->query(sid, cardId, targetSid);
			turns.pop();
			break;
		case Consts::queryMagic:
			if (this->_status == Consts::play) {
				this->_status = Consts::RoomType::pmagicQuery;
			}
			else if (this->_status == Consts::wait) {
				this->_status = Consts::RoomType::magicQuery;
			}
			else {
				cout << "Error : when magic query, room status is " << this->_status << endl;
			}
			this->getRoomScene()->query(sid, magic, targetSid);
			turns.pop();
			break;
		case Consts::endTurn:
			this->getRoomScene()->endTurn();
			turns.pop();
			break;
		case Consts::startTurn :
			this->_status = Consts::RoomType::play;
			this->getRoomScene()->startTurn();
			turns.pop();
			break;
		case Consts::addCard:
			/*
			if (cards.size() == 4) {
				while (cards.size() == 4) {
					auto turn = turns.front();
					cards = turn.cardIds;
					int sid = turn.sid;
					this->getRoomScene()->addCards(sid, cards);
					turns.pop();
				}
			}
			*/
			this->getRoomScene()->addCards(sid, cards);
			turns.pop();
			break;
		case Consts::discarding:
			this->getRoomScene()->discardCards(sid, cards);
			turns.pop();
			break;
		default:
			break;
		}
	}
}
void Room::setCurSid(int curSid) {
	this->curSid = curSid;
}
int Room::getCurSId() {
	return this->curSid;
}
int Room::getPlayerCnt() {
	return this->_playerCnt;
}
int Room::_ridGenerator() {
	static int i = 1;
	return i++;
}

void Room::setTable(Table *table) {
	this->_table = table;
}

Table * Room::getTable() {
	return this->_table;
}

void Room::addCards(int sid,vector<int>cards) {
	playTurn turn = playTurn(sid, cards,Consts::addCard);
	this->turns.push(turn);
}

void Room::query(int sid, int cardId, int targetSid) {
	playTurn turn = playTurn(sid, cardId, targetSid, Consts::queryCard);
	this->turns.push(turn);
	
}

void Room::query(int sid, Magic *magic, int targetSid) {
	playTurn turn = playTurn(sid, magic, targetSid, Consts::queryMagic);
	this->turns.push(turn);
}

void Room::updateHp(int sid, int HpVal) {
	this->getRoomScene()->updateHp(sid, HpVal);
}

void Room::updateAttack(int sid, int attackVal) {
	this->getRoomScene()->updateAttack(sid, attackVal);
}

void Room::enterTable() {
	for (int i = 0; i < this->_playerCnt; i++) {
		auto player = this->getPlayerBySeatId(i);
		if (player->getSeatId() != Global::getPlayer()->getSeatId()) {
			player->setCharacter(new HuXinAI(1));
		}
		else {
			if (player->getRole() == 1) {
				player->setCharacter(new HuXueDong(1));
			}
			else {
				player->setCharacter(new HuXin(1));
			}
		}
		this->_table->AddCharacter(player->getHero(), -1, player->getTeamId());
	}

	this->_table->Act();

}
void Room::startTurn() {
	playTurn turn = playTurn(0, 0, 0, Consts::startTurn);
	this->turns.push(turn);
}

void Room::endTurn() {
	playTurn turn = playTurn(0, 0, 0, Consts::endTurn);
	this->turns.push(turn);
}

void Room::setStatus(int status) {
	this->_status = status;
}

int Room::getStatus() {
	return this->_status;
}

queue<playTurn> Room::getTurn() {
	return this->turns;
}

void Room::addBuff(int sid, vector<string>buffNames) {
	this->getRoomScene()->addBuff(sid, buffNames);
}

void Room::discardCards(int sid, vector<int>cardIds) {
	playTurn turn = playTurn(sid, cardIds, Consts::discarding);
	this->turns.push(turn);
}