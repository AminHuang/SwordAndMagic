#include "ChooseScene.h"
#include "OnGameScene.h"
#include "Global.h"
#include "SAM\Table.h"

Scene*Choose::createScene() {
	auto scene = Scene::create();
	auto layer = Choose::create();
	auto backgroud = Sprite::create("../../Resources/backgroud_choose.jpg");
	Size s = Director::getInstance()->getWinSize();
	backgroud->setContentSize(s);
	backgroud->setScaleX((double)s.width / 1440);
	backgroud->setScaleY((double)s.height / 900);
	backgroud->setAnchorPoint(Vec2(0, 0));
	backgroud->setZOrder(-1000);
	layer->addChild(backgroud);
	scene->addChild(layer);
	return scene;
}

bool Choose::init() {
	if (!Layer::init()) {
		return false;
	}
	this->chapterId = UserDefault::getInstance()->getIntegerForKey("curChapter",1);

	Size s = Director::getInstance()->getWinSize();
	auto leave = ParticleSystemQuad::create("../../Resources/LeaveStorm.plist");
	leave->setPosition(s.width / 2, s.height);
	this->addChild(leave);

	auto chapter = Sprite::create(Consts::base + "chapter.png");
	chapter->setScale(1.0f);
	chapter->setPosition(s.width / 2, s.height / 2 );
	this->addChild(chapter);
	Sprite * left_btn;
	if (this->chapterId <= 1) {
		left_btn = Sprite::create(Consts::base + "select_left_invalid.png");
	}
	else {
		left_btn = Sprite::create(Consts::base + "select_left.png");
	}
	
	Sprite * right_btn;
	if (this->chapterId >= 2) {
		right_btn = Sprite::create(Consts::base + "select_right_invalid.png");
	}
	else {
		right_btn = Sprite::create(Consts::base + "select_right.png");
	}
	this->addChild(left_btn,0,"left_btn");
	left_btn->setPosition(s.width / 4, s.height / 2);
	right_btn->setPosition(s.width * 3 / 4, s.height / 2);
	this->addChild(right_btn,0,"right_btn");
	this->setListener(right_btn, Consts::base + "select_right.png", Consts::base + "select_right_hover.png", "", 3);
	this->setListener(left_btn, Consts::base + "select_left.png", Consts::base + "select_left_hover.png", "", 2);

	auto button = Sprite::create(Consts::base + "select_origin.png");
	this->addChild(button,0,"select_btn");
	button->setScale(0.6f);
	button->setPosition(s.width / 2, s.height / 4 - 80);
	this->setListener(button, Consts::base + "select_origin.png", Consts::base + "select_hover.png", "", 1);

	auto stencil = Sprite::create(Consts::base + "chapter1.png");
	auto clippingNode = ClippingNode::create(stencil);
	clippingNode->setAlphaThreshold(0);
	this->clipping = clippingNode;
	
	chapter = Sprite::create(Consts::base + "chapter" + Value(chapterId).asString() + ".png");
	this->chapter = chapter;
	clippingNode->addChild(chapter);
	clippingNode->setPosition(s.width / 2, s.height / 2);
	this->addChild(clippingNode);

	/*
	auto node = Node::create();
	node->addChild(stencil);
	node->setPosition(s.width / 2, s.height / 2);
	this->addChild(node);
	*/

	return true;
}


void Choose::setListener(Sprite *button, string originImg, string hoverImg, string clickImg ,int type) {
	auto listener = EventListenerMouse::create();
	Size s = Director::getInstance()->getWinSize();
	listener->onMouseDown = [s, button, clickImg,this,type,originImg](Event *event) {
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
				//if (UserDefault::getInstance()->getIntegerForKey("curChapter", 1) < this->chapterId)
					//return;
				OnGame::loadChapter(this->chapterId);	
				auto scene = OnGame::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			}
			else if (type == 2) {
				if (this->chapterId <= 1) {
					return;
				}
				if (this->chapterId <= 2) {
					auto select_left = dynamic_cast<Sprite *>(this->getChildByName("left_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_left_invalid.png");
					select_left->setTexture(texture);
				}
				else {
					auto select_left = dynamic_cast<Sprite *>(this->getChildByName("left_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
					select_left->setTexture(texture);
				}
				auto select_right = dynamic_cast<Sprite *>(this->getChildByName("right_btn"));
				Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_right.png");
				select_right->setTexture(texture);

				if (this->chapterId - 1<= UserDefault::getInstance()->getIntegerForKey("curChapter", 1)) {
					auto select = dynamic_cast<Sprite *>(this->getChildByName("select_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_origin.png");
					select->setTexture(texture);
				}

				//先把当前的关卡向右边移动
				auto chapter = this->chapter;
				auto size = this->chapter->getContentSize();
				auto move = MoveBy::create(1.5, Vec2(size.width,0));
				auto callback = CallFunc::create([chapter,this](){
					this->removeChild(chapter);
				});
				auto actions = Sequence::create(move, callback, nullptr);
				chapter->runAction(actions);

				//然后将新的关卡移入
				this->chapterId--;
				if (UserDefault::getInstance()->getIntegerForKey("curChapter", 1) >= this->chapterId) {
					chapter = Sprite::create(Consts::base + "chapter" + Value(this->chapterId).asString() + ".png");
				}
				else{
					chapter = Sprite::create(Consts::base + "chapter" + Value(this->chapterId).asString() + "_invalid.png");
				}
				this->clipping->addChild(chapter);
				chapter->setPosition(-size.width,0);
				auto moveTo = MoveBy::create(1.5, Vec2(size.width, 0));
				chapter->runAction(moveTo);
				this->chapter = chapter;
			}
			else if (type == 3) {
				if (this->chapterId >= Consts::maxChapter) {
					return;
				}
				if (this->chapterId + 1 >= Consts::maxChapter) {
					auto select_right= dynamic_cast<Sprite *>(this->getChildByName("right_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_right_invalid.png");
					select_right->setTexture(texture);
				}
				else {
					auto select_right= dynamic_cast<Sprite *>(this->getChildByName("right_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
					select_right->setTexture(texture);
				}
				auto select_left = dynamic_cast<Sprite *>(this->getChildByName("left_btn"));
				Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_left.png");
				select_left->setTexture(texture);
				if (this->chapterId + 1> UserDefault::getInstance()->getIntegerForKey("curChapter", 1)) {
					auto select = dynamic_cast<Sprite *>(this->getChildByName("select_btn"));
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "select_invalid.png");
					select->setTexture(texture);
				}

				//先把当前的关卡向右边移动
				auto chapter = this->chapter;
				auto size = this->chapter->getContentSize();
				auto move = MoveBy::create(2, Vec2(-size.width, 0));
				auto callback = CallFunc::create([chapter, this](){
					this->removeChild(chapter);
				});
				auto actions = Sequence::create(move, callback, nullptr);
				chapter->runAction(actions);

				//然后将新的关卡移入
				this->chapterId++;
				if (UserDefault::getInstance()->getIntegerForKey("curChapter", 1) >= this->chapterId) {
					chapter = Sprite::create(Consts::base + "chapter" + Value(this->chapterId).asString() + ".png");
				}
				else{
					chapter = Sprite::create(Consts::base + "chapter" + Value(this->chapterId).asString() + "_invalid.png");
				}
				this->clipping->addChild(chapter);
				chapter->setPosition(size.width, 0);
				auto moveTo = MoveBy::create(2, Vec2(-size.width, 0));
				chapter->runAction(moveTo);
				this->chapter = chapter;
			}
		}
	};
	listener->onMouseMove = [s, button, originImg, hoverImg,type,this](Event * event){
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
				if (this->chapterId > UserDefault::getInstance()->getIntegerForKey("curChapter", 1)) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
			else if (type == 2) {
				if (this->chapterId <= 1) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
			else if (type == 3) {
				if (this->chapterId >= Consts::maxChapter) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
		}
		else {
			if (type == 1) {
				if (this->chapterId > UserDefault::getInstance()->getIntegerForKey("curChapter",1) ) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
			else if (type == 2) {
				if (this->chapterId <= 1) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
			else if (type == 3) {
				if (this->chapterId >= Consts::maxChapter) {
					return;
				}
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), button);
}