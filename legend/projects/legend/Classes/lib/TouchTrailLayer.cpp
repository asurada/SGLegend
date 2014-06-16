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
    
    blade = CCBlade::create(kFileStreak, 24, 40);
    CCLOG("touch begin");
    addChild(blade);
    
    //blade->setColor(ccc3(255,0,0));
    //blade->setOpacity(100);
    blade->setDrainInterval(1.0/40);
    _x = 250;
    _y = 250;
    point = ccp(_x, _y);
    blade->push(point);
   // _bladeSparkle->setPosition(point);
   // _bladeSparkle->resetSystem();
    schedule(schedule_selector(TouchTrailLayer::autoMove), 0.0167f);

    
}

TouchTrailLayer* TouchTrailLayer::create()
{
    TouchTrailLayer *pRet = new TouchTrailLayer();
    pRet->autorelease();
    return pRet;
}

void TouchTrailLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        blade = CCBlade::create(kFileStreak, 24, 40);
        CCLOG("touch begin");
        _map[touch] = blade;
		addChild(blade);
        
        blade->setColor(ccc3(255,0,0));
        //blade->setOpacity(100);
        blade->setDrainInterval(1.0/40);
        point = convertTouchToNodeSpace(touch);
		blade->push(point);
        _bladeSparkle->setPosition(point);
        _x = point.x;
        _y = point.y;
        _bladeSparkle->resetSystem();
        schedule(schedule_selector(TouchTrailLayer::autoMove), 0.1);
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
       // _points.push_back(point);
        point = ccpAdd(ccpMult(point, 0.5f), ccpMult(touch->getPreviousLocation(), 0.03f));
        CCLOG("touch x:%f y:%f",point.x,point.y);
		blade->push(point);
         _bladeSparkle->setPosition(point);
    }
}

void TouchTrailLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        CCLOG("touch end");
        if (_map.find(touch) == _map.end()) continue;
        
        CCBlade *blade = _map[touch];
        blade->autoCleanup();
        _map.erase(touch);
        _bladeSparkle->stopSystem();
    }
}

float alphaX = 2.3;
float alphaY = 2.3;
void TouchTrailLayer::autoMove(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    if(_x > winSize.width){
        alphaX = -( CCRANDOM_0_1()+ 5);
    }
    
    if(_x < 0){
        alphaX = CCRANDOM_0_1()+ 5;
    }
    
    if(_y >winSize.height){
        alphaY = -(CCRANDOM_0_1()+ 5);
    }
    
    if(_y < 0){
        alphaY = CCRANDOM_0_1()+ 5;
    }
    _x = _x + alphaX;
    _y = _y + alphaY;
    point = ccp(_x, _y);
    //_bladeSparkle->setPosition(point);
    blade->push(point);
}

