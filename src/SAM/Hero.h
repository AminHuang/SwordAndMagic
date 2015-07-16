#ifndef Hero_H
#define Hero_H



#include <map>
using namespace std;
class Magic;
#include "Magic.h"
class Sword;
#include "Sword.h"
class Card;
#include "Card.h"
class CardStack;
#include "CardStack.h"
class Table;
//#include "Table.h"
class Character;
#include "Character.h"
#include "Enum.h"

class Turn;
#include "Turn.h"


class Player;
#include "Player.h"

class Hero : public Character {

	public:
		Hero();
		~Hero();
		bool HaveMagic(string magic);
		bool Attack(Character *user, Character *receiver, int times);
		bool Use(Character *user, Character *receiver, Card *card);
		virtual bool AskAnswer(Character *user, Card *card);
		virtual bool AskAnswer(Character *user, Magic *magic);
		bool Have(State state);
		bool AddState(State state, Character *user);
		bool States(int turn);
		bool ClearState(State state);
		//bool DeepWounds();
		bool AddCard(Card *card);
		bool DropACard(Card *card);
		virtual bool Act(Turn *turn); 
		virtual bool DisCard(int k = 2);
		bool LostAll();
		//void SetChoose(int choose);
		void Set(int health, int profession, int atk, Magic *magic1, Magic *magic2, Magic *magic3);
		void SetTable(CardStack *cardstack, vector<Character*> *characters, Table *table);
		virtual string Display();
		//void JudgeMagic(int turn);
		bool GetHurt(Character *user, float dam, int type = 0);
		bool GetHeal(Character *user, float dam, int type = 0);
		int GetHealth();
		int GetMaxHealth();
		int GetAtk();
		int GetProfession();
		int GetTeam();
		bool SetTeam(int team);
		//int GetID();
		//bool SetID(int id);
		Card *GetSword();
		Magic *GetHit();
		bool SetHit(Magic *hit);
		Character *GetHitFrom();
		bool SetHitFrom(Character *hitfrom);
		Card *StealCard(Character *receiver);
		virtual bool MakeChoice(int k, Magic *magic = NULL);
		/*
		1 暗影斗篷
		2 重伤
		3 丢一张基础牌
		*/
		//Player * getPlayer();
		//void setPlayer(Player *player);
		void DrawCard(int k = 2);
		void ClearAllStates();
		bool CometStorm();
		bool BaoDao();
		float CalDam(float dam, int type = 0);
		float CalHeal(float dam, int type = 0);
		//bool DiscardABaseCard();
		bool Shield(float dam);
		bool Attack();
		void Die(Character* killer);
		
		
		int health_;
		int profession_;
		int choose_;
		int maxheal_;
		int heal_;
		float healf_;
		int atk_;
		int addatk_;
		map<State, Character*> *states_;
		vector<Card*> *cards_;
		Sword *sword_;
		Magic *magic1_;
		Magic *magic2_;
		Magic *magic3_;
		CardStack *cardstack_;
		vector<Character*> *characters_;
		float shield_;
		int team_;
		//int id_;
		Magic *hit_;
		Hero *hitfrom_;
		bool attacken_;
		Table *table_;
		//Player *player;
		int huixiang_;
};



#endif
