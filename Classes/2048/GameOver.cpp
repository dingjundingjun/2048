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

	UIButton *btnRestart = UIButton::create();
	btnRestart->setTouchEnabled(true);
	btnRestart->loadTextures("2048/restar.png", "2048/restar_press.png","");  
	btnRestart->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 + 50));
	btnRestart->addTouchEventListener(this, toucheventselector(GameOverScene::switchBtn));
	btnRestart->setTag(BTN_RESTART);
	mLayer->addWidget(btnRestart);

	UIButton *btnExit = UIButton::create();
	btnExit->setTouchEnabled(true);
	btnExit->loadTextures("2048/exit.png", "2048/exit_press.png","");  
	btnExit->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2 - 50));
	btnExit->addTouchEventListener(this, toucheventselector(GameOverScene::switchBtn));
	btnExit->setTag(BTN_EXIT);
	mLayer->addWidget(btnExit);

	this->addChild(mLayer,1);
}

void GameOverScene::switchBtn(CCObject* sender, TouchEventType type)
{
	CCLOG("switchBtnReStart");
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		{
			UIButton *btn = (UIButton*)sender;
			int tag = btn->getTag();
			if(tag == BTN_RESTART)
			{
				CCScene *pScene = TZFGGameScene::scene();
				CCDirector::sharedDirector()->replaceScene(pScene);
			}
			else if(tag == BTN_EXIT)
			{
				CCDirector::sharedDirector()->end();
			}
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