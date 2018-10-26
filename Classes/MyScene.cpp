#include "MyScene.h"
#include "Mymenu.h"
USING_NS_CC;

Scene* MyWorld::createScene()
{//创建场景
	auto scene = Scene::create();
	auto layer = MyWorld::create();
	scene->addChild(layer);
	return scene;
}
bool MyWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
///加载词典中的checkpoint.xml
auto* chinese = Dictionary::createWithContentsOfFile("checkpoint.xml");

//背景精灵
auto *pBackground = Sprite::create("background.png");
pBackground->setPosition(320, 180);
this->addChild(pBackground);

//读取checkpoint.xml中的check1
const char *strl = ((String*)chinese->objectForKey("check1"))->getCString();
//关卡1的按钮
auto pMenu11 = MenuItemImage::create("button.png", "button.png", this, menu_selector(MyWorld::menuButton01));
auto label11 = LabelTTF::create(strl, "Arial", 18);
auto pLabel11 = MenuItemLabel::create(label11);
auto menu11 = Menu::create(pMenu11, pLabel11, NULL);
menu11->setPosition(64 + 128 * 2, 300);
this->addChild(menu11);

//关卡2的按钮
const char *str2 = ((String*)chinese->objectForKey("check2"))->getCString();
auto pMenu12 = MenuItemImage::create("button.png", "button.png", this, menu_selector(MyWorld::menuButton02));
auto label12 = LabelTTF::create(str2, "Arial", 18);
auto pLabel12 = MenuItemLabel::create(label12);
auto menu12 = Menu::create(pMenu12, pLabel12, NULL);
menu12->setPosition(64 + 128 * 3, 300);
this->addChild(menu12);


//关卡3的按钮
const char *str3 = ((String*)chinese->objectForKey("check3"))->getCString();
auto pMenu13 = MenuItemImage::create("button.png", "button.png", this, menu_selector(MyWorld::menuButton03));
auto label13 = LabelTTF::create(str3, "Arial", 18);
auto pLabel13 = MenuItemLabel::create(label13);
auto menu13 = Menu::create(pMenu13, pLabel13, NULL);
menu13->setPosition(64 + 128 * 4, 300);
this->addChild(menu13);

//关卡4的按钮
const char *str4 = ((String*)chinese->objectForKey("check4"))->getCString();
auto pMenu21 = MenuItemImage::create("button.png", "button.png", this, menu_selector(MyWorld::menuButton04));
auto label21 = LabelTTF::create(str4, "Arial", 18);
auto pLabel21 = MenuItemLabel::create(label21);
auto menu21 = Menu::create(pMenu21, pLabel21, NULL);
menu21->setPosition(64 + 128 * 2, 180);
this->addChild(menu21);
//关卡5的按钮
const char *str5 = ((String*)chinese->objectForKey("check5"))->getCString();
auto pMenu22 = MenuItemImage::create("button.png", "button_a.png", this, menu_selector(MyWorld::menuButton05));
auto label22 = LabelTTF::create(str5, "Arial", 18);
auto pLabel22 = MenuItemLabel::create(label22);
auto menu22 = Menu::create(pMenu22, pLabel22, NULL);
menu22->setPosition(64 + 128 * 3, 180);
this->addChild(menu22);
//关卡6的按钮
const char *str6 = ((String*)chinese->objectForKey("check6"))->getCString();
auto pMenu23 = MenuItemImage::create("button.png", "button_a.png", this, menu_selector(MyWorld::menuButton06));
auto label23 = LabelTTF::create(str6, "Arial", 18);
auto pLabel23 = MenuItemLabel::create(label23);
auto menu23 = Menu::create(pMenu23, pLabel23, NULL);
menu23->setPosition(64 + 128 * 4, 180);
this->addChild(menu23);

//主菜单的按钮（返回主菜单）
auto zhupMenu = MenuItemImage::create("zhucaidan.png", "zhucaidanp.png", this, menu_selector(MyWorld::mainmenu));
//auto zhulabel = LabelTTF::create(str7, "Arial", 18);
//auto zhupLabel = MenuItemLabel::create(zhulabel);
auto zhumenu = Menu::create(zhupMenu,/* zhupLabel,*/ NULL);
zhumenu->setPosition(64 + 128 * 3, 60);
this->addChild(zhumenu);
return true;
}
//关卡1
void MyWorld::menuButton01(Ref* pSender)
{
	id = 0;
	//存放键的值id
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//关卡2
void MyWorld::menuButton02(Ref* pSender)
{
	id = 1;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//关卡3
void MyWorld::menuButton03(Ref* pSender)
{
	id = 2;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//关卡4
void MyWorld::menuButton04(Ref* pSender)
{
	id = 3;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//关卡5
void MyWorld::menuButton05(Ref* pSender)
{
	id = 4;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//关卡6
void MyWorld::menuButton06(Ref* pSender)
{
	id = 5;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
//主菜单（返回主菜单）
void  MyWorld::mainmenu(Ref* pSender)
{
	id = 6;
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, Mymenu::createScene()));

}