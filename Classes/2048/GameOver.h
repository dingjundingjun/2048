#ifndef GAME_OVER
#define GAME_OVER
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

#define BTN_RESTART 0
#define BTN_EXIT 1
class GameOverScene : public cocos2d::CCLayer
{
public:
	bool virtual init();
	CREATE_FUNC(GameOverScene);
	static CCScene* scene();
	virtual void keyBackClicked();

	/**��ʼ�����в���*/
	void initLayout();
	/**���¿�ʼ����*/
	void switchBtn(CCObject* sender, TouchEventType type);
private:
	/**�ؼ���*/
	UILayer *mLayer;
	/**���¿�ʼ��Ϸ��ť*/
	CCLabelTTF *mReStartGame;
};
#endif