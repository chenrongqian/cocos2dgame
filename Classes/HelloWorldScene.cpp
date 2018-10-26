#include "HelloWorldScene.h"
#include "Mymenu.h"
#include <ctime>//引入时间封装的类
USING_NS_CC;

//创建场景
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
	//短时间的音效（游戏中消去方块时的声音）被加载
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("zhongle.wav");
	//播放背景音乐（playBackgroundMusic适合长时间播放）
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
	
	//读取词典中的maingame.xml文件
	auto* chinese = Dictionary::createWithContentsOfFile("maingame.xml");

	judge = 0;//判定输赢初始化
	sum = 0;
	propNum = 2;//道具的使用个数
	timeOut = false;//时间剩余初始化为假
	time = FULLTIME;//总时间
	temp = Vec2(-1, -1);//位矢量的值，点击没有符合消去条件就为Vec2(-1, -1)，相当于point(0,0)

	//获取int类型的键值对的值
	int id = UserDefault::sharedUserDefault()->getIntegerForKey("id");//用户的id
		auto* recMap = TMXTiledMap::create(String::createWithFormat("rec%d.tmx", id)->getCString());//创建瓦片地图的对象，读取地图信息
		recMap->setAnchorPoint(Vec2(0, 0));//锚点，以左下角为中心
		recMap->setPosition(0, 0);//位置（0，0）
		addChild(recMap);
		recLayer = recMap->layerNamed("Layer1");//读取瓦片中的图层名称
	
		//创建精灵背景
	auto* background = Sprite::create("maingameBG.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	addChild(background);

	//初始化方块的盘子（整个格子）
	// 向场景中加入方块
	initBoard();				
	//创建计时条的对象
	bar = CountDownBar::createCountDownBar(Vec2(0, 360), 480);
	addChild(bar);

	//创建标签，道具的个数
	propLabel = Label::create(String::createWithFormat("tools:%d", propNum)->getCString(), "Arial", 26);
	propLabel->setAnchorPoint(Vec2(0, 0));
	propLabel->setPosition(510, 170);
	addChild(propLabel);
	// 加入触摸以及监听器
	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setSwallowTouches(true);//触摸向下
	scheduleUpdate();//定时器的更新
    return true;
}

//方块的获取,格子初始化
void HelloWorld::initBoard()
{
	int k = 0;
	int rand_card[WIDTH*HEIGHT] = { 0 };
	// 先获取地图中有多少格子是绿色的
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			// 获取地图上某个图块的id值
			int id = recLayer->tileGIDAt(Vec2( x, y));
			if (id == 2)
			{
				// 如果id=2说明图块为绿色，可以使用。则计数器k+1
				k++;
			}
		}
	}

	// 对t_card中的值取随机数,与rand()函数结合使用
	srand(unsigned(std::time(0)));
	for (int i = 0; i < k / 2; i++)
	{
		rand_card[i] = rand() % 5 + 1;
		rand_card[i + k / 2] = rand_card[i];
	}
	// 将t_card数组中的顺序打乱
	for (int i = 0; i < k; i++)
	{
		int rand_k = rand() % k;
		int t = rand_card[i];
		rand_card[i] = rand_card[rand_k];
		rand_card[rand_k] = t;
	}

	k = 0;
	// 根据数组t_card和地图中的内容开始生产方块并显示
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			// 获取地图上某个图块的id值
			int id = recLayer->tileGIDAt(Vec2(x, y));
			if (id == 2)
			{
				// 如果id=2说明图块为绿色，可以使用。则创建有效方块
				card[x][y] = CardSprite::createCardSprite(rand_card[k], x, y);
				addChild(card[x][y]);
				k++;
				judge++;
				sum = judge;
				
			}
			else
			{
				// 否则生成无效方块
				card[x][y] = CardSprite::createCardSprite(0, x, y);
				addChild(card[x][y]);
			}
		}
	}
}
//触摸开始点
bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	
	// x、y 获取了用户点击在哪个方块上
	Point point = touch->getLocation();//用户点击时候
	int x = (int)point.x / SIZE;
	int y = (int)point.y / SIZE;
	//点击后x，y为指定哪个方块被点击了
	if (x < WIDTH&&y < HEIGHT)
	{//被点击的方块不是空方块
		if (card[x][y]->type != 0)
		{
			int x1 = (int)temp.x;
			int y1 = (int)temp.y;
			//temp不被标志为1，说明该方块被标指
			if (x1 != -1 && y1 != -1)
			{
				// 判断此次点击的方块与上次点击的方块是否类型相同
				if (card[x][y]->type == card[x1][y1]->type)
				{
					// 如果相同且可联通则全部消去
					if (isCanConnection(x, y, x1, y1)==true)
					{
						card[x][y]->cardDelete();
						card[x1][y1]->cardDelete();
					}
					// temp恢复不被标志
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
				// 如果temp中没有记录，就标志被用户点击过
				temp = Vec2(x, y);
				card[x][y]->card->setOpacity(180);//被用户点击过就设置该方块透明
			}
		}
	}
	return false;
}

//直线连通的判断
bool HelloWorld::noCorner(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		// 纵向直线连通
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
	// 横向直线连通
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
//一个拐点连通
bool HelloWorld::oneCorner(int x1, int y1, int x2, int y2)
{
	//x1不等于x2或者y1不等于y2
	if (!(x1 == x2) ||!( y1 == y2))
	{
		//type等于0时，该地方是空方块
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
//两个拐点连通
bool HelloWorld::twoCorner(int x1, int y1, int x2, int y2)
{
	// 先横向扫描
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
	// 再纵向扫描
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

///三种连通的条件的判断
bool HelloWorld::isCanConnection(int x1, int y1, int x2, int y2)
{
	if (x1 == x2&&y1 == y2)
		return false;
	if (noCorner(x1, y1, x2, y2))
	{//能连通，播放音效以及judege-1
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
//更新计时条
void HelloWorld::update(float dt)
{
	if (time > 0)
	{
		bar->barUpdate(time, FULLTIME);
		
		time--;
		if (judge ==sum/2&&sum!=0&&judge!=0)
		{
			//获得屏幕尺寸
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto labbewin = Label::create("You Win!", "Arial", 32);
			labbewin->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
			addChild(labbewin);
		}
	}
	else
	{//时间到
		if (!timeOut)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto labbewin = Label::create("You lose!", "Arial", 32);
			labbewin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			addChild(labbewin);
			//时间到
			timeOut = true;
			// 这里对游戏结束进行响应
			unscheduleUpdate();
		
		}
	}
	
	
}
///使用道具的函数
void HelloWorld::prop(Ref* pSender)
{
	if (propNum > 0)
	{//第一次遍历的目的是找到还存在的方块
		for (int x1 = 0; x1 < WIDTH; x1++)
		{
			for (int y1 = 0; y1 < HEIGHT; y1++)
			{
				if (card[x1][y1]->type != 0)
				{
					// 进行第二次遍历的目的是找到相同的方块以及判断是否连通
					for (int x2 = 0; x2 < WIDTH; x2++)
					{
						for (int y2 = 0; y2 < HEIGHT; y2++)
						{//找到同种方块
							if ((!(x1 == x2&&y1 == y2)) && (card[x1][y1]->type == card[x2][y2]->type))
							{
								//判断是否连通
								if (isCanConnection(x1, y1, x2, y2))
								{
									card[x1][y1]->card->setOpacity(80);//显示透明度
									card[x2][y2]->card->setOpacity(80);//显示透明
									x1 = WIDTH;x2 = WIDTH;
									y1 = HEIGHT;y2 = HEIGHT;
								}
							}
						}
					}
				}
			}
		}
		//使用完道具后，减1
		propNum--;
		//设置输出的格式
		propLabel->setString(String::createWithFormat("tools:%d", propNum)->getCString());
	}
}

//添加云层
void HelloWorld::onEnter()
{
	Layer::onEnter();
	//获取屏幕的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// 加入道具按钮
	auto toolMenuItem = MenuItemImage::create("stop1.png", "stop2.png", this,
		menu_selector(HelloWorld::prop));
	auto labeltool = Label::create("Tool", "Arial", 18);
	auto toolMenu = Menu::create(toolMenuItem, labeltool, NULL);
	toolMenu->setPosition(Vec2(visibleSize.width - visibleSize.width/7, visibleSize.height - 280));
	this->addChild(toolMenu, 20, 999);


	//初始化暂停按钮.
	auto pauseMenuItem = MenuItemImage::create("stop1.png", "stop2.png", this,
		menu_selector(HelloWorld::menuPauseCallback));
	auto labelpause = Label::create("pause","Arial",18);
	auto pauseMenu = Menu::create(pauseMenuItem,labelpause, NULL);
	pauseMenu->setPosition(Vec2(600, visibleSize.height - 28));
	this->addChild(pauseMenu, 20, 999);

};

//暂停函数的响应
void HelloWorld::menuPauseCallback(Ref* pSender)
{

	//暂停当前层中的所有node节点
	this->pause();

	for (const auto& node : this->getChildren())
	{
		node->pause();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//返回主菜单

	auto backMenuItem = MenuItemImage::create("zhu1.png", "zhu2.png", this,
		menu_selector(HelloWorld::menuBackCallback));

	//继续游戏菜单
	auto resumeMenuItem = MenuItemImage::create("jixu1.png", "jixu2.png", this,
		menu_selector(HelloWorld::menuResumeCallback));
	menu = Menu::create(backMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVertically();//菜单项垂直排列
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
///addChild(menu, 图层的层数, 标识号);
	addChild(menu, 20, 1000);

}
///返回主菜单
void HelloWorld::menuBackCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, Mymenu::createScene()));

}
//继续游戏
void HelloWorld::menuResumeCallback(Ref* pSender)
{
	//所有节点继续
	this->resume();
	for (const auto& node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);
}
