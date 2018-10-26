#ifndef __COUNTDOWNBAR_SCENE_H__
#define __COUNTDOWNBAR_SCENE_H__

#include "cocos2d.h"
//倒计时条类
class CountDownBar : public cocos2d::Layer
{
public:
	cocos2d::Sprite* barBG;//精灵类的黑色背景（游戏中的黑色条）
	cocos2d::Sprite* countDownBar;//显示计时的条（游戏中红色条）
	void barUpdate(int timeNow,int timeFull);//计时条的更新，目的改变countDownBar计时条的宽度
	static CountDownBar* createCountDownBar(cocos2d::Point position, int size);//创建计时条（位置以及大小）
	void countDownBarInit(cocos2d::Point position, int size);//计时条的初始化
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CountDownBar);
};

#endif // __COUNTDOWNBAR_SCENE_H__