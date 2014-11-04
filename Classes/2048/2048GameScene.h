#ifndef _2048_GAME_SCENE_H
#define _2048_GAME_SCENE_H
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
#define GAME_AREA_ROW 4
#define GAME_AREA_COLUMN 4

#define MOVE_LEFT 0
#define MOVE_RIGHT 1
#define MOVE_TOP 2
#define MOVE_DOWN 3

static int NUM[2] = {2,4};
static char* gNumRes[] = {"2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png"};
static int gColor[][3] = {{230,223,208},{208,201,188},{217,144,83},{230,133,82},{203,188,150},{230,223,208},{208,201,188},{217,144,83},{230,133,82},{203,188,150},{203,188,150},{230,223,208}};
class TZFGGameScene : public cocos2d::CCLayer
{
public:
	bool virtual init();
	CREATE_FUNC(TZFGGameScene);
	static CCScene* scene();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	/**��ʼ�����в���*/
	void initLayout();
	/**��ʼ������*/
	void initBackGround();
	/**�������һ������*/
	void createSprite();
	/**��շ���*/
	void clearArea();
	void showSprite(int row,int column,int num,bool bAnimate);
	/**�ƶ�����*/
	bool move(int direct);
	/**ˢ����������*/
	void updateAllArea();
	/**������������*/
	double distance(CCPoint pt1,CCPoint pt2);
	/**�ж��Ƿ������Ϸ*/
	bool isGameOver();
private:
	int mGameArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	CCScale9Sprite *mBackgroundSprite;
	CCPoint mTouchDown;
	CCSprite *mGameLayer;
};
#endif