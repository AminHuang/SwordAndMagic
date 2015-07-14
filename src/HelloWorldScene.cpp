#include "HelloWorldScene.h"
#include "ChooseScene.h"
#include "Utils.h"
#include "Consts.h"
#include <iostream>
//#include "SAM\Table.h"


using std::cout;
using std::endl;

Scene* HelloWorld::createScene() {
	auto scene = Scene::create();
	auto layer = HelloWorld::create();

	auto backgroud = Sprite::create("../../Resources/backgroud_begin.jpg");
	Size s = Director::getInstance()->getWinSize();
	backgroud->setContentSize(s);
	backgroud->setScaleX((double)s.width / 1920);
	backgroud->setScaleY((double)s.height / 1080);
	backgroud->setAnchorPoint(Vec2(0,0));
	backgroud->setZOrder(-1000);
	layer->addChild(backgroud);
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}
	Size s = Director::getInstance()->getWinSize();
	if (!UserDefault::getInstance()->isXMLFileExist()) {
		UserDefault::getInstance()->setIntegerForKey("curChapter",1);
	}
	//auto snow = ParticleSnow::create();
	//auto snow = ParticleMeteor::create();
	//auto snow = ParticleGalaxy::create();
	//auto snow = ParticleSun::create();
	//auto snow = ParticleFire::create();
	//auto snow = ParticleSpiral::create();
	//auto snow = ParticleExplosion::create();
	//auto snow = ParticleFireworks::create();
	//auto snow = ParticleFlower::create();
	//auto rain = ParticleRain::create();
	//auto snow = ParticleSmoke::create();
	//rain->setTexture(TextureCache::getInstance()->addImage("../../Resources/rain.png"));
	//this->addChild(rain);
	//auto snow = ParticleSystemQuad::create("../../Resources/snow.plist");
	//snow->setBlendAdditive(false);
	//snow->setScale(1.5f);
	//snow->setPosition(s.width / 4, s.height / 2);
	//this->addChild(snow);

	srand(time(0));
	int angle = Utils::random(0, 90);
	int duration = Utils::random(1, 4);
	this->setStar(Vec2(s.width * 3/4,s.height * 3/4), 0.2f, 0.6f,angle,duration);
	angle = Utils::random(0, 90);
	duration = Utils::random(1, 4);
	this->setStar(Vec2(s.width / 2, s.height * 3 / 4 + 20), 0.2f, 1.2f, angle, duration);
	angle = Utils::random(0, 90);
	duration = Utils::random(1, 4);
	this->setStar(Vec2(s.width * 1/ 4, s.height * 3 / 4 + 50), 0.2f, 0.6f, angle, duration);

	auto galaxy = ParticleGalaxy::create();
	galaxy->setTexture(TextureCache::getInstance()->addImage("../../Resources/smoke.png"));
	galaxy->setPosition(s.width / 2, s.height * 3 / 4);
	this->addChild(galaxy);

	auto logo = Sprite::create(Consts::base + "logo.png");
	logo->setPosition(s.width / 2 + 10, s.height / 2 + 200);
	logo->setScale(0.5f);
	this->addChild(logo);

	auto begin_btn = Sprite::create(Consts::base + "begin_game.png");
	begin_btn->setPosition(s.width / 2, s.height / 2);
	begin_btn->setScale(0.5f);
	this->addChild(begin_btn);
	this->setListener(begin_btn, Consts::base + "begin_game.png", Consts::base +  "begin_game_hover.png", "", 1);
	//this->setListener(begin_btn, "", "", "", 1);

	
	auto begin_sword = Sprite::create(Consts::base + "sword_blank.png");
	begin_sword->setRotation(90);
	begin_sword->setPosition(s.width / 2, s.height / 2);
	begin_sword->setZOrder(-1);
	begin_sword->setScale(0.3f);
	this->addChild(begin_sword);
	//this->setListener(begin_sword, Consts::base + "sword_blank.png",Consts::base +  "sword.png", "", 1);

	auto end_btn = Sprite::create(Consts::base + "end_game.png");
	end_btn->setPosition(s.width / 2, s.height / 2 - 70);
	end_btn->setScale(0.5f);
	this->addChild(end_btn);
	this->setListener(end_btn, Consts::base + "end_game.png", Consts::base +"end_game_hover.png", "", 2);

	auto end_sword = Sprite::create(Consts::base + "sword_blank.png");
	end_sword->setRotation(90);
	end_sword->setPosition(s.width / 2, s.height / 2 - 70);
	end_sword->setZOrder(-1);
	end_sword->setScale(0.3f);
	this->addChild(end_sword);
	//this->setListener(end_sword, Consts::base + "sword_blank.png", Consts::base + "sword.png", "", 2);

	return true;
}

void HelloWorld::setStar(Vec2 loc, double s_scale, double b_scale,int angle,double duration) {
	Size s = Director::getInstance()->getWinSize();
	auto star = Sprite::create("../../Resources/star.png");
	star->setScale(b_scale);
	star->setZOrder(100);
	star->setRotation(angle);
	auto scale_s = ScaleTo::create(duration, s_scale);
	auto scale_b = ScaleTo::create(duration, b_scale);
	auto actions = Sequence::create(scale_s, scale_b, nullptr);
	auto repeat = RepeatForever::create(actions);
	this->addChild(star);
	star->setPosition(loc);
	star->runAction(repeat);
}

void HelloWorld::setListener(Sprite *button, string originImg, string hoverImg, string clickImg, int type) {
	auto listener = EventListenerMouse::create();
	Size s = Director::getInstance()->getWinSize();
	listener->onMouseDown = [s, button, clickImg, this, type](Event *event) {
		auto e = static_cast <EventMouse *>(event);
		auto target = static_cast <Sprite*>(event->getCurrentTarget());
		auto loc = e->getLocationInView();
		loc.y += s.height;
		auto locationInNode = target->convertToNodeSpace(loc);
		//cout << "(" << locationInNode.x << ":" << locationInNode.y << ")" << endl;
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			if (type == 1) {
				auto scene = Choose::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			}
			else {
				Director::getInstance()->end();
			}
		}
	};
	listener->onMouseMove = [s, button, originImg, hoverImg,this,type](Event * event){
		auto e = static_cast <EventMouse *>(event);
		auto target = static_cast <Sprite*>(event->getCurrentTarget());
		auto loc = e->getLocationInView();
		loc.y += s.height;
		auto locationInNode = target->convertToNodeSpace(loc);
		//cout << "(" << locationInNode.x << ":" << locationInNode.y << ")" << endl;
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			if (type == 1) {
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
			else {
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
		}
		else {
			if (type == 1) {
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
			else {
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), button);
}