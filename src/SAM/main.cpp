#include "main.h"
#include <iostream>
using namespace std;

int main() {
	printf("hello world\n");
	Table *t = new Table();
	HuXueDong *p1 = new HuXueDong(1);
	HuXin *p2 = new HuXin(1);
	t -> AddCharacter(p1, -1, 1);
	t -> AddCharacter(p2, -1, 2);
	printf("%d : %d %d %d %d %d\n", p1, p1 -> GetMaxHealth(), p1 -> GetProfession(), p1 -> GetTeam(), p1 -> GetAtk(), p1 -> GetID());
	printf("%d : %d %d %d %d %d\n", p2, p2 -> GetMaxHealth(), p2 -> GetProfession(), p2 -> GetTeam(), p2 -> GetAtk(), p2 -> GetID());
	CardStack *s = t -> GetCardStack();
	//s -> Display();
	int n = 67;
	p1 -> DrawCard(1);
	while (p1 -> cards_ -> at(0) -> GetID() != 50) {
		p1 -> DropACard(p1 -> cards_ -> at(0));
		p1 -> DrawCard(1);
		n--;
	}
	while (n--) {
		p1 -> DrawCard(1);
		p1 -> DropACard(p1 -> cards_ -> at(1));
	}
	for (int i = 0; i < p1 -> cards_ -> size(); i++)
		printf("%s %d\n", p1 -> cards_ -> at(i) -> Display().c_str(), p1 -> cards_ -> at(i) -> GetID());
	//s -> Display();
	printf("%d %d\n", p2 -> GetMaxHealth(), p2 -> GetHealth());
	Card *cc = p1 -> cards_ -> at(0);
	p1 -> Use(p1, p2, cc);
	printf("%d %d\n", p2 -> GetMaxHealth(), p2 -> GetHealth());
	system("pause");
	return 0;
}
