#ifndef __MYMENU_SCENE_H__
#define __MYMENU_SCENE_H__

#include "cocos2d.h"
class Mymenu :public cocos2d::Layer
{
public:

	void checkmode(cocos2d::Ref* pSender);//�ؿ�ģʽ
	void gamehelp(cocos2d::Ref* pSender);//��Ϸ����
	void gameexit(cocos2d::Ref* pSender);//��Ϸ�˳�
	static cocos2d::Scene* createScene();	// ��̬�������û���ȡ��������
	virtual bool init();					// ��ʼ������
	void menu(cocos2d::Ref* pSender);
	CREATE_FUNC(Mymenu);					// ����ʹ����һ����
};
#endif

