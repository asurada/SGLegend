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

#ifndef __TouchTrailLayer__
#define __TouchTrailLayer__

#include "cocos2d.h"
#include "TouchTrailCallback.h"

class CCBlade;

class TouchTrailLayer : public cocos2d::CCLayer {
private:
    std::map< cocos2d::CCTouch *, CCBlade *>  _map;
    std::vector<cocos2d::CCPoint>  _points;
    cocos2d::CCParticleSystemQuad *_bladeSparkle;
    CCBlade *blade;
    cocos2d::CCPoint point;
    cocos2d::CCPoint previewsPoint;
    float _x;
    float _y;
private:
    TouchTrailLayer();
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    bool isCollide(cocos2d::CCPoint object, cocos2d::CCPoint target, float distance);
public:
    static TouchTrailLayer* create();
    CC_SYNTHESIZE(TouchTrailCallback*, touchTrailCallback, Delegate);
    void setPointLists(std::vector<cocos2d::CCPoint>  _points);
    void insert(cocos2d::CCPoint point);
    void autoDraw();
    void autoDrawPoints();
    void autoDrawAfterFinger();
    void bladeCleanup();
    void drawRound(cocos2d::CCPoint center);
    
   
};

#endif
