#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
//�������
class CardSprite : public cocos2d::Layer
{
public:
	int type;//��ʶ���������
	Sprite* card;//����������Ķ���card
	void cardDelete();//��ȥ����ķ���
	static CardSprite* createCardSprite(int type, float x, float y);//��������ķ���
	void cardInit(int type, float x, float y);//�����ʼ��
	virtual bool init();//���ʼ��
	CREATE_FUNC(CardSprite);//
};
#endif