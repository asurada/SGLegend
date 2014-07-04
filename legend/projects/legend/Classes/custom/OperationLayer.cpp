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
    
    balls = CCArray::create();
    balls->retain();
    linkBalls = CCArray::create();
    linkBalls->retain();
    factory = new AnalysisFactory();
    analysisLogic = new AnalysisHexagon();
    brush = CCSprite::create("largeBrush.png");
    brush->retain();
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
    _layer = TouchTrailLayer::create();
    if(!CCLayerColor::initWithColor(ccc4(241, 196, 15, 0),pDirector->getWinSize().width,pDirector->getWinSize().height/2))
    {
        return false;
    }
    setTouchEnabled(true);
    bRet = true;
    
    target = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    target->retain();
    target->setPosition(ccp(s.width / 2, s.height / 2));
    this->addChild(target);
    this->initDrawNode();
    this->addChild(_layer,1);
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
        if(linkBalls != NULL && this->linkBalls->count()>0){
            linkBalls->removeAllObjects();
        }
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        CCObject *obj=NULL;
        CCARRAY_FOREACH(balls,obj){
            CCSprite * spirit = (CCSprite *)obj;
            if(spirit->boundingBox().containsPoint(location)){
                linkBalls->addObject(spirit);
                if(startSprite == NULL){
                    startSprite = spirit;
                }
                
            }
        }
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
        CCObject *ball = NULL;
        

        CCARRAY_FOREACH(balls,ball){
            CCSprite * spirit = static_cast<CCSprite *>(ball);
            if(spirit!= NULL && spirit->boundingBox().containsPoint(location)){
                
               // this->fire();
                
                if(this->isExistedBall(spirit)){
                    startSprite = spirit;
                }else{
                    linkBalls->addObject(spirit);
                    if(startSprite == NULL){
                        startSprite = spirit;
                    }else{
                        endSprite = spirit;
                        this->drawLine();
                        startSprite = spirit;
                        endSprite = NULL;
                    }
                }
                _isLoop = this->isCloseLoop(spirit);
                
            }
        }
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
        
        _linkShape = factory->analysis(_shape,linkBalls);
        CCLOG("shape = %d",_linkShape);
        if(_linkShape != noresult){
            beginFire = true;
        }
        this->autoDrawLine();
    }
    //_layer->initAutoMove();
    
    //drawNode->setRotation(3.14);
    //this->removeDrawNode();
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
    
    balls->removeAllObjects();
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
        
        balls->addObject(pSprite_1);
        balls->addObject(pSprite_2);
        balls->addObject(pSprite_3);
    }
    
    if(_shape >= RECT || _shape >= RHOMBUS){
        
        pSprite_4 = CCSprite::create("bll_04.png");
        pSprite_4->setTag(ENUM_PST_4);
        pSprite_4->setPosition(ballPos_4);
        this->addChild(pSprite_4);
        balls->addObject(pSprite_4);
    }
    
    if(_shape >= PENTAGON){
        pSprite_5 = CCSprite::create("bll_05.png");
        pSprite_5->setTag(ENUM_PST_5);
        pSprite_5->setPosition(ballPos_5);
        this->addChild(pSprite_5);
         balls->addObject(pSprite_5);
    }
    
    if(_shape >= HEXAGON){
        pSprite_6 = CCSprite::create("bll_06.png");
        pSprite_6->setTag(ENUM_PST_6);
        pSprite_6->setPosition(ballPos_6);
        this->addChild(pSprite_6);
        balls->addObject(pSprite_6);
    }
    balls->retain();
        
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
    
    
    x1  = width  * 3.0 / 4.0;
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


bool OperationLayer::isExistedBall(cocos2d::CCSprite * _ball){
    if(linkBalls->count() == 0){
        return false;
    }
    CCSprite *lastBall = (CCSprite *)linkBalls->objectAtIndex(linkBalls->count()-1);
    if(lastBall == _ball){
        return true;
    }else{
        return false;
    }
    
}

bool OperationLayer::isCloseLoop(CCSprite * _ball){
    if(linkBalls->count() < 3){
        return false;
    }
    for (int index =0; index<linkBalls->count()-1; index++) {
        CCSprite * spirit = (CCSprite *)linkBalls->objectAtIndex(index);
        if(spirit == _ball){
            return true;
        }
    }
    return false;
}



void OperationLayer::autoDrawLine(){
    std::vector<cocos2d::CCPoint> tempPoints;
    if(linkBalls->count()>0){
        for(int i=0; i < linkBalls->count(); i++)
        {
            CCSprite *sprite = (CCSprite *)linkBalls->objectAtIndex(i);
            tempPoints.push_back(sprite->getPosition());
        }
    }
    if(tempPoints.size()>0){
        autoPoints.push_back(tempPoints[0]);
       // _layer->insertPoint(tempPoints[0]);
    }
    for(int i=0; i < tempPoints.size()-1; i++)
    {
        CCPoint start = tempPoints[i];
        CCPoint end = tempPoints[i+1];
        CCPoint center = Utility::calCenterPoint(start,end);
        autoPoints.push_back(center);
        autoPoints.push_back(end);
       // _layer->insertPoint(center);
       // _layer->insertPoint(end);
        
    }
   // _layer->initAutoMove();
  // schedule(schedule_selector(OperationLayer::drawCacheLine), SPEED_CONST);
    
}

void OperationLayer::initDrawNode(){
    if(drawNode == NULL || drawNode->getParent() == NULL){
        drawNode = CCDrawNode::create();
        drawNode->retain();
        drawNode->setPosition(ccp(0, 0));
        drawNode->setTag(1);
        this->addChild(drawNode,2);
    }
  
}

void OperationLayer::removeDrawNode(){
    startSprite = NULL;
    endSprite = NULL;
    //drawNode->removeFromParentAndCleanup(true);
}

void OperationLayer::drawLine(){
    
    this->initDrawNode();
    drawNode->drawSegment(startSprite->getPosition(),                    // 起点
                          endSprite->getPosition(),                      // 終点
                          3,                            // 太さ
                          ccc4FFromccc3B(ccRED)         // 色
                          );
}


void OperationLayer::drawCacheLine(){
    
    if(autoPoints.size() >1){
        CCPoint start = autoPoints[0];
        CCPoint end = autoPoints[1];
        
        target->begin();
        float distance = ccpDistance(start, end);
            
        for (int i = 0; i < distance; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;
            brush->setPosition(
                                ccp(start.x + (difx * delta), start.y + (dify * delta)));
                
                
                
                //brush->setOpacity(0.5);
            brush->visit();
        }
        target->end();
//        drawNode->drawSegment(start,                    // 起点
//                              end,                      // 終点
//                              10,                            // 太さ
//                              ccc4FFromccc3B(ccYELLOW)          // 色
//                              );
        autoPoints.erase(autoPoints.begin());
    }else{
        if(beginFire){
           if(operationCallBack != NULL){
               brush->cocos2d::CCNode::removeAllChildrenWithCleanup(true);
               operationCallBack->beginFire(_linkShape);
           
           }
        }else{
           // clearMagicSquare();
        }
        beginFire = false;
    }

}


void OperationLayer::clearMagicSquare(){
    startSprite = NULL;
    endSprite = NULL;
    drawNode->removeFromParentAndCleanup(true);
}

