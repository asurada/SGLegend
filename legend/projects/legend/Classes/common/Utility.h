//
//  Utility.h
//  legend
//
//  Created by 厳 巍 on 2014/05/24.
//
//

#ifndef __legend__Utility__
#define __legend__Utility__
#include "cocos2d.h"
USING_NS_CC;

class Utility{
public:
    static CCPoint calCenterPoint(cocos2d::CCPoint startPoint,cocos2d::CCPoint endPoint);
    static bool isCloseLoop(CCSprite * _ball, CCArray *magicSprites);
    static float calcPercentD(double_t _val ,double_t _minVal ,double_t _maxVal);
    static float getBarScale(float _percent,float _varImageLen,float _viewMaxLen);
};
#endif /* defined(__legend__Utility__) */
