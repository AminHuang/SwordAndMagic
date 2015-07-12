#ifndef __ONGAME_SCENE_H__
#define __ONGAME_SCENE_H__
#include "cocos2d.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

class  CardStack;
#include "SAM\CardStack.h"


using std::string;
using std::vector;
using std::map;
using std::queue;
USING_NS_CC;

class OnGame : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void startGame();
	void timerCallBack(float dt);

	void gameOver(int type);
	void playCard(int sid,int cardId,int targetSid);
	void addCards(int sid, std::vector<int> cardIds);
	void query(int sid,int cardId,int targetSid);
	void query(int sid, Magic *magic, int targetSid);
	void updateHp(int sid, int hpVal);  //更新某个玩家的生命值
	void updateAttack(int sid, int attackVal); //更新某个玩家的攻击力

	void resort(int sid);
	void setListener(Sprite * button, string originImg, string hoverImg, string clickImg, int type);  //给按钮设置时间相应的统一方法
	void selectHero();  //玩家选择英雄之类的特效
	Vec2 handleOutCards(); //处理玩家丢弃的牌
	void clearOutCards();  //清楚场面上的弃牌
	void setBtnRotate(Sprite *btn); //设置按钮旋转
	static void loadChapter(int chapterId); //载入关卡数据
	void resetData(); //重置房间的数据
	void displayBeforeSelect(); //在显示选择角色窗口前房间应该显示的东西
	void displayAfterSelect(); //在显示选择角色窗口后房间应该显示的东西
	void drawLine(int sid,int targetSid); //画线
	void setBuff(int sid, int cardId, int targetSid); //设置buff
	void addBuff(int sid, string buffName,int index); //添加buff
	void addBuff(int sid, vector<string> buffNames); //添加一堆buff
	void discardCards(int sid,vector<int> cardIds); //弃牌
	void moveCard(int sid, int cardId, int targetSid); //将牌移动到另一个人手里
	void createPlayCardPanel(); //添加玩牌的按钮
	void startTurn(); //开始玩家回合
	void endTurn();//结束玩家回合
	void changeTimer(float dt);
	void myUpdate(float dt);
	bool isOkBtnAble();//是否禁用确定按钮
	void discardTurn();//弃牌阶段
	//void setTimer(int sid);
	Node * playCardPanel; //玩家玩牌的面板，包括确定和结束
	CREATE_FUNC(OnGame);
private:
	int targetSid; //玩家选择的出牌对象sid
	int roleId; //玩家选择的角色id
	static int chapterId; //当前所在的关卡
	int cardId; //query的时候的cardId
	/*
	* 计时条有关的属性
	*/
	int time; //倒计时30秒
	int frameTime; //每秒60帧计时条的更新
	double timerScale; //计时条scale属性

	int toBeDiscardNum; //玩家应该丢弃的牌的数量
	int discardedNum;//玩家已经丢弃的牌的数量
	vector<int> cardIds;


	Magic *magic;
	Sprite * role; //玩家当前所选中的角色精灵
	Sprite *targetPic; // 玩家所选择的角色图片
	Sprite * card; //玩家当前所选中的牌
	queue<Sprite *> outCards;  //玩家所丢弃的牌
	vector<Sprite *> disCards; //
	LayerColor * cover; //对丢弃的牌的遮罩
	Sprite * timer;
	Node * selectPanel; //玩家选择角色的面板
	Sprite *role_back;
	Label *discardInfo;

	CC_SYNTHESIZE(bool,isSortable,IsSortable);
	map<int, vector<Sprite *>*> cards;
	map<int, vector<Sprite *>*> buffPics;


};
#endif