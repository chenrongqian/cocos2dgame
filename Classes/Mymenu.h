#ifndef __MYMENU_SCENE_H__
#define __MYMENU_SCENE_H__

#include "cocos2d.h"
class Mymenu :public cocos2d::Layer
{
public:

	void checkmode(cocos2d::Ref* pSender);//关卡模式
	void gamehelp(cocos2d::Ref* pSender);//游戏帮助
	void gameexit(cocos2d::Ref* pSender);//游戏退出
	static cocos2d::Scene* createScene();	// 静态函数，用户获取场景对象
	virtual bool init();					// 初始化场景
	void menu(cocos2d::Ref* pSender);
	CREATE_FUNC(Mymenu);					// 这里使用了一个宏
};
#endif

