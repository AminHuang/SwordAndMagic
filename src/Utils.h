#ifndef __UTILS_H_
#define __UTILS_H_

#include <iostream>
#include <time.h>

class Utils {
public:
	static int random(int left, int right); //返回在left和right范围内一个随机数
	static double random(); //返回在0~1之间的随机数
private:
	static int random(int num);
};
#endif