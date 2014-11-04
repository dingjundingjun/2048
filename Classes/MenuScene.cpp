#include "MenuScene.h"

cocos2d::CCScene* MenuScene::scene()
{
	CCScene* scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	initMenu();
    return true;
}

void MenuScene::initMenu()
{
	mMenu = CCMenu::create();
	int i = 0;
	//CCSize visibelSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize visibelSize = CCDirector::sharedDirector()->getWinSize();
	for(i = 0; i < ITEM_SIZE ;i++)
	{
	  	CCLabelTTF *labelTTF = CCLabelTTF::create();
		labelTTF->setString(gItemList[i]);
		labelTTF->setFontSize(TEXT_SIZE);
		CCMenuItemLabel *menuItemLabel = CCMenuItemLabel::create(labelTTF,this,menu_selector(MenuScene::menuItemCallBack));
		menuItemLabel->setPosition( ccp( visibelSize.width / 2, (visibelSize.height - (i + 1) * 50) ));
		mMenu->addChild(menuItemLabel,i+100);
	}
	mMenu->setPosition(ccp(0,0));
	this->addChild(mMenu);
}

void MenuScene::menuItemCallBack(CCObject *obj)
{
	CCMenuItem *item = (CCMenuItem*)obj;
	int zOrder = item->getZOrder();
	CCLOG("zOrder = %d",zOrder);
	if(zOrder == 100)
	{
	    
	}

}