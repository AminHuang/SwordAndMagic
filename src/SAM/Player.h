#ifndef __PLAYER_H
#define __PLAYER_H


#include <vector>
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

#include "Room.h"
class Room;
#include "SAM\Hero.h"
class Hero;


class Player {
private:
	int _role;  //��ҵĽ�ɫ
	bool _ready; //����Ƿ�׼��
	bool _auto; //����Ƿ��ǵ���
	int _cardArray[20]; //��ҵ������飨��ϣӳ�䣩
	int _seatId; //��ҵ���λ��
	int _userData; //��ҵ���Ϣ
	Room * _room; //��ҵķ����������
	Character * _character;
	int _cardNum;//ʣ��������
	int hpVal; //���Ѫ����ֵ
	int _hitNum;
	int teamId;
	int attackVal;
	Label *attack; //��ҹ�������label��ǩ

	Vec2 _loc; //���ͷ�����ڵ�����
	Size _headPicSize; //���ͷ��Ĵ�С
	std::vector<Sprite *> * cards;
	Label * hp; //���Ѫ����label��ǩ
	Sprite * headPic; //��ҵ�ͷ��
	Character *_hero;
	vector<string> buffs;
	Turn *turn;
public:
	Player();
	Player(Character *_hero);
	~Player();
	int getRole(); //�����û���ɫ
	void setRole(int _role); //�����û���ɫ
	int getAttackVal(); //������ҹ�����
	void setAttackVal(int attack); //������ҹ�����
	Label *getAttack();
	void setAttack(Label *attack);
	void setCharacter(Character *character);
	bool isReady(); //�����û��Ƿ�׼��
	void setReady(bool _ready); //�����û��Ƿ�׼��
	bool isAuto();//�����û��Ƿ��Զ�
	void setHp(Label* hp);
	Label * getHp();
	void setHitNum(int hitNum);
	int getHitNum();
	void setHpVal(int hpVal); //���õ�ǰ�û�������ֵ
	int getHpVal(); //��õ�ǰ�û�������ֵ
	void setAuto(bool _auto);//�����û��Ƿ��Զ� 
	int getSeatId(); //�Ż��û�����λ��
	int getCardNum(); //�����û�������Ŀ
	int *getCards();//�����û��Ŀ���
	Room * getRoom(); //�����û����ڵķ���
	int getTeamId();//������ҵĶ���id
	void setTeamId(int teamId);
	void setSeatId(int _seatId); //�����û�����λ��
	void addCard(int _cardId); //���û����һ����
	void addCard(std::vector<int> _cardId); //���û����һ����
	void removeCard(int _cardId); //ɾ���û���һ����
	void playCard(int cardId,int targetSid); //��ҳ�ĳ����
	void handle(int cardId); //��Ҵ���ĳ����
	void enterRoom(Room *_room); //�û�����ĳ������
	void leaveRoom(); //�û��뿪����
	void setLocation(Vec2 loc);
	Vec2 getLocation();
	void setHeadPicSize(Size size);
	Size getHeadPicSize();
	Character * getHero();
	Sprite * getHeadPic();
	void setHeadPic(Sprite *headPic);
	void addBuff(string buffName); //���buff
	void updateBuff(map<State, Character *> *x); 
	void setTurn(Turn * turn);
	Turn * getTurn();
};
#endif