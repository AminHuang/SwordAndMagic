#include "Utils.h"
#include <iostream>
using std::cout;
using std::endl;

int Utils::random(int num) {
	return rand() % num;
}

double Utils::random() {
	double r = (double)random(1000) / 1000;
	//cout << r << endl;
	return r;
}

int Utils::random(int left, int right) {
	return (right - left) * random() + left;
}


