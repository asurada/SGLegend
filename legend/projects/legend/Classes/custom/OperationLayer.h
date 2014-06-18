//
//  OperationLayer.h
//  legend
//
//  Created by 厳 巍 on 2014/05/21.
//
//

#ifndef __legend__OperationLayer__
#define __legend__OperationLayer__
#include "cocos2d.h"
#include "ShapeConst.h"
#include "AnalysisHexagon.h"
#include "OperationCallback.h"
#include "AnalysisFactory.h"
#include "TouchTrailLayer.h"
USING_NS_CC;

class OperationLayer : public cocos2d::CCLayerColor
{
public:
    int _shape;
    
    virtual bool init();
    static OperationLayer* create();
    void createBall(int shape);
    void setBallInTriangle();
    void setBallInRect();
    void setBallInRhombus();
    void setBallInPentagon();
    void setBallInHexagon();
    void clearMagicSquare();
    CC_SYNTHESIZE(OperationCallback*, operationCallBack, Delegate);
    std::vector<cocos2d::CCPoint> autoPoints;

 
    
private:
    OperationLayer();
    TouchTrailLayer *_layer;
    bool _isLoop;
    AnalysisShape _linkShape;
    bool beginFire = false;
    AnalysisFactory* factory;
    AnalysisHexagon* analysisLogic;
    
//  OperationCallback* operationCallBack;
    
    cocos2d::CCDrawNode* drawNode;
    cocos2d::CCSprite *startSprite;
    cocos2d::CCSprite *endSprite;
    cocos2d::CCSprite* pSprite_1;
    cocos2d::CCSprite* pSprite_2;
    cocos2d::CCSprite* pSprite_3;
    cocos2d::CCSprite* pSprite_4;
    cocos2d::CCSprite* pSprite_5;
    cocos2d::CCSprite* pSprite_6;
    cocos2d::CCPoint ballPos_1;
    cocos2d::CCPoint ballPos_2;
    cocos2d::CCPoint ballPos_3;
    cocos2d::CCPoint ballPos_4;
    cocos2d::CCPoint ballPos_5;
    cocos2d::CCPoint ballPos_6;
    cocos2d::CCArray * balls;
    cocos2d::CCArray *linkBalls;
    cocos2d::CCSprite *brush;
    cocos2d::CCRenderTexture *target;

    void initBall();
    int anlysisWriteHanding(CCArray *linkballs);
    bool isCloseLoop(cocos2d::CCSprite * _ball);
    bool isExistedBall(cocos2d::CCSprite * _ball);
    void autoDrawLine();
    void removeDrawNode();
    void drawCacheLine();
    void initDrawNode();
    void drawLine();
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);



   // void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
};

#endif