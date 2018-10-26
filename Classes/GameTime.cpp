#include "GameTime.h"
USING_NS_CC;
#define BARBG_WIDTH 80//�궨�����ÿ�
#define BARBG_HEIGHT 20//�궨�����ø�
CountDownBar* CountDownBar::createCountDownBar(Point position, int size)
{
	CountDownBar* bar = new CountDownBar();//������ʱ����Ķ���
	if (bar && bar->init())//��������ĳ�ʼΪ����
	{
		bar->autorelease();//�����ͷ�bar
		bar->countDownBarInit(position, size);//��ʱ����λ�ã��Լ���С
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return NULL;
}
bool CountDownBar::init()
{
	if (!Layer::init())//ͼ��û�г�ʼ��
	{
		return false;
	}
	return true;
}
//������ʱ����λ���Լ���С��
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
//��ʱ���ĸ��£�Ŀ�ĸı�countDownBar��ʱ���Ŀ��
void CountDownBar::barUpdate(int timeNow, int timeFull)
{
	countDownBar->setScaleX((float)timeNow / timeFull);
}