#include "Card.h"
#include "cocos2d.h"
USING_NS_CC;
CardSprite* CardSprite::createCardSprite(int type, float x, float y)
{
	
	CardSprite* card = new CardSprite();//创建一个对象
	if (card && card->init())//对象和初始化
	{
		card->autorelease();//card对象释放
		card->cardInit(type, x, y);//初始化
		return card;
	}
	CC_SAFE_DELETE(card);
	return NULL;
}
bool CardSprite::init()
{	
	if (!Layer::init())//如果图层没有初始化
	{
		return false;
	}
	return true;
}
void CardSprite::cardInit(int type, float x, float y)
{
	this->type = type;//种类的值赋值给对象的type
	card = Sprite::create(String::createWithFormat("card%d.png",type)->getCString());//创建精灵card
	card->setPosition(20 + 40 * x, 20 + 40 * y);//位置的摆放
	addChild(card);//将card添加到CardSprite对象中
}
///消去方块
void CardSprite::cardDelete()
{
	this->type = 0;//当type为0时
	auto texture = Director::getInstance()->getTextureCache()->addImage("card0.png");//导演添加card0透明图片
	auto frame = SpriteFrame::create("card0.png", Rect(0, 0, 40, 40));//图片的大小
	card->setDisplayFrame(frame);//显示方块框框
}