#include "2048GameScene.h"
#include "GameOver.h"
CCScene* TZFGGameScene::scene()
{
	CCScene* scene = CCScene::create();
	TZFGGameScene *layer = TZFGGameScene::create();
	scene->addChild(layer);
	return scene;
}

bool TZFGGameScene::init()
{
	setTouchEnabled(true);
	setKeypadEnabled(true);
	preLoadSound();
	std::srand((unsigned int)time(0));
	mAreaMoveSpeed = 0.15;
	mScoreTotal = 0;
	mAddScore = 0;
	mPlaySound = getSound();
	mBestScore = getGameBestScore();
	CCLOG("game besssssssss = %d",mBestScore);
	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	initLayout();
	return true;
}

void TZFGGameScene::initLayout()
{
	initBackGround();
}

void TZFGGameScene::initBackGround()
{
	mGameLayer = CCSprite::create();

	CCSize parentSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* tmp = CCSprite::create("2048/main_layout_background.png");
	CCSize size = tmp->getContentSize();
	CCRect fullRect = CCRectMake(0,0, size.width, size.height);
	CCRect insetRect = CCRectMake(0,0,size.width, size.height);
	tmp->release();
	mBackgroundSprite = CCScale9Sprite::create("2048/main_layout_background.png",fullRect,insetRect);
	mBackgroundSprite->setPreferredSize(CCSizeMake(700,700));
	mBackgroundSprite->setPosition(parentSize.width/2,parentSize.height/2 -5);
	this->addChild(mBackgroundSprite);
	mGameLayer->setContentSize(CCSizeMake(700,700));
	mGameLayer->setPosition(ccp(parentSize.width/2,parentSize.height/2 + 65));
	this->addChild(mGameLayer);

	CCSprite *logoSprite = CCSprite::create("2048/logo.png");
	logoSprite->setAnchorPoint(ccp(0.5,0.5));
	logoSprite->setPosition(ccp(logoSprite->getContentSize().width / 2 + 30,parentSize.height - logoSprite->getContentSize().height/2 - 55));
	this->addChild(logoSprite);

	CCSprite *scoreSprite = CCSprite::create("2048/fenshu.png");
	scoreSprite->setAnchorPoint(ccp(0.5,0.5));
	scoreSprite->setPosition(ccp(scoreSprite->getContentSize().width / 2 + 150,parentSize.height - scoreSprite->getContentSize().height/2 - 45));
	this->addChild(scoreSprite);

	CCSprite *bestSprite = CCSprite::create("2048/lishi.png");
	bestSprite->setAnchorPoint(ccp(0.5,0.5));
	bestSprite->setPosition(ccp(bestSprite->getContentSize().width / 2 + 410,parentSize.height - bestSprite->getContentSize().height/2 - 45));
	this->addChild(bestSprite);

	mScoreBar = CCLabelTTF::create("0","Marker Felt",45);
	ccColor3B c0;  
	c0.r=109;  
	c0.g=70;  
	c0.b=37;
	mScoreBar->setColor(c0);
	mScoreBar->setPosition(ccp(scoreSprite->getPosition().x,parentSize.height - 120));
	this->addChild(mScoreBar);

	mScoreAnimation = CCLabelTTF::create("0","Marker Felt",60);
	mScoreAnimation->setColor(c0);
	mScoreAnimation->setPosition(ccp(scoreSprite->getPosition().x,parentSize.height - 120));
	mScoreAnimation->setVisible(false);
	this->addChild(mScoreAnimation);

	mBestScoreBar = CCLabelTTF::create("0","Marker Felt",40);
	mBestScoreBar->setColor(c0);
	mBestScoreBar->setPosition(ccp(bestSprite->getPosition().x,parentSize.height - 120));
	char str[10];
	memset(str,0,10);
	sprintf(str,"%d",mBestScore);
	mBestScoreBar->setString(str);

	mBtnPlaySound = UIButton::create();
	UILayer *mLayer = UILayer::create();
	this->addChild(mLayer);
	mBtnPlaySound->setTouchEnabled(true);
	updateSoundBtn();
	mBtnPlaySound->setPosition(ccp(680,parentSize.height - scoreSprite->getContentSize().height/2 - 45));
	mBtnPlaySound->addTouchEventListener(this, toucheventselector(TZFGGameScene::switchSound));
	mLayer->addWidget(mBtnPlaySound);
	

	this->addChild(mBestScoreBar);
	clearArea();

	createSprite();
	createSprite();
}

void TZFGGameScene::switchSound(CCObject* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		{
			if(mPlaySound == 1)
			{
				mPlaySound = 0;
			}
			else
			{
				mPlaySound = 1;
			}
			updateSoundBtn();
		}
		break;

	default:
		break;
	}
}

void TZFGGameScene::updateSoundBtn()
{
	if(mPlaySound == 1)
	{
		mBtnPlaySound->loadTextures("2048/sound_open.png","2048/sound_open.png","");
	}
	else
	{
		mBtnPlaySound->loadTextures("2048/sound_close.png","2048/sound_close.png","");
	}
	setSound(mPlaySound);
}

void TZFGGameScene::addScoreCallback()
{
		//mScoreAnimation
}

void TZFGGameScene::showAddScoreAnimation()
{
	char str[10];
	memset(str,0,10);
	sprintf(str,"+%d",mAddScore);
	mScoreAnimation->setString(str);

	mScoreAnimation->setPosition(ccp(mScoreBar->getPosition().x,mScoreBar->getPosition().y - 60));
	mScoreAnimation->setVisible(true);
	CCActionInterval *move = CCMoveBy::create(0.5,ccp(0,100));
	CCActionInterval *alpha = CCFadeOut::create(0.5);
	CCFiniteTimeAction *ccFiniteAction = CCSpawn::create(move,alpha,NULL);
	mScoreAnimation->runAction(ccFiniteAction);
}

void TZFGGameScene::createSprite()
{
	int numIndex = std::rand()%2;
	int index_row = std::rand()%4;
	int index_column = std::rand()%4;

	while (true)
	{
		if (mGameArea[index_row][index_column] == 0)
		{
			mGameArea[index_row][index_column] = NUM[numIndex];
			break;
		}
		index_row = std::rand()%4;
		index_column = std::rand()%4;
	}

	/*for(int n = 0;n<4;n++)
		for (int m = 0;m < 4;m++)
		{
			showSprite(n,m,0);
		}*/

	showSprite(index_row,index_column,numIndex,true);
	if(isGameOver())
	{
		if(mScoreTotal > mBestScore)
		{
			setGameBestScore(mScoreTotal);
		}
		goToGameOverScene();
	}
}

void TZFGGameScene::goToGameOverScene()
{
	CCScene *pScene = GameOverScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void TZFGGameScene::showSprite(int row,int column,int numIndex,bool bAnimate)
{
	CCSprite *sprite = CCSprite::create();

	sprite->setContentSize(ccp(160,160));
	sprite->setAnchorPoint(ccp(0.5,0.5));
	sprite->setPosition(ccp(20 + column*sprite->getContentSize().width + column*AREA_PX + sprite->getContentSize().width/2,mBackgroundSprite->getContentSize().height - 83 - (row+1)*sprite->getContentSize().height - (row+1)*AREA_PX +  sprite->getContentSize().height/2));
	
	ccColor4B color;
	color.r = gColor[numIndex][0];
	color.g = gColor[numIndex][1];
	color.b = gColor[numIndex][2];
	color.a = 255;

	CCLayerColor *layerColorBG =CCLayerColor::create(ccColor4B(color));
	layerColorBG->setContentSize(ccp(160,160));
	//layerColorBG->setPosition(Point(CardSpriteX,CardSpriteY));  

	sprite->addChild(layerColorBG);
	

	CCLabelTTF *labelTTF = CCLabelTTF::create();
	int text = 2;
	if(numIndex < 2)
	{
		ccColor3B color3b;
		color3b.r = 144;
		color3b.g = 138;
		color3b.b = 112;

		labelTTF->setColor(color3b);
	}
	else
	{
		ccColor3B color3b;
		color3b.r = 246;
		color3b.g = 235;
		color3b.b = 195;

		labelTTF->setColor(color3b);
	}
	for(int i=0;i<numIndex;i++)
	{
		text *=2;
	}
	labelTTF->setTag(text);
	char str[10];
	sprintf(str,"%d",text);
	labelTTF->setString(str);
	labelTTF->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
	labelTTF->setFontSize(70);
	
	sprite->addChild(labelTTF);
	if (bAnimate)
	{
		sprite->setScale(0.3);
		CCActionInterval *scale = CCScaleTo::create(0.3,1);
		CCFadeIn *fadeIn = CCFadeIn::create(0.3);
		CCFiniteTimeAction *ccFiniteAction = CCSpawn::create(scale,fadeIn,NULL);
		sprite->runAction(ccFiniteAction);
	}
	mGameLayer->addChild(sprite,1,row*10 + column);
}

void TZFGGameScene::clearArea()
{
	int i = 0;
	int j = 0;
	for(i = 0;i < GAME_AREA_ROW ; i++)
	{
		for (j = 0; j < GAME_AREA_COLUMN;j++)
		{
			mGameArea[i][j] = 0;
		}
	}
}

bool TZFGGameScene::move(int direct)
{
	int i = 0;
	int j = 0;
	int tempArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	for (i = 0;i < GAME_AREA_ROW;i++)
	{
		for (j = 0;j < GAME_AREA_COLUMN;j++)
		{
			tempArea[i][j] = mGameArea[i][j];
		}
	}
	switch(direct)
	{
	case MOVE_LEFT:
		{
			int n = 0;
			for(i = 0;i < GAME_AREA_ROW ; i++)
			{
				int tempColumn[GAME_AREA_COLUMN];
				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
				}
				n = 0;
				//去0
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
				}
				//合并
				for(n = 0;n < GAME_AREA_COLUMN; n++)
				{
					if(n < GAME_AREA_COLUMN - 1 && tempColumn[n] == tempColumn[n+1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						tempColumn[n+1] = 0;
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}

				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
				}
				n = 0;
				//去0
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}
			}
			break;
		}

	case MOVE_RIGHT:
		{
			//移动
			int n = 0;
			for(i = 0;i < GAME_AREA_ROW ; i++)
			{
				int tempColumn[GAME_AREA_COLUMN];
				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
				}
				n = GAME_AREA_COLUMN - 1;
				//去0
				for (j = GAME_AREA_COLUMN - 1; j >= 0 ;j--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
				}
				//合并
				for(n = GAME_AREA_COLUMN - 1;n >=0; n--)
				{
					if(n > 0 && tempColumn[n] == tempColumn[n-1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						tempColumn[n-1] = 0;
					}
				}

				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}

				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
				}
				n = GAME_AREA_COLUMN - 1;
				//去0
				for (j = GAME_AREA_COLUMN - 1; j >= 0 ;j--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}
			}
			break;
		}
	case MOVE_TOP:
		{
			int n = 0;
			for(j = 0;j < GAME_AREA_COLUMN ; j++)
			{
				int tempColumn[GAME_AREA_ROW];
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
				}
				n = 0;
				//去0
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
				}
				//合并
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					if(n < GAME_AREA_ROW - 1 && tempColumn[n] == tempColumn[n+1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						tempColumn[n+1] = 0;
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}

				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
				}
				n = 0;
				//去0
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}
			}
			break;
		}
	case MOVE_DOWN:

		{

			int n = 0;
			for(j = 0;j < GAME_AREA_COLUMN ; j++)
			{
				int tempColumn[GAME_AREA_ROW];
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
				}
				n = GAME_AREA_ROW - 1;
				//去0
				for (i = GAME_AREA_ROW - 1; i >= 0 ;i--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
				}
				//合并
				for(n = GAME_AREA_ROW - 1;n >= 0; n--)
				{
					if(n > 0 && tempColumn[n] == tempColumn[n-1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						tempColumn[n-1] = 0;
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}

				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
				}
				n = GAME_AREA_ROW - 1;
				//去0
				for (i = GAME_AREA_ROW - 1; i >= 0 ;i--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}
			}
			break;
		}
	}
	bool bChange = false;
	for (i = 0;i < GAME_AREA_ROW;i++)
	{
		for (j = 0;j < GAME_AREA_COLUMN;j++)
		{
			if(tempArea[i][j] != mGameArea[i][j])
			{
				bChange = true;
				break;
			}
		}
	}
	if(!bChange)
		return false;
	updateAllArea();
	return true;
}

void TZFGGameScene::updateScoreBar()
{
	mScoreTotal += mAddScore;
	char str[10];
	memset(str,0,10);
	sprintf(str,"%d",mScoreTotal);
	mScoreBar->setString(str);
	showAddScoreAnimation();
	mAddScore = 0;
}

void TZFGGameScene::moveCallback()
{
	if(bUpdate)
	{
		CCLOG("moveCallback");
		updateAllArea();
		showAddAreaAnimation();
		bUpdate = false;
		createSprite();
		if(mAddScore != 0)
		{
			updateScoreBar();
			playGetScoreSound();
		}
	}
}

void TZFGGameScene::showAddAreaAnimation()
{
	for(int i = 0 ; i < GAME_AREA_ROW;i++)
	{
		for(int j = 0 ; j < GAME_AREA_COLUMN;j++)
		{
			if(mAddArea[i][j] == 1)
			{
				CCLOG("sprite i = %d,j=%d 11111111111111111",i,j);
				CCSprite *sprite = (CCSprite*)mGameLayer->getChildByTag(i*10 + j);
				if(sprite != NULL)
				{
					sprite->setScale(1.2);
					CCLOG("sprite i = %d,j=%d",i,j);
					CCActionInterval *jump = CCScaleTo::create(0.3,1);
					//CCFiniteTimeAction *ccFiniteAction = CCSequence::create(jump,CCCallFunc::create(this,callfunc_selector(TZFGGameScene::moveCallback)),NULL);
					sprite->runAction(jump);
				}
			}
		}
	}
}

void TZFGGameScene::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void TZFGGameScene::moveAnimation(int direct,int move[4][4])
{
	bUpdate = true;
	switch(direct)
	{
		case MOVE_LEFT:
			{
				for(int i = 0 ; i < GAME_AREA_ROW;i++)
			{
				int moveLength = 0;
				for(int j = 0 ; j < GAME_AREA_COLUMN;j++)
				{
					if(move[i][j] == 1)
					{
						moveLength++;
					}
					CCSprite *sprite = (CCSprite*)mGameLayer->getChildByTag(i*10 + j);
					if(sprite != NULL)
					{
						float m;
						m = -1 * moveLength * (sprite->getContentSize().width + AREA_PX);
						CCLOG("sprite i = %d,j=%d,m = %f",i,j,m);
						CCActionInterval *move = CCMoveBy::create(mAreaMoveSpeed,ccp(m,0));
						CCFiniteTimeAction *ccFiniteAction = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(TZFGGameScene::moveCallback)),NULL);
						sprite->runAction(ccFiniteAction);
					}
				}
			}
			break;
				break;
			}
		case MOVE_RIGHT:
		{
			for(int i = 0 ; i < GAME_AREA_ROW;i++)
			{
				int moveLength = 0;
				for(int j = GAME_AREA_COLUMN - 1 ; j >= 0;j--)
				{
					if(move[i][j] == 1)
					{
						moveLength++;
					}
					CCSprite *sprite = (CCSprite*)mGameLayer->getChildByTag(i*10 + j);
					if(sprite != NULL)
					{
						float m;
						m = moveLength * (sprite->getContentSize().width + AREA_PX);
						CCLOG("sprite i = %d,j=%d,m = %f",i,j,m);
						CCActionInterval *move = CCMoveBy::create(mAreaMoveSpeed,ccp(m,0));
						CCFiniteTimeAction *ccFiniteAction = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(TZFGGameScene::moveCallback)),NULL);
						sprite->runAction(ccFiniteAction);
					}
				}
			}
			break;
		}
		case MOVE_DOWN:
			{
				for(int j = 0 ; j < GAME_AREA_ROW;j++)
			{
				int moveLength = 0;
				for(int i = GAME_AREA_COLUMN - 1 ; i >= 0 ;i--)
				{
					CCLOG("sprite i = %d,j=%d,move = %d",i,j,move[i][j]);
					if(move[i][j] == 1)
					{
						moveLength++;
					}
					CCSprite *sprite = (CCSprite*)mGameLayer->getChildByTag(i*10 + j);
					if(sprite != NULL)
					{
						float m;
						m = -1 * moveLength * (sprite->getContentSize().height + AREA_PX);
						CCLOG("sprite i = %d,j=%d,m = %d",i,j,moveLength);
						CCActionInterval *move = CCMoveBy::create(mAreaMoveSpeed,ccp(0,m));
						CCFiniteTimeAction *ccFiniteAction = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(TZFGGameScene::moveCallback)),NULL);
						sprite->runAction(ccFiniteAction);
					}
				}
			}
				break;
			}
		case MOVE_TOP:
		{
				for(int j = 0 ; j < GAME_AREA_ROW;j++)
			{
				int moveLength = 0;
				for(int i = 0 ; i < GAME_AREA_COLUMN;i++)
				{
					CCLOG("sprite i = %d,j=%d,move = %d",i,j,move[i][j]);
					if(move[i][j] == 1)
					{
						moveLength++;
					}
					CCSprite *sprite = (CCSprite*)mGameLayer->getChildByTag(i*10 + j);
					if(sprite != NULL)
					{
						float m;
						m = moveLength * (sprite->getContentSize().height + AREA_PX);
						CCLOG("sprite i = %d,j=%d,m = %d",i,j,moveLength);
						CCActionInterval *move = CCMoveBy::create(mAreaMoveSpeed,ccp(0,m));
						CCFiniteTimeAction *ccFiniteAction = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(TZFGGameScene::moveCallback)),NULL);
						sprite->runAction(ccFiniteAction);
					}
				}
			}
			break;
		}
	}
	
}

bool TZFGGameScene::moveOther(int direct)
{
	int i = 0;
	int j = 0;
	int tempArea[GAME_AREA_ROW][GAME_AREA_COLUMN];
	int tempMove[GAME_AREA_ROW][GAME_AREA_COLUMN];
	int tempAdd[GAME_AREA_COLUMN];
	for (i = 0;i < GAME_AREA_ROW;i++)
	{
		for (j = 0;j < GAME_AREA_COLUMN;j++)
		{
			tempArea[i][j] = mGameArea[i][j];
		}
	}
	switch(direct)
	{
	case MOVE_LEFT:
		{
			int n = 0;
			for(i = 0;i < GAME_AREA_ROW ; i++)
			{
				int tempColumn[GAME_AREA_COLUMN];
				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
					tempMove[i][n] = 0;
					mAddArea[i][n] = 0;
				}
				n = 0;
				

				//去0
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
					else
					{
						tempMove[i][j] = 1;
					}
				}
				//合并
				for(n = 0;n < GAME_AREA_COLUMN; n++)
				{
					if(n < GAME_AREA_COLUMN - 1 && tempColumn[n] == tempColumn[n+1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						tempColumn[n+1] = 0;
						mAddScore += tempColumn[n];
						mAddArea[i][n] = 1;
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}

				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
					tempAdd[n] = 0;
				}
				n = 0;
				//去0
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n] = mGameArea[i][j];
						tempAdd[n] = mAddArea[i][j];
						n++;
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
					mAddArea[i][j] = tempAdd[j];
				}
			}
			break;
		}

	case MOVE_RIGHT:
		{
			//移动
			int n = 0;
			for(i = 0;i < GAME_AREA_ROW ; i++)
			{
				int tempColumn[GAME_AREA_COLUMN];
				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
					tempMove[i][n] = 0;
					mAddArea[i][n] = 0;
				}
				n = GAME_AREA_COLUMN - 1;
				//去0
				for (j = GAME_AREA_COLUMN - 1; j >= 0 ;j--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
					else
					{
						tempMove[i][j] = 1;
					}
				}
				//合并
				for(n = GAME_AREA_COLUMN - 1;n >=0; n--)
				{
					if(n > 0 && tempColumn[n] == tempColumn[n-1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						mAddScore += tempColumn[n];
						tempColumn[n-1] = 0;
						mAddArea[i][n] = 1;
					}
				}

				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
				}

				for(n = 0;n < GAME_AREA_COLUMN;n++)
				{
					tempColumn[n] = 0;
					tempAdd[n] = 0;
				}
				n = GAME_AREA_COLUMN - 1;
				//去0
				for (j = GAME_AREA_COLUMN - 1; j >= 0 ;j--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n] = mGameArea[i][j];
						tempAdd[n] = mAddArea[i][j];
						n--;
					}
				}
				for (j = 0; j < GAME_AREA_COLUMN ;j++)
				{
					mGameArea[i][j] = tempColumn[j];
					mAddArea[i][j] = tempAdd[j];
				}
			}
			break;
		}
	case MOVE_TOP:
		{
			int n = 0;
			for(j = 0;j < GAME_AREA_COLUMN ; j++)
			{
				int tempColumn[GAME_AREA_ROW];
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
					tempMove[n][j] = 0;
					mAddArea[n][j] = 0;
				}
				n = 0;
				//去0
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					//CCLOG("move  i = %d,j=%d,gamearea = %d",i,j,mGameArea[i][j]);
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n++] = mGameArea[i][j];
					}
					else
					{
						
						tempMove[i][j] = 1;
						//CCLOG("tempMove  i = %d,j=%d,area = %d",i,j,tempMove[i][j]);
					}
				}
				//CCLOG("tempMove  i = %d,j=%d,area = %d",i,j,tempMove[1][1]);
				//合并
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					if(n < GAME_AREA_ROW - 1 && tempColumn[n] == tempColumn[n+1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						mAddScore += tempColumn[n];
						tempColumn[n+1] = 0;
						mAddArea[n][j] = 1;
						CCLOG("22222222222222222 n = %d,j=%d",n,j);
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}

				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
					tempAdd[n] = 0;
				}
				n = 0;
				//去0
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n] = mGameArea[i][j];
						tempAdd[n] = mAddArea[i][j];
						n++;
						//CCLOG("3333333333 n = %d,j=%d,p=%d",n,j,mAddArea[i][j]);
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
					mAddArea[i][j] = tempAdd[i];
					CCLOG("3333333333 i = %d,j=%d,p=%d",i,j,mAddArea[i][j]);
				}
			}
			break;
		}
	case MOVE_DOWN:

		{
			int n = 0;
			for(j = 0;j < GAME_AREA_COLUMN ; j++)
			{
				int tempColumn[GAME_AREA_ROW];
				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
					tempMove[n][j] = 0;
					mAddArea[n][j] = 0;
				}
				n = GAME_AREA_ROW - 1;
				//去0
				for (i = GAME_AREA_ROW - 1; i >= 0 ;i--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n--] = mGameArea[i][j];
					}
					else
					{
						tempMove[i][j] = 1;
					}
				}
				CCLOG("tempMove  i = %d,j=%d,area = %d",i,j,tempMove[1][1]);
				//合并
				for(n = GAME_AREA_ROW - 1;n >= 0; n--)
				{
					if(n > 0 && tempColumn[n] == tempColumn[n-1] && tempColumn[n] != 0)
					{
						tempColumn[n] = 2*tempColumn[n];
						mAddScore += tempColumn[n];
						tempColumn[n-1] = 0;
						mAddArea[n][j] = 1;
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
				}

				for(n = 0;n < GAME_AREA_ROW;n++)
				{
					tempColumn[n] = 0;
					tempAdd[n] = 0;
				}
				n = GAME_AREA_ROW - 1;
				//去0
				for (i = GAME_AREA_ROW - 1; i >= 0 ;i--)
				{
					if(mGameArea[i][j] != 0)
					{
						tempColumn[n] = mGameArea[i][j];
						tempAdd[n] = mAddArea[i][j];
						n--;
					}
				}
				for (i = 0; i < GAME_AREA_ROW ;i++)
				{
					mGameArea[i][j] = tempColumn[i];
					mAddArea[i][j] = tempAdd[i];
				}
			}
			break;
		}
	}
	bool bChange = false;
	for (i = 0;i < GAME_AREA_ROW;i++)
	{
		for (j = 0;j < GAME_AREA_COLUMN;j++)
		{
			if(tempArea[i][j] != mGameArea[i][j])
			{
				bChange = true;
				break;
			}
		}
	}
	if(!bChange)
		return false;
	moveAnimation(direct,tempMove);
	//updateAllArea();
	return true;
}

void TZFGGameScene::updateAllArea()
{
	//先清除
	mGameLayer->removeAllChildren();

	for (int i = 0;i < GAME_AREA_ROW;i++)
	{
		for (int j = 0;j < GAME_AREA_COLUMN;j++)
		{
			int index = mGameArea[i][j];
			int indexNum = 0;
			while(index > 2)
			{
				index = index / 2;
				indexNum++;
			}
			if(mGameArea[i][j] != 0)
			{
				showSprite(i,j,indexNum,false);
			}
		}
	}
}

void TZFGGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch *touch = (CCTouch*)(*it);
	mTouchDown = touch->getLocation();
}

void TZFGGameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	 
}

void TZFGGameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation(); 

		double d = distance(mTouchDown,touchLocation);  
		CCLOG("两点的距离 ：%f",d );  
		//如果触摸距离超过20判断手势方向  
		if (d>50) 
		{  
			bool bMove = false;
			if (mTouchDown.x-touchLocation.x<0&&mTouchDown.x-touchLocation.x<mTouchDown.y-touchLocation.y&&touchLocation.x-mTouchDown.x>mTouchDown.y-touchLocation.y) {  
				CCLOG("right");  
				bMove = moveOther(MOVE_RIGHT);
			}  
			if (mTouchDown.x-touchLocation.x>0&&mTouchDown.x-touchLocation.x>mTouchDown.y-touchLocation.y&&touchLocation.x-mTouchDown.x<mTouchDown.y-touchLocation.y) {  
				CCLOG("left");  
				bMove = moveOther(MOVE_LEFT);
			}  

			if (mTouchDown.y-touchLocation.y<0&&mTouchDown.y-touchLocation.y<mTouchDown.x-touchLocation.x&&touchLocation.y-mTouchDown.y>mTouchDown.x-touchLocation.x) {  
				CCLOG("up");  
				bMove = moveOther(MOVE_TOP);

			}  
			if (mTouchDown.y-touchLocation.y>0&&mTouchDown.y-touchLocation.y>mTouchDown.x-touchLocation.x&&touchLocation.y-mTouchDown.y<mTouchDown.x-touchLocation.x) {   
				CCLOG("down"); 
				bMove = moveOther(MOVE_DOWN);
			}  
			/*
			if(bMove)
				createSprite();
				*/
		}  
}


double TZFGGameScene::distance(CCPoint pt1,CCPoint pt2)
{
    double d;
    d=sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y));
    return d;
}

bool TZFGGameScene::isGameOver()
{
	bool bFull = true;
	for(int i = 0;i < GAME_AREA_ROW;i++)
		for (int j = 0;j < GAME_AREA_COLUMN;j++)
		{
			int p = mGameArea[i][j];
			if(mGameArea[i][j] == 0)
			{
				return false;
			}
			CCLOG("is GameOver i = %d,j = %d",i,j);
			if(i - 1 >= 0 && mGameArea[i-1][j] == p)
			{
				return false;
			}
			if(i + 1 < GAME_AREA_COLUMN && mGameArea[i + 1][j] == p)
			{
				return false;
			}
			if(j - 1 >= 0 && mGameArea[i][j - 1] == p)
			{
				return false;
			}
			if(j + 1 < GAME_AREA_COLUMN && mGameArea[i][j + 1] == p)
			{
				return false;
			}
		}
	return bFull;
}

int TZFGGameScene::getGameBestScore()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/jy/jytzfegame/GameDataControl", "getBestScore", "()I")) {
		jclass header_class = t.env->FindClass("com/jy/jytzfegame/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/jy/jytzfegame/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"getBestScore","()I");
		int score = t.env->CallIntMethod(header_object,getBestScoreID);
		CCLOG("get best score = %d",score);
		return score;
	}
#endif
	return 1111;
}


void TZFGGameScene::setGameBestScore(int score)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/jy/jytzfegame/GameDataControl", "setBestScore", "(I)I")) {
		jclass header_class = t.env->FindClass("com/jy/jytzfegame/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/jy/jytzfegame/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"setBestScore","(I)I");
		t.env->CallIntMethod(header_object,getBestScoreID,score);
		CCLOG("get best score = %d",score);
	}
#endif
}

int TZFGGameScene::getSound()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/jy/jytzfegame/GameDataControl", "getSound", "()I")) {
		jclass header_class = t.env->FindClass("com/jy/jytzfegame/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/jy/jytzfegame/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"getSound","()I");
		int score = t.env->CallIntMethod(header_object,getBestScoreID);
		CCLOG("get best score = %d",score);
		return score;
	}
#endif
	return 1;
}


void TZFGGameScene::setSound(int score)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/jy/jytzfegame/GameDataControl", "setSound", "(I)I")) {
		jclass header_class = t.env->FindClass("com/jy/jytzfegame/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/jy/jytzfegame/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"setSound","(I)I");
		t.env->CallIntMethod(header_object,getBestScoreID,score);
		CCLOG("get best score = %d",score);
	}
#endif
}

void TZFGGameScene::showAD()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "showBannerStatic", "()V")) {
		jclass header_class = t.env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "showBannerStatic", "()V");
		CCLOG("get best init_id1111111111111111111111111");
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		CCLOG("get best score2222222222222222222222222");
	}
#endif
}

void TZFGGameScene::preLoadSound()
{
	SimpleAudioEngine::sharedEngine()->preloadEffect("score.mp3");
}

void TZFGGameScene::playGetScoreSound()
{
	if(mPlaySound == 1)
	{
		CCLOG("play getScoreSound");
		SimpleAudioEngine::sharedEngine()->playEffect("score.mp3");
	}
}



