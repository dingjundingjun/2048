#ifndef _2048_GAME_SCENE_H
#define _2048_GAME_SCENE_H



#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;
using namespace CocosDenshion;
/**��Ϸ��������*/
#define GAME_AREA_ROW 4
/**��Ϸ��������*/
#define GAME_AREA_COLUMN 4
/**�ƶ�����*/
#define MOVE_LEFT 0
#define MOVE_RIGHT 1
#define MOVE_TOP 2
#define MOVE_DOWN 3

#define AREA_PX  7

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

/**���ֵ�����*/
static int NUM[2] = {2,4};
static char* gNumRes[] = {"2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png"};
/**�������ֵı���ɫ
����Ϊ2,4,8,16,32,64,128,256,512,1024,2048,4096
*/
static int gColor[][3] = {{238,231,213},{238,227,195},{246,174,115},{230,113,34},{246,121,89},{246,89,48},{238,202,106},{238,202,106},{238,202,106},{238,202,106},{238,202,106},{238,202,106}};
class TZFGGameScene : public cocos2d::CCLayer
{
public:
	bool virtual init();
	CREATE_FUNC(TZFGGameScene);
	static CCScene* scene();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void keyBackClicked();

	/**��ʼ�����в���*/
	void initLayout();
	/**��ʼ������*/
	void initBackGround();
	/**�������һ������*/
	void createSprite();
	/**��շ���*/
	void clearArea();
	/**��ʾ����*/
	void showSprite(int row,int column,int num,bool bAnimate);
	/**�ƶ�����*/
	bool move(int direct);
	/**��һ���ƶ��㷨*/
	bool moveOther(int direct);
	/**ˢ����������*/
	void updateAllArea();
	/**�ƶ�����*/
	void moveAnimation(int direct,int move[4][4]);
	/**������������*/
	double distance(CCPoint pt1,CCPoint pt2);
	/**�ж��Ƿ������Ϸ*/
	bool isGameOver();
	/**�ƶ������ص�*/
	void moveCallback();
	/**�÷ֽ����ص�*/
	void addScoreCallback();
	/**���·���*/
	void updateScoreBar();
	/**��ת����������*/
	void goToGameOverScene();
	/**��ȡ��߷���*/
	int getGameBestScore();
	/**������߷���*/
	void setGameBestScore(int score);
	/**��������*/
	void preLoadSound();
	/**���ŵ÷���Ч*/
	void playGetScoreSound();
	/**��ʾ�÷ֶ���*/
	void showAddScoreAnimation();
	/**��ʾ�ϲ�����*/
	void showAddAreaAnimation();
	/**�����Ƿ񲥷�����*/
	void setSound(int score);
	/**��ȡ�Ƿ񲥷�����*/
	int getSound();
private:
	int mGameArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	CCScale9Sprite *mBackgroundSprite;
	CCPoint mTouchDown;
	CCSprite *mGameLayer;
	/**��Ļ��С*/
	CCSize mScreenSize;
	/**��ֻ֤ˢ��һ��*/
	bool bUpdate;
	/**�����ƶ��ٶ�*/
	float mAreaMoveSpeed;
	/**��ʾ����*/
	CCLabelTTF *mScoreBar;
	/**��ʾ��߷���*/
	CCLabelTTF *mBestScoreBar;
	/**�ܷ���*/
	int mScoreTotal;
	/**���ӵķ���*/
	int mAddScore;
	/**��߷���*/
	int mBestScore;
	/**��¼�ϲ���λ��*/
	int mAddArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	/**������ʾ�÷ֶ�����*/
	CCLabelTTF *mScoreAnimation;
	int mPlaySound;

};
#endif