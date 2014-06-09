//
//  Utility.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/24.
//
//

#include "Utility.h"
cocos2d::CCPoint Utility::calCenterPoint(cocos2d::CCPoint startPoint,cocos2d::CCPoint endPoint){
    return ccp((startPoint.x + endPoint.x)/2, (startPoint.y + endPoint.y)/2);
}