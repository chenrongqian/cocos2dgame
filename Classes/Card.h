#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
//方块的类
class CardSprite : public cocos2d::Layer
{
public:
	int type;//标识方块的种类
	Sprite* card;//声明精灵类的对象card
	void cardDelete();//消去方块的方法
	static CardSprite* createCardSprite(int type, float x, float y);//创建方块的方法
	void cardInit(int type, float x, float y);//方块初始化
	virtual bool init();//类初始化
	CREATE_FUNC(CardSprite);//
};
#endif