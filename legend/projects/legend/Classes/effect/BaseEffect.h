//
//  BaseEffect.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__BaseEffect__
#define __legend__BaseEffect__

#include "cocos2d.h"

class BaseEffect : public cocos2d::CCSprite{
    public:
        void explode();
        void fadeout();
        void rotation();
        void fadein();
};

#endif /* defined(__legend__BaseEffect__) */
