//
//  OperationLayer.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/21.
//
//

#include "OperationLayer.h"
#include "cocos2d.h"
#include "Utility.h"
#include "ShapeConst.h"
#include "StoneData.h"

#define SPEED_CONST 0.01f

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//デバイスがiOSの時
#else
//デバイスがAndroidの時
#endif

USING_NS_CC;


enum DrawShape{
   ENUM_SHARP_TRIANGLE,
   ENUM_SHARP_RECT    ,
   ENUM_SHARP_RHOMBUS ,
   ENUM_SHARP_PENTAGON,
   ENUM_SHARP_HEXAGON ,
   ENUM_SHARP_STAR,
};

OperationLayer::OperationLayer()
{
    
    magicSprites = CCArray::create();
    magicSprites->retain();
    factory = new AnalysisFactory();
    magicMarks = new CCArray();
    magicMarks->retain();
    brush = CCSprite::create("largeBrush.png");
    brush->retain();
}

OperationLayer::~OperationLayer(){
    
}

OperationLayer* OperationLayer::create()
{

    OperationLayer *pRet = new OperationLayer();
    pRet->autorelease();
    return pRet;
}

bool OperationLayer::init()
{
    bool bRet = false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCDirector * pDirector = cocos2d::CCDirector::sharedDirector();
    //CCLOG("width=%f,height=%f",s.width,s.height);
    _touchTrailLayer = TouchTrailLayer::create();
    _touchTrailLayer->setDelegate(this);
    marklayer = CCLayer::create();
    marklayer->setContentSize(CCSize(pDirector->getWinSize().width,pDirector->getWinSize().height/2));
    marklayer->setAnchorPoint(CCPointMake(0.5,0.5));
    marklayer->setPosition(ccp(0,0));
    if(!CCLayerColor::initWithColor(ccc4(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height/2))
    {
        return false;
    }
    setTouchEnabled(true);
    bRet = true;
    this->addChild(_touchTrailLayer,2);
    this->addChild(marklayer,1);
    //#define TRIANGLE 3
    //#define RECT     4
    //#define RHOMBUS  5
    //#define PENTAGON 6
    //#define HEXAGON  7
    analysisLogic = this->createBall(HEXAGON);
    CCArray* array = CCArray::create();
    array->addObject(StoneData::create("bll_01.png"));
    array->addObject(StoneData::create("bll_02.png"));
    array->addObject(StoneData::create("bll_03.png"));
    array->addObject(StoneData::create("bll_04.png"));
    array->addObject(StoneData::create("bll_05.png"));
    array->addObject(StoneData::create("bll_06.png"));
    analysisLogic->init(this,array);
    return bRet;
}


void OperationLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{

    CCSetIterator it;
    CCTouch* touch;
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        if(magicSprites != NULL && this->magicSprites->count()>0){
            magicSprites->removeAllObjects();
        }
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
}

void OperationLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it;
	for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        CCTouch* touch = (CCTouch*)(*it);
        if(!touch)
            break;
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
}

void OperationLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;

    }
}

AnalysisLogic* OperationLayer::createBall(int shape){
    _shape = shape;
    switch (shape) {
        case 1:
            return NULL;
        case 2:
            return NULL;
        case TRIANGLE:
            return new AnalysisTriangle();
        case RECT:
            return new AnalysisRect();
        case RHOMBUS:
            return new AnalysisRhombus();
        case PENTAGON:
            return new AnalysisPentagon();
        case HEXAGON:
            return new AnalysisHexagon();
        default:
            return NULL;
    }
}






CCSprite* OperationLayer::isHit(cocos2d::CCPoint point){
    CCObject *obj=NULL;
    CCARRAY_FOREACH(analysisLogic->getContainer(),obj){
        CCSprite *spirit = (CCSprite *)obj;
        //CCLOG("x=%f,y=%f",point.x,point.y);
        if(spirit->boundingBox().containsPoint(point)){
            return spirit;
        }
    }
    return NULL;
}

//==========================TouchTrailCallback====================================
void OperationLayer::touchBegin_TouchTrail(cocos2d::CCPoint point){
    //CCLOG("touchBegin_TouchTrail");
    magicSprites->removeAllObjects();
    CCSprite *spirit =isHit(point);
    if(spirit){
        if(_touchTrailLayer->insert(spirit->getPosition())){
            magicSprites->addObject(spirit);
            brushSprite = addMark(spirit->getPosition());
            magicMarks->addObject(brushSprite);
            //魔法石毎アニメ
            //animate(spirit);
        }
    }
}

void OperationLayer::touchMove_TouchTrail(cocos2d::CCPoint point){
    //CCLOG("touchMove_TouchTrail");
    CCSprite *spirit =isHit(point);
    if(!brushSprite || !brushSprite->getParent()) return;
    adjustMark(brushSprite, brushSprite->getPosition(), point);
    if(spirit){
        if(_touchTrailLayer->insert(spirit->getPosition())){
            magicSprites->addObject(spirit);
            adjustMark(brushSprite, brushSprite->getPosition(), spirit->getPosition());
            magicMarks->addObject(brushSprite);
            brushSprite = addMark(spirit->getPosition());
        }
    }
}


void OperationLayer::touchEnd_TouchTrail(cocos2d::CCPoint point){
    //CCLOG("touchEnd_TouchTrail");
    removeAllMagicSquare();
    CCSprite *spirit =isHit(point);
    if(!spirit){
        magicMarks->removeObject(brushSprite);
    }
    //adjustMark(brushSprite, brushSprite->getPosition(), point);
    //魔方陣アニメ
    //CCFiniteTimeAction *rotate = CCRotateTo::create(2.0f, 270.f);
    //marklayer->runAction(rotate);
    _touchTrailLayer->autoDrawAfterFinger();
}


void OperationLayer::animate(CCSprite *spirit){
    CCActionInterval* scaleAction = CCScaleBy::create(.5, 2);
    //縮小のアクション
    CCActionInterval* scaleAction2 = CCScaleBy::create(.5, .5);
    //拡大->縮小の順番にアクションを並べる
    CCSequence* sequence = CCSequence::create(scaleAction, scaleAction2, NULL);
    //3回リピート
    CCRepeat* repeat = CCRepeat::create(sequence, -1);
    spirit->runAction(repeat);
}


void OperationLayer::onPop(cocos2d::CCPoint point){
    draw(point);
}

void OperationLayer::onPopLast(cocos2d::CCPoint point){
    draw(point);
    resultData = factory->analysis(_shape,magicSprites);
    CCLOG("value = %d,order = %d",resultData->getValue(),resultData->getValue());
    if(resultData->getShape() != noresult){
        operationCallBack->beginFire(resultData->getShape());
    }
    tempMagicPoints.clear();
}

void OperationLayer::onPopStop(){

}


void OperationLayer::draw(cocos2d::CCPoint point){
    tempMagicPoints.insert(tempMagicPoints.begin(),point);
    if(tempMagicPoints.size() < 2){
        brushSprite = makeBrushImage();
        magicMarks->addObject(brushSprite);
        return;
    }else if(tempMagicPoints.size() == 2){
        CCPoint diffPoint = ccpSub(tempMagicPoints[0], tempMagicPoints[1]);
        float dist = ccpDistance(tempMagicPoints[0], tempMagicPoints[1]);
        float angleRadians = atan2f(diffPoint.y, diffPoint.x);
        angleRadians = -angleRadians;
        float cocosAngle = CC_RADIANS_TO_DEGREES(angleRadians);
        brushSprite->setScaleX(dist/320);
        brushSprite->setRotation(cocosAngle);
        brushSprite->runAction(CCTintTo::create(1, 255, 0, 0));
        tempMagicPoints.pop_back();
    }
    brushSprite = makeBrushImage();
    magicMarks->addObject(brushSprite);
}

cocos2d::CCSprite* OperationLayer::makeBrushImage(){
    CCSprite *brush= CCSprite::create("brush.png");
    brush->setAnchorPoint(CCPointMake(0,0.5));//image height/2
    brush->setPosition(tempMagicPoints[0]);
    brush->setScaleX(1/320);
    fadeout(brush,2);
    marklayer->addChild(brush);
    return brush;
}


cocos2d::CCSprite* OperationLayer::addMark(CCPoint point){
    CCSprite *brush= CCSprite::create("brush.png");
    brush->setAnchorPoint(CCPointMake(0,0.5));//image height/2
    brush->setPosition(point);
    brush->setOpacity(225);
    brush->setScaleX(1/320);
    fadeout(brush,1);
    marklayer->addChild(brush);
    return brush;
}


cocos2d::CCSprite* OperationLayer::adjustMark(CCSprite* brush,CCPoint start,CCPoint end){
    float dist = ccpDistance(start, end);
    CCPoint diffPoint = ccpSub(end,start);
    float angleRadians = atan2f(diffPoint.y, diffPoint.x);
    angleRadians = -angleRadians;
    float cocosAngle = CC_RADIANS_TO_DEGREES(angleRadians);
    brush->setRotation(cocosAngle);
    brush->setScaleX(dist/320);
    return brush;
}


void OperationLayer::fadeout(CCSprite* sprite,float time)
{
    CCFadeTo *fadeOut = CCFadeTo::create(time,0);
    sprite->runAction(fadeOut);
}

void OperationLayer::removeAllMagicSquare(){
    CCObject* obj = NULL;
    CCARRAY_FOREACH(magicMarks,obj)
    {
        ((CCSprite *)obj)->removeFromParentAndCleanup(true);
    }
    magicMarks->removeAllObjects();
}



