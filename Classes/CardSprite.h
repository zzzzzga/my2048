#ifndef _CARDSPRITE_H_
#define _CARDSPRITE_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
#define  GRIDSIZE 100
#define  MARGINSIZE 8

class CardSprite:public Node
{
public:
	static CardSprite* create(int val, Point pos);

	bool init(int val, Point pos);
	void update();

public:
	int _val=0;
	Label* label_val=NULL;
	LayerColor* bg_color=NULL;
};

#endif