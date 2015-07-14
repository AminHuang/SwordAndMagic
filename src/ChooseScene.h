#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__

#include "cocos2d.h"
#include <string>
using std::string;
USING_NS_CC;

class Choose : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void setListener(Sprite * button, string originImg, string hoverImg, string clickImg,int type);
	CREATE_FUNC(Choose);
private:
	int chapterId;   //玩家当前选择的关卡id
	Sprite * chapter; //玩家当前所选择的关卡精灵
	ClippingNode * clipping; //裁剪节点

};
#endif