#include "HelloWorldScene.h"
#include "Util.h"

#define TOLEFT 80
#define TOBOTTOM 40
#define PI 3.1415927
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg_layer = LayerColor::create(Color4B(100, 100, 100, 255));
	this->addChild(bg_layer);

	score_str = Label::createWithTTF("Score:", "fonts/arial.ttf", 64);
	score_str->setPosition(Vec2(visibleSize.width*3/4, visibleSize.height / 2 + 50));
	this->addChild(score_str, 1);

	score_num = Label::createWithTTF(__String::createWithFormat("%d", score)->getCString(), "fonts/arial.ttf", 64);
	score_num->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height / 2 - 50));
	this->addChild(score_num, 1);

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cardArray[i][j] = CardSprite::create(0, origin+Vec2(GRIDSIZE * i + TOLEFT, GRIDSIZE * j + TOBOTTOM));
			this->addChild(cardArray[i][j], 1);
		}
	}

	createCard();
	createCard();
	createCard();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [=](Touch* touch, Event* event)->bool{
			beginPos = touch->getLocation();
			return true;
		};
	listener->onTouchMoved = [=](Touch* touch, Event* event){
			
		};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
			float angle = getRad(touch->getLocation(), beginPos);

			CCLOG("%f", angle / PI * 180);

			if (angle > -PI / 4 && angle<PI / 4)
			{
				CCLOG("UP");
				operatorUp();
			}
			else if (angle>PI / 4 && angle<PI * 3 / 4)
			{
				CCLOG("Right");
				operatorRight();
			}
			else if (angle>PI * 3 / 4 || angle<PI*-3 / 4)
			{
				CCLOG("Down");
				operatorDown();
			}
			else if (angle>PI*-3 / 4 && angle < PI / -4)
			{
				CCLOG("left");
				operatorLetf();
			}
			checkGame();//判断游戏是否结束
			setScore();//设置分数
			if (isMove)
			{
				createCard();
			}
			Update();
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
void HelloWorld::checkGame()
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArray[y][x]->_val == 0 ||
				(x < 3 && cardArray[x][y]->_val == cardArray[x + 1][y]->_val) ||
				(x>0 && cardArray[x][y]->_val == cardArray[x - 1][y] -> _val) ||
				(y < 3 && cardArray[x][y]->_val == cardArray[x][y + 1]->_val) ||
				(y > 0 && cardArray[x][y]->_val == cardArray[x][y - 1]->_val))
			{
				isGameOver = false;
			}
		}

	}
	if (isGameOver)
	{
		log("GameOver!!!!!!");

		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}
void HelloWorld::setScore()
{
	score_num->setString(__String::createWithFormat("%d", score)->getCString());
}

float HelloWorld::getRad(Point p1, Point p2)
{
	float detax = p1.x - p2.x;
	float detay = p1.y - p2.y;
	float xie = sqrt(pow(detax, 2) + pow(detay, 2));

	float angle = acos(detay / xie);

	if (p1.x < p2.x)
	{
		angle = -angle;
	}

	return angle;
}

void HelloWorld::createCard()
{
	int j = rand() % 4;
	int i = rand() % 4;

	CCLOG("%d, %d", i, j);

	if (cardArray[i][j]->_val>0)
	{
		createCard();
	}
	else
	{
		cardArray[i][j]->_val = rand() % 10 < 1 ? 4 : 2;
		cardArray[i][j]->update();
	}

}


void HelloWorld::operatorDown()
{
	isMove = false;
	for (int i = 0; i < 4; i++)//列
	{
		for (int j = 0; j < 4; j++)//行
		{
			if (cardArray[i][j]->_val == 0)
				continue;
			else
			{
				for (int k = 0; k < j; k++)
				{
					if (cardArray[i][k]->_val == 0)		//找到最前面的0
					{
						if (k==0)
						{
							cardArray[i][k]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
							break;
						}
						if (cardArray[i][k-1]->_val == cardArray[i][j]->_val)
						{
							cardArray[i][k-1]->_val *= 2;
							cardArray[i][j]->_val = 0;
							score += cardArray[i][k - 1]->_val;
							isMove = true;
						}
						else
						{
							cardArray[i][k]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
						}
						break;
					}
					else
					{
						if (k == j - 1)	//两个之间没有0
						{
							if (cardArray[i][k]->_val == cardArray[i][j]->_val)
							{
								cardArray[i][k]->_val *= 2;
								cardArray[i][j]->_val = 0;
								score += cardArray[i][k]->_val;
								isMove = true;
							}
						}
					}
				}
			}
		}
	}
		
}
void HelloWorld::operatorUp()
{
	isMove = false;
	for (int i = 3; i >= 0 ; i--)//列
	{
		for (int j = 3; j >= 0; j--)//行
		{
			if (cardArray[i][j]->_val == 0)
				continue;
			else
			{
				for (int k = 3; k > j; k--)
				{
					if (cardArray[i][k]->_val == 0)
					{
						if (k==3)
						{
							cardArray[i][k]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
							break;
						}
						if (cardArray[i][k + 1]->_val == cardArray[i][j]->_val)
						{
							cardArray[i][k + 1]->_val *= 2;
							cardArray[i][j]->_val = 0;
							score += cardArray[i][k + 1]->_val;
							isMove = true;
						}
						else
						{
							cardArray[i][k]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
						}
						break;
					}
					else
					{
						if (k == j + 1)	//两个之间没有0
						{
							if (cardArray[i][k]->_val == cardArray[i][j]->_val)
							{
								cardArray[i][k]->_val *= 2;
								cardArray[i][j]->_val = 0;
								score += cardArray[i][k]->_val;
								isMove = true;
							}
						}
					}
				}
			}
		}
	}
}
void HelloWorld::operatorRight()
{
	isMove = false;
	for (int j = 3; j >=0 ; j--)//行
	{
		for (int i = 3; i >= 0; i--)//列
		{
			if (cardArray[i][j]->_val == 0)
				continue;
			else
			{
				for (int k = 3; k > i; k--)
				{
					if (cardArray[k][j]->_val == 0)
					{
						if (k == 3)
						{
							cardArray[k][j]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
							break;
						}
						if (cardArray[k+1][j]->_val == cardArray[i][j]->_val)
						{
							cardArray[k+1][j]->_val *= 2;
							cardArray[i][j]->_val = 0;
							score += cardArray[k + 1][j]->_val;
							isMove = true;
						}
						else
						{
							cardArray[k][j]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
						}
						break;
					}
					else
					{
						if (k == i + 1)	//两个之间没有0
						{
							if (cardArray[k][j]->_val == cardArray[i][j]->_val)
							{
								cardArray[k][j]->_val *= 2;
								cardArray[i][j]->_val = 0;
								score += cardArray[k][j]->_val;
								isMove = true;
							}
						}
					}
				}
			}
		}
	}
}
void HelloWorld::operatorLetf()
{
	isMove = false;
	for (int j = 0; j < 4 ; j++)//行
	{
		for (int i = 0; i < 4; i++)//列
		{
			if (cardArray[i][j]->_val == 0)
				continue;
			else
			{
				for (int k = 0; k < i; k++)
				{
					if (cardArray[k][j]->_val == 0)
					{
						if (k == 0)
						{
							cardArray[k][j]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
							break;
						}
						if (cardArray[k - 1][j]->_val == cardArray[i][j]->_val)
						{
							cardArray[k - 1][j]->_val *= 2;
							cardArray[i][j]->_val = 0;
							score += cardArray[k - 1][j]->_val;
							isMove = true;
						}
						else
						{
							cardArray[k][j]->_val = cardArray[i][j]->_val;
							cardArray[i][j]->_val = 0;
							isMove = true;
						}
						break;
					}
					else
					{
						if (k == i - 1)	//两个之间没有0
						{
							if (cardArray[k][j]->_val == cardArray[i][j]->_val)
							{
								cardArray[k][j]->_val *= 2;
								cardArray[i][j]->_val = 0;
								score += cardArray[k][j]->_val;
								isMove = true;
							}
						}
					}
				}
			}
		}
	}
}

void HelloWorld::Update()
{
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cardArray[i][j]->update();
		}
	}
}
