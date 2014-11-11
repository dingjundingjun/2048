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
/**游戏方块行数*/
#define GAME_AREA_ROW 4
/**游戏方块列数*/
#define GAME_AREA_COLUMN 4
/**移动方向*/
#define MOVE_LEFT 0
#define MOVE_RIGHT 1
#define MOVE_TOP 2
#define MOVE_DOWN 3

#define AREA_PX  7

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

/**出现的数字*/
static int NUM[2] = {2,4};
static char* gNumRes[] = {"2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png","2048/num_8.png","2048/num_16.png","2048/num_32.png","2048/num_2.png","2048/num_4.png"};
/**各种数字的背景色
依次为2,4,8,16,32,64,128,256,512,1024,2048,4096
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

	/**初始化所有布局*/
	void initLayout();
	/**初始化背景*/
	void initBackGround();
	/**随机生成一个方块*/
	void createSprite();
	/**清空方块*/
	void clearArea();
	/**显示方块*/
	void showSprite(int row,int column,int num,bool bAnimate);
	/**移动方块*/
	bool move(int direct);
	/**另一种移动算法*/
	bool moveOther(int direct);
	/**刷新整个区域*/
	void updateAllArea();
	/**移动计算*/
	void moveAnimation(int direct,int move[4][4]);
	/**计算两点间距离*/
	double distance(CCPoint pt1,CCPoint pt2);
	/**判断是否结束游戏*/
	bool isGameOver();
	/**移动结束回调*/
	void moveCallback();
	/**得分结束回调*/
	void addScoreCallback();
	/**更新分数*/
	void updateScoreBar();
	/**跳转到结束界面*/
	void goToGameOverScene();
	/**获取最高分数*/
	int getGameBestScore();
	/**设置最高分数*/
	void setGameBestScore(int score);
	/**加载声音*/
	void preLoadSound();
	/**播放得分音效*/
	void playGetScoreSound();
	/**显示得分动画*/
	void showAddScoreAnimation();
	/**显示合并动画*/
	void showAddAreaAnimation();
	/**保存是否播放声音*/
	void setSound(int score);
	/**获取是否播放声音*/
	int getSound();
private:
	int mGameArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	CCScale9Sprite *mBackgroundSprite;
	CCPoint mTouchDown;
	CCSprite *mGameLayer;
	/**屏幕大小*/
	CCSize mScreenSize;
	/**保证只刷新一次*/
	bool bUpdate;
	/**方块移动速度*/
	float mAreaMoveSpeed;
	/**显示分数*/
	CCLabelTTF *mScoreBar;
	/**显示最高分数*/
	CCLabelTTF *mBestScoreBar;
	/**总分数*/
	int mScoreTotal;
	/**增加的分数*/
	int mAddScore;
	/**最高分数*/
	int mBestScore;
	/**记录合并的位置*/
	int mAddArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	/**用来显示得分动画的*/
	CCLabelTTF *mScoreAnimation;
	int mPlaySound;

};
#endif