#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class MyWorld:public cocos2d::Layer
{
public:
	
	int id;
	static cocos2d::Scene* createScene();	// 静态函数，用户获取场景对象
	virtual bool init();					// 初始化场景
	void menu(cocos2d::Ref* pSender);
	void menuButton01(cocos2d::Ref* pSender);
	void menuButton02(cocos2d::Ref* pSender);
	void menuButton03(cocos2d::Ref* pSender);
	void menuButton04(cocos2d::Ref* pSender);
	void menuButton05(cocos2d::Ref* pSender);
	void menuButton06(cocos2d::Ref* pSender);
	
	void mainmenu(cocos2d::Ref* pSender);//“主菜单”按钮，返回主菜单的函数
	CREATE_FUNC(MyWorld);					// 这里使用了一个宏
};



#endif

