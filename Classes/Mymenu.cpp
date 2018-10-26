#include "Mymenu.h"
#include "MyScene.h"
USING_NS_CC;
Scene* Mymenu::createScene()
{//创建场景
	auto scene = Scene::create();
	auto layer = Mymenu::create();
	scene->addChild(layer);
	return scene;
}
bool Mymenu::init()
{
	if (!Layer::init())
	{
		return false;
	}


	//加载词典文件menu.xml
	auto* chinese = Dictionary::createWithContentsOfFile("menu.xml");
	//主菜单背景

	auto *pBackground = Sprite::create("GameMenu.png");
	pBackground->setPosition(320, 180);
	this->addChild(pBackground);

	//游戏主题动物连连看
	const char *sthene = ((String*)chinese->objectForKey("Animal"))->getCString();
	auto labelthene = LabelTTF::create(sthene, "Arial", 32);
	labelthene->setPosition(535, 270);
	this->addChild(labelthene);

	//关卡模式
	const char *strlmode = ((String*)chinese->objectForKey("CheckMode"))->getCString();
	auto pMenumode = MenuItemImage::create("menubutton.png", "menubutton.png", this, menu_selector(Mymenu::checkmode));
	auto labelmode = LabelTTF::create(strlmode, "Arial", 18);
	auto pLabelmode = MenuItemLabel::create(labelmode);
	auto menumode = Menu::create(pMenumode, pLabelmode, NULL);
	menumode->setPosition(235, 240);
	this->addChild(menumode);

	//游戏帮助
	const char *strlhelp = ((String*)chinese->objectForKey("GameHelp"))->getCString();
	auto pMenuhelp = MenuItemImage::create("menubutton.png", "menubutton.png", this, menu_selector(Mymenu::gamehelp));
	auto labelhelp = LabelTTF::create(strlhelp, "Arial", 18);
	auto pLabelhelp = MenuItemLabel::create(labelhelp);
	auto menuhelp = Menu::create(pMenuhelp, pLabelhelp, NULL);
	menuhelp->setPosition(235, 200);
	this->addChild(menuhelp);

	//游戏退出
	const char *strlexit = ((String*)chinese->objectForKey("GameExit"))->getCString();
	auto pMenuexit = MenuItemImage::create("menubutton.png", "menubutton.png", this, menu_selector(Mymenu::gameexit));
	auto labelexit = LabelTTF::create(strlexit, "Arial", 18);
	auto pLabelexit = MenuItemLabel::create(labelexit);
	auto menuexit = Menu::create(pMenuexit, pLabelexit, NULL);
	menuexit->setPosition(235,160);
	this->addChild(menuexit);
	return true;

}
//关卡模式
void Mymenu::checkmode(Ref* pSender)
{
	
	Director::sharedDirector()->replaceScene(TransitionMoveInL::create(0.5f, MyWorld::createScene()));
}
//游戏帮助
void Mymenu::gamehelp(Ref* pSender)
{	
}

//游戏退出
void Mymenu::gameexit(Ref* pSender)
{
	exit(0);
}
