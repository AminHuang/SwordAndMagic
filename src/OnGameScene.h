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
	void updateHp(int sid, int hpVal);  //����ĳ����ҵ�����ֵ
	void updateAttack(int sid, int attackVal); //����ĳ����ҵĹ�����

	void resort(int sid);
	void setListener(Sprite * button, string originImg, string hoverImg, string clickImg, int type);  //����ť����ʱ����Ӧ��ͳһ����
	void selectHero();  //���ѡ��Ӣ��֮�����Ч
	Vec2 handleOutCards(); //������Ҷ�������
	void clearOutCards();  //��������ϵ�����
	void setBtnRotate(Sprite *btn); //���ð�ť��ת
	static void loadChapter(int chapterId); //����ؿ�����
	void resetData(); //���÷��������
	void displayBeforeSelect(); //����ʾѡ���ɫ����ǰ����Ӧ����ʾ�Ķ���
	void displayAfterSelect(); //����ʾѡ���ɫ���ں󷿼�Ӧ����ʾ�Ķ���
	void drawLine(int sid,int targetSid); //����
	void setBuff(int sid, int cardId, int targetSid); //����buff
	void addBuff(int sid, string buffName,int index); //���buff
	void addBuff(int sid, vector<string> buffNames); //���һ��buff
	void discardCards(int sid,vector<int> cardIds); //����
	void moveCard(int sid, int cardId, int targetSid); //�����ƶ�����һ��������
	void createPlayCardPanel(); //������Ƶİ�ť
	void startTurn(); //��ʼ��һغ�
	void endTurn();//������һغ�
	void changeTimer(float dt);
	void myUpdate(float dt);
	bool isOkBtnAble();//�Ƿ����ȷ����ť
	void discardTurn();//���ƽ׶�
	//void setTimer(int sid);
	Node * playCardPanel; //������Ƶ���壬����ȷ���ͽ���
	CREATE_FUNC(OnGame);
private:
	int targetSid; //���ѡ��ĳ��ƶ���sid
	int roleId; //���ѡ��Ľ�ɫid
	static int chapterId; //��ǰ���ڵĹؿ�
	int cardId; //query��ʱ���cardId
	/*
	* ��ʱ���йص�����
	*/
	int time; //����ʱ30��
	int frameTime; //ÿ��60֡��ʱ���ĸ���
	double timerScale; //��ʱ��scale����

	int toBeDiscardNum; //���Ӧ�ö������Ƶ�����
	int discardedNum;//����Ѿ��������Ƶ�����
	vector<int> cardIds;


	Magic *magic;
	Sprite * role; //��ҵ�ǰ��ѡ�еĽ�ɫ����
	Sprite *targetPic; // �����ѡ��Ľ�ɫͼƬ
	Sprite * card; //��ҵ�ǰ��ѡ�е���
	queue<Sprite *> outCards;  //�������������
	vector<Sprite *> disCards; //
	LayerColor * cover; //�Զ������Ƶ�����
	Sprite * timer;
	Node * selectPanel; //���ѡ���ɫ�����
	Sprite *role_back;
	Label *discardInfo;

	CC_SYNTHESIZE(bool,isSortable,IsSortable);
	map<int, vector<Sprite *>*> cards;
	map<int, vector<Sprite *>*> buffPics;


};
#endif