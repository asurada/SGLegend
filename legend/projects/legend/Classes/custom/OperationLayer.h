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
#include "AnalysisTriangle.h"
#include "AnalysisRhombus.h"
#include "AnalysisRect.h"
#include "AnalysisPentagon.h"

#include "OperationCallback.h"
#include "AnalysisFactory.h"
#include "TouchTrailLayer.h"
#include "TouchTrailCallback.h"


USING_NS_CC;

class OperationLayer : public cocos2d::CCLayerColor,TouchTrailCallback
{
public:
    int _shape;
    virtual bool init();
    static OperationLayer* create();
    AnalysisLogic* createBall(int shape);
    TouchTrailLayer *_touchTrailLayer;
    CC_SYNTHESIZE(OperationCallback*, operationCallBack, Delegate);
    std::vector<cocos2d::CCPoint> tempMagicPoints;
    CCArray *magicMarks;
    CCArray *magicSprites;
    cocos2d::CCSprite* brushSprite;
    cocos2d::CCSprite* makeBrushImage();
    void fadeout(CCSprite* sprite,float time);
    void draw(cocos2d::CCPoint point);
    void removeAllMagicSquare();
    
private:
    OperationLayer();
    ~OperationLayer();
    ResultData *resultData;
    AnalysisFactory* factory;
    AnalysisLogic* analysisLogic;
    
    cocos2d::CCSprite *brush;
    CCLayer * marklayer;
    CCSprite* isHit(cocos2d::CCPoint point);
    cocos2d::CCSprite* addMark(CCPoint point);
    cocos2d::CCSprite* adjustMark(CCSprite* brush,CCPoint start,CCPoint end);
    void animate(CCSprite *spirit);
    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchBegin_TouchTrail(cocos2d::CCPoint point);
    void touchMove_TouchTrail(cocos2d::CCPoint point);
    void touchEnd_TouchTrail(cocos2d::CCPoint point);
    void onPop(cocos2d::CCPoint point);
    void onPopLast(cocos2d::CCPoint point);
    void onPopStop();
};

#endif