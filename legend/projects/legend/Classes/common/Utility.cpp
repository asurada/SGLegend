//
//  Utility.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/24.
//
//

#include "Utility.h"

CCPoint Utility::calCenterPoint(cocos2d::CCPoint startPoint,cocos2d::CCPoint endPoint){
    return ccp((startPoint.x + endPoint.x)/2, (startPoint.y + endPoint.y)/2);
}

bool Utility::isCloseLoop(CCSprite * _ball, CCArray *magicSprites){
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

float Utility::calcPercentD(double_t _val ,double_t _minVal ,double_t _maxVal)
{
	double_t v  = _val - _minVal;
	double_t mv = _maxVal - _minVal;
	if( mv == 0.0f ){ return 0.0f; }	// 0除算回避
	return (float)(v * 100.0f / mv);
}

float Utility::getBarScale(float _percent,float _varImageLen,float _viewMaxLen){
    float per = _percent/100.0f;	// _percent は 100.0f が 100% の値をとるのでまず100.0fで割る
	if( per < 0.0f ){ per = 0.0f; }
	if( per > 1.0f ){ per = 1.0f; }
	if( _varImageLen <= 0.0f || per == 0.0f ){ return 0.0f; }
	float barRate = _viewMaxLen / _varImageLen;
	return barRate * per;
}