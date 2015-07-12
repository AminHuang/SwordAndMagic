#include "OnGameScene.h"
#include "Global.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "SAM\Heros\HuXueDong.cpp"
#include "SAM\Heros\HuXin.cpp"
#include "SAM\Heros\HuXinAI.cpp"
#include "Consts.h"
#include <math.h>

#define _room Global::getRoom()
#define _player Global::getPlayer()

using std::cout;
using std::endl;

int OnGame::chapterId = 0;
Scene* OnGame::createScene() {
	

	auto scene = Scene::create();
	auto layer = OnGame::create();

	scene->addChild(layer);
	return scene;
}
bool OnGame::init() {
	if (!Layer::init()) {
		return false;
	}

	Global::getRoom()->setRoomScene(this);
	this->addChild(Global::getRoom());
	auto backgroud = Sprite::create("../../Resources/backgroud_room"+Value(OnGame::chapterId).asString() + ".png");
	Size s = Director::getInstance()->getWinSize();
	backgroud->setAnchorPoint(Vec2(0, 0));
	backgroud->setZOrder(-1000);
	this->addChild(backgroud);

	//设置并隐藏玩家当前回合高亮背景图
	auto role_back = Sprite::create(Consts::base + "role_back.png");
	role_back->setVisible(false);
	role_back->setZOrder(-1);
	role_back->setScale(0.3f);
	this->setBtnRotate(role_back);
	this->role_back = role_back;
	this->addChild(role_back);

	//设置并隐藏计时条
	auto timer = Sprite::create(Consts::base + "line.png");
	this->timer = timer;
	timer->setRotation(90);
	timer->setAnchorPoint(Vec2(0, 0));
	timer->setScaleY(0.5f);
	//timer->setPosition(s.width / 2, s.height / 2);
	this->schedule(schedule_selector(OnGame::changeTimer), 1.0f);
	this->schedule(schedule_selector(OnGame::myUpdate));
	timer->setVisible(false);
	this->addChild(timer);

	/*
	auto back = LayerColor::create(Color4B(200, 200, 200, 255),400,200);
	back->ignoreAnchorPointForPosition(false);
	back->setAnchorPoint(Vec2(0.5, 0.5));
	back->setPosition(s.width / 2, s.height / 2);
	this->addChild(back);
	*/

	auto info = Label::createWithSystemFont("You have to discard 3 cards ! ", "Arial", 24);
	this->addChild(info);
	info->setVisible(false);
	info->setPosition(s.width / 2, 230);
	this->discardInfo = info;

	//先重置房间的数据
	this->resetData();
	//然后展示其他玩家的图片以及牌区域
	this->displayBeforeSelect();
	//显示选择英雄的面板
	this->selectHero();

	return true;
}

//开始游戏的特效
void OnGame::startGame() {
	Global::getRoom()->startGame();
}

void OnGame::timerCallBack(float dt) {
	/*this->num--;
	if (this->num < 0) {
		this->num = 30;
		_eventDispatcher->setEnabled(false);
		this->unschedule(schedule_selector(OnGame::timerCallBack));
	}
	std::stringstream ss;
	ss << num;
	this->timer->setString(ss.str());*/
}

void OnGame::playCard(int sid, int cardId, int targetSid) {
	if (sid == _player->getSeatId()) {
		if (_room->getStatus() == Consts::magicQuery || _room->getStatus() == Consts::cardQuery) {
			_room->setStatus(Consts::wait);
		}
		else if (_room->getStatus() == Consts::pmagicQuery) {
			_room->setStatus(Consts::play);
			this->startTurn();
		}
	}

	if (sid != _player->getSeatId()) {
		auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
		if (cardName == "DisturbCard") {
			if (this->playCardPanel != nullptr) {
				this->removeChild(this->playCardPanel);
				this->playCardPanel = nullptr;
			} 
		}
	}

	Global::getRoom()->setIsActable(false);
	this->time = 30;
	auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
	cout << "Info : sid " << sid << " play card " <<cardName<<" , target is "<<targetSid<< endl;
	//this->moveCard(sid, cardId, targetSid);
	//this->card = nullptr;
	//return;
	this->_eventDispatcher->setEnabled(false);
	auto cards = this->cards[sid];
	auto s = Director::getInstance()->getWinSize();
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	//出牌后会出现一条线
	if (targetSid == -1) {
		for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {
			auto otherPlayer = Global::getRoom()->getPlayerBySeatId(i);
			if (player->getTeamId() != otherPlayer->getTeamId()) {
				this->drawLine(sid, otherPlayer->getSeatId());
			}
		}
	}
	else if (targetSid != sid){
		this->drawLine(sid, targetSid);
	}

	//this->setBuff(sid, cardId, targetSid);

	if (sid != Global::getPlayer()->getSeatId()) {
		auto card = cards->at(cards->size() - 1);
		cout << "Info : sid " << sid << " remove a card " <<card<< endl;
		this->removeChild(card);
		//通过判断牌的类型，来选择出牌的图片
		
		auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
		Sprite* newCard = nullptr;
		if (cardName == "Chop" || cardName == "Dodge" || cardName == "Parry" || cardName == "Thorn" || cardName == "HealthStone")
			newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + ".png");
		else
			newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + "_" + Consts::heros[player->getRole()] + ".png");
		newCard->setScale(0.5f);
		newCard->setAnchorPoint(Vec2(0.5, 0.5));
		auto loc = player->getLocation();
		auto picSize = player->getHeadPicSize();
		loc.y -= picSize.height / 2;
		loc.y += 1 / 4 * (s.height / 2 - loc.y);
		loc.x += 1 / 4 * (s.width / 2 - loc.x);
		newCard->setPosition(loc);
		this->addChild(newCard);
		auto tar_loc = this->handleOutCards();
		this->outCards.push(newCard);
		this->disCards.push_back(newCard);
		auto move = MoveTo::create(0.2,tar_loc );
		auto callback = CallFunc::create([this,newCard]() {
			Global::getRoom()->setIsActable(true);
			this->getEventDispatcher()->setEnabled(true);
		});
		auto actions = Sequence::create(move,callback,nullptr);
		newCard->runAction(actions);
		newCard->setZOrder(-2);
		cards->pop_back();
	}
	else {
		int sid = Global::getPlayer()->getSeatId();

		//从vector中删除玩家出的牌
		auto result = find(cards->begin(), cards->end(), this->card);
		cards->erase(result);
		this->resort(sid);

		//将确定按钮重置成灰色
		auto play_btn = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_btn"));
		auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
		Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g3.png");
		play_btn->setTexture(texture);
		texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g3_font.png");
		play_font->setTexture(texture);

		Size s = Director::getInstance()->getWinSize();
		this->card->setAnchorPoint(Vec2(0.5, 0.5));


		//由于重置了锚点，所以要把图片移位
		int width = this->card->getContentSize().width * this->card->getScale() / 2;
		int height = this->card->getContentSize().height * this->card->getScale() / 2;
		this->card->setPosition(this->card->getPosition().x + width, this->card->getPosition().y + height);

		auto scale = ScaleTo::create(0.3, 0.5f);
		auto loc = this->handleOutCards();
		this->outCards.push(this->card);
		this->disCards.push_back(this->card);
		auto move = MoveTo::create(0.3, loc);
		auto callback = CallFunc::create([this, sid]() {
			this->getEventDispatcher()->removeEventListenersForTarget(this->card);
			this->card = nullptr;
			this->getEventDispatcher()->setEnabled(true);
			Global::getRoom()->setIsActable(true);
		});
		auto acs = Spawn::create(scale, move, nullptr);
		auto actions = Sequence::create(acs, callback, nullptr);
		this->card->runAction(actions);
		this->card->setZOrder(-2);
	}

	//不管怎样，先把所有的头像效果去掉
	for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {
		auto player = Global::getRoom()->getPlayerBySeatId(i);
		int role = player->getRole();
		auto texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + ".png");
		player->getHeadPic()->setTexture(texture);
	}
}

void OnGame::addCards(int sid, std::vector<int> cardIds) {
	cout << "Info : sid " << sid <<" add cards, size is "<<cardIds.size()<< endl;
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	//响应点击事件
	auto player = Global::getPlayer();
	auto room = Global::getRoom();
	listener->onTouchBegan = [this,player,room](Touch *touch, Event * event) {
		auto target = static_cast <Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode)) {
			if (player->getHitNum() > 0 && room->getCurSId() == player->getSeatId()) {
				//play_menu->setVisible(true);
			}

			if (_room->getStatus() != Consts::discard) {
				/*
				* 如果玩家之前已经点击了一个牌了，那么点击另一张牌，将进行如下处理：
				* 1.将之前点击的牌放回，并弹出正在点击的牌
				* 2.将确定按钮重置成灰色，并把目标玩家重置为无效
				*/

				//不管怎样，先把所有的头像效果去掉
				for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {
					auto player = Global::getRoom()->getPlayerBySeatId(i);
					int role = player->getRole();
					auto texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + ".png");
					player->getHeadPic()->setTexture(texture);
				}
				//目标玩家重置为无效
				this->targetSid = -10;
				this->targetPic = nullptr;


				if (target->getPositionY() == 0) {
					//放回和弹出牌
					target->setPositionY(50);
					int cardId = *(int*)target->getUserData();
					auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();

					//如果是AOE牌而且是法师，那么不需要指定出牌对象
					if (cardName == "AoeCard" && Global::getPlayer()->getRole() == 1) {
						this->targetSid = -1;
						for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {
							auto player = Global::getRoom()->getPlayerBySeatId(i);
							if (player->getTeamId() != Global::getPlayer()->getTeamId()) {
								int role = player->getRole();
								auto texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + "_click.png");
								player->getHeadPic()->setTexture(texture);
							}
						}
					}
					else if (cardName == "HealthStone" || cardName == "BuffCard" || cardName == "DefenseCard" || cardName == "PassCard" || (cardName == "AoeCard" && Global::getPlayer()->getRole() == 2)) {
						int role = Global::getPlayer()->getRole();
						auto texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + "_click.png");
						Global::getPlayer()->getHeadPic()->setTexture(texture);
						this->targetSid = Global::getPlayer()->getSeatId();
					}

					if (this->card != nullptr && this->card != target)
						this->card->setPositionY(0);
					this->card = target;
				}
				else {
					target->setPositionY(0);
					this->card = nullptr;
				}
				//如果是AOE或者对自己用的卡，那么就不把按钮重置成灰色的
				if (this->playCardPanel != nullptr) {
					auto play_btn = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_btn"));
					auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
					if (this->isOkBtnAble()) {
						Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2.png");
						play_btn->setTexture(texture);
						texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
						play_font->setTexture(texture);
					}
					else {
						Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g3.png");
						play_btn->setTexture(texture);
						texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g3_font.png");
						play_font->setTexture(texture);
					}
				}
			}
			else {
				if (target->getPositionY() == 0) {
					target->setPositionY(50);
					int cardId = *(int*)target->getUserData();
					this->cardIds.push_back(cardId);
				}
				else {
					for (int i = 0; i < this->cardIds.size(); i++) {
						this->cardIds[i] = -1;
					}
					target->setPositionY(0);
				}
			}
			return true;
		}
		return false;
	};

	//给其他玩家添加牌
	auto tmp = this->cards[sid];
	auto s = Director::getInstance()->getWinSize();
	if (sid != Global::getPlayer()->getSeatId()) {
		int i = tmp->size();
		for (auto cardId : cardIds) {
			auto card = Sprite::create("../../Resources/card_back.png");
			int padding = card->getContentSize().width * 0.3 * 0.4;
			card->setAnchorPoint(Vec2(0,1));
			card->setScale(0.25f);

			Player *player = Global::getRoom()->getPlayerBySeatId(sid);
			auto loc = player->getLocation();
			auto size = player->getHeadPicSize();
			card->setPosition(loc.x - size.width / 2 + i * padding, loc.y - size.height + 50);
			this->addChild(card);
			tmp->push_back(card);
			i++;
		}
		Global::getRoom()->setIsActable(true);
	}
	else if (sid == Global::getPlayer()->getSeatId()) {
		int i = tmp->size();
		for (auto cardId : cardIds) {
			Sprite * card = nullptr;
			auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
			if (cardName == "Chop" || cardName == "Dodge" || cardName == "Parry" || cardName == "Thorn" || cardName=="HealthStone")
				card = Sprite::create("../../Resources/card_" + Value(cardName).asString() + ".png");
			else
				card = Sprite::create("../../Resources/card_"+Value(cardName).asString()+"_"+Consts::heros[Global::getPlayer()->getRole()]+".png");
			card->setScale(0.7f);
			int padding = card->getContentSize().width * 0.3 * 0.6;
			card->setAnchorPoint(Vec2(0, 0));

			card->setPosition(s.width / 4 + i * padding, 0);

			int *k = new int(cardId);
			card->setUserData(k);
			card->setZOrder(i + 1);
			this->addChild(card);
			tmp->push_back(card);
			this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), card);
			i++;
		}
		this->resort(sid);
	}
}

bool _compare(Sprite *a, Sprite *b) {
	return *(int*)a->getUserData() < *(int*)b->getUserData();
}

void OnGame::resort(int sid) {
	auto cards = this->cards[sid];
	this->_eventDispatcher->setEnabled(false);
	cout << "Info : sid " << sid << " resort, and cards size is " << cards->size() << endl;
	auto s = Director::getInstance()->getWinSize();
	//this->_eventDispatcher->setEnabled(false);
	if (sid == Global::getPlayer()->getSeatId()) {
		sort(cards->begin(), cards->end(), _compare);
		int *k = new int(0);
		int num = cards->size();
		for (int i = 0; i < num; i++) {
			int padding = cards->at(i)->getContentSize().width * 0.3 * 0.6;
			auto move = MoveTo::create(0.5, Vec2(s.width/4 + i*padding,0));
			auto callback = CallFunc::create([this,num,k](){
				//(*k)++;
				//if ((*k) == num) {
					//this->_eventDispatcher->setEnabled(true);
					//delete k;
				//}
				this->_eventDispatcher->setEnabled(true);
				Global::getRoom()->setIsActable(true);
			});
			auto actions = Sequence::create(move, callback, nullptr);
			//cout << i << endl;
			//cout << s.width / 4 + i*padding << endl;
			cards->at(i)->setZOrder(i);
			cards->at(i)->runAction(actions);
		}
	}
}

void OnGame::query(int sid, int cardId, int targetId) {
	auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
	cout << "Info : sid "<< sid <<" query target "<<targetId<<" card is "<<cardName<< endl;
	Size s = Director::getInstance()->getWinSize();
	if (targetId == Global::getPlayer()->getSeatId()) {
		this->cardId = cardId;
		this->createPlayCardPanel();
		this->timer->setPosition(s.width / 4, 225);
		this->timer->setVisible(true);
		this->time = 30;
		this->timerScale = 494 / this->timer->getContentSize().height;
	}
}

void OnGame::query(int sid, Magic *magic, int targetId) {
	cout << "Info : sid " << sid << " query target " << targetId << " magic is " << magic->Display()<< endl;
	Size s = Director::getInstance()->getWinSize();
	if (targetId == Global::getPlayer()->getSeatId()) {
		this->magic = magic;
		this->createPlayCardPanel();
		this->timer->setPosition(s.width / 4, 225);
		this->timer->setVisible(true);
		this->time = 30;
		this->timerScale = 494 / this->timer->getContentSize().height;
	}
}
/*
* type为1时为玩家选择角色的按钮响应
* type为2时为玩家点击重新开始游戏的按钮响应
* type为3时为玩家点击玩牌的时候 确定 按钮响应
* type为4时为玩家点击玩牌的时候 结束 按钮响应
* type为5时为返回上一关卡的按钮响应
* type为6时为进入下一关卡的按钮响应
* type为7时为弃牌的时候确定按钮响应
*/
void OnGame::setListener(Sprite *button, string originImg, string hoverImg, string clickImg,int type) {
	auto listener = EventListenerMouse::create();
	Size s = Director::getInstance()->getWinSize();
	listener->onMouseDown = [s,button,clickImg,type,this](Event *event) {
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
				if (_player->getRole() == -1)
					return;
				this->getEventDispatcher()->setEnabled(false);
				this->displayAfterSelect();
				auto vanish = FadeOut::create(1);
				auto callback = CallFunc::create([this]() {
					this->removeChild(this->selectPanel);
					this->startGame();
					this->getEventDispatcher()->setEnabled(true);
				});
				auto nodes = this->selectPanel->getChildren();
				for (auto node : nodes) {
					node->runAction(vanish->clone());
				}
				Global::getRoom()->enterTable();
				vanish = FadeOut::create(1.5);
				auto actions = Sequence::create(vanish, callback, nullptr);
				this->selectPanel->runAction(actions);
			}
			else if (type == 2) {
				this->removeAllChildren();
				OnGame::loadChapter(OnGame::chapterId);
				this->init();
			}
			else if (type == 3) {
				if (!this->isOkBtnAble())
					return;
				if (Global::getRoom()->getStatus() == Consts::play && this->targetSid != -10) {
					if (this->card != nullptr) {
						auto cardId = this->card->getUserData();
						Global::getPlayer()->playCard(*(int*)cardId, this->targetSid);
					}
				}
				else if (Global::getRoom()->getStatus() == Consts::cardQuery) {
					if (this->card != nullptr) {
						auto cardId = *(int*)this->card->getUserData();
						auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
						auto queryCard = Global::getRoom()->getTable()->GetCardStack()->GetCard(this->cardId)->Display();
						if (queryCard == "Chop" && cardName == "Parry") {
							Global::getPlayer()->playCard(cardId, Global::getPlayer()->getSeatId());
							Global::getRoom()->getTable()->Act();
							this->removeChild(this->playCardPanel);
							this->playCardPanel = nullptr;
						}
						else if (queryCard == "Thorn" && cardName == "Dodge") {
							Global::getPlayer()->playCard(cardId, Global::getPlayer()->getSeatId());
							Global::getRoom()->getTable()->Act();
							this->removeChild(this->playCardPanel);
							this->playCardPanel = nullptr; 
						}
					}
				}
				else if (_room->getStatus() == Consts::magicQuery || _room->getStatus() == Consts::pmagicQuery) {
					if (this->card != nullptr) {
						auto cardId = *(int*)this->card->getUserData();
						auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
						if (cardName == "DisturbCard") {
							Global::getPlayer()->playCard(cardId, Global::getPlayer()->getSeatId());
							this->removeChild(this->playCardPanel);
							this->playCardPanel = nullptr;
						}
					}
				}
			}
			else if (type == 4) {
				//this->gameOver();
				//this->discardTurn();
				//return;
				this->removeChild(this->playCardPanel);
				this->playCardPanel = nullptr;
				cout << "Info : status is "<<Global::getRoom()->getStatus()<< endl;
				if (Global::getRoom()->getStatus() == Consts::play) {
					Global::getPlayer()->getTurn()->DiscardTurn();
					_room->setStatus(Consts::wait);
				}
				else if (Global::getRoom()->getStatus() == Consts::cardQuery) {
					auto card = Global::getRoom()->getTable()->GetCardStack()->GetCard(this->cardId);
					card->Effect();
					_room->setStatus(Consts::wait);
					//Global::getRoom()->getTable()->Act();
				}
				else if (Global::getRoom()->getStatus() == Consts::magicQuery) {
					cout << "here1" << endl;
					this->magic->Effect();
					_room->setStatus(Consts::wait);
					//Global::getRoom()->getTable()->Act();
				}
				else if (_room->getStatus() == Consts::pmagicQuery){
					cout << "here2" << endl;
					this->magic->Effect();
					_room->setStatus(Consts::play);
					this->startTurn();
				}
				Global::getRoom()->setIsActable(true);
			}
			else if (type == 5) {
				if (OnGame::chapterId - 1 < 1)
					return;
				this->removeAllChildren();
				OnGame::loadChapter(--OnGame::chapterId);
				this->init();
			}
			else if (type == 6) {
				if (OnGame::chapterId + 1 > Consts::maxChapter || OnGame::chapterId + 1 > UserDefault::getInstance()->getIntegerForKey("curChapter"))
					return;
				this->removeAllChildren();
				OnGame::loadChapter(++OnGame::chapterId);
				this->init();
			}
			else if (type == 7) {
				vector<int> cardIds;
				while (!this->cardIds.empty()) {
					auto cardId = this->cardIds.back();
					if (cardId != -1) {
						cardIds.push_back(cardId);
					}
					this->cardIds.pop_back();
				}
				if (cardIds.size() + this->discardedNum > this->toBeDiscardNum) {
					return;
				}
				else {
					this->discardedNum += cardIds.size();
					this->discardCards(_player->getSeatId(), cardIds);
				}
				string info = "You have to discard ";
				info += Value(this->toBeDiscardNum - this->discardedNum).asString();
				info += " cards ! ";
				this->discardInfo->setString(info);

				if (this->toBeDiscardNum == this->discardedNum) {
					//_room->getTable()->Act();
					this->discardInfo->setVisible(false);
				}
			}
		}
	};
	listener->onMouseMove = [s,button,originImg,hoverImg,type,this](Event * event){
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
				if (_player->getRole() == -1)
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->selectPanel->getChildByName("btn_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g1_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 3) {
				if (!this->isOkBtnAble())
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g1_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 4) {
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("end_font"));
				if (_room->getStatus() == Consts::play)
					texture = TextureCache::getInstance()->addImage(Consts::base + "btn_e1_font.png");
				else
					texture = TextureCache::getInstance()->addImage(Consts::base + "btn_d1_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 5) {
				if (OnGame::chapterId <= 1)
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
			else if (type == 6) {
				if (OnGame::chapterId >= UserDefault::getInstance()->getIntegerForKey("curChapter"))
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
			else if (type == 7) {
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g1_font.png");
				play_font->setTexture(texture);
			}
			else {
				Texture2D* texture = TextureCache::getInstance()->addImage(hoverImg);
				button->setTexture(texture);
			}
		}
		else {
			if (type == 1) {
				if (_player->getRole() == -1)
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->selectPanel->getChildByName("btn_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 3) {
				if (!this->isOkBtnAble())
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 4) {
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("end_font"));
				if (_room->getStatus() == Consts::play)
					texture = TextureCache::getInstance()->addImage(Consts::base + "btn_e2_font.png");
				else
					texture = TextureCache::getInstance()->addImage(Consts::base + "btn_d2_font.png");
				play_font->setTexture(texture);
			}
			else if (type == 5) {
				if (OnGame::chapterId <= 1)
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
			else if (type == 6) {
				if (OnGame::chapterId >= UserDefault::getInstance()->getIntegerForKey("curChapter"))
					return;
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
			else if (type == 7) {
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
				auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
				play_font->setTexture(texture);
			}
			else {
				Texture2D* texture = TextureCache::getInstance()->addImage(originImg);
				button->setTexture(texture);
			}
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), button);
}

Vec2 OnGame::handleOutCards() {
	Vec2 loc;
	Size s = Director::getInstance()->getWinSize();

	/*for (int i = 0; i < this->disCards.size(); i++) {
		auto card = this->disCards[i];
		card->setPosition(i * 10 + 100,s.height/2);
	}*/

	loc.y = s.height / 2;
	//cout << outCards.size()<< endl;
	if (outCards.size() == 0) {
		loc.x = s.width / 2;
	}
	else if (outCards.size() == 1) {
		auto card = outCards.front();
		auto size = card->getContentSize();
		//cout << size.width << "," << size.height << endl;
		auto scale = card->getScale();
		//cout << scale << endl;
		int padding = size.width * scale;
		loc.x = s.width / 2 - padding / 2;
		auto callback = CallFunc::create([this,s,padding,size,scale]() {
			if (this->cover == nullptr) {
				auto layer = LayerColor::create(Color4B(0, 0, 0, 200), size.width * scale, size.height * scale);
				layer->ignoreAnchorPointForPosition(false);
				layer->setAnchorPoint(Vec2(0.5, 0.5));
				layer->setPosition(Vec2(s.width / 2 + padding / 2, s.height / 2));
				layer->setZOrder(-1);
				this->addChild(layer);
				this->cover = layer;
			}
		});
		auto move = MoveTo::create(0.3, Vec2(s.width / 2 + padding / 2, s.height/2));
		auto actions = Sequence::create(move, callback, nullptr);
		card->runAction(actions);
	}
	else if (outCards.size() == 2) {
		auto card = outCards.front();
		outCards.pop();
		auto size = card->getContentSize();
		//cout << size.width << "," << size.height << endl;
		auto scale = card->getScale();
		//cout << scale << endl;
		int padding = size.width * scale;
		loc.x = s.width / 2 - padding / 2;
		auto vanish = FadeOut::create(0.1f);
		auto callback = CallFunc::create([card, this]() {
			cout << "Info : outCards remove a card"<<card<< endl;
			this->removeChild(card);
		});
		auto actions = Sequence::create(vanish, callback, nullptr);
		card->runAction(actions);
		card = outCards.front();
		auto move = MoveTo::create(0.3, Vec2(s.width/2 +padding /2,s.height / 2));
		card->runAction(move);
	}
	
	//cout <<"("<< loc.x << "," << loc.y <<")"<< endl;
	//loc.x = s.width / 2;
	//loc.y = s.height / 2;
	return loc;
}

void OnGame::updateHp(int sid, int hpVal) {
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	if (hpVal < player->getHpVal()) {
		
	}
	else if(hpVal > player->getHpVal()){

	}
	auto hpLabel =  player->getHp();
	hpLabel->setString(Value(hpVal).asString());
	player->setHpVal(hpVal);
	if (hpVal < 0) {
		//this->gameOver();
	}
}

void OnGame::gameOver(int type) {
	cout << "Info : gameover ! " << endl;
	this->unscheduleAllSelectors();
	_room->unscheduleAllSelectors();

	Size s = Director::getInstance()->getWinSize();
	auto layer = LayerColor::create(Color4B(0, 0, 0, 220), s.width, s.height);
	layer->setZOrder(100);
	this->addChild(layer);

	Sprite *panel = nullptr;
	if (type == 1)
		panel = Sprite::create(Consts::base + "victory.png");
	else if (type == 2) {
		panel = Sprite::create(Consts::base + "fail.png");
	}
	panel->setPosition(s.width / 2, s.height / 2);
	panel->setScale(0.6f);
	panel->setZOrder(101);
	this->addChild(panel);

	Sprite * restart_btn = Sprite::create(Consts::base + "restart.png");
	
	layer->addChild(restart_btn);
	restart_btn->setPosition(s.width / 2, s.height / 8 + 100);
	restart_btn->setScale(0.6f);
	_eventDispatcher->removeAllEventListeners();
	this->setListener(restart_btn, "../../Resources/restart.png", "../../Resources/restart_hover.png", "../../Resources/restart_hover.png",2);

	Sprite * back_btn = nullptr;
	Sprite * next_btn = nullptr;
	if (OnGame::chapterId <= 1) {
		back_btn = Sprite::create(Consts::base + "back_chapter_invalid.png");
	}
	else {
		back_btn = Sprite::create(Consts::base + "back_chapter.png");
	}

	if (OnGame::chapterId >= UserDefault::getInstance()->getIntegerForKey("curChapter")) {
		next_btn = Sprite::create(Consts::base + "next_chapter_invalid.png");
	}
	else {
		next_btn = Sprite::create(Consts::base + "next_chapter.png");
	}
	layer->addChild(back_btn);
	back_btn->setPosition(s.width / 4, s.height / 8 + 100);
	back_btn->setScale(0.6f);
	layer->addChild(next_btn);
	next_btn->setPosition(s.width * 3/ 4, s.height / 8 + 100);
	next_btn->setScale(0.6f);
	this->setListener(back_btn, Consts::base + "back_chapter.png", Consts::base + "back_chapter_hover.png", Consts::base + "back_chapter_hover.png", 5);
	this->setListener(next_btn, Consts::base + "next_chapter.png", Consts::base + "next_chapter_hover.png", Consts::base + "next_chapter_hover.png", 6);
}

void OnGame::selectHero() {
	Size s = Director::getInstance()->getWinSize();
	
	auto panel = Node::create();
	auto btn_ok = Sprite::create(Consts::base + "btn_g3.png");
	panel->addChild(btn_ok);
	btn_ok->setScale(0.2f);
	btn_ok->setPosition(Vec2(s.width / 2, s.height / 4));
	this->setBtnRotate(btn_ok);

	auto btn_ok_font = Sprite::create(Consts::base + "btn_g3_font.png");
	panel->addChild(btn_ok_font,0,"btn_font");
	btn_ok_font->setScale(0.2f);
	btn_ok_font->setPosition(Vec2(s.width / 2, s.height / 4));

	this->selectPanel = panel;
	this->addChild(panel);
	
	
	int num =2;
	int mid = num / 2;
	int offset = 0;
	for (int i = 0; i < num; i++) {
		auto filePath = Consts::base + Consts::rolePics[i % 2];
		auto rolePic = Sprite::create(filePath);
		auto picSize = rolePic->getContentSize();
		int padding = 20;
		panel->addChild(rolePic);
		if (num % 2 == 0) {
			offset = (padding + picSize.width) / 2;
		}
		rolePic->setPosition(Vec2(s.width / 2 + (padding + picSize.width) * (i - mid) + offset, s.height / 2));
		rolePic->setScale(0.8f);
		int * k = new int(i + 1);
		rolePic->setUserData(k);
		auto moveUp = MoveBy::create(4, Vec2(0, 40));
		auto moveDown = MoveBy::create(4, Vec2(0, -40));
		auto actions = Sequence::create(moveUp, moveDown, nullptr);
		auto repeat = RepeatForever::create(actions);
		rolePic->runAction(repeat);

		auto listener = EventListenerMouse::create();
		listener->onMouseDown = [s, btn_ok, btn_ok_font, this,rolePic,i,repeat](Event *event) {
			auto e = static_cast <EventMouse *>(event);
			auto target = static_cast <Sprite*>(event->getCurrentTarget());
			auto loc = e->getLocationInView();
			loc.y += s.height;
			auto locationInNode = target->convertToNodeSpace(loc);
			//玩家选了哪个角色就设置玩家哪个角色	
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode)) {
				int id = *(int*)target->getUserData();
				Global::getPlayer()->setRole(id);
				Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2.png");
				btn_ok->setTexture(texture);
				texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
				btn_ok_font->setTexture(texture);

				if (role != nullptr) {
					if (id != *(int*)this->role->getUserData()) {
						int id = *(int*)this->role->getUserData();
						texture = TextureCache::getInstance()->addImage(Consts::base + Consts::rolePics[id - 1]);
						this->role->setTexture(texture);
					}
				}
				texture = TextureCache::getInstance()->addImage(Consts::base + Consts::rolePicsClick[i]);
				rolePic->setTexture(texture);
				this->role = rolePic;
			}
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),rolePic);
	}
	this->setListener(btn_ok, Consts::base + "btn_g2.png", Consts::base + "btn_g1.png", "", 1);
}

void OnGame::setBtnRotate(Sprite * btn) {
	auto rotate = RotateBy::create(10, 360);
	auto repeat = RepeatForever::create(rotate);
	btn->runAction(repeat);
}

void OnGame::loadChapter(int chapterId) {
	OnGame::chapterId = chapterId;
	string config = FileUtils::getInstance()->getStringFromFile(Consts::base + "chapter.json");
	rapidjson::Document d;
	d.Parse<rapidjson::kParseDefaultFlags>(config.c_str());
	string chapter = "chapter" + Value(chapterId).asString();

	//先创建一个房间
	auto room = Room::create();
	Table *table = new Table();
	room->setTable(table);
	room->retain();
	Global::setRoom(room);

	//添加玩家
	Player *player = new Player();
	player->setTeamId(1);
	Global::setPlayer(player);
	player->setAuto(false);
	player->enterRoom(room);
	

	//添加电脑玩家
	int playerCnt = d[chapter.c_str()]["playerCnt"].GetInt();
	for (int i = 0; i < d[chapter.c_str()]["players"].Size(); i++) {
		rapidjson::Value &player = d[chapter.c_str()]["players"][i];
		Player *x = new Player();
		int role = player["role"].GetInt();
		x->setRole(role);
		if (role == 1) {
			x->setHpVal(60);
			x->setAttackVal(6);
		}
		else if (role == 2) {
			x->setHpVal(60);
			x->setAttackVal(6);
		}
		x->setTeamId(2);
		x->enterRoom(room);
	}
}

void OnGame::resetData() {
	this->targetSid = -10;
	this->card = nullptr;
	this->cover = nullptr;
	this->role = nullptr;
	this->targetPic = nullptr;
	this->playCardPanel = nullptr;
	for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {
		this->cards[i] = new std::vector<Sprite *>();
		this->buffPics[i] = new std::vector < Sprite * >();
	}
	while (!this->outCards.empty()) {
		this->outCards.pop();
	}
	for (int i = 0; i < Global::getRoom()->getPlayerCnt(); i++) {

	}
}

void OnGame::displayBeforeSelect() {
	//其他玩家角色图片，血量，牌区域之类的
	Size s = Director::getInstance()->getWinSize();
	auto listener = EventListenerMouse::create();
	auto player = Global::getPlayer();
	int sid = player->getSeatId();
	Room * room = Global::getRoom();
	double angle = 0;
	for (int i = 0; i < room->getPlayerCnt() - 1; i++) {
		int otherSid = (i + sid + 1) % room->getPlayerCnt();
		Player *other_player = room->getPlayerBySeatId(otherSid);
		auto role = other_player->getRole();
		auto role_pic = Sprite::create(Consts::base +Consts::heroPics[role - 1] +".png");
		other_player->setHeadPic(role_pic);
		role_pic->setScale(0.3f);
		int width = role_pic->getContentSize().width * role_pic->getScale();
		int height = role_pic->getContentSize().height * role_pic->getScale();

		//cout << height << endl; 180
		//记录玩家的座位号
		int * k = new int(otherSid);
		role_pic->setUserData(k);

		int a = s.width / 2;
		int b = s.height / 2;
		double d_angle = 3.14 / room->getPlayerCnt();
		angle += d_angle;
		double x = cos(angle) * a + s.width / 2;
		double y = sin(angle) * b + s.height / 2;


		//设置玩家角色图片
		role_pic->setAnchorPoint(Vec2(0.5, 1));
		role_pic->setPosition(x, y);
		other_player->setLocation(Vec2(x, y));

		this->addChild(role_pic);
		listener->onMouseDown = [s, this,role_pic,role](Event *event) {
			auto e = static_cast <EventMouse *>(event);
			auto target = static_cast <Sprite*>(event->getCurrentTarget());
			auto loc = e->getLocationInView();
			loc.y += s.height;
			auto locationInNode = target->convertToNodeSpace(loc);
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode)) {
				/*
				* 当玩家点击了某个其他玩家的头像，如果这时候恰好玩家已经选择了一张牌，那么进行如下处理：
				* 1.将按钮置换成黄色，并设置目标玩家sid
				*/

				if (this->card != nullptr) {

					int cardId = *(int*)this->card->getUserData();
					auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
					/*
					* 如果是玩家自由出牌阶段，那么将不能出闪和招
					*/
					if (Global::getRoom()->getStatus() == Consts::play) {
						if (cardName == "Dodge" || cardName == "Parry" || this->targetSid == - 1 || this->targetSid == Global::getPlayer()->getSeatId() || cardName == "DisturbCard")
							return;

						//点击玩家的头像，就将该头像重置成被选择状态，并把之前选择的头像重置成普通状态
						
						if (this->targetPic != nullptr) {
							int sid = *(int*)this->targetPic->getUserData();
							int role = Global::getRoom()->getPlayerBySeatId(sid)->getRole();
							Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + ".png");
							this->targetPic->setTexture(texture);
						}
						Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + "_click.png");
						role_pic->setTexture(texture);


						//将按钮置换成黄色
						if (this->playCardPanel != nullptr) {
							auto play_btn = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_btn"));
							auto play_font = dynamic_cast<Sprite*>(this->playCardPanel->getChildByName("play_font"));
							texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2.png");
							play_btn->setTexture(texture);
							texture = TextureCache::getInstance()->addImage(Consts::base + "btn_g2_font.png");
							play_font->setTexture(texture);
						}
						this->targetPic = target;
						this->targetSid = *(int *)(target->getUserData());
					}
				}
			}
		};
		listener->onMouseMove = [s, this,role_pic,role](Event * event){
			auto e = static_cast <EventMouse *>(event);
			auto target = static_cast <Sprite*>(event->getCurrentTarget());
			auto loc = e->getLocationInView();
			loc.y += s.height;
			auto locationInNode = target->convertToNodeSpace(loc);
			//cout << "(" << locationInNode.x << ":" << locationInNode.y << ")" << endl;
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode)) {
				if (role_pic != this->targetPic && this->targetSid != -1) {
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + "_hover.png");
					role_pic->setTexture(texture);
				}
			}
			else {
				if (role_pic != this->targetPic && this->targetSid != -1) {
					Texture2D* texture = TextureCache::getInstance()->addImage(Consts::base + Consts::heroPics[role - 1] + ".png");
					role_pic->setTexture(texture);
				}
			}
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), role_pic);

		//设置玩家的血量
		auto hp = Sprite::create(Consts::base + "hp.png");
		hp->setPosition(x - width / 2 - 50, y - 30);
		hp->setScale(0.2f);
		this->addChild(hp);

		int hpVal = other_player->getHpVal();
		auto hp_d = Label::create(Value(hpVal).asString(), "Arial", 30);
		hp_d->setPosition(x - width / 2, y - 30);
		other_player->setHp(hp_d);
		this->addChild(hp_d);

		//设置玩家的攻击力
		auto dps = Sprite::create(Consts::base + "dps_"+ Consts::heros[role] + ".png");
		dps->setPosition(x - width / 2 - 50, y - 60);
		dps->setRotation(90);
		dps->setScale(0.2f);
		this->addChild(dps);

		int attackVal = player->getAttackVal();
		auto attack = Label::create(Value(attackVal).asString(), "Arial", 30);
		attack->setPosition(x - width / 2, y - 60);
		other_player->setAttack(attack);
		this->addChild(attack);

		other_player->setHeadPicSize(Size(width, height));
	}
}

void OnGame::displayAfterSelect() {
	//玩家牌区域背景
	Size s = Director::getInstance()->getWinSize();
	auto cardPanel = Sprite::create(Consts::base + "card_panel.png");
	cardPanel->setAnchorPoint(Vec2(0,0));
	cardPanel->setScaleY(0.5f);
	cardPanel->setScaleX(0.75f);
	cardPanel->setPosition(s.width / 4, 0);
	this->addChild(cardPanel);

	//玩家角色图片
	Player * player = Global::getPlayer();
	auto role = player->getRole();
	auto role_pic = Sprite::create(Consts::base + Consts::heroPics[role - 1] + ".png");
	role_pic->setScale(0.4f);
	role_pic->setAnchorPoint(Vec2(0, 0));
	role_pic->setPosition(s.width / 4 - 160, 0);
	player->setHeadPicSize(Size(s.width / 4, 0));
	this->addChild(role_pic);
	player->setHeadPic(role_pic);

	if (player->getRole() == 1) {
		player->setAttackVal(4);
		player->setHpVal(60);
	}
	else if (player->getRole() == 2) {
		player->setAttackVal(6);
		player->setHpVal(60);
	}

	//设置玩家角色信息
	//血量
	auto hp = Sprite::create(Consts::base + "hp.png");
	hp->setPosition(s.width / 4 - 200, s.height / 4 + 30);
	hp->setScale(0.2f);
	this->addChild(hp);

	int hpVal = player->getHpVal();
	auto hp_d = Label::create(Value(hpVal).asString(), "Arial", 30);
	hp_d->setPosition(s.width / 4 - 150, s.height / 4 + 30);
	Global::getPlayer()->setHp(hp_d);
	this->addChild(hp_d);

	//攻击力
	auto dps = Sprite::create(Consts::base + "dps_" + Consts::heros[role] + ".png");
	dps->setPosition(s.width / 4 - 200, s.height / 4);
	dps->setScale(0.2f);
	dps->setRotation(90);
	this->addChild(dps);

	int attackVal = player->getAttackVal();
	auto attack = Label::create(Value(attackVal).asString(), "Arial", 30);
	attack->setPosition(s.width / 4 - 150, s.height / 4);
	Global::getPlayer()->setAttack(attack);
	this->addChild(attack);

	//this->createPlayCardPanel();
}

void OnGame::updateAttack(int sid,int attackVal) {
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	if (attackVal < player->getAttackVal()) {

	}
	else if (attackVal > player->getAttackVal()){

	}
	auto attackLabel = player->getAttack();
	attackLabel->setString(Value(attackVal).asString());
	player->setAttackVal(attackVal);
}

void OnGame::drawLine(int sid,int targetSid) {
	auto s = Director::getInstance()->getWinSize();
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	auto targetPlayer = Global::getRoom()->getPlayerBySeatId(targetSid);

	auto loc = player->getLocation();
	if (player->getSeatId() == Global::getPlayer()->getSeatId()) {
		loc = Vec2(s.width / 2, s.height / 4);
	}
	else {
		auto picSize = player->getHeadPicSize();
		loc.y -= picSize.height / 2;
	}

	auto targetLoc = targetPlayer->getLocation();
	if (targetPlayer->getSeatId() == Global::getPlayer()->getSeatId()) {
		targetLoc = Vec2(s.width / 2, s.height / 4);
	}
	else {
		auto picSize = targetPlayer->getHeadPicSize();
		targetLoc.y -= picSize.height / 2;
	}

	double tan = (loc.x - targetLoc.x) / (loc.y - targetLoc.y);
	double angle = 0;
	if (loc.y < targetLoc.y) {
		angle = atan(tan) / 3.14 * 180;
		if (angle < 0) {
			angle += 360;
		}
	}
	else {
		angle = atan(tan) / 3.14 * 180 + 180;
	}
	auto line = Sprite::create("../../Resources/line.png");
	line->setRotation(angle);
	line->setAnchorPoint(Vec2(0, 0));
	line->setPosition(loc.x, loc.y);
	line->setScaleY(0.2f);
	this->addChild(line);

	auto size = line->getContentSize();
	int len = size.height;
	double length = sqrt((loc.x - targetLoc.x) * (loc.x - targetLoc.x) + (loc.y - targetLoc.y) * (loc.y - targetLoc.y));
	double ratio = length / len;

	auto scale = ScaleTo::create(1, ratio);
	auto vanish = FadeOut::create(1);
	auto callback = CallFunc::create([line, this]() {
		this->removeChild(line);
	});
	auto actions = Sequence::create(scale, vanish, callback, nullptr);
	line->runAction(actions);
}

/*
void OnGame::setBuff(int sid, int cardId, int targetSid) {
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	if (player== Global::getPlayer()) {
		auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
		cout << cardName << endl;
		if (player->getRole() == 1) {
			if (cardName == "ControlCard") {
				auto buffName = "skiptotalturn";
				auto player = Global::getRoom()->getPlayerBySeatId(targetSid);
				player->addBuff(buffName);
			}
			else if (cardName == "DefenseCard") {
				auto buffName = "iceblock";
				player->addBuff(buffName);
			}
			else if (cardName == "BuffCard") {
				auto buffName = "arcaneecho";
				player->addBuff(buffName);
			}
			else if (cardName == "DebuffCard") {
				auto buffName = "arcaneinstability";
				auto player = Global::getRoom()->getPlayerBySeatId(targetSid);
				player->addBuff(buffName);
			}
		}
		else if(player->getRole() == 2) {
			if (cardName == "BuffCard") {
				auto buffName = "deathwish";
				player->addBuff(buffName);
			}
			else if (cardName == "AoeCard") {
				auto buffName = "sweep";
				player->addBuff(buffName);
			}
			else if (cardName == "DebuffCard") {
				auto buffName = "deepwounds";
				auto player = Global::getRoom()->getPlayerBySeatId(targetSid);
				player->addBuff(buffName);
			}
			else if (cardName == "DefenseCard") {
				auto buffName = "dieaftersword";
				player->addBuff(buffName);
			}
			else if (cardName == "PassCard") {
				auto buffName = "avatar";
				player->addBuff(buffName);
			}
			else if (cardName == "ControlCard") {
				auto buffName = "skipactturn";
				auto player = Global::getRoom()->getPlayerBySeatId(targetSid);
				player->addBuff(buffName);
			}
		}
	}
}

*/

void OnGame::addBuff(int sid, string buffName,int index) {
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	auto s = Director::getInstance()->getWinSize();
	auto buff = Sprite::create(Consts::base + "buff_" + buffName + ".png");
	this->buffPics[sid]->push_back(buff);
	buff->setScale(0.1f);
	buff->setZOrder(1);
	int padding = buff->getContentSize().width * buff->getScale();
	this->addChild(buff);
	if (player->getSeatId() == Global::getPlayer()->getSeatId()) {
		buff->setAnchorPoint(Vec2(0, 0));
		buff->setPosition(s.width / 4 + padding * (index - 1), 230);	
	}
	else {
		buff->setAnchorPoint(Vec2(0, 1));
		auto size = player->getHeadPicSize();
		auto loc = player->getLocation();
		loc.x -= size.width / 2;
		loc.y -= size.height;
		buff->setPosition(loc.x + padding * (index - 1), loc.y - 28);
	}
}
void OnGame::addBuff(int sid, vector<string>buffNames) {
	auto buffs = this->buffPics[sid];
	while (!buffs->empty()) {
		auto buff = buffs->back();
		this->removeChild(buff);
		buffs->pop_back();
	}
	for (int i = 0; i < buffNames.size(); i++) {
		this->addBuff(sid, buffNames[i], i + 1);
	}
}

void OnGame::discardCards(int sid, vector<int> cardIds) {
	cout << "Info : sid " << sid << " discard cards, size is " << cardIds.size() << endl;
	this->_eventDispatcher->setEnabled(false);
	auto cards = this->cards[sid];
	auto s = Director::getInstance()->getWinSize();
	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	int k = 0;
	int num = cardIds.size();

	int cardWidth = 108;
	double padding = (double)400 / num;
	if (padding < 108) {
		cardWidth = padding;
	}
	vector<int> locs;
	if (num % 2 == 0) {
		for (int i = -num / 2; i < num / 2; i++) {
			locs.push_back(i * cardWidth + s.width / 2 + cardWidth / 2);
		}
	}
	else {
		for (int i = -num / 2; i <= num / 2; i++) {
			locs.push_back(i * cardWidth + s.width / 2);
		}
	}
	//cout << padding << endl;
	for (auto cardId : cardIds) {
		if (sid != Global::getPlayer()->getSeatId()) {
			auto card = cards->at(cards->size() - 1);
			this->removeChild(card);
			//通过判断牌的类型，来选择出牌的图片

			auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
			Sprite* newCard = nullptr;
			if (cardName == "Chop" || cardName == "Dodge" || cardName == "Parry" || cardName == "Thorn" || cardName == "HealthStone")
				newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + ".png");
			else
				newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + "_" + Consts::heros[player->getRole()] + ".png");
			newCard->setScale(0.5f);
			newCard->setAnchorPoint(Vec2(0.5, 0.5));
			auto loc = player->getLocation();
			auto picSize = player->getHeadPicSize();
			loc.y -= picSize.height / 2;
			loc.y += 1 / 4 * (s.height / 2 - loc.y);
			loc.x += 1 / 4 * (s.width / 2 - loc.x);
			newCard->setPosition(loc);
			this->addChild(newCard);
			
			auto move = MoveTo::create(0.3, Vec2(locs[k], s.height / 2));
			
			auto vanish = FadeOut::create(1);
			auto callback = CallFunc::create([this, newCard]() {
				this->removeChild(newCard);
				Global::getRoom()->setIsActable(true);
				this->getEventDispatcher()->setEnabled(true);
			});
			auto actions = Sequence::create(move, vanish,callback, nullptr);
			newCard->runAction(actions);
			newCard->setZOrder(-2);
			cards->pop_back();
			k++;
		}
		else {
			int sid = Global::getPlayer()->getSeatId();
			Sprite * _card = nullptr;
			for (auto card : *cards) {
				auto _cardId = *(int*)card->getUserData();
				if (_cardId == cardId) {
					_card = card;
					break;
				}
			}
			if (_card == nullptr) {
				cout << "Error : when discardCards, can't find this card " << cardId << endl;
				//continue;
			}
			//从vector中删除玩家出的牌
			auto result = find(cards->begin(), cards->end(), _card);
			cards->erase(result);
			
			
			_card->setAnchorPoint(Vec2(0.5, 0.5));


			//由于重置了锚点，所以要把图片移位
			int width = _card->getContentSize().width * _card->getScale() / 2;
			int height = _card->getContentSize().height * _card->getScale() / 2;
			_card->setPosition(_card->getPosition().x + width, _card->getPosition().y + height);

			auto scale = ScaleTo::create(0.3, 0.5f);

			auto move = MoveTo::create(0.3, Vec2(locs[k],s.height / 2));


			auto vanish = FadeOut::create(2);
			auto callback = CallFunc::create([this, sid,_card]() {
				this->getEventDispatcher()->removeEventListenersForTarget(card);
				this->removeChild(_card);
				this->getEventDispatcher()->setEnabled(true);
				Global::getRoom()->setIsActable(true);
			});
			auto acs = Spawn::create(scale, move, nullptr);
			auto actions = Sequence::create(acs,vanish,callback, nullptr);
			_card->runAction(actions);
			_card->setZOrder(-2);
			k++;
		}
	}
	this->resort(sid);
}

void OnGame::moveCard(int sid, int cardId, int targetSid) {
	auto cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
	cout << "Info : sid " << sid << " move card " << cardName << " , target is " << targetSid << endl;
	this->getEventDispatcher()->setEnabled(false);
	auto cards = this->cards[sid];
	auto s = Director::getInstance()->getWinSize();
	if (sid == Global::getPlayer()->getSeatId()) {
		for (auto card : *cards) {
			int _cardId = *(int*)card->getUserData();
			if (_cardId == cardId) {
				auto x = find(cards->begin(), cards->end(), card);
				if (x == cards->end()) {
					cout << "Error : when moveCard, can't find this card " << cardId << endl;
					//continue;
				}
				cards->erase(x);
				this->removeChild(card);
				this->resort(sid);
				break;
			}
		}
	}
	else {
		auto card = cards->at(cards->size() - 1);
		this->removeChild(card);
		cards->pop_back();
	}

	auto player = Global::getRoom()->getPlayerBySeatId(sid);
	auto targetPlayer = Global::getRoom()->getPlayerBySeatId(targetSid);

	cardName = Global::getRoom()->getTable()->GetCardStack()->GetCard(cardId)->Display();
	Sprite* newCard = nullptr;
	if (cardName == "Chop" || cardName == "Dodge" || cardName == "Parry" || cardName == "Thorn" || cardName == "HealthStone")
		newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + ".png");
	else
		newCard = Sprite::create("../../Resources/card_" + Value(cardName).asString() + "_" + Consts::heros[player->getRole()] + ".png");
	newCard->setScale(0.5f);
	newCard->setAnchorPoint(Vec2(0.5, 0.5));
	auto loc = player->getLocation();
	auto picSize = player->getHeadPicSize();
	if (player->getSeatId() == Global::getPlayer()->getSeatId()) {
		loc = Vec2(s.width / 2, s.height / 4);
	}
	else {
		loc.y -= picSize.height;
	}
	auto targetLoc = targetPlayer->getLocation();
	picSize = targetPlayer->getHeadPicSize();
	//cout << "(" << targetLoc.x << "," << targetLoc.y << ")" << endl;
	if (targetPlayer->getSeatId() == Global::getPlayer()->getSeatId()) {
		targetLoc = Vec2(s.width / 2, s.height / 4);
	}
	else {
		targetLoc.y -= picSize.height;
		cout << targetLoc.y << endl;
	}
	//cout << "(" << targetLoc.x << "," << targetLoc.y << ")" << endl;
	newCard->setPosition(loc);
	this->addChild(newCard);
	auto move = MoveTo::create(1, targetLoc);
	auto vanish = FadeOut::create(0.2);
	auto callback = CallFunc::create([this, newCard]() {
		this->removeChild(newCard);
		this->getEventDispatcher()->setEnabled(true);
	});
	auto actions = Sequence::create(move, vanish,callback, nullptr);
	newCard->runAction(actions);

	vector<int> x;
	x.push_back(cardId);
	this->addCards(targetSid,x);
}

void OnGame::createPlayCardPanel() {
	auto s = Director::getInstance()->getWinSize();

	if (this->playCardPanel != nullptr) {
		this->removeChild(this->playCardPanel);
		this->playCardPanel = nullptr;
	}

	//出牌的确定按钮
	auto panel = Node::create();
	auto play_btn = Sprite::create(Consts::base + "btn_g3.png");
	panel->addChild(play_btn, 0, "play_btn");
	play_btn->setScale(0.2f);
	play_btn->setPosition(Vec2(s.width / 4 + 100, s.height / 4 + 150));
	this->setBtnRotate(play_btn);
	auto btn_ok_font = Sprite::create(Consts::base + "btn_g3_font.png");
	panel->addChild(btn_ok_font, 0, "play_font");
	btn_ok_font->setScale(0.2f);
	btn_ok_font->setPosition(Vec2(s.width / 4 + 100, s.height / 4 + 150));

	//出牌结束按钮
	auto end_btn = Sprite::create(Consts::base + "btn_g2.png");
	panel->addChild(end_btn, 0, "end_btn");
	end_btn->setScale(0.2f);
	end_btn->setPosition(Vec2(s.width * 3 / 4 - 100, s.height / 4 + 150));
	this->setBtnRotate(end_btn);
	Sprite *end_font = nullptr;
	if (_room->getStatus() == Consts::play) {
		end_font = Sprite::create(Consts::base + "btn_e2_font.png");
	}
	else {
		end_font = Sprite::create(Consts::base + "btn_d2_font.png");
	}
	panel->addChild(end_font, 0, "end_font");
	end_font->setScale(0.2f);
	end_font->setPosition(Vec2(s.width * 3 / 4 - 100, s.height / 4 + 150));

	this->setListener(play_btn, Consts::base + "btn_g2.png", Consts::base + "btn_g1.png", "", 3);
	this->setListener(end_btn, Consts::base + "btn_g2.png", Consts::base + "btn_g1.png", "", 4);
	this->playCardPanel = panel;
	panel->setZOrder(21);
	this->addChild(panel);
}

void OnGame::startTurn() {
	cout << "Info : start turn!" << endl;
	auto s = Director::getInstance()->getWinSize();
	this->createPlayCardPanel();
	Global::getRoom()->setIsActable(true);

	this->timer->setPosition(s.width / 4, 225);
	this->time = 30;
	this->timerScale = 494 / this->timer->getContentSize().height;
	this->timer->setScaleY(timerScale);
	this->timer->setVisible(true);

	Global::getRoom()->setCurSid(Global::getPlayer()->getSeatId());
}

void OnGame::endTurn() {
	cout << "Info : end turn!" << endl;
	auto next_sid = (_room->getCurSId() + 1) %(_room->getPlayerCnt());
	_room->setCurSid(next_sid);
	
	if (next_sid != _player->getSeatId()) {
		this->role_back->setVisible(true);
		auto player = _room->getPlayerBySeatId(next_sid);
		this->role_back->setPosition(player->getLocation().x,player->getLocation().y - 66);

		auto size = player->getHeadPicSize();
		auto loc = player->getLocation();
		loc.x -= size.width / 2;
		loc.y -= size.height;
		this->timer->setPosition(loc.x, loc.y - 32);
		this->time = 30;
		this->timerScale = 0.3;
	}
	else {
		this->role_back->setVisible(false);
	}

	if (Global::getRoom()->getStatus() == Consts::RoomType::wait || Global::getRoom()->getStatus() == Consts::RoomType::play) {
		Global::getRoom()->getTable()->Act();
	}
	Global::getRoom()->setIsActable(true);
	this->clearOutCards();
}

void OnGame::changeTimer(float dt) {
	this->time--;
	if (this->time == 0) {
		cout << "Info : status is " << Global::getRoom()->getStatus() << endl;
		this->removeChild(this->playCardPanel);
		this->playCardPanel = nullptr;
		if (Global::getRoom()->getStatus() == Consts::play) {
			Global::getPlayer()->getTurn()->DiscardTurn();
			_room->setStatus(Consts::wait);
		}
		else if (Global::getRoom()->getStatus() == Consts::cardQuery) {
			auto card = Global::getRoom()->getTable()->GetCardStack()->GetCard(this->cardId);
			card->Effect();
			_room->setStatus(Consts::wait);
		}
		else if (Global::getRoom()->getStatus() == Consts::magicQuery) {
			cout << "here3" << endl;
			this->magic->Effect();
			_room->setStatus(Consts::wait);
		}
		else if (Global::getRoom()->getStatus() == Consts::pmagicQuery) {
			cout << "here4" << endl;
			this->magic->Effect();
			_room->setStatus(Consts::play);
			this->startTurn();
		}
		Global::getRoom()->setIsActable(true);
	}
	if (this->time < 0) {
		return;
	}
	this->frameTime = 60;
}

void OnGame::myUpdate(float dt) {
	if (this->frameTime < 0) {
		return;
	}
	double scale = (double)this->time / 30 + (double)this->frameTime / (60 * 30);
	//cout << scale << endl;
	this->timer->setScaleY(scale * this->timerScale);
	this->frameTime--;
}

bool OnGame::isOkBtnAble() {
	//if (_room->getTurn().size() != 0)
		//return false;

	int state = _room->getStatus();
	//cout << state << endl;
	switch (state) {
	case Consts::cardQuery:
		if (this->cardId < 0) {
			cout << "Error : cardId can't less than 0" << endl;
			return false;
		}
		if (this->card != nullptr) {
			auto cardId = *(int *)this->card->getUserData();
			auto queryCard = _room->getTable()->GetCardStack()->GetCard(this->cardId)->Display();
			auto cardName = _room->getTable()->GetCardStack()->GetCard(cardId)->Display();
			if (queryCard == "Thorn") {
				if (cardName == "Dodge")
					return true;
			}
			else if (queryCard == "Chop") {
				if (cardName == "Parry")
					return true;
			}
			else {
				cout << "Error : cardName "<<queryCard<<" is incorrect ! " << endl;
			}
			return false;
		}
		return false;
		break;
	case Consts::pmagicQuery:
	case Consts::magicQuery:
		if (this->card != nullptr) {
			auto cardId = *(int *)this->card->getUserData();
			auto cardName = _room->getTable()->GetCardStack()->GetCard(cardId)->Display();
			if (cardName == "DisturbCard")
				return true;
		}
		return false;
		break;
	case Consts::play:
		if (this->card != nullptr && this->targetSid != -10) {
			auto cardId = *(int *)this->card->getUserData();
			auto cardName = _room->getTable()->GetCardStack()->GetCard(cardId)->Display();
			//选中了一张卡，先看一下卡的类型
			if (cardName == "Dodge" || cardName == "Parry" || cardName == "DisturbCard")
				return false;
			return true;
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}

void OnGame::clearOutCards() {
	while (!this->outCards.empty()) {
		auto card = this->outCards.front();
		auto fade = FadeOut::create(1.0f);
		auto callback = CallFunc::create([this,card](){
			this->removeChild(card);
		});
		auto actions = Sequence::create(fade, callback, nullptr);
		card->runAction(actions);
		this->outCards.pop();
	}

	if (this->cover != nullptr) {
		this->removeChild(this->cover);
		this->cover = nullptr;
	}
}

void OnGame::discardTurn() {
	_room->setStatus(Consts::discard);
	this->removeChild(this->playCardPanel);
	this->playCardPanel = nullptr;
	this->clearOutCards();

	this->time = 30;

	this->toBeDiscardNum = 6;
	this->discardedNum = 0;
	while (!this->cardIds.empty()) {
		this->cardIds.pop_back();
	}


	auto s = Director::getInstance()->getWinSize();
	string info = "You have to discard ";
	info += Value(this->toBeDiscardNum).asString();
	info += " cards ! ";
	this->discardInfo->setString(info);
	this->discardInfo->setVisible(true);
	//弃牌的确定按钮
	auto panel = Node::create();
	auto play_btn = Sprite::create(Consts::base + "btn_g3.png");
	panel->addChild(play_btn, 0, "play_btn");
	play_btn->setScale(0.2f);
	play_btn->setPosition(Vec2(s.width / 2, s.height / 4 + 150));
	this->setBtnRotate(play_btn);
	auto btn_ok_font = Sprite::create(Consts::base + "btn_g3_font.png");
	panel->addChild(btn_ok_font, 0, "play_font");
	btn_ok_font->setScale(0.2f);
	btn_ok_font->setPosition(Vec2(s.width / 2, s.height / 4 + 150));

	this->setListener(play_btn, Consts::base + "btn_g2.png", Consts::base + "btn_g1.png", "", 7);
	this->playCardPanel = panel;
	panel->setZOrder(21);
	this->addChild(panel);
}
