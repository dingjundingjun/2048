#include "GameOver.h"
#include "2048GameScene.h"

CCScene* GameOverScene::scene()
{
	CCScene* scene = CCScene::create();
	GameOverScene *layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	setTouchEnabled(true);
	setKeypadEnabled(true);
	std::srand((unsigned int)time(0));
	initLayout();
	return true;
}

void GameOverScene::initLayout()
{
	CCSize mScreenSize = CCDirector::sharedDirector()->getWinSize();
	mLayer = UILayer::create();
	this->addChild(mLayer);
	UIButton *b = UIButton::create();
	b->setTitleText("restart");
	b->setTitleFontName("Marker Felt");
	ccColor3B c0;  
	c0.r=0;  
	c0.g=0;  
	c0.b=0;
	b->setTitleColor(c0);
	b->setTitleFontSize(30);
	b->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2));
	b->addTouchEventListener(this, toucheventselector(GameOverScene::switchBtnReStart));
	mLayer->addWidget(b);
}

void GameOverScene::switchBtnReStart(CCObject* sender, TouchEventType type)
{
	CCLOG("switchBtnReStart");
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		{
			CCScene *pScene = TZFGGameScene::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		break;

	default:
		break;
	}
}

void GameOverScene::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}