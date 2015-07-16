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
	int _role;  //玩家的角色
	bool _ready; //玩家是否准备
	bool _auto; //玩家是否是电脑
	int _cardArray[20]; //玩家的牌数组（哈希映射）
	int _seatId; //玩家的座位号
	int _userData; //玩家的信息
	Room * _room; //玩家的房间对象引用
	Character * _character;
	int _cardNum;//剩余牌数量
	int hpVal; //玩家血量的值
	int _hitNum;
	int teamId;
	int attackVal;
	Label *attack; //玩家攻击力的label标签

	Vec2 _loc; //玩家头像所在的坐标
	Size _headPicSize; //玩家头像的大小
	std::vector<Sprite *> * cards;
	Label * hp; //玩家血量的label标签
	Sprite * headPic; //玩家的头像
	Character *_hero;
	vector<string> buffs;
	Turn *turn;
public:
	Player();
	Player(Character *_hero);
	~Player();
	int getRole(); //返回用户角色
	void setRole(int _role); //设置用户角色
	int getAttackVal(); //设置玩家攻击力
	void setAttackVal(int attack); //返回玩家攻击力
	Label *getAttack();
	void setAttack(Label *attack);
	void setCharacter(Character *character);
	bool isReady(); //返回用户是否准备
	void setReady(bool _ready); //设置用户是否准备
	bool isAuto();//返回用户是否自动
	void setHp(Label* hp);
	Label * getHp();
	void setHitNum(int hitNum);
	int getHitNum();
	void setHpVal(int hpVal); //设置当前用户的生命值
	int getHpVal(); //获得当前用户的生命值
	void setAuto(bool _auto);//设置用户是否自动 
	int getSeatId(); //放回用户的座位号
	int getCardNum(); //返回用户卡的数目
	int *getCards();//返回用户的卡组
	Room * getRoom(); //返回用户所在的房间
	int getTeamId();//返回玩家的队伍id
	void setTeamId(int teamId);
	void setSeatId(int _seatId); //设置用户的座位号
	void addCard(int _cardId); //给用户添加一张牌
	void addCard(std::vector<int> _cardId); //给用户添加一组牌
	void removeCard(int _cardId); //删除用户的一张牌
	void playCard(int cardId,int targetSid); //玩家出某张牌
	void handle(int cardId); //玩家处理某张牌
	void enterRoom(Room *_room); //用户进入某个房间
	void leaveRoom(); //用户离开房间
	void setLocation(Vec2 loc);
	Vec2 getLocation();
	void setHeadPicSize(Size size);
	Size getHeadPicSize();
	Character * getHero();
	Sprite * getHeadPic();
	void setHeadPic(Sprite *headPic);
	void addBuff(string buffName); //添加buff
	void updateBuff(map<State, Character *> *x); 
	void setTurn(Turn * turn);
	Turn * getTurn();
};
#endif