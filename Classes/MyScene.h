#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class MyWorld:public cocos2d::Layer
{
public:
	
	int id;
	static cocos2d::Scene* createScene();	// ��̬�������û���ȡ��������
	virtual bool init();					// ��ʼ������
	void menu(cocos2d::Ref* pSender);
	void menuButton01(cocos2d::Ref* pSender);
	void menuButton02(cocos2d::Ref* pSender);
	void menuButton03(cocos2d::Ref* pSender);
	void menuButton04(cocos2d::Ref* pSender);
	void menuButton05(cocos2d::Ref* pSender);
	void menuButton06(cocos2d::Ref* pSender);
	
	void mainmenu(cocos2d::Ref* pSender);//�����˵�����ť���������˵��ĺ���
	CREATE_FUNC(MyWorld);					// ����ʹ����һ����
};



#endif

