/*
 * CCBlade
 *
 * Copyright (c) 2011 - Ngo Duc Hiep
 * Copyright (c) 2012 - YangLe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "TouchTrailLayer.h"
#include "CCBlade.h"
#define kFileStreak "Deco_shine_v1.png"

USING_NS_CC;

TouchTrailLayer::TouchTrailLayer()
{
    setTouchEnabled(true);
    _bladeSparkle = CCParticleSystemQuad::create("blade_sparkle.plist");
    _bladeSparkle->stopSystem();
    this->addChild(_bladeSparkle);
//    
    blade = CCBlade::create(kFileStreak, 24, 40);
    blade->setDrainInterval(1.0/40);
    addChild(blade);
//
////     blade->setColor(ccc3(255,0,0));
////     blade->setOpacity(100);
   
////     _x = 350;
////     _y = 350;
////     point = ccp(_x, _y);
//     blade->push(point);
//    // _bladeSparkle->setPosition(point);
//     _bladeSparkle->resetSystem();
    

    
}

TouchTrailLayer* TouchTrailLayer::create()
{
    TouchTrailLayer *pRet = new TouchTrailLayer();
    pRet->autorelease();
    return pRet;
}

void TouchTrailLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    _points.clear();
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        CCBlade *blade = CCBlade::create(kFileStreak, 24, 40);
        CCLOG("touch begin");
        _map[touch] = blade;
		addChild(blade);
        
        blade->setColor(ccc3(255,0,0));
        //blade->setOpacity(100);
        blade->setDrainInterval(1.0/40);
        point = convertTouchToNodeSpace(touch);
		blade->push(point);
        //previewsPoint = point;
        insertPoint(point);
        _bladeSparkle->setPosition(point);
        _bladeSparkle->resetSystem();
	}
}

void TouchTrailLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        CCLOG("touch move");
        if (_map.find(touch) == _map.end()) continue;
        CCBlade *blade = _map[touch];
        CCPoint point = convertTouchToNodeSpace(touch);
        insertPoint(point);
        //previewsPoint = point;
        point = ccpAdd(ccpMult(point, 0.5f), ccpMult(touch->getPreviousLocation(), 0.5f));
        CCLOG("touch x:%f y:%f",point.x,point.y);
		blade->push(point);
         _bladeSparkle->setPosition(point);
    }
}

void TouchTrailLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
//    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
//        CCTouch *touch = (CCTouch *)*it;
//        CCLOG("touch end");
//        if (_map.find(touch) == _map.end()) continue;
//        CCBlade *blade = _map[touch];
//        blade->autoCleanup();
//        _map.erase(touch);
 //       _bladeSparkle->stopSystem();
////
//    }
    autoDrawAfterFinger();
    //initAutoMove();
}

float alphaX = 5;
float alphaY = 5;
void TouchTrailLayer::autoDraw(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    if(_x > winSize.width){
        alphaX = -( CCRANDOM_0_1()+ 10);
    }
    
    if(_x < 0){
        alphaX = CCRANDOM_0_1()+ 10;
    }
    
    if(_y >winSize.height){
        alphaY = -(CCRANDOM_0_1()+ 10);
    }
    
    if(_y < 0){
        alphaY = CCRANDOM_0_1()+ 10;
    }
    _x = _x + alphaX;
    _y = _y + alphaY;
    
    point = ccp(_x, _y);
//    float root = 60 - pow(_y,2);
//    if(root > 0){
//        _x = sqrtf(root);
//    }else{
//        _x = -sqrtf(root);
//    }
    blade->push(point);
}


void TouchTrailLayer::drawRound(CCPoint center){
    _y = _y + alphaY;
    if(_y > 650){
        alphaY = -5;
    }
    if(_y < 50){
        alphaY = 5;
    }
    float root = pow(300,2) - pow(_y-350,2);
    if(root > 350){
        _x = sqrtf(root);
    }else{
        _x = -sqrtf(-root);
    }
    point = ccp(_x+350, _y);
    blade->push(point);
}

void TouchTrailLayer::insertPoint(cocos2d::CCPoint point){
    _points.insert(_points.begin(), point);
}

void TouchTrailLayer::autoDrawPoints(){
    CCLOG("_point.size :%d",(int)_points.size());
    if(_points.size() > 0){
        CCPoint point = _points.back();
        bool dist  = isCollide(point, ccp(0, 0), 20);
        
        blade->push(_points.back());
        _points.pop_back();
    }else{
        unschedule(schedule_selector(TouchTrailLayer::autoDrawPoints));
    }
}

void TouchTrailLayer::initAutoMove(){
    blade = CCBlade::create(kFileStreak, 24, 40);
    CCLOG("touch begin");
    addChild(blade);
    blade->setDrainInterval(1.0/40.0);
    schedule(schedule_selector(TouchTrailLayer::autoDraw), 0.012);
}


void TouchTrailLayer::autoDrawAfterFinger(){
    schedule(schedule_selector(TouchTrailLayer::autoDrawPoints), 0.0167f);
}


bool TouchTrailLayer::isCollide(cocos2d::CCPoint object, cocos2d::CCPoint target, float distance){
    float result = ccpLength(ccpSub(object,target));
    if(result <= distance){
        return true;
    }
    return false;
}


