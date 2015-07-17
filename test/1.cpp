#include<iostream>
using namespace std;

class A{
	public:
		A() {
		}
		virtual int getk() {
			return 1;
		}
		void setk(int kk) {
			k = kk;
		}
		void pp() {
			printf("%d\n", k);
		}
	private:
		int k;
};


class B : public A{
	public:
		B() {
			setk(6);
		}
		int getk() {
			return 5;
		}
};


int main(void){
	B b;
	A *p = &b;
	printf("%d\n", p->getk());
	p->pp();
	system("pause");
	return 0;
}
