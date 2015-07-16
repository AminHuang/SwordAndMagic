#ifndef __ROOM_H_
#define __ROOM_H_

#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include "Player.h"
class Player;
#include "Consts.h"
#include "OnGameScene.h"
#include "SAM\Table.h"

using std::queue;
struct playTurn {
	int sid;
	int cardId;
	int targetSid;
	int type;
	Magic *magic;
	vector<int> cardIds;
	playTurn() {
		sid = -1;
		targetSid = -1;
		cardId = -1;
		type = 0;
	}
	playTurn(int sid, int cardId, int targetSid, int type) {
		this->sid = sid;
		this->cardId = cardId;
		this->targetSid = targetSid;
		this->type = type;
		this->magic = nullptr;
	}
	playTurn(int sid, Magic* magic, int targetSid, int type) {
		this->sid = sid;
		this->cardId = cardId;
		this->targetSid = targetSid;
		this->type = type;
		this->magic = magic;
	}
	playTurn(int sid, vector<int> cardIds,int type) {
		this->sid = sid;
		this->cardIds = cardIds;
		this->type = type;
	}
};

class Room : public Node {
private:
	int _playerCnt;
	int _rid;
	int _status;
	OnGame * _roomScene;
	static const int MAX_PLAYER = 10;
	Player *_playerArr[MAX_PLAYER];
	//Turn new_turn;
	int curSid;
	Table *_table;
	queue<playTurn> turns;
	CC_SYNTHESIZE(bool, isActable, IsActable);
	static int _ridGenerator();
public:
	CREATE_FUNC(Room);
	virtual bool init();
	void setTable(Table *table);
	Table *getTable();
	void setStatus(int _status); //���÷����״̬
	int getStatus(); //���ط����״̬
	OnGame * getRoomScene();
	void setRoomScene(OnGame * roomScene);
	void startGame(); //��ʼ��Ϸ
	void setTurn(int sid, int cardId, int targetSid);
	//Turn getTurn();
	void setCurSid(int sid);
	int getCurSId();
	void next();
	void gameOver(); //������Ϸ
	void playCard(int sid, int cardId, int targetSid); //����Գ��ƽ�����ת���� 
	void addPlayer(Player *_player); //���ĳ�����
	void removePlayer(Player *_player); //�Ƴ�ĳ�����
	Player *getPlayerBySeatId(int seatId); //ͨ����λ�Ż�����
	int getPlayerCnt();
	void playCard(float dt);
	void addCards(int sid, std::vector<int> cardIds);
	void query(int sid, int cardId, int targetSid);
	void query(int sid, Magic *magic, int targetSid);
	void updateHp(int sid, int hpVal);  //����ĳ����ҵ�����ֵ
	void updateAttack(int sid, int attackVal); //����ĳ����ҵĹ�����
	void addBuff(int sid, vector<string> buffNames);
	void discardCards(int sid, vector<int> cardIds);
	void enterTable();
	void startTurn();
	void endTurn();
	queue<playTurn> getTurn();

};
#endif