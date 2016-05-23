#include "CardSprite.h"

CardSprite* CardSprite::create(int val, Point pos)
{
	CardSprite* pRef = new CardSprite();
	if (pRef && pRef->init(val, pos))
	{
		pRef->autorelease();
		return pRef;
	}

	CC_SAFE_DELETE(pRef);
	return NULL;
}

bool CardSprite::init(int val, Point pos)
{
	if (!Node::init())
	{
		return false;
	}
	_val = val;

	this->setAnchorPoint(Point::ZERO);
	this->setPosition(pos);

	this->setContentSize(Size(GRIDSIZE, GRIDSIZE));
	
	bg_color = LayerColor::create(Color4B(200, 200, 200, 255));
	bg_color->setPosition(Vec2(MARGINSIZE/2, MARGINSIZE/2));
	bg_color->setContentSize(Size(GRIDSIZE - MARGINSIZE, GRIDSIZE - MARGINSIZE));
	addChild(bg_color,1);

	if (_val>0)
	{
		label_val = Label::createWithTTF(__String::createWithFormat("%d", _val)->getCString(), "fonts/arial.ttf", 32);
		label_val->setPosition(Vec2(GRIDSIZE / 2, GRIDSIZE / 2));
		addChild(label_val, 2);
	}

	return true;
}

void CardSprite::update()
{
	if (_val>0)
	{
		if (label_val)
		{
			label_val->setString(__String::createWithFormat("%d", _val)->getCString());
		}
		else
		{
			label_val = Label::createWithTTF(__String::createWithFormat("%d", _val)->getCString(), "fonts/arial.ttf", 32);
			label_val->setPosition(Vec2(GRIDSIZE / 2, GRIDSIZE / 2));
			addChild(label_val, 2);
		}
		label_val->setVisible(true);
	}
	if (_val == 0)
	{
		if (label_val)
		{
			label_val->setVisible(false);
		}
	}
	if (_val == 0)
	{
		bg_color->setColor(Color3B(200, 190, 180));
	}
	if (_val == 2)
	{
		bg_color->setColor(Color3B(240, 200, 170));
	}
	if (_val == 4)
	{
		bg_color->setColor(Color3B(240, 200, 100));
	}
	if (_val == 8) {
		bg_color->setColor(Color3B(240, 180, 120));
	}
	if (_val == 16) {
		bg_color->setColor(Color3B(240, 140, 90));
	}
	if (_val == 32) {
		bg_color->setColor(Color3B(240, 120, 90));
	}
	if (_val == 64) {
		bg_color->setColor(Color3B(240, 90, 60));
	}
	if (_val == 128) {
		bg_color->setColor(Color3B(240, 90, 60));
	}
	if (_val == 256) {
		bg_color->setColor(Color3B(240, 200, 70));
	}
	if (_val == 512) {
		bg_color->setColor(Color3B(240, 200, 70));
	}
	if (_val == 1024) {
		bg_color->setColor(Color3B(0, 130, 0));
	}
	if (_val == 2048) {
		bg_color->setColor(Color3B(0, 130, 0));
	}
}