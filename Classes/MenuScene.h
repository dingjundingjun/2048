#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
#define ITEM_SIZE 4
#define TEXT_SIZE 35
static const char* gItemList[ITEM_SIZE] = {"test1","test2","test3","test4"};
class MenuScene : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(MenuScene);
	virtual bool init();
	static cocos2d::CCScene* scene();

	void initMenu();
	void menuItemCallBack(CCObject *obj);
private:
	CCMenu *mMenu;
};

#endif