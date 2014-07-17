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



#define SPEED_CONST 0.01f

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//デバイスがiOSの時
#else
//デバイスがAndroidの時
#endif

USING_NS_CC;


enum Position{
    ENUM_PST_1=1,
    ENUM_PST_2=2,
    ENUM_PST_3=3,
    ENUM_PST_4=4,
    ENUM_PST_5=5,
    ENUM_PST_6=6,
};

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
    
    spritesContainer = CCArray::create();
    spritesContainer->retain();
    magicSprites = CCArray::create();
    magicSprites->retain();
    factory = new AnalysisFactory();
    analysisLogic = new AnalysisHexagon();
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
    CCLOG("width=%f,height=%f",s.width,s.height);
    _touchTrailLayer = TouchTrailLayer::create();
    _touchTrailLayer->setDelegate(this);
    marklayer = CCLayer::create();


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
    this->createBall(HEXAGON);
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



void OperationLayer::createBall(int shape){
    _shape = shape;
    switch (shape) {
        case 1:
            break;
        case 2:
            break;
        case TRIANGLE:
            setBallInTriangle();
            break;
        case RECT:
            setBallInRect();
            break;
        case RHOMBUS:
            setBallInRhombus();
            break;
        case PENTAGON:
            setBallInPentagon();
            break;
        case HEXAGON:
            setBallInHexagon();
            break;
        default:
            break;
    }
    this->initBall();
}



void OperationLayer::initBall(){
    
    spritesContainer->removeAllObjects();
    if(_shape >= TRIANGLE){
        pSprite_1 = CCSprite::create("bll_01.png");
        pSprite_1->setPosition(ballPos_1);
        pSprite_1->setTag(ENUM_PST_1);
        this->addChild(pSprite_1);
        
        pSprite_2 = CCSprite::create("bll_02.png");
        pSprite_2->setTag(ENUM_PST_2);
        pSprite_2->setPosition(ballPos_2);
        this->addChild(pSprite_2);
        
        pSprite_3 = CCSprite::create("bll_03.png");
        pSprite_3->setTag(ENUM_PST_3);
        pSprite_3->setPosition(ballPos_3);
        this->addChild(pSprite_3);
        
        spritesContainer->addObject(pSprite_1);
        spritesContainer->addObject(pSprite_2);
        spritesContainer->addObject(pSprite_3);
    }
    
    if(_shape >= RECT || _shape >= RHOMBUS){
        
        pSprite_4 = CCSprite::create("bll_04.png");
        pSprite_4->setTag(ENUM_PST_4);
        pSprite_4->setPosition(ballPos_4);
        this->addChild(pSprite_4);
        spritesContainer->addObject(pSprite_4);
    }
    
    if(_shape >= PENTAGON){
        pSprite_5 = CCSprite::create("bll_05.png");
        pSprite_5->setTag(ENUM_PST_5);
        pSprite_5->setPosition(ballPos_5);
        this->addChild(pSprite_5);
        spritesContainer->addObject(pSprite_5);
    }
    
    if(_shape >= HEXAGON){
        pSprite_6 = CCSprite::create("bll_06.png");
        pSprite_6->setTag(ENUM_PST_6);
        pSprite_6->setPosition(ballPos_6);
        this->addChild(pSprite_6);
        spritesContainer->addObject(pSprite_6);
    }
    spritesContainer->retain();
        
}


void OperationLayer::setBallInTriangle(){
    CCSize visibleSize = this->getContentSize();
    float width =visibleSize.width;
    float height =visibleSize.height;
    
    float x1,x2,x3,y1,y2,y3;
                                                 
    x1 = width / 2.0;
    y1 = height *4.0/5.0;
    y2 = height /4;
    y3 = height /4;
    
    x2 = width / 2.0 - (y1-y2)/tan(60.0*M_PI/180.0);
    x3 = width / 2.0 + (y1-y2)/tan(60.0*M_PI/180.0);
   
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
}




void OperationLayer::setBallInRect(){
    
    CCSize visibleSize = this->getContentSize();
    float width =visibleSize.width;
    float height =visibleSize.height;
    float x1,x2,x3,x4,y1,y2,y3,y4;
    
    
    x1  = width * 3.0 / 4.0;
    x2 = x1;
    y1 = height * 3.0 / 4.0;
    y4 = y1;
    y2 = height * 1.0 / 4.0;
    y3 = y2;
    x3 = width  * 1.0 / 4.0;
    x4 = x3;

    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);

}



void OperationLayer::setBallInRhombus(){
    CCSize visibleSize = this->getContentSize();
    float width =visibleSize.width;
    float height =visibleSize.height;
    float x1,x2,x3,x4,y1,y2,y3,y4;
    x1 = width  * 1.0 / 2.0;
    x3 = x1;
    y1 = height * 4.0 / 5.0;
    y3 = height * 1.0 / 5.0;
    y2 = height * 1.0 / 2.0;
    y4 = y2;
    x2 = width  * 4.0 / 5.0;
    x4 = width  * 1.0 / 5.0;
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);


}


void OperationLayer::setBallInPentagon(){
    CCSize visibleSize = this->getContentSize();
    float width = visibleSize.width;
    float height = visibleSize.height;
    float x1,x2,x3,x4,x5,y1,y2,y3,y4,y5;
    float centerX,centerY;
    float distance;
    
    centerX = width / 2.0;
    centerY = height / 2.0;
    
    x1 = width  * 1.0 / 2.0;
    y1 = height * 6.0 / 7.0;
    distance = y1 - centerY;
    x2 = centerX + cos(18.0*M_PI/180.0)*(distance);
    y2 = centerY + sin(18.0*M_PI/180.0)*(distance);
    
    x3 = centerX + cos(54.0*M_PI/180.0)*(distance);
    y3 = centerY - sin(54.0*M_PI/180.0)*(distance);
    
    x4 = centerX - (x3 - centerX);
    y4 = y3;
    
    x5 = centerX -(x2 - centerX);
    y5 = y2;
    
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);
    ballPos_5 = ccp(x5, y5);

}


void OperationLayer::setBallInHexagon(){
    CCSize visibleSize = this->getContentSize();
    float width = visibleSize.width;
    float height = visibleSize.height;
    float x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6;
    float centerX,centerY;
    float distance;
    
    centerX = width / 2.0;
    centerY = height / 2.0;
    x1 = width  * 1.0 / 2.0;
    y1 = height * 7.0 / 8.0;
    
    distance = y1 - centerY;
    
    x2 = centerX + distance * sin(60 * M_PI /180);
    y2 = centerY + distance * cos(60 * M_PI /180);
    
    x3 = centerX + distance * sin(60 * M_PI /180);
    y3 = centerY - distance * cos(60 * M_PI /180);
    
  
    x4 = width  * 1.0 / 2.0;
    y4 = height * 1.0 / 8.0;
    
    x5 = centerX -(x3 - centerX);
    y5 = y3;
    
    x6 = centerX -(x2 - centerX);
    y6 = y2;
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);
    ballPos_5 = ccp(x5, y5);
    ballPos_6 = ccp(x6, y6);


}



bool OperationLayer::isCloseLoop(CCSprite * _ball){
    if(magicSprites->count() < 3){
        return false;
    }
    for (int index =0; index<magicSprites->count()-1; index++) {
        CCSprite * spirit = (CCSprite *)magicSprites->objectAtIndex(index);
        if(spirit == _ball){
            return true;
        }
    }
    return false;
}


CCSprite* OperationLayer::isHit(cocos2d::CCPoint point){
    CCObject *obj=NULL;
    CCARRAY_FOREACH(spritesContainer,obj){
        CCSprite *spirit = (CCSprite *)obj;
        if(spirit->boundingBox().containsPoint(point)){
            return spirit;
        }
    }
    return NULL;
}

//==========================TouchTrailCallback====================================
void OperationLayer::touchBegin_TouchTrail(cocos2d::CCPoint point){
    CCLOG("touchBegin_TouchTrail");
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
    CCLOG("touchMove_TouchTrail");
    CCSprite *spirit =isHit(point);
    adjustMark(brushSprite, brushSprite->getPosition(), point);
    if(spirit){
        if(_touchTrailLayer->insert(spirit->getPosition())){
            magicSprites->addObject(spirit);
            adjustMark(brushSprite, brushSprite->getPosition(), point);
            magicMarks->addObject(brushSprite);
            brushSprite = addMark(spirit->getPosition());
        }
    }
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



void OperationLayer::touchEnd_TouchTrail(cocos2d::CCPoint point){
    CCLOG("touchEnd_TouchTrail");
    removeAllMagicSquare();
    //魔方陣アニメ
    //CCFiniteTimeAction *rotate = CCRotateTo::create(2.0f, 270.f);
    //marklayer->runAction(rotate);
    _touchTrailLayer->autoDrawAfterFinger();
    
    
}

void OperationLayer::onPop(cocos2d::CCPoint point){
    draw(point);
}

void OperationLayer::onPopLast(cocos2d::CCPoint point){
    draw(point);
    _linkShape = factory->analysis(_shape,magicSprites);
    CCLOG("shape = %d",_linkShape);
    if(_linkShape != noresult){
        operationCallBack->beginFire(_linkShape);
    }
    tempMagicPoints.clear();
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
    marklayer->addChild(brush);
    return brush;
}

cocos2d::CCSprite* OperationLayer::addMark(CCPoint point){
    CCSprite *brush= CCSprite::create("brush.png");
    brush->setAnchorPoint(CCPointMake(0,0.5));//image height/2
    brush->setPosition(point);
    brush->setOpacity(150);
    brush->setScaleX(1/320);
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



void OperationLayer::removeAllMagicSquare(){
    CCObject* obj = NULL;
    CCARRAY_FOREACH(magicMarks,obj)
    {
        ((CCSprite *)obj)->removeFromParentAndCleanup(true);
    }
    magicMarks->removeAllObjects();
}



