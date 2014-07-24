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
