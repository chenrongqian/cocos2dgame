#include "Card.h"
#include "cocos2d.h"
USING_NS_CC;
CardSprite* CardSprite::createCardSprite(int type, float x, float y)
{
	
	CardSprite* card = new CardSprite();//����һ������
	if (card && card->init())//����ͳ�ʼ��
	{
		card->autorelease();//card�����ͷ�
		card->cardInit(type, x, y);//��ʼ��
		return card;
	}
	CC_SAFE_DELETE(card);
	return NULL;
}
bool CardSprite::init()
{	
	if (!Layer::init())//���ͼ��û�г�ʼ��
	{
		return false;
	}
	return true;
}
void CardSprite::cardInit(int type, float x, float y)
{
	this->type = type;//�����ֵ��ֵ�������type
	card = Sprite::create(String::createWithFormat("card%d.png",type)->getCString());//��������card
	card->setPosition(20 + 40 * x, 20 + 40 * y);//λ�õİڷ�
	addChild(card);//��card��ӵ�CardSprite������
}
///��ȥ����
void CardSprite::cardDelete()
{
	this->type = 0;//��typeΪ0ʱ
	auto texture = Director::getInstance()->getTextureCache()->addImage("card0.png");//�������card0͸��ͼƬ
	auto frame = SpriteFrame::create("card0.png", Rect(0, 0, 40, 40));//ͼƬ�Ĵ�С
	card->setDisplayFrame(frame);//��ʾ������
}