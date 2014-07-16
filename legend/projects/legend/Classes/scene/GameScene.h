//
//  GameScene.h
//  legend
//
//  Created by 厳 巍 on 2014/05/17.
//
//

#ifndef __legend__GameScene__
#define __legend__GameScene__

#include "OperationCallback.h"
#include "OperationLayer.h"
#include "cocos2d.h"
#include "Box2D.h"

class GameScene : public cocos2d::CCLayer,OperationCallback
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    GameScene();
    ~GameScene();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void startFireAnm(cocos2d::CCPoint &pos,const char * image,const char * plist,const char * imgSplit,int count);
    void cleanupSprite(cocos2d::CCSprite* inSprite);
    void addRectangleBetweenPointsToBody(b2Body *body, CCPoint start, CCPoint end);
    
    void attack();
    void monsterAttack();
    void explode();
 
    void update(float dt);
    
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
        
    virtual void beginFire(AnalysisShape shape);
    virtual void endFire(AnalysisShape shape);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
    
private:
    b2World* world;
    cocos2d::CCPoint previousLocation;
	b2Body* currentPlatformBody;
    cocos2d::CCPoint ballPos_1;
    cocos2d::CCPoint ballPos_2;
    cocos2d::CCPoint ballPos_3;
    cocos2d::CCPoint ballPos_4;
    cocos2d::CCPoint ballPos_5;
    cocos2d::CCPoint ballPos_6;
    cocos2d::CCPoint center;
    cocos2d::CCPoint monster;
    cocos2d::CCSprite *startSprite;
    cocos2d::CCSprite *endSprite;
    cocos2d::CCSprite *bullet;
    cocos2d::CCSprite* pSprite_1;
    cocos2d::CCSprite* pSprite_2;
    cocos2d::CCSprite* pSprite_3;
    cocos2d::CCSprite* pSprite_4;
    cocos2d::CCSprite* pSprite_5;
    cocos2d::CCSprite* pSprite_6;
    cocos2d::CCSprite* pSprite_round;
    cocos2d::CCSprite* pSprite_char;
    cocos2d::CCSprite* pSprite_monster;
    cocos2d::CCSprite* pSprite_bg_1;
    cocos2d::CCSprite* pSprite_bg_2;
    cocos2d::CCArray *ballArray;
    cocos2d::CCArray *touchBallArray;
    std::vector<cocos2d::CCPoint> autoPoints;
    cocos2d::CCPoint startPoint;
    cocos2d::CCPoint endPoint;
    OperationLayer *operationlayer;
    void initPhysics();
    cocos2d::CCSprite* animationSprite;

//    cocos2d::CCDrawNode* drawNode;
//    cocos2d::CCPoint calCenterPoint(cocos2d::CCPoint startPoint,cocos2d::CCPoint endPoint);
//    void autoDrawLine();
//    void drawCacheLine();
};
#endif /* defined(__legend__GameScene__) */
