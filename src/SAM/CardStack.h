#ifndef CardStack_H
#define CardStack_H


class Card;
#include "Card.h"

class CardStack {

	public:
		CardStack();
		~CardStack();
		Card *GetTheTop();
		bool Shuffle();
		bool Discard(Card *card);
		void NewCard(Card *card);
		Card *GetCard(int id);
		void Display();
	private:
		vector<Card*> *cardstack_;
		vector<Card*> *desertstack_;
		vector<Card*> *cards_;
		int num_;

};



#endif
