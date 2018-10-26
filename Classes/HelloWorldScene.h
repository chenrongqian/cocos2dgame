#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "MyScene.h"
#include "cocos2d.h"
#include "Card.h"
#include "GameTime.h"
#include"SimpleAudioEngine.h"
#define WIDTH 12//宽12格子
#define HEIGHT 9//高9个格子
#define SIZE 40//每个尺寸为40
#define FULLTIME 3000//时间
class HelloWorld : public cocos2d::Layer
{
public:
	int sum;
	int judge;
	int propNum;
	bool timeOut;
	
	int time;
	Point temp;
	TMXLayer* recLayer;
	CardSprite* card[WIDTH][HEIGHT];
	CountDownBar* bar;
	cocos2d::Label* scoreLabel;
	cocos2d::Label* timeLabel;
	cocos2d::Label* propLabel;
	void initBoard();
	bool noCorner(int x1, int y1, int x2, int y2);
	bool oneCorner(int x1, int y1, int x2, int y2);
	bool twoCorner(int x1, int y1, int x2, int y2);
	bool isCanConnection(int x1, int y1, int x2, int y2);
	

	void prop(cocos2d::Ref* pSender);

    static cocos2d::Scene* createScene();
    virtual bool init(); 
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch *touch, Event *event);


	virtual void onEnter();

	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);

private:
	cocos2d::Menu* menu;
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
