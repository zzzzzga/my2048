#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void operatorDown();
	void operatorUp();
	void operatorRight();
	void operatorLetf();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	int score=0;
	Label* score_str;
	Label* score_num;
	CardSprite* cardArray[4][4];
	bool isMove=false;
	Vec2 beginPos;
	void checkGame();
	void setScore();

public:
	void createCard();
	float getRad(Point p1, Point p2);
	void Update();
};

#endif // __HELLOWORLD_SCENE_H__
