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

		//��ʼ���������
		//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ�� 
		unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);    //��ת��Ϊ���� 
		srand(rand_seed);

		return rand_0_1();
	}
};

#endif