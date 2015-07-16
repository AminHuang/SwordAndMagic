#ifndef __CONSTS_H_
#define __CONSTS_H_

#include <iostream>
#include "cocos2d.h"
#include <string>

USING_NS_CC;

using std::cout;
using std::endl;
using std::string;
class Consts{
public:
	~Consts();
	Consts();
	static string base;
	static string rolePics[2];
	static string rolePicsClick[2];
	static int maxChapter;
	static string heroPics[2];
	static string heros[3];
	static enum eventType {
		invalid,
		playCard,
		queryCard,
		queryMagic,
		endTurn,
		startTurn,
		addCard,
		updateBuff,
		updateHp,
		updateAttack,
		discarding
	};
	static enum RoomType {
		before,
		play,
		cardQuery,
		magicQuery,
		pmagicQuery,
		wait,
		discard
	};
};

#endif __CONSTS_H_