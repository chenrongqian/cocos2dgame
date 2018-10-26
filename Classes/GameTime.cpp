#include "GameTime.h"
USING_NS_CC;
#define BARBG_WIDTH 80//宏定义设置宽
#define BARBG_HEIGHT 20//宏定义设置高
CountDownBar* CountDownBar::createCountDownBar(Point position, int size)
{
	CountDownBar* bar = new CountDownBar();//创建计时条类的对象
	if (bar && bar->init())//对象和他的初始为真真
	{
		bar->autorelease();//主动释放bar
		bar->countDownBarInit(position, size);//计时条的位置，以及大小
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return NULL;
}
bool CountDownBar::init()
{
	if (!Layer::init())//图层没有初始化
	{
		return false;
	}
	return true;
}
//创建计时条（位置以及大小）
void CountDownBar::countDownBarInit(cocos2d::Point position, int size)
{
	barBG = Sprite::create("barBG.png");
	barBG->setAnchorPoint(Vec2(0, 1));
	barBG->setScaleX((float)size / BARBG_WIDTH);
	barBG->setPosition(position);
	addChild(barBG);
	countDownBar = Sprite::create("bar.png");
	countDownBar->setAnchorPoint(Vec2(0, 0));
	countDownBar->setPosition(0, 0);
	barBG->addChild(countDownBar);
}
//计时条的更新，目的改变countDownBar计时条的宽度
void CountDownBar::barUpdate(int timeNow, int timeFull)
{
	countDownBar->setScaleX((float)timeNow / timeFull);
}