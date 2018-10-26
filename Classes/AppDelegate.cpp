#include "AppDelegate.h"
USING_NS_CC;
///应用程序的类
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("GAME", Rect(0, 0, 640, 360));
        director->setOpenGLView(glview);
    }
	//一般默认为安卓分辨率为640*360
	director->getOpenGLView()->setDesignResolutionSize(640, 360, ResolutionPolicy::FIXED_WIDTH);//FIXED_WIDTH表示屏幕固定宽度
    // turn on display FPS
    director->setDisplayStats(false);//false时，不显示帧数

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);//每秒显示的帧数

    // create a scene. it's an autorelease object

	auto scene = Mymenu::createScene();//应用程序打开时，进入的场景（Mymenu类的场景）
    // run

    director->runWithScene(scene);//导演执行运行场景

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
