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

	/**��ʼ�����в���*/
	void initLayout();
	/**���¿�ʼ����*/
	void switchBtnReStart(CCObject* sender, TouchEventType type);
private:
	/**�ؼ���*/
	UILayer *mLayer;
	/**���¿�ʼ��Ϸ��ť*/
	CCLabelTTF *mReStartGame;
};
#endif