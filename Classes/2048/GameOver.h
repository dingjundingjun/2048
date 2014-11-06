#ifndef GAME_OVER
#define GAME_OVER
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class GameOverScene : public cocos2d::CCLayer
{
public:
	bool virtual init();
	CREATE_FUNC(GameOverScene);
	static CCScene* scene();

	/**初始化所有布局*/
	void initLayout();
	/**重新开始监听*/
	void switchBtnReStart(CCObject* sender, TouchEventType type);
private:
	/**控件层*/
	UILayer *mLayer;
	/**重新开始游戏按钮*/
	CCLabelTTF *mReStartGame;
};
#endif