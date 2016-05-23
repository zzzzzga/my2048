#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Util
{
public:
	float random_0_1()
	{
		struct timeval now;
		gettimeofday(&now, NULL);

		//初始化随机种子
		//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
		unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //都转化为毫秒 
		srand(rand_seed);

		return rand_0_1();
	}
};

#endif