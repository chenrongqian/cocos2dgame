#include "HelloWorldScene.h"
#include "Mymenu.h"
#include <ctime>//����ʱ���װ����
USING_NS_CC;

//��������
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//��ʱ�����Ч����Ϸ����ȥ����ʱ��������������
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("zhongle.wav");
	//���ű������֣�playBackgroundMusic�ʺϳ�ʱ�䲥�ţ�
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
	
	//��ȡ�ʵ��е�maingame.xml�ļ�
	auto* chinese = Dictionary::createWithContentsOfFile("maingame.xml");

	judge = 0;//�ж���Ӯ��ʼ��
	sum = 0;
	propNum = 2;//���ߵ�ʹ�ø���
	timeOut = false;//ʱ��ʣ���ʼ��Ϊ��
	time = FULLTIME;//��ʱ��
	temp = Vec2(-1, -1);//λʸ����ֵ�����û�з�����ȥ������ΪVec2(-1, -1)���൱��point(0,0)

	//��ȡint���͵ļ�ֵ�Ե�ֵ
	int id = UserDefault::sharedUserDefault()->getIntegerForKey("id");//�û���id
		auto* recMap = TMXTiledMap::create(String::createWithFormat("rec%d.tmx", id)->getCString());//������Ƭ��ͼ�Ķ��󣬶�ȡ��ͼ��Ϣ
		recMap->setAnchorPoint(Vec2(0, 0));//ê�㣬�����½�Ϊ����
		recMap->setPosition(0, 0);//λ�ã�0��0��
		addChild(recMap);
		recLayer = recMap->layerNamed("Layer1");//��ȡ��Ƭ�е�ͼ������
	
		//�������鱳��
	auto* background = Sprite::create("maingameBG.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	addChild(background);

	//��ʼ����������ӣ��������ӣ�
	// �򳡾��м��뷽��
	initBoard();				
	//������ʱ���Ķ���
	bar = CountDownBar::createCountDownBar(Vec2(0, 360), 480);
	addChild(bar);

	//������ǩ�����ߵĸ���
	propLabel = Label::create(String::createWithFormat("tools:%d", propNum)->getCString(), "Arial", 26);
	propLabel->setAnchorPoint(Vec2(0, 0));
	propLabel->setPosition(510, 170);
	addChild(propLabel);
	// ���봥���Լ�������
	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* listener = EventListenerTouchOneByOne::create();
	// �󶨼����¼�
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);//��������
	scheduleUpdate();//��ʱ���ĸ���
    return true;
}

//����Ļ�ȡ,���ӳ�ʼ��
void HelloWorld::initBoard()
{
	int k = 0;
	int rand_card[WIDTH*HEIGHT] = { 0 };
	// �Ȼ�ȡ��ͼ���ж��ٸ�������ɫ��
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			// ��ȡ��ͼ��ĳ��ͼ���idֵ
			int id = recLayer->tileGIDAt(Vec2( x, y));
			if (id == 2)
			{
				// ���id=2˵��ͼ��Ϊ��ɫ������ʹ�á��������k+1
				k++;
			}
		}
	}

	// ��t_card�е�ֵȡ�����,��rand()�������ʹ��
	srand(unsigned(std::time(0)));
	for (int i = 0; i < k / 2; i++)
	{
		rand_card[i] = rand() % 5 + 1;
		rand_card[i + k / 2] = rand_card[i];
	}
	// ��t_card�����е�˳�����
	for (int i = 0; i < k; i++)
	{
		int rand_k = rand() % k;
		int t = rand_card[i];
		rand_card[i] = rand_card[rand_k];
		rand_card[rand_k] = t;
	}

	k = 0;
	// ��������t_card�͵�ͼ�е����ݿ�ʼ�������鲢��ʾ
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			// ��ȡ��ͼ��ĳ��ͼ���idֵ
			int id = recLayer->tileGIDAt(Vec2(x, y));
			if (id == 2)
			{
				// ���id=2˵��ͼ��Ϊ��ɫ������ʹ�á��򴴽���Ч����
				card[x][y] = CardSprite::createCardSprite(rand_card[k], x, y);
				addChild(card[x][y]);
				k++;
				judge++;
				sum = judge;
				
			}
			else
			{
				// ����������Ч����
				card[x][y] = CardSprite::createCardSprite(0, x, y);
				addChild(card[x][y]);
			}
		}
	}
}
//������ʼ��
bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	
	// x��y ��ȡ���û�������ĸ�������
	Point point = touch->getLocation();//�û����ʱ��
	int x = (int)point.x / SIZE;
	int y = (int)point.y / SIZE;
	//�����x��yΪָ���ĸ����鱻�����
	if (x < WIDTH&&y < HEIGHT)
	{//������ķ��鲻�ǿշ���
		if (card[x][y]->type != 0)
		{
			int x1 = (int)temp.x;
			int y1 = (int)temp.y;
			//temp������־Ϊ1��˵���÷��鱻��ָ
			if (x1 != -1 && y1 != -1)
			{
				// �жϴ˴ε���ķ������ϴε���ķ����Ƿ�������ͬ
				if (card[x][y]->type == card[x1][y1]->type)
				{
					// �����ͬ�ҿ���ͨ��ȫ����ȥ
					if (isCanConnection(x, y, x1, y1)==true)
					{
						card[x][y]->cardDelete();
						card[x1][y1]->cardDelete();
					}
					// temp�ָ�������־
					temp = Vec2(-1, -1);
				}
				else
				{
					card[x1][y1]->card->setOpacity(255);
					temp = Vec2(-1, -1);
				}
			}
			else
			{
				// ���temp��û�м�¼���ͱ�־���û������
				temp = Vec2(x, y);
				card[x][y]->card->setOpacity(180);//���û�����������ø÷���͸��
			}
		}
	}
	return false;
}

//ֱ����ͨ���ж�
bool HelloWorld::noCorner(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		// ����ֱ����ͨ
		int start = y1 < y2 ? y1 : y2;
		int end = y1 > y2 ? y1 : y2;
		for (int i = start + 1; i < end; i++)
		{
			if (card[x1][i]->type != 0)
			{
				
				return false;
			}
		}
	
		return true;
	}
	// ����ֱ����ͨ
	else if (y1 == y2)
	{
		
		int start = x1 < x2 ? x1 : x2;
		int end = x1 > x2 ? x1 : x2;
		for (int i = start + 1; i < end; i++)
		{
			if (card[i][y1]->type != 0)
			{
				
				return false;
			}
		}
	
		return true;
	}
	return false;
}
//һ���յ���ͨ
bool HelloWorld::oneCorner(int x1, int y1, int x2, int y2)
{
	//x1������x2����y1������y2
	if (!(x1 == x2) ||!( y1 == y2))
	{
		//type����0ʱ���õط��ǿշ���
		if (card[x1][y2]->type==0)
		{
			if (noCorner(x1, y1, x1, y2) && noCorner(x2, y2, x1, y2))
			{
				
				return true;
			}
			
			
		}
		
		if (card[x2][y1]->type==0)
		{
			if (noCorner(x1, y1, x2, y1) && noCorner(x2, y2, x2, y1))
			{
				return true;
			}	
		}
	}
	return false;
}
//�����յ���ͨ
bool HelloWorld::twoCorner(int x1, int y1, int x2, int y2)
{
	// �Ⱥ���ɨ��
	for (int i = 0; i < WIDTH; i++)
	{
		if (i != x1&&card[i][y1]->type== 0)
		{
			if (noCorner(x1, y1, i, y1) && oneCorner(x2, y2, i, y1))
			{
				
				return true;
			}
		}
	}
	// ������ɨ��
	for (int j = 0; j < HEIGHT; j++)
	{
		if (j != y1&&card[x1][j]->type == 0)
		{
			if (noCorner(x1, y1, x1, j) && oneCorner(x2, y2, x1, j))
			{
				
				return true;
			}
		}
	}
	return false;
}

///������ͨ���������ж�
bool HelloWorld::isCanConnection(int x1, int y1, int x2, int y2)
{
	if (x1 == x2&&y1 == y2)
		return false;
	if (noCorner(x1, y1, x2, y2))
	{//����ͨ��������Ч�Լ�judege-1
		judge--;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("zhongle.wav", false);
		return true;
	}
	
	if (oneCorner(x1, y1, x2, y2))
	{
		judge--;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("zhongle.wav", false);
		return true;
	}
	if (twoCorner(x1, y1, x2, y2))
	{
		judge--;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("zhongle.wav", false);
		return true;
}
	return false;
}
//���¼�ʱ��
void HelloWorld::update(float dt)
{
	if (time > 0)
	{
		bar->barUpdate(time, FULLTIME);
		
		time--;
		if (judge ==sum/2&&sum!=0&&judge!=0)
		{
			//�����Ļ�ߴ�
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto labbewin = Label::create("You Win!", "Arial", 32);
			labbewin->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
			addChild(labbewin);
		}
	}
	else
	{//ʱ�䵽
		if (!timeOut)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto labbewin = Label::create("You lose!", "Arial", 32);
			labbewin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			addChild(labbewin);
			//ʱ�䵽
			timeOut = true;
			// �������Ϸ����������Ӧ
			unscheduleUpdate();
		
		}
	}
	
	
}
///ʹ�õ��ߵĺ���
void HelloWorld::prop(Ref* pSender)
{
	if (propNum > 0)
	{//��һ�α�����Ŀ�����ҵ������ڵķ���
		for (int x1 = 0; x1 < WIDTH; x1++)
		{
			for (int y1 = 0; y1 < HEIGHT; y1++)
			{
				if (card[x1][y1]->type != 0)
				{
					// ���еڶ��α�����Ŀ�����ҵ���ͬ�ķ����Լ��ж��Ƿ���ͨ
					for (int x2 = 0; x2 < WIDTH; x2++)
					{
						for (int y2 = 0; y2 < HEIGHT; y2++)
						{//�ҵ�ͬ�ַ���
							if ((!(x1 == x2&&y1 == y2)) && (card[x1][y1]->type == card[x2][y2]->type))
							{
								//�ж��Ƿ���ͨ
								if (isCanConnection(x1, y1, x2, y2))
								{
									card[x1][y1]->card->setOpacity(80);//��ʾ͸����
									card[x2][y2]->card->setOpacity(80);//��ʾ͸��
									x1 = WIDTH;x2 = WIDTH;
									y1 = HEIGHT;y2 = HEIGHT;
								}
							}
						}
					}
				}
			}
		}
		//ʹ������ߺ󣬼�1
		propNum--;
		//��������ĸ�ʽ
		propLabel->setString(String::createWithFormat("tools:%d", propNum)->getCString());
	}
}

//����Ʋ�
void HelloWorld::onEnter()
{
	Layer::onEnter();
	//��ȡ��Ļ�ĳߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ������߰�ť
	auto toolMenuItem = MenuItemImage::create("stop1.png", "stop2.png", this,
		menu_selector(HelloWorld::prop));
	auto labeltool = Label::create("Tool", "Arial", 18);
	auto toolMenu = Menu::create(toolMenuItem, labeltool, NULL);
	toolMenu->setPosition(Vec2(visibleSize.width - visibleSize.width/7, visibleSize.height - 280));
	this->addChild(toolMenu, 20, 999);


	//��ʼ����ͣ��ť.
	auto pauseMenuItem = MenuItemImage::create("stop1.png", "stop2.png", this,
		menu_selector(HelloWorld::menuPauseCallback));
	auto labelpause = Label::create("pause","Arial",18);
	auto pauseMenu = Menu::create(pauseMenuItem,labelpause, NULL);
	pauseMenu->setPosition(Vec2(600, visibleSize.height - 28));
	this->addChild(pauseMenu, 20, 999);

};

//��ͣ��������Ӧ
void HelloWorld::menuPauseCallback(Ref* pSender)
{

	//��ͣ��ǰ���е�����node�ڵ�
	this->pause();

	for (const auto& node : this->getChildren())
	{
		node->pause();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�������˵�

	auto backMenuItem = MenuItemImage::create("zhu1.png", "zhu2.png", this,
		menu_selector(HelloWorld::menuBackCallback));

	//������Ϸ�˵�
	auto resumeMenuItem = MenuItemImage::create("jixu1.png", "jixu2.png", this,
		menu_selector(HelloWorld::menuResumeCallback));
	menu = Menu::create(backMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVertically();//�˵��ֱ����
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
///addChild(menu, ͼ��Ĳ���, ��ʶ��);
	addChild(menu, 20, 1000);

}
///�������˵�
void HelloWorld::menuBackCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, Mymenu::createScene()));

}
//������Ϸ
void HelloWorld::menuResumeCallback(Ref* pSender)
{
	//���нڵ����
	this->resume();
	for (const auto& node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);
}
