#ifndef __UTILS_H_
#define __UTILS_H_

#include <iostream>
#include <time.h>

class Utils {
public:
	static int random(int left, int right); //������left��right��Χ��һ�������
	static double random(); //������0~1֮��������
private:
	static int random(int num);
};
#endif