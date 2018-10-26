#ifndef __COUNTDOWNBAR_SCENE_H__
#define __COUNTDOWNBAR_SCENE_H__

#include "cocos2d.h"
//����ʱ����
class CountDownBar : public cocos2d::Layer
{
public:
	cocos2d::Sprite* barBG;//������ĺ�ɫ��������Ϸ�еĺ�ɫ����
	cocos2d::Sprite* countDownBar;//��ʾ��ʱ��������Ϸ�к�ɫ����
	void barUpdate(int timeNow,int timeFull);//��ʱ���ĸ��£�Ŀ�ĸı�countDownBar��ʱ���Ŀ��
	static CountDownBar* createCountDownBar(cocos2d::Point position, int size);//������ʱ����λ���Լ���С��
	void countDownBarInit(cocos2d::Point position, int size);//��ʱ���ĳ�ʼ��
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CountDownBar);
};

#endif // __COUNTDOWNBAR_SCENE_H__