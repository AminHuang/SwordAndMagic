#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <time.h>
#include <iostream>
#include <string>
USING_NS_CC;

using std::string;
class HelloWorld : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void setStar(Vec2 loc, double s_scale, double b_scale,int angle, double duration);
	void setListener(Sprite * button, string originImg, string hoverImg, string clickImg, int type);
	CREATE_FUNC(HelloWorld);
private:
	Sprite *sword;
};
#endif

